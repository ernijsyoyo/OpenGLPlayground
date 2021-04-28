#include <Mesh.h>

Mesh::Mesh(std::vector<float> _vertices, std::vector<unsigned int> _indices) {
  this->vertices = _vertices;
  this->indices = _indices;
}

Mesh::~Mesh() {

}

std::vector<float> Mesh::getVertices() {
  return this->vertices;
}

std::vector<unsigned int> Mesh::getIndices() {
  return this->indices;
}

float* Mesh::C_getVertices() {
  return &Mesh::vertices.at(0);
}

unsigned int* Mesh::C_getIndices() {
  return &Mesh::indices.at(0);
}

Plane::Plane(glm::vec3 pos, float scale) {
  // Specify triangle vertices
  float _vertices[] = {
    // positions          
     /* X                |    Y                 |   Z                 */     
     0.5f * scale + pos.x,  0.5f * scale + pos.y, 0.0f * scale + pos.z,   
     0.5f * scale + pos.x, -0.5f * scale + pos.y, 0.0f * scale + pos.z,   
    -0.5f * scale + pos.x, -0.5f * scale + pos.y, 0.0f * scale + pos.z, 
    -0.5f * scale + pos.x,  0.5f * scale + pos.y, 0.0f * scale + pos.z   
  };
  unsigned int _indices[] = {  // note that we start from 0!
    0, 3, 1,   // first triangle
    3, 2, 1    // second triangle
  };

  unsigned int _verticesSize = sizeof(_vertices) / sizeof(float);
  unsigned int _indicesSize = sizeof(indices) / sizeof(unsigned int);
  this->vertices.insert(this->vertices.end(),
                        &_vertices[0],
                        &_vertices[_verticesSize]);
  this->indices.insert(this->indices.end(),
                        &_indices[0],
                        &_indices[_indicesSize]);
}