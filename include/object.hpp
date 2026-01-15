#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <iostream>
#include <vector>

#include "material.hpp"
#include "mesh.hpp"
#include "object.hpp"

class Object {
private:
  float pitch, yaw, roll;
  glm::vec3 position;

public: 
  Material* material;
  Mesh* mesh;

  Object(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
       float pitch = 0.0f, 
       float yaw = 0.0f, 
       float roll = 0.0f) {

    this->position = position;

    this->pitch = pitch;
    this->yaw = yaw;
    this->roll = roll;
  }

  void add_material(Material* material) {
    this->material = material;
  }

  void add_mesh(Mesh* mesh) {
    this->mesh = mesh;
  }

  void move_to(glm::vec3 position) {
    this->position = position;
  }

  void set_rotation(float pitch, float yaw, float roll) {
    this->pitch = pitch;
    this->yaw = yaw;
    this->roll = roll;
  }

  glm::mat4 get_model() {
    auto model = glm::mat4(1.0f);

    // rotate
    model = glm::rotate(model, glm::radians(this->pitch), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(this->yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(this->roll), glm::vec3(0.0f, 0.0f, 1.0f));

    // translate
    model = glm::translate(model, this->position);

    return model;
  }

  glm::vec3 get_position() {
    return this->position;
  }
};
