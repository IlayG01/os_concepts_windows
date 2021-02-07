# Process Shared Memory

> Mapping a file into physical memory(RAM) | heap in chunk, sharing the file object between 2 different processes, using 1 process to read, and the other process to write, and checking how they effect each other memory image.

![output](https://github.com/IlayG01/os_concepts_windows/blob/master/processsharedmemory/Images/output.png)

![howitlooks](https://github.com/IlayG01/os_concepts_windows/blob/master/processsharedmemory/Images/howitlooks.png)

## Description

- Mapping files into the physical memory is useful, we can save space in our RAM & we can share memory between different processes.
- processsharedmemory.exe (source code in processsharedmemort.c) mapping file - data into the physical memory, and spawn write2sharedmemory.exe (source code in write2sharedmemory.c).
- The write action that done in write2sharedmemory.exe, effects processsharedmemory.exe as well - shared memory.

## External Resources

- [CreateFile-MSDN](https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea)
- [CreateFileMapping-MSDN](https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-createfilemappinga)
- [MapViewOfFile-MSDN](https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-mapviewoffile)
- [OpenFileMappingA-MSDN](https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-openfilemappinga)

### Notice

- More info about creating processes can be found [here](https://github.com/IlayG01/os_concepts_windows/tree/master/Process)
