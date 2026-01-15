#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>

#include <string>
#include <iostream>
#include <vector>

#include "shader.hpp"
#include "material.hpp"


Material::Material(Shader* shader) {
  this->shader = shader;
  this->texIdx = 0;
  glGenTextures(MAX_TEXTURES, this->textures);
}

Material::~Material() {
  std::cout << "Deleting material" << std::endl;
  glDeleteTextures(MAX_TEXTURES, this->textures);
}

void Material::add_texture(std::string path, std::string uniform) {
  if (texIdx >= MAX_TEXTURES) {
    std::cout << "Error:Material:AddTexture: Maximum number of textures exceded" << std::endl;
    return;
  }


  glBindTexture(GL_TEXTURE_2D, this->textures[texIdx]);

  // maybe configure wrapping
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  int widht, height, nrChannels;

  stbi_set_flip_vertically_on_load(true);

  unsigned char* data = stbi_load(path.c_str(), &widht, &height, &nrChannels, 0);
  std::cout << "width: " << widht << std::endl;
  if (data) {
    std::cout << "Info: Loaded texture successfully from " << path << std::endl;

    if (path.find(".jpg") != std::string::npos) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widht, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    } else {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widht, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }

    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Error: Could not load texture image " << path << std::endl;
  }

  stbi_image_free(data);

  this->uniforms.emplace_back(uniform); 
  this->texIdx++;
}

void Material::map_uniforms() {
  this->shader->run();

  for (size_t i = 0; i < this->texIdx; i++) {
    this->shader->set_uniformI(this->uniforms[i], i);
  }
}

void Material::activate() {
  for (size_t i = 0; i < this->texIdx; i++) {
    glActiveTexture(GL_TEXTURE1 * i);
    glBindTexture(GL_TEXTURE_2D, this->textures[i]);
  }

  this->shader->run();
}

uint32_t* Material::get_textures() {
  return this->textures;
}
