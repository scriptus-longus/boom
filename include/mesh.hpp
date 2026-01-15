#pragma once
#include <vector>

class Mesh {
private:
  size_t n_elements;
  uint32_t VAO, VBO, EBO;
public:
  Mesh(std::vector<float>, std::vector<uint32_t>);

  ~Mesh();

  void draw();
};
