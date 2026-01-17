#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

class Texture {
private:
  std::string uniform;
public:
  int width;
  int height;

  uint32_t texture;

  Texture(std::string, GLenum format = GL_RGB, bool flip = false);

  ~Texture();

  void activate(GLenum tex_idx = GL_TEXTURE0);
};

