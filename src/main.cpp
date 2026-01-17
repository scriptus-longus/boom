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
#include "texture.hpp"
#include "animation.hpp"
#include "sprite.hpp"

/*#define MAP_MAX_X 6
#define MAP_MAX_Z 11*/

#define MAX_MATERIALS 10

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


std::vector<float> rectangleModel = {
  -0.5f, -0.5f,  00.0f,   0.0f, 0.0f,
   0.5f, -0.5f,  0.0f,   1.0f, 0.0f,
   0.5f,  0.5f,  0.0f,   1.0f, 1.0f,
  -0.5f,  0.5f,  0.0f,   0.0f, 1.0f
};

std::vector<uint32_t> rectangleIndices =  {
   0,  1,  2,   
   2,  3,  0,   // Front
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
  Sprite *gun;
  glm::vec3 position;

public:
  Player(Camera* cam, Sprite* gun) {
    this->cam = cam;
    this->gun = gun;

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

    if(InputHandler::keyPressed(GLFW_KEY_SPACE))
      this->gun->play_animation();

    auto delta = InputHandler::pullMouseDelta();
    this->cam->rotate(-delta.y, delta.x);
    this->cam->set_position(this->position);
  }
};

/*class Texture {
private:
  std::string uniform;
public:
  int width;
  int height;

  uint32_t texture;

  Texture(std::string path, GLenum format, bool flip = false) {
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

    this->uniform = "texture1";   // TODO change
  }

  *Texture() {
    glDeleteTextures(1, &this->texture);
  }

  void activate() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    //this->shader->run();
  }
};*/

/*class Animation {
private:
  //std::vector<Texture*> frames;
  //Texture* atlas;
  std::vector<glm::vec4> UVs;
  float frame_time;   // in fps
  
  bool started_playing;
  bool finished_playing;

  int current_frame;

  float timer;
public:
  Animation(std::vector<glm::vec4> UVs) {
    this->frame_time = 0.04;
    this->UVs = UVs;

    this->started_playing = false;
    this->current_frame = 0;

    this->timer = 0.0f;
  }

  glm::vec4 getUV() {
    return this->UVs[current_frame];
  }

  void play() {
    this->started_playing = true;
    this->finished_playing = false;
  }

  void update(float dt, bool cycle = false) {
    if (!this->started_playing)
      return;
  
    this->timer += dt;
    if (timer >= this->frame_time) {
      timer = 0.0f;
      current_frame = (current_frame + 1) % this->UVs.size();

      if (current_frame == 0 && this->is_playing()) {
        this->finished_playing = true;
        this->started_playing = false;
      }
    }
  }

  bool is_playing() {
    if (this->started_playing && !this->finished_playing)
      return true;
    return false;
  }
};*/


// Sprites live in the camera space not world space
/*class Sprite {
  Shader *shader;
  Texture *texture;

  //std::vector<Animation> animations;
  glm::vec4 uv;
  Mesh* mesh;
  glm::vec2 position;

public:
  Animation* animation;

  Sprite(Mesh* mesh, Texture* texture, Shader* shader, glm::vec2 position = {0, 0}, glm::vec4 uv = {0.0, 0.0, 1.0, 1.0}) {
  //rectangle.move_to(glm::vec3(0.2f, -0.6f, 0.0f));
    this->texture = texture;
    this->shader = shader;
    this->mesh = mesh;
    this->uv = uv;
    this->position = position;
    this->animation = nullptr;
  }

  void add_animation(Animation* animation) {
    this->animation = animation;
  }

  void play_animation() {
    if (animation != nullptr) {
      animation->play();
    }
  }

  void update(float dt) {
    if (animation != nullptr) {
      animation->update(dt);
      this->uv = animation->getUV();
    }
  }

  void draw() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, {this->position.x, this->position.y, 0.0f});

    this->texture->activate();
    this->shader->run();

    this->shader->set_uniform("uv", this->uv.x, this->uv.y, this->uv.z, this->uv.w);

    this->shader->set_uniformMat("model", model);
    this->mesh->draw();
  }
};*/

static Material* materialMap[MAX_MATERIALS];

void framebuffer_size_callback(GLFWwindow*, int width, int height) {
  glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow*, double xpos, double ypos) {
  InputHandler::handleMouseMove(xpos, ypos);
}


