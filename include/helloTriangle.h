#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Shaders.h>
#include <Mesh.h>

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
public:
  helloTriangle(int sizeX, int sizeY);
  ~helloTriangle();
  int openWindow();
};