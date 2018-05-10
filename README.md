# GLSL to SPIR-V converter

Simple converter from GLSL to SPIR-V (syntax as [specified](https://github.com/KhronosGroup/SPIRV-Tools/blob/master/syntax.md) by Khronos Group). Made for personal educational purposes.

## Build

Compilation is only tested on Linux. Windows might work, provided you change the "OSDependent"-section of the `LIB_DIRS` variable in the Makefile.

The converter builds on the two projects [SPIRV-Tools](https://github.com/KhronosGroup/SPIRV-Tools) and [glslang](https://github.com/KhronosGroup/glslang). These are not included in this project and must be built separately. In addition, a [Vulkan SDK](https://www.lunarg.com/vulkan-sdk/) is necessary at the moment (might change).

Before building, ensure all the five variables in the Makefile (`GLSLANG_ROOT`, `GLSLANG_BIN`, `SPIRV_TOOLS_ROOT`, `SPIRV_TOOLS_BIN` and `VULKAN_ROOT`) are set to values appropriate to your system. Some explanations are provided in the file. Then run
```
$ make
```
and you should receive a brand new binary file `glsl2spirv`. You may now convert any number of GLSL source files with
```
./glsl2spirv source1.vert source2.frag (...)
```
The results are shown in terminal.

Note that all shader files must have corresponding file suffixes (.vert, .frag, .comp etc.).