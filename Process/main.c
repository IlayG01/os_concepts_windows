/*****************************************************************************************************\
File Name : main.c
Author    : Ilay Gilman
Purpose   : creating process
\*****************************************************************************************************/

/* Include Section ***********************************************************************************/
#include <stdio.h>
#include <Windows.h>

/* Definition Section ********************************************************************************/
#define EXE_FILENAME ("helloworld.exe")
#define PROC_ARG ("4")

int main()
{
	/* proc info init */
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	/* passed exe (bin + passed_arg) */
	CHAR exe_filename[] = EXE_FILENAME;
	CHAR process_arg[] = PROC_ARG;
	INT size = strlen(exe_filename) + strlen(process_arg) + 2;
	PCHAR param = (PCHAR)malloc(size * sizeof(CHAR));
	if (param == NULL)
	{
		printf("Couldn't allocate memory\n");
		return 1;
	}
	sprintf_s(param, size, "%s %s", exe_filename, process_arg);
	/* starting the child process. */ 
	if (! CreateProcessA(
		NULL,
		param,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi))
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return 2;
	}

	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	//free memory
	free(param);
	return 0;
}