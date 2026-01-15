#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

struct ShaderSrc {
  std::string vert_src;
  std::string frag_src;

  std::string to_str() {
    std::stringstream ret;

    ret << "Vertex Shader:" << std::endl
        << "----------------------" << std::endl
        << vert_src << std::endl << std::endl
        << "Frag Shader:" << std::endl
        << "----------------------" << std::endl
        << frag_src << std::endl << std::endl;

    return ret.str();
  }
};

std::vector<ShaderSrc> read_shadersrc(std::string);

/*--------------------
Shader
  - contains one fragment shader and one vertex shader
-----------------------*/
class Shader {
  private:
    ShaderSrc src;
    uint32_t vertexShader;
    uint32_t fragmentShader;
    uint32_t shaderProgram;

    /* ---------------------
    Show debug info for comile errors 
    ------------------------*/
    void check_compile_error();
  
    /* ---------------------
    Compile the shaders
    ------------------------*/
    void compile();

    /* ---------------------
    Link the shaders
    ------------------------*/
    void link();



  public:
    Shader(ShaderSrc src);

    ~Shader(); 
    void set_uniform(std::string name, float a);

    void set_uniform(std::string name, float a, float b, float c, float d);


    void set_uniformI(std::string name, int a);

    void set_uniformMat(std::string name, glm::mat4 projection);

    uint32_t get_id();

    void run();

    std::string to_str();
};
