#pragma once
#include <glm/glm.hpp>

#include <cstring>
#include <string>
#include <iostream>

#define MAP_MAX_X 6
#define MAP_MAX_Z 11

class Map {
private:
  static inline int map[MAP_MAX_X][MAP_MAX_Z];/* = {
      {1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0},
      {1, 2, 0, 1, 0, 0, 1, 0, 1, 0, 0},
      {1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0},
      {1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
      {0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0},
      {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
    };*/
  static inline glm::vec3 start_pos;

public:
  static void init(int gameMap[MAP_MAX_X][MAP_MAX_Z]) {
    std::memcpy(map, gameMap, MAP_MAX_X*MAP_MAX_Z*sizeof(int));

    for (int x = 0; x < MAP_MAX_X; x++) {
      for (size_t z = 0; z < MAP_MAX_Z; z++) {
        if (map[x][z] == 1) {
          start_pos = {-x, 0.0f, z};
        }
      }
    }
  }

  static bool is_free(float x, float z) {
    int cx = int(floor(x));
    int cz = int(floor(z));

    if (cx > MAP_MAX_X || cz  > MAP_MAX_Z || cx < 0 || cz < 0) 
      return true;

    return map[cx][cz] != 1;
  }

  static bool is_walkable(float x, float z) {
    int x_upper = x + 0.2;
    int x_lower = x - 0.2;

    int z_upper = z + 0.2;
    int z_lower = z - 0.2;
   
    // check if point is off map
    

    /*if (x > MAP_MAX_X || z  > MAP_MAX_Z || x < 0 || z < 0) 
      return true;*/

    return is_free(x_upper, z_upper) &&
           is_free(x_upper, z_lower) &&
           is_free(x_lower, z_upper) &&
           is_free(x_lower, z_lower);
  }

  static glm::vec3 get_start_pos() {
    return start_pos;
  }
};
