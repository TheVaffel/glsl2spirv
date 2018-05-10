# glslang home and build directories
GLSLANG_ROOT=~/SDK/glslang
GLSLANG_BIN=${GLSLANG_ROOT}/build

# SPIRV-Tools home and build directories
SPIRV_TOOLS_ROOT=~/Programs/SPIRV-Tools
SPIRV_TOOLS_BIN=${SPIRV_TOOLS_ROOT}/build

# With LunarG's SDK, this is something like path/to/SDK/1.0.xx.x/x86_64
VULKAN_ROOT=${VULKAN_SDK}

INCLUDES = -I . -I ${SPIRV_TOOLS_ROOT}/include -I ${VULKAN_ROOT}/include -I ${GLSLANG_ROOT}

LIB_DIRS = -L ${GLSLANG_BIN}/hlsl -L ${GLSLANG_BIN}/glslang -L ${GLSLANG_BIN}/SPIRV -L ${GLSLANG_BIN}/OGLCompilersDLL -L ${GLSLANG_BIN}/glslang/OSDependent/Unix -L ${SPIRV_TOOLS_BIN}/source

LIBS = -l glslang -l OSDependent -l SPIRV -l OGLCompiler -l HLSL -l pthread -l SPIRV-Tools


CC=g++

glsl2spirv: 
	${CC} -std=c++11 glsl_util.cpp glsl2spirv.cpp -o $@ ${INCLUDES} ${LIB_DIRS} ${LIBS}


