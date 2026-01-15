#pragma once
#include <glm/glm.hpp>

#include <string>


class Camera {
private:
  glm::vec3 position;
  glm::vec3 camFront;
  glm::vec3 camUp;

  float pitch;
  float yaw;

  void update_rotation();

public:
  Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp = glm::vec3(0.0, 1.0f, 0.0f));

  /*
  functions to rotate the camera
  */
  void rotate(float, float, bool free=false);

  void set_rotation(float, float);

  /*
  Functions to move the camera
  */
  void move(glm::vec3);
  /*
  void move_front(float);

  void move_right(float);*/

  void set_position(glm::vec3);
  
  // simple offset movement
  void move_xoffset(float);

  void move_yoffset(float);

  void move_zoffset(float);

  glm::vec3 get_position();

  glm::vec3 get_front();

  glm::vec3 get_up();

  // get the view matrix
  glm::mat4 get_lookAt();

  glm::mat4 get_projection(int, int);
};
