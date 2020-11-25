/*****************************************************************************************************\
File Name : main.c
Author    : Ilay Gilman
Purpose   : creating multiple threads
\*****************************************************************************************************/

/* Include Section ***********************************************************************************/
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

/* Definition Section ********************************************************************************/
# define NUM_OF_THREADS (4)

/* thread function */
DWORD WINAPI loop(LPVOID lparam) { /*LPVOID magic*/
	int serial_id = (int)lparam;
	for (int i = 1; i <= 1000; i++) {
		printf("Thread: %d, var = %d\n", serial_id, i);
	};
	/* procexp investigate */
	Sleep(50000);
	return 0;
}

int main()
{
	/* set up thread_ids and thread handlers*/
	int serial_ids[NUM_OF_THREADS];
	HANDLE handles[NUM_OF_THREADS] = { NULL };
	for (int index = 0; index < NUM_OF_THREADS; index++)
	{
		serial_ids[index] = index;
	}

	/* creating threads */
	for (int i = 0; i < NUM_OF_THREADS; i++)
	{
		LPVOID serial_id = (LPVOID)serial_ids[i];
		handles[i] = CreateThread(
					 NULL,
					 0,
					 loop,
					 serial_id,
					 0,
					 NULL);
		if (handles[i] == NULL)
		{
			return 1;
		}

	}

	/* waiting for all the threads we created */
	DWORD dwEvent =  WaitForMultipleObjects(
									NUM_OF_THREADS,
									handles,
									TRUE,
									INFINITE);

	/* closing threads handles */
	for (int i = 0; i < NUM_OF_THREADS; i++)
	{
		CloseHandle(&handles[i]);
	}

	return 0;
}