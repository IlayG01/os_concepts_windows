/*****************************************************************************************************\
File Name : pe_iat_hooking.cpp
Author    : Ilay Gilman
Purpose   : Hooking PE Import Address Table (IAT)
\*****************************************************************************************************/

/* Include Section ***********************************************************************************/
#include <stdio.h>
#include <Windows.h>

/* Definition Section ********************************************************************************/
#define BUFFER_SIZE (36)
#define FILE_NAME ("demo.txt")
#define HACKED_MSG ("Hacked by 1l4yG")

/* Functions section *********************************************************************************/

/*****************************************************************************************************\
* Function Name                           :                 hook
* Function Porpuse                        :                 manipulate the iat (changes func_to_hook to new_func_address)
* Function Params                         :                 PCSTR func_to_hook, PCSTR dll_to_hook, DWORD new_func_address
* Return Values                           :                 0 if success, other if fail
* Remarks                                 :                 to use this function in large scale, consider
															use an enum for error codes
* Authors                                 :                 Ilay Gilman
\*****************************************************************************************************/
int hook(PCSTR func_to_hook, PCSTR dll_to_hook, DWORD new_func_address);

/*****************************************************************************************************\
* Function Name                 :         show_msg
* Function Porpuse              :         pops a msgbox
* Function Params               :         None
* Return Values                 :         None
* Remarks                       :         the function contains an inline assembly to fix the stack
										  after the hooking
* Authors                       :         Ilay Gilman
\****************************************************************************************************/
void show_msg();

/* contains the interrupted function we hooked */
DWORD saved_hooked_func_addr;

/* Main section ************************************************************************************/

int main(void)
{
	/* hooking */
	PCSTR func_to_hook = "CreateFileA";
	PCSTR dll_to_hook = "KERNEL32.dll";
	DWORD new_func_addr = (DWORD)&show_msg;
	hook(func_to_hook, dll_to_hook, new_func_addr);
	/* done hooking the IAT*/
	HANDLE hFile;
	CHAR buffer[BUFFER_SIZE];
	/* trying to open a file for reading */
	hFile = CreateFileA(FILE_NAME,
						GENERIC_READ,
						0,			   //do not share
						NULL,		   //default security
						OPEN_EXISTING, //open only if exists
						FILE_ATTRIBUTE_NORMAL,
						NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		DWORD err = GetLastError();
		printf("Unable to open file, error num - %d\n", err);
		return 1;
	}
	/* reading from file to buffer */
	if (FALSE == ReadFile(hFile, buffer, BUFFER_SIZE - 1, NULL, NULL))
	{
		DWORD err = GetLastError();
		printf("Unable to read from file, error num - %d\n", err);
		return 2;
	}
	printf("%.34s\n", buffer);
	/* close file */
	if (0 == CloseHandle(hFile))
	{
		printf("Unable to close file\n");
		return 3;
	}
	return 0;
}

int hook(PCSTR func_to_hook, PCSTR dll_to_hook, DWORD new_func_address)
{
	PIMAGE_DOS_HEADER dos_header;
	PIMAGE_NT_HEADERS nt_header;
	PIMAGE_OPTIONAL_HEADER32 optional_header;
	IMAGE_DATA_DIRECTORY import_directory;
	DWORD descriptor_start_rva;
	PIMAGE_IMPORT_DESCRIPTOR import_descriptor;
	int index;

	/* get the base address of current exe */
	DWORD base_addr = (DWORD)GetModuleHandle(NULL);
	/* get the import directory addr */
	dos_header = (PIMAGE_DOS_HEADER)(base_addr);
	if (((*dos_header).e_magic) != IMAGE_DOS_SIGNATURE)
	{
		printf("Couldnt find DOS_HEADER valid signature (MZ)\n");
		return 4;
	}
	nt_header = (PIMAGE_NT_HEADERS)(base_addr + (*dos_header).e_lfanew);
	if (((*nt_header).Signature) != IMAGE_NT_SIGNATURE)
	{
		printf("Couldnt find NT_HEADER valid signature (PE)\n");
		return 5;
	}
	optional_header = &(*nt_header).OptionalHeader;
	if (((*optional_header).Magic) != 0x10B)
	{
		printf("Couldnt find Optional_Header valid 32bit Magic (0x10B)\n");
		return 6;
	}
	import_directory = (*optional_header).DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
	descriptor_start_rva = import_directory.VirtualAddress;
	import_descriptor = (PIMAGE_IMPORT_DESCRIPTOR)((base_addr + descriptor_start_rva));

	/* searching for the DLL which includes the function were hooking */
	index = 0;
	char *dll_name;
	while ((*import_descriptor).Characteristics != 0)
	{
		dll_name = (char *)(base_addr + (*import_descriptor).Name);
		if (!strcmp(dll_to_hook, dll_name))
		{
			break;
		}
		index++;
	}
	/* in case we didnt find the dll in the import directory(null terminated array) */
	if (import_descriptor[index].Characteristics == 0)
	{
		printf("DLL wasnt found\n");
		return 7;
	}
	/* searching the function we want to hook inside the dll */
	PIMAGE_THUNK_DATA thunk_int; // import names table
	PIMAGE_THUNK_DATA thunk_iat; // import address table
	PIMAGE_IMPORT_BY_NAME name_data;

	thunk_int = (PIMAGE_THUNK_DATA)(base_addr + import_descriptor[index].OriginalFirstThunk);
	thunk_iat = (PIMAGE_THUNK_DATA)(base_addr + import_descriptor[index].FirstThunk);
	if ((thunk_iat == NULL) or (thunk_int == NULL))
	{
		printf("Unable to reach the import names table\n");
		return 8;
	}

	/* looping the import names table */
	while (((*thunk_int).u1.AddressOfData != 0) && (!((*thunk_iat).u1.Ordinal) && IMAGE_ORDINAL_FLAG))
	{
		name_data = (PIMAGE_IMPORT_BY_NAME)(base_addr + (*thunk_int).u1.AddressOfData);
		if (!strcmp(func_to_hook, (char *)(*name_data).Name))
		{
			break;
		}
		thunk_iat++;
		thunk_int++;
	}

	/* FINALLY - the hook */
	DWORD p_old = NULL;	 // variable to pass the old protection of memory after the hook
	DWORD p_demo = NULL; // demo variable
	saved_hooked_func_addr = (*thunk_iat).u1.Function;
	VirtualProtect((LPVOID) & ((*thunk_iat).u1.Function), sizeof(DWORD), PAGE_READWRITE, &p_old);
	(*thunk_iat).u1.Function = new_func_address;
	VirtualProtect((LPVOID) & ((*thunk_iat).u1.Function), sizeof(DWORD), p_old, &p_demo);

	return 0;
}

void show_msg()
{
	MessageBoxA(0, "Hooked", HACKED_MSG, 0);
	/* this inline asm makes sure to restore stack state as MessageBoxA
		should do at the end, and jmp to ReadFileA in order to complete the running as usual (hooking purpose) */
	_asm {
		pop edi
		pop esi
		pop ebx
		add esp, 0x0
		mov esp, ebp
		pop ebp
		jmp saved_hooked_func_addr
	}
}