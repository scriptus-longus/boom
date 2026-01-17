#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <iostream>

#include "shader.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include "object.hpp"
#include "camera.hpp"
#include "input_handler.hpp"
#include "sprite.hpp"

class Scene {
private:
  float deltaTime;
  float lastFrame;

public:
  static inline bool dbg_mode = false;
  Camera* cam;
  std::vector<Object*> objects;
  std::vector<Shader*> shader;
  std::vector<Sprite*> sprites;
  GLFWwindow* window; 


  Scene(Camera*, GLFWwindow*);

  void add_object(Object* cube);

  void add_shader(Shader* object);
  void add_sprite(Sprite* sprite);

  void update();

  void render();

  void processInput();

  float get_delta_time();
};

