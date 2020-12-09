/*****************************************************************************************************\
File Name : child.c
Author    : Ilay Gilman
Purpose   : recieve/creates mutex, waiting for it to be available, and prints a msg.
\*****************************************************************************************************/

/* Include Section ***********************************************************************************/
#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[])
{
    //checks for valid usage
    if (argc != 2)
    {
        printf("Incorrect number of arguments\n");
        return 1;
    }

    /* crate|recieve mutex */
    HANDLE hMutex = CreateMutexA(
        NULL,    /* default security */
        FALSE,   /* initially not owned */
        "Ilay"); /* mutex name */

    if (hMutex)
    {
        /* wait for single object */
        DWORD waitResult = WaitForSingleObject(hMutex, INFINITE);
        if (waitResult != WAIT_OBJECT_0)
        {
            // Mutex not free, do what ever you want
            printf("Mutex could not be obtained for too long\n");
        }
        else
        {
            // Mutex free
            int id = atoi(argv[1]);
            printf("[$] Hello World Process got this argument --> %d\n", id);
            Sleep(5000);
            ReleaseMutex(hMutex);
        }
        CloseHandle(hMutex);
        return 0;
    }
    else
    {
        printf("Invalid Mutex handle\n");
        return 2;
    }
}