#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <glad/glad.h>
#include <ShaderReader.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Mesh.h>
#include <math.h>
#include <Texture2D.h>
#include <memory>


class helloTriangle
{
private:
  /**
   * @brief Pixels in X
   * 
   */
  const int dimensionX;
  
  /**
   * @brief Pixels in Y
   * 
   */
  const int dimensionY;

  /**
   * @brief Main window on which the graphics are rendered
   * 
   */
  GLFWwindow* renderWindow;

  /**
   * @brief Initializes pointers to OpenGL functions
   * 
   * @return int 
   */
  int initGLAD();
  
  /**
   * @brief Closes the render window
   * 
   */
  void closeWindow();
  
  /**
   * @brief Sets rendering mode to wire frame
   * 
   */
  void setWireFrame();
  
  /**
   * @brief Sets rendering mode to filled
   * 
   */
  void setFill();

  /**
   * @brief Main function for starting the rendering
   * 
   */
  void initializeRendering();

  /**
   * @brief Get a sine of the current time
   * 
   * @return float
   */
  float getTimedCoefficient();

public:
  helloTriangle(int sizeX, int sizeY);
  ~helloTriangle();
  int openWindow();
  static ShaderReader* activeShader;
};

#endif