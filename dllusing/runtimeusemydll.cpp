/*****************************************************************************************************\
File Name : runtimeusemydll.cpp
Author    : Ilay Gilman
Purpose   : loading our 'mydll' on run time.
\*****************************************************************************************************/

/* Include Section ***********************************************************************************/
#include <stdio.h>
#include <Windows.h>

/* Definition Section ********************************************************************************/
#define LIBRARY "C:\\mydll.dll"

/* PFUNC is defined as pointer to function that gets and returning void */
/* like our share function */
typedef void (*PFUNC)(void);

int main()
{
	/* loading dll */
	HMODULE hModule = LoadLibraryA(LIBRARY);
	if (NULL == hModule)
	{
		printf("Failed to load DLL\n");
		return 1;
	}
	/* loading function (gets specific address after dll loaded)*/
	PFUNC pFunc = (PFUNC)GetProcAddress(hModule, "Share");
	if (NULL != pFunc)
	{
		(*pFunc)();
	}
	else
	{
		printf("Failed to load function\n");
		return 2;
	}
	return 0;
}
