#pragma once

#include <vector>
#include <stdint.h>
#include <iostream>
#include <glad/glad.h>

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp> // value_ptr


class Mesh
{
protected:
  unsigned int VBO, VAO, EBO;
  std::vector<unsigned int> faces;
  std::vector<float> vertices;
  std::vector<float> color;
  std::vector<float> textureCoords;
  std::vector<float> meshInformation;
public:
  Mesh();
  ~Mesh();
  std::vector<float> getVertices();
  std::vector<unsigned int> getPolygons();
  virtual void draw();
  float* C_getVertices();
  float* C_getMeshInfo();
  unsigned int* C_getPolygons();
};

class Plane : Mesh
{
private:
  /**
   * @brief Object's transform matrix
   * 
   */
  glm::mat4 transformMatrix;
  const glm::mat4 blankMatrix = glm::mat4(1.0f);

public:
  Plane();
  ~Plane();

  void fillBuffersOpenGL();

  /**
   * @brief Combines vertices, texture coords and color into a single vector
   * 
   */
  void fillMeshInformation();

  /**
   * @brief Move the object to a given global position
   * 
   * @param transMatrix 
   */
  void translate(glm::vec3 transMatrix);

  /**
   * @brief Rotate an object
   * 
   * @param transMatrix 
   */
  void rotate(glm::mat4 transMatrix);
  
  /**
   * @brief Scale an object on an axis-per-axis basis
   * 
   * @param transMatrix 
   */
  void scale(glm::vec3 transMatrix);
  
  /**
   * @brief Scale the object evenly accross all axis
   * 
   * @param coefficient Scaling coefficient
   */
  void scaleEven(float coefficient);

  /**
   * @brief Issue an OpenGL draw call.
   * 
   */
  void draw() override;
};

