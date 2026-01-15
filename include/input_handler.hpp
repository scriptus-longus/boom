#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>


class InputHandler {
private:
  static inline bool firstMouse = true;
  static inline float lastX = 0.0f;
  static inline float lastY = 0.0f;

  static inline glm::vec2 mouseDelta = {0.0f, 0.0f};

  static inline bool prev_key_down_map[300] = {false};
  static inline bool key_down_map[300] = {false};

  static constexpr float mouseSensitivity = 1.0f;
public:
  static void handleMouseMove(double, double);

  static glm::vec2 pullMouseDelta();

  static void getKeyPress(GLFWwindow* window);

  static bool keyDown(int key);

  static bool keyPressed(int key);
};
