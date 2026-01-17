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
#include "sprite.hpp"


Sprite::Sprite(Mesh* mesh, Texture* texture, Shader* shader, glm::vec2 position, glm::vec4 uv) {
//rectangle.move_to(glm::vec3(0.2f, -0.6f, 0.0f));
  this->texture = texture;
  this->shader = shader;
  this->mesh = mesh;
  this->uv = uv;
  this->position = position;
  this->animation = nullptr;
}

void Sprite::add_animation(Animation* animation) {
  this->animation = animation;
}

void Sprite::play_animation() {
  if (animation != nullptr) {
    animation->play();
  }
}

void Sprite::update(float dt) {
  if (animation != nullptr) {
    animation->update(dt);
    this->uv = animation->getUV();
  }
}

void Sprite::draw() {
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, {this->position.x, this->position.y, 0.0f});

  this->texture->activate();
  this->shader->run();

  this->shader->set_uniform("uv", this->uv.x, this->uv.y, this->uv.z, this->uv.w);

  this->shader->set_uniformMat("model", model);
  this->mesh->draw();
}
