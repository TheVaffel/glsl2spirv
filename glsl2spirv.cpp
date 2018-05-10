#include <spirv-tools/libspirv.hpp>
#include <vulkan/vulkan.h>
#include <glsl_util.h>

#include <string>
#include <fstream>
#include <vector>

VkShaderStageFlagBits getType(std::string file_name){
  if(file_name.length() < 6){
    printf("The source file name should of the form <name>.<stage suffix>\n");
    exit(-1);
  }

  std::string ending = file_name.substr(file_name.length() - 5, 5); // Get 5 last characters

  // The file endings are subject to Khronos' own usage
  // (https://github.com/KhronosGroup/glslang#execution-of-standalone-wrapper)
  if(ending ==".vert"){
    printf("This is a Vertex shader\n");
    return VK_SHADER_STAGE_VERTEX_BIT;
  }
  else if(ending ==".tesc"){
    return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
  }
  else if(ending ==".tese"){
    return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
  }
  else if(ending ==".geom"){
    return VK_SHADER_STAGE_GEOMETRY_BIT;
  }
  else if(ending ==".frag"){
    printf("This is a fragment shader\n");
    return VK_SHADER_STAGE_FRAGMENT_BIT;
  }
  else if(ending ==".comp"){
    return VK_SHADER_STAGE_COMPUTE_BIT;
  }
  else{
    printf("Sorry, could not parse file ending \"%s\"\nPossible endings are: .vert, .tesc, .tese, .geom, .frag .comp\n", ending.c_str());
    exit(-1);
  }
  
  
}

int main(int argc, const char** argv){
  if(argc == 1){
    printf("You must supply GLSL file names!\n");
    exit(-1);
  }

  
  glslang::InitializeProcess();

  spvtools::SpirvTools disassembler(SPV_ENV_VULKAN_1_0);
  
  for(int i = 1; i < argc; i++){
    std::ifstream file_stream(argv[i]);
    std::stringstream buf;
    buf << file_stream.rdbuf();
    std::string source = buf.str();

    std::vector<unsigned int> spirv;
    VkShaderStageFlagBits stage = getType(std::string(argv[i]));
    
    if(GLSLtoSPV(stage, source.c_str(), spirv)){
      printf("The first part of the spirv is:\n");
      for(int i = 0; i < 10; i++){
	printf("0x%x\n", spirv[i]);
      }
    }else{
      printf("Compilation of source file %s failed!\n", argv[i]);
      exit(-1);
    }

    std::string disassembly;
    if(!disassembler.Disassemble(spirv, &disassembly)){
      printf("Could not disassemble!\n");
    }

    printf("Disassembly:\n\n%s\n", disassembly.c_str());
  }
  
  
}
