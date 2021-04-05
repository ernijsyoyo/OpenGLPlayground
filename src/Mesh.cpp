#include <Mesh.h>

Mesh::Mesh(std::vector<float> _vertices, std::vector<unsigned int> _polygons) {
  this->vertices = _vertices;
  this->polygons = _polygons;
}

Mesh::~Mesh() {

}

std::vector<float> Mesh::getVertices() {
  return this->vertices;
}

std::vector<unsigned int> Mesh::getPolygons() {
  return this->polygons;
}

float* Mesh::C_getVertices() {
  return &Mesh::vertices.at(0);
}

unsigned int* Mesh::C_getPolygons() {
  return &Mesh::polygons.at(0);
}