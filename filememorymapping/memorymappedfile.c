/*****************************************************************************************************\
File Name : memorymappedfile.c
Author    : Ilay Gilman
Purpose   : loading whole file into heap|physical ram - (waste of memory).
\*****************************************************************************************************/

/* Include Section ***********************************************************************************/
#include <Windows.h>
#include <stdio.h>
#define FILENAME "garbage.bin"

/* Decleration Section *******************************************************************************/

/*****************************************************************************************************\
* Function Name                           :                 count_in_data
* Function Porpuse                        :                 counting 'a' appearance in recieved buffer
* Function Params                         :                 LPSTR data, CHAR sign_to_count
* Return Values                           :                 int number_of_appearance
* Remarks                                 :                 ASCII sign only
* Authors                                 :                 Ilay Gilman
\*****************************************************************************************************/
int count_in_data(LPSTR data, CHAR sign_to_count);

/* Main Section **************************************************************************************/

int main()
{
	HANDLE hFile;
	CHAR file_name[] = FILENAME;
	LPCSTR pFileName = file_name;
	hFile = CreateFileA(
		pFileName,	  /* file name */
		GENERIC_READ, /* access type */
		0,			  /* other processes can't share */
		NULL,
		OPEN_EXISTING, /* open only if file exists */
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD file_size = GetFileSize(hFile, NULL);
	/* copying whole file content to memory - waste of memory */
	LPVOID pBuf;
	LPSTR data;
	pBuf = malloc(file_size + 1);
	if (0 == ReadFile(hFile, pBuf, file_size, NULL, NULL))
	{
		printf("Unable to read\n");
		return 1;
	}
	data = (LPSTR)pBuf;

	/* Sleep for analyze program in procexp / vmmmap */
	Sleep(50000);

	printf("The number of occurance is %d\n", count_in_data(pBuf, 'A'));

	/* cleanup */
	free(pBuf);
	CloseHandle(hFile);
	return 0;
}

INT count_in_data(LPSTR data, CHAR sign_to_count)
{
	INT counter = 0;
	INT index = 0;
	while (*(data + index) != '\0')
	{
		if (*(data + index) == sign_to_count)
		{
			counter++;
		}
		index++;
	}
	return counter;
}