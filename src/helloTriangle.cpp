#include <helloTriangle.h>  

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp> // value_ptr


ShaderReader* helloTriangle::activeShader = nullptr;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);  

helloTriangle::helloTriangle(int sizeX, int sizeY) : dimensionX(sizeX), dimensionY(sizeY) {
  glfwInit();
  // Set GLFW version to 3.3 since we want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
  initGLAD();
}

helloTriangle::~helloTriangle() {

}

int helloTriangle::initGLAD() { 
  // Init glad function pointers before calling any OpenGL functions
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return -1;
  }  
  return 0;
}

int helloTriangle::openWindow() {
  // Create a window context
  renderWindow = glfwCreateWindow(dimensionX, dimensionY, "OpenGL Playground", NULL, NULL);
  if (renderWindow == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(renderWindow);
  glfwSetFramebufferSizeCallback(renderWindow, framebuffer_size_callback);
  
  initGLAD();
  glViewport(0, 0, dimensionX, dimensionY);

  initializeRendering();
}

void helloTriangle::initializeRendering() {
  // Create a shader linker program and attach the shaders
  ShaderReader shader("res/shaders/Vertex/VertTextTrans.glsl", "res/shaders/Fragment/FragTexture.glsl");
  shader.use();

  // Create a plane
  Plane myPlane;
    
  // Render loop
  while(!glfwWindowShouldClose(renderWindow)) {
    // read input
    closeWindow();
    setWireFrame();
    setFill(); 

    // Process graphics
    glClearColor(0.41f, 0.51f, 0.31f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Translation
    myPlane.draw();
    auto scalar = getTimedCoefficient();
    myPlane.scaleEven(scalar);
    

    // Render
    glfwSwapBuffers(renderWindow);
    glfwPollEvents();    
  }
  
  // glDeleteVertexArrays(1, &VAO);
  // glDeleteBuffers(1, &VBO);
  // glDeleteProgram(shader.shaderProgram);
}

float helloTriangle::getTimedCoefficient() {
  // Derive a sin from 
  return (sin(glfwGetTime()) / 2.0f) + 0.5f;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    std::cout << "resized" << std::endl;
    glViewport(0, 0, width, height);
} 
void helloTriangle::setWireFrame(){
  if(glfwGetKey(renderWindow, GLFW_KEY_W) == GLFW_PRESS){
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
}

void helloTriangle::setFill(){
  if(glfwGetKey(renderWindow, GLFW_KEY_F) == GLFW_PRESS){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

void helloTriangle::closeWindow() {
    if(glfwGetKey(renderWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(renderWindow, true);
}
