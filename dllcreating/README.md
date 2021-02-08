# Creating DLL

> Creating DLL in Visual Sutdio Environment.

![visualstudioconfiguration](https://github.com/IlayG01/os_concepts_windows/blob/master/dllcreating/Images/vscnf.png)

![outputfile](https://github.com/IlayG01/os_concepts_windows/blob/master/dllcreating/Images/output.png)

## External Resources

- [Precompiled Header Files](https://docs.microsoft.com/en-us/cpp/build/creating-precompiled-header-files?view=msvc-160)
- [pragma once](https://docs.microsoft.com/en-us/cpp/preprocessor/once?view=msvc-160&viewFallbackFrom=vs-2019)
- [ifdef](https://docs.microsoft.com/en-us/cpp/preprocessor/hash-ifdef-and-hash-ifndef-directives-c-cpp?view=vs-2019)
- [extern C](https://embeddedartistry.com/blog/2017/05/01/mixing-c-and-c-extern-c/)

### Notice

- After compilation, we recieve .dll file & .lib file.
  Why we got lib? isnt it dynamic linking?
  well this file doesnt contain code, only the symbols of the exported dll functions. so linker can use this file to incept in executable the right references to our dll file.
  the dll file contains the code.
- More info about linkers & loaders can be found briefly [here](https://www.geeksforgeeks.org/difference-between-linker-and-loader/) or more detailed in some videos of [The Life Of Binaries Course](https://www.youtube.com/watch?v=ls8I__h1IYE&list=PLUFkSN0XLZ-n_Na6jwqopTt1Ki57vMIc3)

### Credit

- Ilay Gilman
