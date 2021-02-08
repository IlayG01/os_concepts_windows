#include "pch.h"   /* Precompiled Header Files */
#define DLL_EXPORT /* important to define before mydll.h code - effects the ifdef code */
#include "mydll.h"

/* Documented in the header file */
extern "C"
{
	DECLDIR void Share()
	{
		printf("I am an exported function, can be called outside the DLL\n");
	}
	void Keep()
	{
		printf("I am not exported, can be called only within the DLL\n");
	}
}

/* our DLL entry point */
BOOL APIENTRY DllMain(HANDLE hModule, // Handle to DLL module
					  DWORD ul_reason_for_call,
					  LPVOID lpReserved) // Reserved
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// A process is loading the DLL.
		printf("DLL PROCESS ATTACH - Start\n");
		Share();
		Keep();
		printf("DLL PROCESS ATTACH - End\n");
		break;
	case DLL_THREAD_ATTACH:
		// A process is creating a new thread.
		break;
	case DLL_THREAD_DETACH:
		// A thread exits normally.
		break;
	case DLL_PROCESS_DETACH:
		// A process unloads the DLL.
		break;
	}
	return TRUE;
}
