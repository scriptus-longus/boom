#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

//#include <string>
#include <cstring>
#include <iostream>

#include "input_handler.hpp"

void InputHandler::handleMouseMove(double xpos, double ypos)  {
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;

    firstMouse = false;
  }

  mouseDelta.x = static_cast<float>(xpos - lastX) * mouseSensitivity;
  mouseDelta.y = static_cast<float>(ypos - lastY) * mouseSensitivity;

  lastX = xpos;
  lastY = ypos;
}

glm::vec2 InputHandler::pullMouseDelta() {
  glm::vec2 delta = mouseDelta;
  mouseDelta = {0.0f, 0.0f};

  return delta;
}

void InputHandler::getKeyPress(GLFWwindow* window) {
  std::memcpy(prev_key_down_map, key_down_map, sizeof(prev_key_down_map));
  

  key_down_map[GLFW_KEY_W] = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
  key_down_map[GLFW_KEY_A] = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
  key_down_map[GLFW_KEY_S] = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
  key_down_map[GLFW_KEY_D] = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;

  key_down_map[GLFW_KEY_UP] = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
  key_down_map[GLFW_KEY_DOWN] = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;
  
  key_down_map[GLFW_KEY_TAB] = glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS;

  key_down_map[GLFW_KEY_ESCAPE] = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;

  key_down_map[GLFW_KEY_SPACE] = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
}

bool InputHandler::keyDown(int key) {
  if (key >= 300) {
    return false;
  }

  return key_down_map[key];
}

bool InputHandler::keyPressed(int key) {
  if (key >= 300) {
    return false;
  }

  return key_down_map[key] && !prev_key_down_map[key];
}

