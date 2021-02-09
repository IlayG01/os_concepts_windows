# Using DLL

> Using DLL - Load Time & Run Time

![output](https://github.com/IlayG01/os_concepts_windows/blob/master/dllusing/Images/output.png)

## External Resources

- [LoadLibraryA-MSDN](https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibrarya)
- [GetProcAddress-MSDN](https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getprocaddress)
- [Function Pointers in C](https://www.geeksforgeeks.org/function-pointer-in-c/)
- [Difference between load-time & run-time linking](https://stackoverflow.com/questions/2055840/difference-between-load-time-dynamic-linking-and-run-time-dynamic-linking)

### Notice

- The used dll in created [here](https://github.com/IlayG01/os_concepts_windows/tree/master/dllcreating)
- runtimeusemydll.cpp is using the dll on run time (when the process need that library, it load the dll on run time)
- usemydll.cpp is loading the dll on load-time (before the process even going to usemydll.exe entry point)
- In order to understand how loadtime & runtime loading effects the binary foramt of PE's & parsed by the OS consider watch [this video](https://www.youtube.com/watch?v=Cb6Q3-E4y2c&list=PLUFkSN0XLZ-n_Na6jwqopTt1Ki57vMIc3&index=16) from [The Life Of Binary](https://www.youtube.com/watch?v=ls8I__h1IYE&list=PLUFkSN0XLZ-n_Na6jwqopTt1Ki57vMIc3)

### Credit

- Ilay Gilman
