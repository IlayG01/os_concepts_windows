# Hooking PE Import Address Table (IAT)

> Hooking a portable executable (PE) binary.

In PE files there is an IAT that holdes all the virtual addresses of the functions we import from different dll's.
Were about to manipulate this table, in order to run our own code.
![explaination](https://github.com/IlayG01/os_concepts_windows/blob/master/pe_iat_hooking/Images/explaination.png)

![hacked](https://github.com/IlayG01/os_concepts_windows/blob/master/pe_iat_hooking/Images/hacked.png)

![continue](https://github.com/IlayG01/os_concepts_windows/blob/master/pe_iat_hooking/Images/end.png)

## External Resources

- [LoadLibraryA-MSDN](https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibrarya)
- [GetProcAddress-MSDN](https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getprocaddress)
- [Function Pointers in C](https://www.geeksforgeeks.org/function-pointer-in-c/)
- [Difference between load-time & run-time linking](https://stackoverflow.com/questions/2055840/difference-between-load-time-dynamic-linking-and-run-time-dynamic-linking)

### Notice

- This concept require early knowledge in PE format & assembly (x86).
- I am highly recommand to cover these in [The Life Of Binaries](https://www.youtube.com/watch?v=ls8I__h1IYE&list=PLUFkSN0XLZ-n_Na6jwqopTt1Ki57vMIc3) and [Introductory Intel x86](https://www.youtube.com/watch?v=H4Z0S9ZbC0g&list=PL038BE01D3BAEFDB0)

### Credit

- Ilay Gilman
