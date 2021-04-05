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
  // vertex vert_1(-0.5f, -0.5f, 0.0f);
  // vertex vert_2(0.5f, -0.5f, 0.0f);
  // vertex vert_3(0.5f, 0.0f, 0.0f);
  // polygon triangle(&vert_1, &vert_2, &vert_3);

  // Get and create shader holders
  auto vertexShader = Shaders::getExampleVertShader();
  auto fragShader = Shaders::getExampleFragmentShader();
  auto vertexShader_C_STR = vertexShader.c_str();
  auto fragShader_C_STR = fragShader.c_str();
  
  // Create vertex/fragment shader objects
  auto vertexShaderRef = glCreateShader(GL_VERTEX_SHADER);
  auto fragShaderRef = glCreateShader(GL_FRAGMENT_SHADER);
  
  // Set shader source code and compile
  glShaderSource(vertexShaderRef, 1, &vertexShader_C_STR, NULL);
  glShaderSource(fragShaderRef, 1, &fragShader_C_STR, NULL);
  glCompileShader(vertexShaderRef);
  glCompileShader(fragShaderRef);
  
  // Check for runtime compilation errors
  Shaders::checkCompileTimeVertexErrors(vertexShaderRef);
  Shaders::checkCompileTimeFragErrors(fragShaderRef);

  // Create a shader linker program and attach the shaders
  auto shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShaderRef);
  glAttachShader(shaderProgram, fragShaderRef);
  glLinkProgram(shaderProgram);
  Shaders::checkLinkTimeErrors(shaderProgram);
  glUseProgram(shaderProgram);

  glDeleteShader(vertexShaderRef);
  glDeleteShader(fragShaderRef);

  // Specify triangle vertices
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };  

  // Generate Vertex Buffer Object, VBO is buffer access ID
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);  
  glGenBuffers(1, &VBO); 
  // Generate and bind Vertex Array Object
  glBindVertexArray(VAO);
  
  // Bind Vertex Buffer Object to a GL ARRAY BUFFER. All future GL ARRAY Buffer calls for are given to VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // Fill buffer with data
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);  

  while(!glfwWindowShouldClose(window)) {
    // read input
    closeWindow(window);

    // Process graphics
    glClearColor(0.4f, 0.5f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Render
    glfwSwapBuffers(window);
    glfwPollEvents();    
  }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    std::cout << "resized" << std::endl;
    glViewport(0, 0, width, height);
} 

void helloTriangle::closeWindow(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
