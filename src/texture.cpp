#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

#include "texture.hpp"

Texture::Texture(std::string path, GLenum format, bool flip) {
  glGenTextures(1, &this->texture);
  glBindTexture(GL_TEXTURE_2D, this->texture);

  // maybe configure wrapping
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  //int widht, height, nrChannels;

  if (flip) {
    stbi_set_flip_vertically_on_load(true);
  }

  int nrChannels;
  unsigned char* data = stbi_load(path.c_str(), &this->width, &this->height, &nrChannels, 0);
  if (data) {
    std::cout << "Info: Loaded texture successfully from " << path << std::endl;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, format, GL_UNSIGNED_BYTE, data);

    //glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Error: Could not load texture image " << path << std::endl;
  }

  stbi_image_free(data);
}

Texture::~Texture() {
  glDeleteTextures(1, &this->texture);
}

void Texture::activate(GLenum tex_idx) {
  glActiveTexture(tex_idx);
  glBindTexture(GL_TEXTURE_2D, this->texture);
  //this->shader->run();
}

