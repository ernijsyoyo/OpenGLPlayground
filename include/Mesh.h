#include <vector>
#include <stdint.h>

class Mesh
{
private:
  std::vector<float> vertices;
  std::vector<unsigned int> polygons;
public:
  Mesh(std::vector<float> vertices, std::vector<unsigned int> polygons);
  ~Mesh();
  std::vector<float> getVertices();
  std::vector<unsigned int> getPolygons();
  float* C_getVertices();
  unsigned int* C_getPolygons();
};
