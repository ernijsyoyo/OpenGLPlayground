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

unsigned int Shaders::getVertShader(Shaders::vertShaders vertexShadeMode) {
  // Determine which shader to work with
  const char* vertexShaderSrc;
  switch (vertexShadeMode) {
    case Shaders::vertShaders::dfltVertShdr:
      vertexShaderSrc = Shaders::ExampleVertShader.c_str();
      break;
  }

  // Get shader source code and create blank vertex shader
  auto vertexShaderRef = glCreateShader(GL_VERTEX_SHADER);

  // Set shader source code and compile
  glShaderSource(vertexShaderRef, 1, &vertexShaderSrc, NULL);
  glCompileShader(vertexShaderRef);

  // Check for compile errors and return
  Shaders::checkShaderCompileTimeErrors(vertexShaderRef, "VERTEX");
  return vertexShaderRef;
}

unsigned int Shaders::getFragShader(Shaders::fragShaders fragmentShaderMode) {
  // Determine which shader to work with
  const char* fragShaderSrc;
  switch (fragmentShaderMode) {
    case Shaders::fragShaders::dfltFragShdr:
      fragShaderSrc = Shaders::ExampleFragShader.c_str();
      break;
  }
  
  // Get shader source code and create blank vertex shader
  auto fragShaderRef = glCreateShader(GL_FRAGMENT_SHADER);
  
  // Set shader source code and compile
  glShaderSource(fragShaderRef, 1, &fragShaderSrc, NULL);
  glCompileShader(fragShaderRef);

  // Check for compile errors and return
  Shaders::checkShaderCompileTimeErrors(fragShaderRef, "FRAGMENT");
  return fragShaderRef;
}

unsigned int Shaders::getExampleLinkProgram(Shaders::vertShaders vertexShadeMode,
                                            Shaders::fragShaders fragmentShaderMode) {
  // Get shaders
  unsigned int vertexShader = Shaders::getVertShader(vertexShadeMode);
  unsigned int fragmentShader = Shaders::getFragShader(fragmentShaderMode);
  
  // Create a shader linker program and attach the shader references
  auto shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  
  // Check for errors and clean-up unused shaders
  Shaders::checkLinkTimeErrors(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  
  return shaderProgram;
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