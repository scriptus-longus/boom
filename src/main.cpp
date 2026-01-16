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
#include "map.hpp"

/*#define MAP_MAX_X 6
#define MAP_MAX_Z 11*/

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

int gameMap[MAP_MAX_X][MAP_MAX_Z] = {
  {1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0},
  {1, 2, 2, 1, 0, 0, 1, 2, 1, 0, 0},
  {1, 2, 2, 1, 1, 1, 1, 2, 1, 0, 0},
  {1, 1, 2, 2, 2, 2, 2, 2, 1, 0, 0},
  {0, 1, 1, 1, 1, 2, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
};

/*class Map {
private:
  static inline int map[MAP_MAX_X][MAP_MAX_Z] = {
      {1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0},
      {1, 2, 0, 1, 0, 0, 1, 0, 1, 0, 0},
      {1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0},
      {1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
      {0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0},
      {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
    };
  static inline glm::vec3 start_pos;

public:
  static void init(int map[MAP_MAX_X][MAP_MAX_Z]) {
    std::memcpy(this->map, map, MAP_MAX_X*MAP_MAX_Z*sizeof(int));
    for 
    for (int x = 0; x < MAP_MAX_X; x++) {
      for (size_t z = 0; z < MAP_MAX_Z; z++) {
        if (map[x][z] == 1) {
          start_pos = {-x, 0.0f, z};
        }
      }
    }
  }

  bool is_free(glm::vec3 point) {
    int x = -1 * (int)point.x;
    int z = (int)point.z;
    
    // check if point is off map
    if (x > MAP_MAX_X || z  > MAP_MAX_Z || x < 0 || z < 0) 
      return false

    return map[x][y] != 0
  }

  glm::vec3 get_start_pos() {
    return start_pos;
  }
}*/

class Player {
private:
  Camera *cam;
  glm::vec3 position;

public:
  Player(Camera* cam) {
    this->cam = cam;
    this->position = cam->get_position();
  }

  // movement relative to Player coordinates
  void move(glm::vec3 v) {
    auto frontVec = this->cam->get_front();
    glm::vec3 base_x = glm::normalize(glm::vec3(frontVec.x, 0.0, frontVec.z));
    glm::vec3 base_z = glm::normalize(glm::cross(frontVec, this->cam->get_up()));

    // linear combindation
    glm::vec3 new_pos = this->position + v.x * base_x + v.z * base_z; //+ v.y * base_y;

    if (Map::is_walkable(new_pos.x, this->position.z)) {
      this->position.x = new_pos.x;
    }

    if (Map::is_walkable(this->position.x, new_pos.z)) {
      this->position.z = new_pos.z;
    }

    // update cam position
    //this->cam->set_position(new_pos);
  }
  

  void update(float dt) {
    float v = 4.0f * dt;

    /*
    Player movement
    */
    if(InputHandler::keyDown(GLFW_KEY_W))
      this->move({v, 0.0, 0.0});
    if(InputHandler::keyDown(GLFW_KEY_S)) 
      this->move({-v, 0.0, 0.0});

    if(InputHandler::keyDown(GLFW_KEY_A)) 
      this->move({0.0, 0.0, -v});
    if(InputHandler::keyDown(GLFW_KEY_D)) 
      this->move({0.0, 0.0, v});


    auto delta = InputHandler::pullMouseDelta();
    this->cam->rotate(delta.y, delta.x);
    this->cam->set_position(this->position);
  }
};

void framebuffer_size_callback(GLFWwindow*, int width, int height) {
  glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow*, double xpos, double ypos) {
  InputHandler::handleMouseMove(xpos, ypos);
}


std::vector<Object> build_map(int map[MAP_MAX_X][MAP_MAX_Z], 
                              Mesh* mesh, 
                              Material* wallMaterial,
                              Material* floorMaterial,
                              Material* topMaterial) {
  std::vector<Object> cubes;

  for (int x = 0; x < MAP_MAX_X; x++) {
    for (size_t z = 0; z < MAP_MAX_Z; z++) {
      Object cube;

      if (map[x][z] == 1) {
        auto cubePosition = glm::vec3(x + 0.5, 0.0f, z + 0.5);

        cube.move_to(cubePosition);
        cube.add_mesh(mesh);
        cube.add_material(wallMaterial);

        cubes.emplace_back(cube);
      } else if (map[x][z] == 2) {
        auto cubePosition = glm::vec3(x + 0.5, -1.0f, z + 0.5);

        cube.move_to(cubePosition);
        cube.add_mesh(mesh);
        cube.add_material(floorMaterial);

        cubes.emplace_back(cube);

        // add top cube
        Object topCube;
        topCube.move_to(glm::vec3(x+0.5, 1.0f, z+0.5f));
        topCube.add_mesh(mesh);
        topCube.add_material(topMaterial);
        cubes.emplace_back(topCube);
      }
    }
  }

  return cubes;
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
  Camera cam = Camera(glm::vec3(1.5f, 0.0f, 1.5f),
                    glm::vec3(1.5f, 0.0f, 2.0f));
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
  Material wallMaterial = Material(&shader);

  //my_material.add_texture("res/textures/face.png", "texture1");
  //my_material.add_texture("res/textures/container.jpg", "texture2");
  wallMaterial.add_texture("res/textures/wall.png", "texture1");
  wallMaterial.map_uniforms();

  Material floorMaterial = Material(&shader);

  floorMaterial.add_texture("res/textures/container.jpg", "texture1");
  floorMaterial.map_uniforms();

  Material topMaterial = Material(&shader);

  topMaterial.add_texture("res/textures/grey.png", "texture1");
  topMaterial.map_uniforms();
  /* --------------------------
  Create objects in the scene
  -----------------------------*/
  Mesh cubeMesh(cubeModel, cubeIndices);
  Map::init(gameMap);

  auto cubes = build_map(gameMap, 
                        &cubeMesh, 
                        &wallMaterial,
                        &floorMaterial,
                        &topMaterial);
  /*glm::vec3 cubePositions[] = {
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
  };*/

  //Object cubes[10];
  Player player(&cam);

  for (size_t i = 0; i < cubes.size(); i++) {
    scene.add_object(&cubes[i]);
  }

  while(!glfwWindowShouldClose(window)) {
    if (!scene.dbg_mode) {
      player.update(scene.get_delta_time());
    }
    scene.update();
    scene.render();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  

  glfwTerminate();
  return 0;
}
