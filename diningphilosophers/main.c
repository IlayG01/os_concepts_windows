/*****************************************************************************************************\
File Name : main.c
Author    : Ilay Gilman
Purpose   : solving dining philosophers problem
\*****************************************************************************************************/

/* Include Section ***********************************************************************************/
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

/* Definition Section ********************************************************************************/
#define NUM_OF_THREADS (5)
#define NUM_OF_MEALS (500000)

/* all the forks/sticks on the table */
CRITICAL_SECTION firstForkLock;
CRITICAL_SECTION secondForkLock;
CRITICAL_SECTION thirdForkLock;
CRITICAL_SECTION fourthForkLock;
CRITICAL_SECTION fifthForkLock;

/* the passed data to each thread - id, left fork/stick, right fork/stick */
typedef struct PhilosopherInfo
{
	int id;
	CRITICAL_SECTION* leftFork;
	CRITICAL_SECTION* rightFork;
} PhilosopherInfo_t;

/* each thread */
DWORD WINAPI philosopher(LPVOID lpParameter)
{
	PhilosopherInfo_t* info = (PhilosopherInfo_t*)lpParameter;
	int mealsCounter = 0;
	/* LOG - printf("Philosopher num %d entered the room\n", (*info).id); */
	while (TRUE)
	{
		EnterCriticalSection((*info).leftFork);
		/* LOG - printf("Philosopher num %d got the left fork\n", (*info).id); */
		BOOL success = TryEnterCriticalSection((*info).rightFork);
			if (success)
			{
				/* LOG - printf("Philosopher num %d got the right fork\n", (*info).id); */
				LeaveCriticalSection((*info).rightFork);
				LeaveCriticalSection((*info).leftFork);
				mealsCounter++;
				if (mealsCounter == NUM_OF_MEALS)
				{
					printf("Philosopher num %d ate %d times\n", (*info).id, mealsCounter);
					break;
				}
			}
			else
			{
				LeaveCriticalSection((*info).leftFork);
			}
	}
	return 0;
}

int main(void)
{
	/* set up thread_info (philosophers) and thread handlers */
	PhilosopherInfo_t ids[NUM_OF_THREADS];
	CRITICAL_SECTION *forks[5] = { &firstForkLock, &secondForkLock, &thirdForkLock, &fourthForkLock, &fifthForkLock };
	for (int i = 0; i < NUM_OF_THREADS; i++)
	{
		ids[i].id = i;
		ids[i].leftFork = forks[i];
		ids[i].rightFork = forks[(i + 1) % NUM_OF_THREADS];  /* last philosopher got the first fork to his right */
	}
	HANDLE handles[NUM_OF_THREADS] = { NULL };

	/* initializing locks */
	for (int i = 0; i < NUM_OF_THREADS; i++)
	{
		InitializeCriticalSection(forks[i]);
	}

	/* creating threads */
	for (int i = 0; i < NUM_OF_THREADS; i++)
	{
		LPVOID phil_id = &ids[i];
		handles[i] = CreateThread(
			NULL,
			0,
			philosopher,
			phil_id,
			0,
			NULL);
		if (handles[i] == NULL)
		{
			printf("Unable to create new thread\n");
			return 1;
		}
	}

	/* waiting for all the threads we created */
	DWORD dwEvent = WaitForMultipleObjects(
		NUM_OF_THREADS,
		handles,
		TRUE,
		INFINITE);

	/* closing threads handles */
	for (int i = 0; i < NUM_OF_THREADS; i++)
	{
		CloseHandle(&handles[i]);
	}

	/* destructing locks */
	for (int i = 0; i < NUM_OF_THREADS; i++)
	{
		DeleteCriticalSection(forks[i]);
	}

	return 0;
}



