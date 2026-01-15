#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include <vector>
#include <math.h>

#include "camera.hpp"

void Camera::update_rotation() {
  glm::vec3 dir;
  dir.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
  dir.y = sin(glm::radians(this->pitch));
  dir.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

  this->camFront = glm::normalize(dir);

}

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp) {
  this->camPos = position;
  this->camFront = glm::normalize(target - position);

  this->camUp = worldUp; //glm::vec3(0.0f, 0.1f, 0.0f);


  this->pitch = glm::degrees(asin(camFront.y));
  this->yaw = glm::degrees(atan2(camFront.z, camFront.x));
}

/*
functions to rotate the camera
*/
void Camera::rotate(float pitch_offset, float yaw_offset, bool free) {
  this->pitch += pitch_offset;
  this->yaw += yaw_offset;

  if (!free) {
    if (this->pitch > 89.0f)
      this->pitch = 89.0f;
    if (this->pitch < -89.0f)
      this->pitch = -89.0f;
  }

  this->update_rotation();
}

void Camera::set_rotation(float pitch, float yaw) {
  this->pitch = pitch;
  this->yaw = yaw;

  this->update_rotation();
}

/*
Functions to move the camera
*/
void Camera::move(glm::vec3 dir) {
  this->camPos += dir;
}

void Camera::move_front(float v) {
  this->camPos += glm::normalize(glm::vec3(this->camFront.x, 0, this->camFront.z)) * v;
}

void Camera::move_right(float v) {
  this->camPos += glm::normalize(glm::cross(this->camFront, this->camUp)) * v;
}

void Camera::set_position(glm::vec3 pos) {
  this->camPos = pos;
}

// simple offset movement
void Camera::move_xoffset(float xoffset) {
  this->camPos.x += xoffset;
}

void Camera::move_yoffset(float yoffset) {
  this->camPos.y += yoffset;
}

void Camera::move_zoffset(float zoffset) {
  this->camPos.z += zoffset;
}

glm::vec3 Camera::get_pos() {
  return this->camPos;
}

glm::vec3 Camera::get_front() {
  return this->camFront;
}

glm::vec3 Camera::get_up() {
  return this->camUp;
}

// get the view matrix
glm::mat4 Camera::get_lookAt() {
  return glm::lookAt(this->camPos, this->camPos + this->camFront, this->camUp);
}

glm::mat4 Camera::get_projection(int width, int height) {
  return glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
}
