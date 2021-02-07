/*****************************************************************************************************\
File Name : processsharedmemory.c
Author    : Ilay Gilman
Purpose   : using shared memory between 2 different procs(pointing to same physical ram).
			reading from the first proc(parent), writing from the second proc(child).
			the changes effect both process.
\*****************************************************************************************************/

/* Include Section ***********************************************************************************/
#include <stdio.h>
#include <Windows.h>

/* Definition Section ********************************************************************************/
/* file mapped to shared memory */
#define FILENAME ("gibrish.bin")
/* child proc */
#define EXE_FILENAME ("write2sharedmemory.exe")
/* shared */
#define MAPPED_OBJECT_NAME ("mappedfileholder")

int main(void)
{
    /* getting system info */
    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);
    int mem_buffer_size = sys_info.dwAllocationGranularity;
    printf("PROC1 - The system buffer size is %d\n", mem_buffer_size);

    /* getting file handler */
    HANDLE hFile = CreateFileA(
        FILENAME,                     // file name
        GENERIC_READ | GENERIC_WRITE, // access type - read & write
        0,                            // other processes can't share
        NULL,
        OPEN_EXISTING, // open only if file exists
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (hFile == NULL)
    {
        printf("PROC1 - Unable to create file\n");
        return 1;
    }
    DWORD file_size = GetFileSize(hFile, NULL);

    /* creating file mapping */
    HANDLE hMapping = CreateFileMappingA(
        hFile,               // file handle
        NULL,                // default security
        PAGE_READWRITE,      // read&write access
        0,                   // maximum object size - high order dword
        0,                   // maximum object size - low order dword
        MAPPED_OBJECT_NAME); // name of mapping object
    if (hMapping == NULL)
    {
        printf("PROC1 Could not create file mapping object. %d\n", GetLastError());
        return 2;
    }

    /* mapping to memory */
    LPSTR pBuf;
    pBuf = (LPSTR)MapViewOfFile(
        hMapping,
        FILE_MAP_READ,
        0,
        0,
        mem_buffer_size);
    if (pBuf == NULL)
    {
        printf("PROC1 Could not map the view of the file to memory.\n");
        return 3;
    }

    /* logging current data in ram */
    printf("PROC1 - The first letters in the ram are %.7s\n", pBuf);
    Sleep(1000);

    /* creating proc to write to shared memory */
    /* proc init */
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    /* passed exe (bin + passed_arg) */
    CHAR exe_filename[] = EXE_FILENAME;
    CHAR process_arg[] = MAPPED_OBJECT_NAME;
    INT size = strlen(exe_filename) + strlen(process_arg) + 2;
    PCHAR param = (PCHAR)malloc(size * sizeof(CHAR));
    if (param == NULL)
    {
        printf("PROC1 Couldn't allocate memory\n");
        return 4;
    }
    sprintf_s(param, size, "%s %s", exe_filename, process_arg);
    /* starting the child process. */
    if (!CreateProcessA(
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
        printf("PROC1 CreateProcess failed (%d).\n", GetLastError());
        return 5;
    }

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);

    /* logging current data in ram */
    printf("PROC1 - The first letters in the ram are %.7s\n", pBuf);
    Sleep(1000);

    /* unmapping it - no need to hold data in the ram anymore */
    if (0 == UnmapViewOfFile(pBuf))
    {
        printf("PROC1 Could not unmap view of file to memory.\n");
        return 6;
    }

    // Close process and thread handles.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    //free memory
    free(param);

    return 0;
}
