#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class helloTriangle
{
private:
  /* data */
public:
  helloTriangle();
  ~helloTriangle();
  void processInput(GLFWwindow *window);
  int openWindow();
  void printHello();
};