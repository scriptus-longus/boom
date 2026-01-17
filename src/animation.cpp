#include <glm/glm.hpp>

#include <string>
#include <iostream>
#include <vector>

#include "animation.hpp"

Animation::Animation(std::vector<glm::vec4> UVs) {
  this->frame_time = 0.04;
  this->UVs = UVs;

  this->started_playing = false;
  this->current_frame = 0;

  this->timer = 0.0f;
}

glm::vec4 Animation::getUV() {
  return this->UVs[current_frame];
}

void Animation::play() {
  this->started_playing = true;
  this->finished_playing = false;
}

void Animation::update(float dt, bool cycle) {
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

bool Animation::is_playing() {
  if (this->started_playing && !this->finished_playing)
    return true;
  return false;
}

