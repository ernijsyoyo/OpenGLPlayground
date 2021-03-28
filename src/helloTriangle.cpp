#include <helloTriangle.h>


helloTriangle::helloTriangle(){
  glfwInit();
  // Set GLFW version to 3.3 since we want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

}

helloTriangle::~helloTriangle(){

}

int helloTriangle::openWindow(){
  // Create a window context
  GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Playground", NULL, NULL);
  if (window == NULL)
  {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
  }
  glfwMakeContextCurrent(window);

  // Init glad before calling any OpenGL functions
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return -1;
  }  
  glViewport(0, 0, 800, 600);
  while(!glfwWindowShouldClose(window))
  {
      processInput(window);

      glfwSwapBuffers(window);
      glfwPollEvents();    
  }

}

void helloTriangle::processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void helloTriangle::printHello(){
  std::cout << "Hello Cheese" << std::endl;
}