# File Minimal Memory Mapping

> Mapping a file into physical memory(RAM) | heap in chunks to save memory usage.

![garbage_info](https://github.com/IlayG01/os_concepts_windows/blob/master/minimalfilememorymapping/Images/garbagefileinfo.png)

![procexp_view](https://github.com/IlayG01/os_concepts_windows/blob/master/minimalfilememorymapping/Images/physicalmemory.png)

## Description

- Mapping files into the physical memory is useful, we can save space in our RAM & we can share memory between different processes.
- This code is mapping file(data) into the physical memory in a bit more complicated, using CreateFile, CreateFileMapping, MapViewOfFile, UnmapViewOfFile to save memory usage.
- We can see much batter results than the last method we used in - https://github.com/IlayG01/os_concepts_windows/tree/master/filememorymapping

## External Resources

- CreateFile MSDN
- CreateFileMapping MSDN
- MapViewOfFile MSDN
- UnmapViewOfFile MSDN

### Notice

- garbage file can be any txt/bin file
