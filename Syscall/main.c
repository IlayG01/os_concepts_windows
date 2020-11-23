/*****************************************************************************************************\
File Name : main.c
Author    : Ilay Gilman
Purpose   : implement simple syscall to monitor in procmon
\*****************************************************************************************************/

/* Include Section ***********************************************************************************/
#include <Windows.h>
#include <stdio.h>

/* Definition Section ********************************************************************************/
#define BUFFER_SIZE (10)
DWORD g_BytesTransferred = 0;


VOID CALLBACK FileIOCompletionRoutine(
	__in  DWORD dwErrorCode,
	__in  DWORD dwNumberOfBytesTransfered,
	__in  LPOVERLAPPED lpOverlapped
);

VOID CALLBACK FileIOCompletionRoutine(
	__in  DWORD dwErrorCode,
	__in  DWORD dwNumberOfBytesTransfered,
	__in  LPOVERLAPPED lpOverlapped)
{
	g_BytesTransferred = dwNumberOfBytesTransfered;
}

int main(int argc, char* argv[])
{
	HANDLE hFile;
	DWORD  dwBytesRead = 0;
	char   ReadBuffer[BUFFER_SIZE] = { 0 };
	OVERLAPPED ol = { 0 };

	if (argc != 2)
	{
		printf("Usage: syscall <file_to_read>\n");
		return 1;
	}

	hFile = CreateFile(argv[1],
					   GENERIC_READ,
					   FILE_SHARE_READ,
					   NULL,
					   OPEN_EXISTING,
					   FILE_ATTRIBUTE_NORMAL,
					   NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("Unable to open file\n");
		return 2;
	}

	/* Read one character less than the buffer size to save room for the terminating NULL character. */
	if (FALSE == ReadFileEx(hFile, ReadBuffer, BUFFER_SIZE - 1, &ol, FileIOCompletionRoutine))
	{
		printf("Terminal failure: Unable to read from file.\n GetLastError=%08x\n", GetLastError());
		CloseHandle(hFile);
		return 3;
	}
	/* in order to have time to monitor in the procmon program */
	SleepEx(5000, TRUE);
	dwBytesRead = g_BytesTransferred;

	CloseHandle(hFile);
	return 0;
}