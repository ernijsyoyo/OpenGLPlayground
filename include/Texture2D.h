#pragma once

#include <string>
#include <glad.h>
#include <iostream>


class Texture2D
{
private:
  unsigned int texture;
  int width;
  int height;
  int nrChannels;
  unsigned char *data;
public:
  Texture2D(std::string path, bool flipUponLoad);
  ~Texture2D();
  void load();
  unsigned int getTextureId();
};