#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include <vector>

#include "shader.hpp"
#include "texture.hpp"
#include "mesh.hpp"
#include "animation.hpp"

class Sprite {
  Shader *shader;
  Texture *texture;

  //std::vector<Animation> animations;
  glm::vec4 uv;
  Mesh* mesh;
  glm::vec2 position;

public:
  Animation* animation;

  Sprite(Mesh* mesh, Texture* texture, Shader* shader, glm::vec2 position = {0, 0}, glm::vec4 uv = {0.0, 0.0, 1.0, 1.0});

  void add_animation(Animation* animation);

  void play_animation();

  void update(float dt);

  void draw();
};
