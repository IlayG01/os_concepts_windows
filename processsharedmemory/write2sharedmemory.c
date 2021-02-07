/*****************************************************************************************************\
File Name : write2sharedmemory.c
Author    : Ilay Gilman
Purpose   : recieve file mapping handler name & write to it.
\*****************************************************************************************************/

/* Include Section ***********************************************************************************/
#include <Windows.h>
#include <stdio.h>

/* Definition Section ********************************************************************************/
#define CHAR_TO_WRITE ("SUCCESS")

int main(int argc, char *argv[])
{
	/* validating recieve data */
	if (argc != 2)
	{
		printf("PROC2 - Usage: writetosharedmemory <file_mapping_handle_name>");
		return 1;
	}

	/* getting system info */
	SYSTEM_INFO sys_info;
	GetSystemInfo(&sys_info);
	int mem_buffer_size = sys_info.dwAllocationGranularity;
	printf("PROC2 - The system buffer size is %d\n", mem_buffer_size);

	/* try to open recieved file mapping handler */
	HANDLE hMapping = OpenFileMappingA(
		FILE_MAP_WRITE, // permissions
		TRUE,			// can be passed to childs
		argv[1]);		// the handler name
	if (hMapping == NULL)
	{
		printf("PROC2 - Could not open file mapping <%s> object. errno %d\n", argv[1], GetLastError());
		return 2;
	}

	/* mapping to memory */
	LPSTR pBuf;
	pBuf = (LPSTR)MapViewOfFile(
		hMapping,
		FILE_MAP_WRITE,
		0,
		0,
		mem_buffer_size);
	if (pBuf == NULL)
	{
		printf("PROC2 - Could not map view of file to memory. errno %d\n", GetLastError());
		return 3;
	}

	/* writing to mapped ram i/o */
	for (int i = 0; i < 7; i++)
	{
		pBuf[i] = CHAR_TO_WRITE[i];
	}

	/* logging */
	printf("PROC2 - First letters changed to %s\n", CHAR_TO_WRITE);

	return 0;
}
