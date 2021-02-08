/* Specifies that the compiler includes the header file only once, when compiling a source code file. */
#pragma once

/* https://docs.microsoft.com/en-us/cpp/preprocessor/hash-ifdef-and-hash-ifndef-directives-c-cpp?view=msvc-160&viewFallbackFrom=vs-2019 */
#ifdef DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif
/*
why extern "C"?

C and C++ use different function name mangling techniques.
C++ allows function overloading, which means the linker needs to mangle the function name to indicate which specific prototype it needs to call.
By declaring a function with extern "C", it changes the linkage requirements so that the C++ compiler does not add the extra mangling information to the symbol.
*/
extern "C"
{
	/* DECLDIR turns to __Declspec(dllexport) if DLL_EXPORT is defined - sharing Share function */
	DECLDIR void Share();
	/* Keep function is private in every scenario */
	void Keep();
}