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

const std::string Shaders::getExampleVertShader() {
  return Shaders::ExampleVertShader;
}

const std::string Shaders::getExampleFragmentShader() {
  return Shaders::ExampleFragShader;
}

void Shaders::checkCompileTimeVertexErrors(unsigned int shaderId){
  int  success;
  char infoLog[512];
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

  if(!success) {
      glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
}

void Shaders::checkCompileTimeFragErrors(unsigned int shaderId){
  int  success;
  char infoLog[512];
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

  if(!success) {
      glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
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