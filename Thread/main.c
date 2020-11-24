/*****************************************************************************************************\
File Name : main.c
Author    : Ilay Gilman
Purpose   : creating thread
\*****************************************************************************************************/

/* Include Section ***********************************************************************************/
#include <Windows.h>
#include <stdio.h>


/* Structs & Unions Section ****************************************************************************/
/* struct passed to the thread function */
typedef struct NumbersStruct
{
	int first_number;
	int second_number;
} NumbersStruct_t;


/* thread function */
DWORD WINAPI foo(LPVOID lparam) { /*LPVOID magic*/
	NumbersStruct_t* nums = (NumbersStruct_t*)lparam;
	INT count = nums->first_number + nums->second_number;
	for (INT i = 1; i <= count; i++) 
	{
		printf("foo\n");
	}
	/* hold the thread to watch it in the procexp */
	Sleep(50);
	return 1;

}

int main()
{
	NumbersStruct_t my_struct = { .first_number = 3, .second_number = 4 };
	LPVOID pstruct = &my_struct;
	HANDLE thread_h = CreateThread(NULL,
								   0,
								   foo,
								   pstruct,
								   0,
								   NULL);

	/* waiting the process to return */
	if (thread_h)
	{
		WaitForSingleObject(thread_h, INFINITE);
	}
}