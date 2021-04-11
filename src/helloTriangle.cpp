#include <helloTriangle.h>
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
  return 0;
}

int helloTriangle::openWindow() {
  // Create a window context
  GLFWwindow* window = glfwCreateWindow(dimensionX, dimensionY, "OpenGL Playground", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  
  // Init glad function pointers before calling any OpenGL functions
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return -1;
  }  
  glViewport(0, 0, dimensionX, dimensionY);

  startRendering(window);
}

void helloTriangle::startRendering(GLFWwindow* window) {
  // Create a shader linker program and attach the shaders
  auto vertShaderMode = Shaders::vertShaders::dfltVertShdr;
  auto fragShaderMode = Shaders::fragShaders::fragShader_Uniform;
  auto shaderProgram = Shaders::getExampleLinkProgram(vertShaderMode, fragShaderMode);
  glUseProgram(shaderProgram);

  // Specify triangle vertices
  float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
  };
  
  unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
  }; 

  // Generate Vertex Buffer Object, VBO is buffer access ID
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);  
  glGenBuffers(1, &VBO); 
  glGenBuffers(1, &EBO);
  
  // Generate and bind Vertex Array Object
  glBindVertexArray(VAO);
  
  // Bind Vertex Buffer Object to a GL ARRAY BUFFER. All future GL ARRAY Buffer calls for are given to VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  // Copy index array into the buffer
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  
  // Fill buffer with data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);  

  while(!glfwWindowShouldClose(window)) {
    // read input
    closeWindow(window);
    setWireFrame(window);
    setFill(window);

    int vertexColorLocation = glGetUniformLocation(shaderProgram, "controllableColor");
    glUseProgram(shaderProgram);
    auto coefficient = helloTriangle::getTimedCoefficient();
    glUniform4f(vertexColorLocation, 0.0f, coefficient, coefficient, 1.0f);

    // Process graphics
    glClearColor(0.41f, 0.51f, 0.31f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Render
    glfwSwapBuffers(window);
    glfwPollEvents();    
  }
  
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);
}

float helloTriangle::getTimedCoefficient() {
  // Derive a sin from 
  return (sin(glfwGetTime()) / 2.0f) + 0.5f;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    std::cout << "resized" << std::endl;
    glViewport(0, 0, width, height);
} 
void helloTriangle::setWireFrame(GLFWwindow *window){
  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
}

void helloTriangle::setFill(GLFWwindow *window){
  if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

void helloTriangle::closeWindow(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
