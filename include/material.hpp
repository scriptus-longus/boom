#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>


#include <string>
#include <iostream>
#include <vector>

#include "shader.hpp"

#define MAX_TEXTURES 9

class Material {
private:
  uint32_t textures[MAX_TEXTURES];
  std::vector<std::string> uniforms;
  size_t texIdx;

public:
  Shader* shader;

  Material(Shader* shader);

  ~Material();

  void add_texture(std::string path, std::string uniform);

  void map_uniforms();

  void activate();

  uint32_t* get_textures();
};
