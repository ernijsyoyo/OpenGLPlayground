#include <Shaders.h>

/* Member Variables */
const std::string Shaders::ExampleVertShader = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const std::string Shaders::ExampleFragShader = "#version 330 core \n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";


/* Functions */
Shaders::Shaders() {

}

Shaders::~Shaders(){

}

unsigned int Shaders::getExampleVertShader() {
  // Get shader source code and create blank vertex shader
  auto vertexShaderSrc = Shaders::ExampleVertShader.c_str();
  auto vertexShaderRef = glCreateShader(GL_VERTEX_SHADER);

  // Set shader source code and compile
  glShaderSource(vertexShaderRef, 1, &vertexShaderSrc, NULL);
  glCompileShader(vertexShaderRef);

  // Check for compile errors and return
  Shaders::checkShaderCompileTimeErrors(vertexShaderRef, "VERTEX");
  return vertexShaderRef;
}

unsigned int Shaders::getExampleFragmentShader() {
  // Get shader source code and create blank vertex shader
  auto fragShaderSrc = Shaders::ExampleFragShader.c_str();
  auto fragShaderRef = glCreateShader(GL_FRAGMENT_SHADER);
  
  // Set shader source code and compile
  glShaderSource(fragShaderRef, 1, &fragShaderSrc, NULL);
  glCompileShader(fragShaderRef);

  // Check for compile errors and return
  Shaders::checkShaderCompileTimeErrors(fragShaderRef, "FRAGMENT");
  return fragShaderRef;
}

void Shaders::checkShaderCompileTimeErrors(unsigned int shaderId, std::string shaderType){
  int  success;
  char infoLog[512];
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

  if(!success) {
      glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::" << shaderType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
}

void Shaders::checkLinkTimeErrors(unsigned int linkProgramID) {
  int  success;
  char infoLog[512];
  glGetProgramiv(linkProgramID, GL_LINK_STATUS, &success);
  if(!success) {
    glGetProgramInfoLog(linkProgramID, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::LINK_PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
}