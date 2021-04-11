#include <Shaders.h>

/* Vertex Shaders */
const std::string Shaders::ExampleVertShader = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "out vec4 vertexColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
    "}\0";
const std::string Shaders::VertShaderColors = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "uniform float offset;\n"
    "out vec3 vertexColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.xyz + offset, 1.0);\n"
    "   vertexColor = aColor;\n"
    "}\0";

/* FragmentShaders */
const std::string Shaders::ExampleFragShader = "#version 330 core \n"
    "in vec3 vertexColor;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(vertexColor, 1.0f);\n"
    "}\0";

const std::string Shaders::FragShader_Uniform = "#version 330 core \n"
    "uniform vec4 controllableColor;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = controllableColor;\n"
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
    case Shaders::vertShaders::colorsInVertexArray:
      vertexShaderSrc = Shaders::VertShaderColors.c_str();
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
    case Shaders::fragShaders::fragShader_Uniform:
      fragShaderSrc = Shaders::FragShader_Uniform.c_str();
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