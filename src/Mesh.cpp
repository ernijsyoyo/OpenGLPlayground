#include <Mesh.h>
#include <helloTriangle.h>

Mesh::Mesh() {

}

Mesh::~Mesh() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  
}

std::vector<float> Mesh::getVertices() {
  return this->vertices;
}

std::vector<unsigned int> Mesh::getPolygons() {
  return this->faces;
}

float* Mesh::C_getVertices() {
  return &Mesh::vertices.at(0);
}

float* Mesh::C_getMeshInfo() {
  return &Mesh::meshInformation[0];
}

unsigned int* Mesh::C_getPolygons() {
  return &Mesh::faces[0];
}

void Mesh::draw() {

}

Plane::Plane() {
  transformMatrix = glm::mat4(1.0f);
  float vertices[] = {
    // positions       
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f 
  };
  unsigned int indices[] = {  // note that we start from 0!
    0, 3, 1,   // first triangle
    3, 2, 1
  };
  float colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f
  };
  float textureCoords[] = {
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f 
  };

  
  this->vertices.assign(vertices, vertices + sizeof(vertices)/sizeof(float));
  this->color.assign(colors, colors + sizeof(colors) / sizeof(float));
  this->textureCoords.assign(textureCoords, textureCoords + sizeof(textureCoords)/sizeof(float));
  this->faces.assign(indices, indices + sizeof(indices)/sizeof(unsigned int));
  fillMeshInformation();
  fillBuffersOpenGL();
}

Plane::~Plane() {
  
}

void Plane::fillBuffersOpenGL() { 
  // Texturing
  Texture2D texture("res/textures/fruitsconv.jpg", true);
  texture.load();
  Texture2D texture2("res/textures/frida4conv.jpg", true);
  texture2.load();
  
  helloTriangle::activeShader->setInt("texture1", 0);
  helloTriangle::activeShader->setInt("texture2", 1);
  
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture.getTextureId());
  
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture2.getTextureId());

  // Generate Vertex Buffer Object, VBO is buffer access ID
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);  
  glGenBuffers(1, &VBO); 
  glGenBuffers(1, &EBO);
  
  // Generate and bind Vertex Array Object
  glBindVertexArray(VAO);
  auto meshInfo = meshInformation.size() * sizeof(float);
  // Bind Vertex Buffer Object to a GL ARRAY BUFFER. All future GL ARRAY Buffer calls for are given to VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, meshInformation.size() * sizeof(float), meshInformation.data(), GL_STATIC_DRAW);
  
  // Copy index array into the buffer
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(unsigned int), faces.data(), GL_STATIC_DRAW);
  
  // Fill buffer with data  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);  
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);  
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);  
}


void Plane::fillMeshInformation(){
  // TODO translate this into vertex datastructures
  auto verticesSize = vertices.size(); // 3 per loop
  auto colorSize    = color.size();  // 3 per loop
  auto textureSize  = textureCoords.size(); // 2 per loop
  auto totalSize = verticesSize + colorSize + textureSize;
  assert(totalSize % 8 == 0);
  meshInformation.reserve(totalSize);
  
  auto vertexCounter = 0;
  auto colorCounter = 0;
  auto textureCounter = 0;
  for (size_t i = 0; i < totalSize; i+=8)
  {
    // Vertices
    meshInformation.push_back(vertices[vertexCounter]);
    meshInformation.push_back(vertices[vertexCounter + 1]);
    meshInformation.push_back(vertices[vertexCounter + 2]);
    vertexCounter += 3;

    // Colors
    meshInformation.push_back(color[colorCounter]);
    meshInformation.push_back(color[colorCounter + 1]);
    meshInformation.push_back(color[colorCounter + 2]);
    colorCounter += 3;

    // Texture coords
    meshInformation.push_back(textureCoords[textureCounter]);
    meshInformation.push_back(textureCoords[textureCounter + 1]);
    textureCounter += 2;
  }
}

void Plane::rotate(glm::mat4 transMatrix) {

}

void Plane::translate(glm::vec3 globalPosition) {
  transformMatrix = glm::translate(blankMatrix, globalPosition);
}

void Plane::scale(glm::vec3 scaleAmountXYZ) {
  transformMatrix = glm::scale(blankMatrix, scaleAmountXYZ);
}

void Plane::scaleEven(float coefficient) {
  scale(glm::vec3(coefficient, coefficient, coefficient));
}

void Plane::draw() {
  glBindVertexArray(VAO);
  helloTriangle::activeShader->setTransform("transform", transformMatrix);
  glDrawElements(GL_TRIANGLES, this->faces.size(), GL_UNSIGNED_INT, 0);
}