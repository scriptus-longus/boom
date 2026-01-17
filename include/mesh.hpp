#pragma once
#include <vector>

class Mesh {
private:
  size_t n_elements;
public:
  uint32_t VAO, VBO, EBO;
  Mesh(std::vector<float>, std::vector<uint32_t>);

  ~Mesh();

  void draw();
};
