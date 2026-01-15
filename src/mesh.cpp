#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>

#include "mesh.hpp"

Mesh::Mesh(std::vector<float> vertices, std::vector<uint32_t> indices) {
  glGenVertexArrays(1, &this->VAO);
  glGenBuffers(1, &this->VBO);
  glGenBuffers(1, &this->EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

  /*std::cout << vertices << std::endl;
  std::cout << cubeModel << std::endl << std::endl;

  std::cout << sizeof(vertices) << std::endl;
  std::cout << sizeof(cubeModel) << std::endl << std::endl;*/
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

  // set vertex attributes 
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);


  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  this->n_elements = indices.size();
}

Mesh::~Mesh() {
  std::cout << "Deleting cube" << std::endl;
  glDeleteVertexArrays(1, &this->VAO);
  glDeleteVertexArrays(1, &this->VBO);
  glDeleteVertexArrays(1, &this->EBO);
}

void Mesh::draw() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
  glDrawElements(GL_TRIANGLES, this->n_elements, GL_UNSIGNED_INT, 0);
}
