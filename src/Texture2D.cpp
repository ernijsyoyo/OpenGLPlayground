#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture2D.h"


Texture2D::Texture2D(std::string path, bool flipUponLoad) {
  if(flipUponLoad) {
    stbi_set_flip_vertically_on_load(flipUponLoad);  
  }

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load and generate the texture
  data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);   
}

Texture2D::~Texture2D() {
    stbi_image_free(data);
}

void Texture2D::load() {
  if (data)
  {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
      std::cout << "Failed to load texture" << std::endl;
  }
}

unsigned int Texture2D::getTextureId() {
  return texture;
}
  
  
  