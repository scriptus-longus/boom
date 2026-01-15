#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "shader.hpp"

/* -----------------
Helper function to read the shader src
--------------------*/
std::vector<ShaderSrc> read_shadersrc(std::string file_path) {
  std::ifstream shader_file(file_path);
  std::vector<ShaderSrc> ret;

  enum readState  {
    STATE_VERT, STATE_FRAG, STATE_NONE
  };

  if (!shader_file.is_open()) {
    std::cout << "Error::Shader::ReadFile: Could not open Shader file" << std::endl;
    return ret;
  }


  readState current_state = STATE_NONE;

  std::stringstream vertShaderSrc;
  std::stringstream fragShaderSrc;
  std::string line;

  while(std::getline(shader_file, line)) {
    if (line.find("#DEF_SHADER") != std::string::npos) {
      vertShaderSrc.str(std::string());
      fragShaderSrc.str(std::string());
    } else if (line.find("#END_SHADER") != std::string::npos) {
      ret.push_back({.vert_src=vertShaderSrc.str(),
                     .frag_src=fragShaderSrc.str()});
    } else if (line.find("#VERT_SHADER") != std::string::npos) {
      current_state = STATE_VERT; 
    } else if (line.find("#FRAG_SHADER") != std::string::npos) {
      current_state = STATE_FRAG; 
    } else {
      if (current_state == STATE_VERT) {
        vertShaderSrc << line << std::endl;  
      } else if (current_state == STATE_FRAG) {
        fragShaderSrc << line << std::endl;
      }     
    }
  }

  return ret;
}

/* ---------------------
Show debug info for comile errors 
------------------------*/
void Shader::check_compile_error() {  // TODO: change type enum
  int success;
  char infoLog[512];
  glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(this->vertexShader, 512, NULL, infoLog);
    std::cout << "Error::Shader::Vertex::ComilationError\n" << infoLog << std::endl;
  }

  glGetShaderiv(this->fragmentShader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(this->fragmentShader, 512, NULL, infoLog);
    std::cout << "Error::Shader::Fragment::ComilationError\n" << infoLog << std::endl;
  }
}
  
/* ---------------------
Compile the shaders
------------------------*/
void Shader::compile() {
  const char* vert_src = this->src.vert_src.c_str();
  this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(this->vertexShader, 1, &vert_src, NULL);
  glCompileShader(this->vertexShader);


  const char* frag_src = this->src.frag_src.c_str();
  this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(this->fragmentShader, 1, &frag_src, NULL);
  glCompileShader(this->fragmentShader);

  this->check_compile_error();
}

/* ---------------------
Link the shaders
------------------------*/
void Shader::link() {
  // linking
  this->shaderProgram = glCreateProgram();

  glAttachShader(this->shaderProgram, this->vertexShader);
  glAttachShader(this->shaderProgram, this->fragmentShader);
  glLinkProgram(this->shaderProgram);
  
  int success;
  char infoLog[512];
  // check for link errors
  glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
  if(!success) {
    glGetProgramInfoLog(this->shaderProgram, 512, NULL, infoLog);
    std::cout << "Error::Shader::Linking\n" << infoLog << std::endl;
  }
}

Shader::Shader(ShaderSrc src) {
  this->src = src;

  this->compile();
  this->link();
}

Shader::~Shader() {
  glDeleteShader(this->vertexShader);
  glDeleteShader(this->fragmentShader);

  glDeleteProgram(this->shaderProgram);
}

void Shader::set_uniform(std::string name, float a) {
  int uniformLoc = glGetUniformLocation(this->shaderProgram, name.c_str());
  glUniform1f(uniformLoc, a);
}

void Shader::set_uniform(std::string name, float a, float b, float c, float d) {
  int uniformLoc = glGetUniformLocation(this->shaderProgram, name.c_str());
  glUniform4f(uniformLoc, a, b, c, d);
}


void Shader::set_uniformI(std::string name, int a) {
  int uniformLoc = glGetUniformLocation(this->shaderProgram, name.c_str());
  glUniform1i(uniformLoc, a);
}

void Shader::set_uniformMat(std::string name, glm::mat4 projection) {
  int uniformLoc = glGetUniformLocation(this->shaderProgram, name.c_str());
  glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

uint32_t Shader::get_id() {
  return this->shaderProgram;
}

void Shader::run() {
  glUseProgram(this->shaderProgram);
}

std::string Shader::to_str() {
  return this->src.to_str();
}
