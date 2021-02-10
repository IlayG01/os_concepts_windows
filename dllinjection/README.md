# Making DLL Injection

> Creating DLL to Inject in Visual Sutdio Environment, Writing Code to Inject The DLL We Made.

![visualstudioconfiguration](https://github.com/IlayG01/os_concepts_windows/blob/master/dllinjection/Images/vscnf.png)

![outputfile](https://github.com/IlayG01/os_concepts_windows/blob/master/dllinjection/Images/output.png)

![injectionsetup](https://github.com/IlayG01/os_concepts_windows/blob/master/dllinjection/Images/injectionsetup.png)

![result](https://github.com/IlayG01/os_concepts_windows/blob/master/dllinjection/Images/Injectedproc.png)

## The Steps To Inject

- Picking a running process (and setting the process id of the running process we chose in the code)
- Open the remote process we chose
- Allocating memory & writing to memory in the remote process (the dll we about to load)
- Creating the new thread
- The new thread will be the loadlibrary with the path of
  the dll we want to inject, which will run the DllMain of our injected(created) dll

## External Resources

- [DLL_Injection](https://en.wikipedia.org/wiki/DLL_injection)
- [DLL_Injection using LoadLibrary](https://arvanaghi.com/blog/dll-injection-using-loadlibrary-in-C/)
- [VirtualAllocEx-MSDN](https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualallocex)
- [WriteProcessMemory-MSDN](https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-writeprocessmemory)
- [CreateRemoteThread-MSDN](https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createremotethread)

### Notice

- If this is the first time you are creating dll, consider seeing the documented code here - [dllcreation](https://github.com/IlayG01/os_concepts_windows/tree/master/dllcreating)
- Injected_dll.cpp, Injected_dll.h, pch.h are the code for building the injected DLL
- dll_injection.cpp is the code to inject the dll into remote process
- The injected dll & the remote process need to be on the same arch(GetProcAddress need to point to the same dll function in both)
  Getprocaddress is in Kernel32.dll
- Also to make sure CreateRemoteThread can happen in the remote process you chose

### Credit

- Ilay Gilman
