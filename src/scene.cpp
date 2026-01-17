#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <iostream>
#include <vector>

#include "shader.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include "object.hpp"
#include "input_handler.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "sprite.hpp"

Scene::Scene(Camera* cam, GLFWwindow* window) {
  this->cam = cam;
  this->window = window;
  this->deltaTime = 0.0f;

  this->lastFrame = 0.0f;
}

void Scene::add_object(Object* cube) {
  this->objects.emplace_back(cube);
}

void Scene::add_shader(Shader* object) {
  this->shader.emplace_back(object);
}

void Scene::add_sprite(Sprite* sprite) {
  this->sprites.emplace_back(sprite);
}

void Scene::update() {
  float time = static_cast<float>(glfwGetTime());
  this->deltaTime = time - lastFrame;
  this->lastFrame = time;

  // handle user input 
  InputHandler::getKeyPress(window);
  this->processInput();
}

void Scene::render() {
  // clear screen
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // draw objects
  for (auto& object : this->objects) {
    auto model = object->get_model();
     

    if (object->material != nullptr) {
      object->material->activate();
      object->material->shader->set_uniformMat("model", model);
    } 

    if(object->mesh != nullptr) {
      object->mesh->draw();
    }
  }

  int width, height;
  glfwGetWindowSize(this->window, &width, &height);
  
  // update view and projection in camera
  auto view = this->cam->get_lookAt();
  auto projection = this->cam->get_projection(width, height);

  for (auto& s : this->shader) {
    s->set_uniformMat("projection", projection);
    s->set_uniformMat("view", view);
  }

  if (!this->dbg_mode) {
    for (auto& s: this->sprites) {
      s->update(this->deltaTime);
      s->draw();
    }
  }
}

void Scene::processInput() {
  float v = static_cast<float>(4.0f * this->deltaTime);

  if(InputHandler::keyPressed(GLFW_KEY_TAB)) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    this->dbg_mode = !this->dbg_mode;
  }

  // debug mode only features
  if (!this->dbg_mode) {
    return;
  }

  if(InputHandler::keyDown(GLFW_KEY_W))
    this->cam->move({v, 0.0, 0.0});
  if(InputHandler::keyDown(GLFW_KEY_S)) 
    this->cam->move({-v, 0.0, 0.0});

  if(InputHandler::keyDown(GLFW_KEY_A)) 
    this->cam->move({0.0, 0.0, -v});
  if(InputHandler::keyDown(GLFW_KEY_D)) 
    this->cam->move({0.0, 0.0, v});

  if(InputHandler::keyDown(GLFW_KEY_UP)) 
    this->cam->move_yoffset(v);
  if(InputHandler::keyDown(GLFW_KEY_DOWN))
    this->cam->move_yoffset(-v);


  if(InputHandler::keyPressed(GLFW_KEY_ESCAPE)) {
    int32_t polygonMode[2];

    glGetIntegerv(GL_POLYGON_MODE, polygonMode);
    if (polygonMode[0] == GL_FILL) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
  }

  auto delta = InputHandler::pullMouseDelta();
  this->cam->rotate(delta.y, delta.x);
}

float Scene::get_delta_time() {
  return this->deltaTime;
}
