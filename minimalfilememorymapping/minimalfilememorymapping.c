/*****************************************************************************************************\
File Name : minimalfilememorymapping.c
Author    : Ilay Gilman
Purpose   : loading file into heap|physical ram - in minimal waste of memory.
\*****************************************************************************************************/

/* Include Section ***********************************************************************************/
#include <Windows.h>
#include <stdio.h>

/* Definition Section ********************************************************************************/
#define FILENAME ("gibrish.bin")
#define SEARCH_LETTER ('A')

/* Decleration Section *******************************************************************************/

/*****************************************************************************************************\
* Function Name                           :                 count_in_data
* Function Porpuse                        :                 counting revieved sign appearance in recieved buffer
* Function Params                         :                 LPSTR data, CHAR sign_to_count, INT data_size
* Return Values                           :                 int number_of_appearance
* Remarks                                 :                 ASCII sign only
* Authors                                 :                 Ilay Gilman
\*****************************************************************************************************/
INT count_in_data(LPSTR data, CHAR sign_to_count, INT data_size);

/* get file handle, mapping file to memory, unmapping, close file handle*/
int main()
{
	/* getting system info & available buffer size */
	SYSTEM_INFO sys_info;
	GetSystemInfo(&sys_info);
	int mem_buffer_size = sys_info.dwAllocationGranularity;
	printf("The system buffer size is %d\n", mem_buffer_size);

	/* getting file handler */
	HANDLE hFile;
	LPCSTR pFileName = FILENAME;
	hFile = CreateFileA(
		pFileName,         // file name
		GENERIC_READ,     // access type
		0,               // other processes can't share
		NULL,
		OPEN_EXISTING, // open only if file exists
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	DWORD file_size = GetFileSize(hFile, NULL);

	/* creating file mapping */
	HANDLE hMapping = CreateFileMappingA(
		hFile,             // file handle
		NULL,             // default securit
		PAGE_READONLY,   // read access
		0,              // maximum object size - high order dword
		0,             // maximum object size - low order dword
		"gibrish.bin");    // name of mapping object
	if (hMapping == NULL)
	{
		printf("Could not create file mapping object.\n");
		return 1;
	}

	/* looping through file to count */
	unsigned int file_location = 0, counter = 0;
	LPSTR pBuf;
	while (file_location <= (file_size - mem_buffer_size))
	{
		/* mapping to memory */
		pBuf = (LPSTR)MapViewOfFile(
			hMapping,
			FILE_MAP_READ,
			0,
			file_location,
			mem_buffer_size);
		if (pBuf == NULL)
		{
			printf("Could not map view of file to memory.\n");
			return 2;
		}
		/* updating counter while part of the file is mapped */
		counter += count_in_data(pBuf, SEARCH_LETTER, mem_buffer_size);
		file_location += mem_buffer_size;
		/* unmapping it */
		if (0 == UnmapViewOfFile(pBuf))
		{
			printf("Could not unmap view of file to memory.\n");
			return 3;
		}
	}

	/* taking care for the reminder of the file */
	int reminder = file_size - file_location;
	pBuf = (LPSTR)MapViewOfFile(
		hMapping,
		FILE_MAP_READ,
		0,
		file_location,
		reminder);
	if (pBuf == NULL)
	{
		printf("Could not map view of file to memory.\n");
		return 2;
	}
	/* updating counter */
	counter += count_in_data(pBuf, SEARCH_LETTER, mem_buffer_size);
	/* unmapping reminder */
	if (0 == UnmapViewOfFile(pBuf))
	{
		printf("Could not unmap view of file to memory.\n");
		return 3;
	}

	/* result printing */
	printf("The number of appearance is %d\n", counter);

	CloseHandle(hMapping);
	CloseHandle(hFile);
	return 0;
}

INT count_in_data(LPSTR data, CHAR sign_to_count, INT data_size)
{
	INT counter = 0, index = 0;
	while (*(data + index) != '\0' && index < data_size-1)
	{
		if (*(data + index) == sign_to_count)
		{
			counter++;
		}
		index++;
	}
	return counter;
}