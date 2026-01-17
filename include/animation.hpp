#pragma once
#include <glm/glm.hpp>

#include <string>
#include <iostream>
#include <vector>


class Animation {
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
  Animation(std::vector<glm::vec4> UVs);

  glm::vec4 getUV();

  void play();

  void update(float dt, bool cycle = false);

  bool is_playing();
};

