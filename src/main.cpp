#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
//#include <fstream>
#include <vector>
//#include <sstream>
#include <memory>
#include <math.h>

#include "shader.hpp"
#include "material.hpp"
#include "camera.hpp"
#include "input_handler.hpp"
#include "mesh.hpp"
#include "scene.hpp"
#include "object.hpp"

#define MAX_TEXTURES 9

//float cubeModel[] = {
std::vector<float> cubeModel = {
  // ===== Front face (+Z) =====
  -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
   0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
   0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
  -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,

  // ===== Back face (-Z) =====
   0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
  -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
   0.5f,  0.5f, -0.5f,   0.0f, 1.0f,

  // ===== Left face (-X) =====
  -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
  -0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,

  // ===== Right face (+X) =====
   0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
   0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
   0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
   0.5f,  0.5f,  0.5f,   0.0f, 1.0f,

  // ===== Top face (+Y) =====
  -0.5f,  0.5f,  0.5f,   0.0f, 0.0f,
   0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
   0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,

  // ===== Bottom face (-Y) =====
  -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
   0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
   0.5f, -0.5f,  0.5f,   1.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,   0.0f, 1.0f
};

std::vector<uint32_t> cubeIndices =  {
   0,  1,  2,   2,  3,  0,   // Front
   4,  5,  6,   6,  7,  4,   // Back
   8,  9, 10,  10, 11,  8,   // Left
  12, 13, 14,  14, 15, 12,   // Right
  16, 17, 18,  18, 19, 16,   // Top
  20, 21, 22,  22, 23, 20    // Bottom
};

void framebuffer_size_callback(GLFWwindow*, int width, int height) {
  glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow*, double xpos, double ypos) {
  InputHandler::handleMouseMove(xpos, ypos);
}


int main() {
  // a little bit of warmup math
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "Hello OpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glViewport(0, 0, 800, 600);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
 
  // Get window dimension
  int width, height;
  glfwGetWindowSize(window, &width, &height);

  glEnable(GL_DEPTH_TEST);


  /* --------------------
  Create the Scene
  ----------------------*/
  Camera cam = Camera(glm::vec3(0.0f, 0.0f, -7.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f));
  Scene scene(&cam, window);
  

  /* -----------------------------------
  Read Shaders
  --------------------------------------*/

  auto srcs = read_shadersrc("res/shader/shader.shd");
  if (srcs.size() <= 0) {
    std::cout << "Failed to Load Shader Source" << std::endl;
    return -1;
  }

  Shader shader(srcs[0]);

  scene.add_shader(&shader);

  /* -----------------------------------
  load textures and create materials
  --------------------------------------*/
  Material my_material = Material(&shader);

  my_material.add_texture("res/textures/face.png", "texture1");
  my_material.add_texture("res/textures/container.jpg", "texture2");
  my_material.map_uniforms();

  /* --------------------------
  Create objects in the scene
  -----------------------------*/
  Mesh cubeMesh(cubeModel, cubeIndices);

  glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f) 
  };

  Object cubes[10];
  for (size_t i = 0; i < 10; i++) {

    cubes[i].move_to(cubePositions[i]);
    cubes[i].add_mesh(&cubeMesh);
    cubes[i].add_material(&my_material);

    scene.add_object(&cubes[i]);
  }

  while(!glfwWindowShouldClose(window)) {
    scene.update();
    scene.render();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  

  glfwTerminate();
  return 0;
}
