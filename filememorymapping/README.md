# File Memory Mapping

> Mapping a whole file into physical memory(RAM) | heap.

![garbage_info](https://github.com/IlayG01/os_concepts_windows/blob/master/filememorymapping/Images/garbagefileinfo.png)

![procexp_view](https://github.com/IlayG01/os_concepts_windows/blob/master/filememorymapping/Images/physicalmemory.png)

![vmmap_view](https://github.com/IlayG01/os_concepts_windows/blob/master/filememorymapping/Images/vmmapview.png)

## Description

- Mapping files into the physical memory is useful, we can save space in our RAM & we can share memory between different processes.
- This code is mapping file(data) into the physical memory in a simple & wasteful way.

## External Resources

- [Malloc-MSDN](https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/malloc?view=msvc-160)

### Notice

- garbage file can be any txt/bin file
- more efficient way mentioned [here](https://github.com/IlayG01/os_concepts_windows/tree/master/minimalfilememorymapping)
