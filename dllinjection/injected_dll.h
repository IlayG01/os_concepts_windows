#pragma once

#ifdef DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif

extern "C"
{
	DECLDIR void Pop(); //shared function that can be called from outside the dll
}