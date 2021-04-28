#include <vector>
#include <stdint.h>
#include <vec3.hpp>


class Mesh
{
protected:
  glm::vec3 position;
  std::vector<float> vertices;
  std::vector<unsigned int> indices;
public:
  Mesh(std::vector<float> vertices, std::vector<unsigned int> indices);
  ~Mesh();
  std::vector<float> getVertices();
  std::vector<unsigned int> getIndices();
  float* C_getVertices();
  unsigned int* C_getIndices();
};

class Plane : Mesh
{
private:
  /* data */
public:
  Plane(glm::vec3 pos, float sizeScalar);
  ~Plane();
};

class Cube : Mesh
{
private:
  /* data */
public:
  Cube(glm::vec3 pos, float sizeScaler);
  ~Cube();
};

class Sphere : Mesh
{
private:
  /* data */
public:
  Sphere(glm::vec3 pos, float sizeScaler);
  ~Sphere();
};



