/*****************************************************************************************************\
File Name : usemydll.cpp
Author    : Ilay Gilman
Purpose   : loads our 'mydll' at load time.
\*****************************************************************************************************/

/* we need to bring the Share function */
/* 
option 1 is by include mydll.h 
option 2 is by tell the compiler about share prototype as exported function - as done below
*/
extern "C" __declspec(dllimport) void Share();

int main()
{
	Share();
	return 0;
}

/* 
NOTICE - we need to place mydll.dll in our directory / in local PATH / in VisualStudio PATH
when dllimport is called, the linker is going through each dll file in PATH & current path
looking for our asked function in the symbols table of each dll
*/
