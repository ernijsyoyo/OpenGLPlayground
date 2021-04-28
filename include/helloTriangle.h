#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Shaders.h>
#include <Mesh.h>
#include <math.h>
#include <ShaderReader.h>
#include <Texture2D.h>


class helloTriangle
{
private:
  const int dimensionX;
  const int dimensionY;

  /* Initializes OpenGL function pointers */
  int initGLAD();
  /* Reads user input for closing the window*/
  void closeWindow(GLFWwindow *window);
  void setWireFrame(GLFWwindow *window);
  void setFill(GLFWwindow *window);
  /* Initializes the render loop*/
  void startRendering(GLFWwindow* window);
  float getTimedCoefficient();
public:
  helloTriangle(int sizeX, int sizeY);
  ~helloTriangle();
  int openWindow();
};

#endif