std::vector<Object> build_map(int map[MAP_MAX_X][MAP_MAX_Z], 
                              Mesh* mesh) {
                              //Material* wallMaterial,
                              //Material* floorMaterial,
                              //Material* topMaterial) {
  std::vector<Object> cubes;

  for (int x = 0; x < MAP_MAX_X; x++) {
    for (size_t z = 0; z < MAP_MAX_Z; z++) {
      Object cube;
      cube.add_mesh(mesh);
      cube.add_material(materialMap[map[x][z] - 1]);

      if (map[x][z] == 2) {
        auto cubePosition = glm::vec3(x + 0.5, -1.0f, z + 0.5);

        cube.move_to(cubePosition);
        cubes.emplace_back(cube);

        Object topCube;
        topCube.move_to(glm::vec3(x+0.5, 1.0f, z+0.5f));

        topCube.add_mesh(mesh);
        topCube.add_material(materialMap[MAX_MATERIALS-1]);

        cubes.emplace_back(topCube);
        //cube.add_mesh(mesh);
        //cube.add_material(wallMaterial);

      } else {
        auto cubePosition = glm::vec3(x + 0.5, 0.0f, z + 0.5);
        //cube.add_material(materialMap[map[x][z] - 1]);
        cube.move_to(cubePosition);

        cubes.emplace_back(cube);
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
  Shader player_shader(srcs[1]);

  scene.add_shader(&shader);
  scene.add_shader(&player_shader);

  /* -----------------------------------
  load textures and create materials
  --------------------------------------*/
  Material wallMaterial = Material(&shader);

  //my_material.add_texture("res/textures/face.png", "texture1");
  //my_material.add_texture("res/textures/container.jpg", "texture2");
  wallMaterial.add_texture("res/textures/wall.png", "texture1");
  wallMaterial.map_uniforms();

  Material floorMaterial = Material(&shader);

  floorMaterial.add_texture("res/textures/floor.png", "texture1");
  floorMaterial.map_uniforms();

  Material topMaterial = Material(&shader);

  topMaterial.add_texture("res/textures/grey.png", "texture1");
  topMaterial.map_uniforms();

  materialMap[0] = &wallMaterial;
  materialMap[1] = &floorMaterial;
  materialMap[9] = &topMaterial;


  Texture shotgunAtlas("res/textures/revolver.png", GL_RGBA);
  player_shader.set_uniformI("texture1", shotgunAtlas.texture);


  std::vector<glm::vec4> uvs = {
    glm::vec4(0.2f, 0.58f, 0.4f, 1.0f),
    glm::vec4(0.4f, 0.62f, 0.6f, 1.0f),
    glm::vec4(0.6f, 0.6f, 0.8f, 1.0f),
    glm::vec4(0.0f, 0.6f, 0.20f, 1.0f),
  };

  /*std::vector<glm::vec4> uvs = {
    glm::vec4(0.0f, 0.68f, 0.15f, 1.0f),
    glm::vec4(0.14f, 0.73f, 0.32f, 1.0f),
    glm::vec4(0.32f, 0.73f, 0.48f, 1.0f),
    glm::vec4(0.48f, 0.73f, 0.63f, 1.0f),
    glm::vec4(0.632f, 0.73f, 0.78f, 1.0f),
    glm::vec4(0.78f, 0.73f, 1.0f, 1.0f),
  };*/

  Animation shotgunAnimation(uvs);


  /* --------------------------
  Create objects in the scene
  -----------------------------*/
  Mesh cubeMesh(cubeModel, cubeIndices);
  Mesh rectangleMesh(rectangleModel, rectangleIndices);

  std::cout << cubeMesh.EBO << std::endl;
  std::cout << rectangleMesh.EBO << std::endl;

  Map::init(gameMap);

  auto cubes = build_map(gameMap, 
                        &cubeMesh);


  Sprite gunSprite(&rectangleMesh, 
                  &shotgunAtlas, 
                  &player_shader, 
                  glm::vec2(0.2f, -0.6f), 
                  uvs[0]);

  gunSprite.add_animation(&shotgunAnimation);
  scene.add_sprite(&gunSprite);


  for (size_t i = 0; i < cubes.size(); i++) {
    scene.add_object(&cubes[i]);
  }

  Player player(&cam, &gunSprite);

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
