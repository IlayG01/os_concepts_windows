/*****************************************************************************************************\
File Name : parent.c
Author    : Ilay Gilman
Purpose   : creating 2 child procs & using mutex lock in them
\*****************************************************************************************************/

/* Include Section ***********************************************************************************/
#include <stdio.h>
#include <Windows.h>

/* Definition Section ********************************************************************************/
#define EXE_FILENAME ("child.exe")
#define NUM_OF_PROCS (4)

int main()
{
    /* crate|recieve mutex */
    HANDLE hMutex = CreateMutexA(
        NULL,    /* default security */
        FALSE,   /* initially not owned */
        "Ilay"); /* mutex name */
    if (hMutex == NULL)
    {
        printf("Invalid Mutex handle\n");
        return 1;
    }
    INT size = strlen(EXE_FILENAME) + 3; /* 3(1 for space, 1 for digit, 1 for null terminate */
    PCHAR param = (PCHAR)malloc(size * sizeof(CHAR));
    if (param == NULL)
    {
        printf("Unable to alloc memory\n");
        return 2;
    }
    STARTUPINFO si;
    PROCESS_INFORMATION pi[NUM_OF_PROCS];

    for (int i = 0; i < NUM_OF_PROCS; i++)
    {
        sprintf_s(param, size, "%s %d", EXE_FILENAME, i);
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi[i], sizeof(pi[i]));
        if (NULL == CreateProcessA(
                        NULL,
                        param,
                        NULL,
                        NULL,
                        FALSE,
                        0,
                        NULL,
                        NULL,
                        &si,
                        &pi[i]))
        {
            printf("CreateProcess failed (%d).\n", GetLastError());
            return 3;
        }
    }

    // Wait until childs process exits.
    for (int i = 0; i < NUM_OF_PROCS; i++)
    {
        WaitForSingleObject(pi[i].hProcess, INFINITE);
    }

    ReleaseMutex(hMutex);

    // Close process and mutex handles.
    for (int i = 0; i < NUM_OF_PROCS; i++)
    {
        CloseHandle(pi[i].hProcess);
        CloseHandle(pi[i].hThread);
    }

    //free used memory
    free(param);

    return 0;
}