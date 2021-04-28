#include "ShaderReader.h"
ShaderReader::~ShaderReader(){

}

ShaderReader::ShaderReader(const char* vertexPath, const char* fragmentPath) {
    // 1. retrieve the vertex/fragment source code from filePath
    vertexShaderPath = vertexPath;
    fragmentShaderPath = fragmentPath;
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();		
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();		
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    vShaderCode = vertexCode.c_str();
    fShaderCode = fragmentCode.c_str();
    compileShaderProgram();
}

void ShaderReader::compileShaderProgram() {
  // Get shader source code and create blank vertex shader
  auto vertexShaderRef = glCreateShader(GL_VERTEX_SHADER);
  auto fragShaderRef = glCreateShader(GL_FRAGMENT_SHADER);

  // Set shader source code and compile
  glShaderSource(vertexShaderRef, 1, &vShaderCode, NULL);
  glShaderSource(fragShaderRef, 1, &fShaderCode, NULL);
  glCompileShader(vertexShaderRef);
  glCompileShader(fragShaderRef);

  // Check for compile errors and return
  checkShaderCompileTimeErrors(vertexShaderRef, "VERTEX", vertexShaderPath);
  checkShaderCompileTimeErrors(fragShaderRef, "FRAGMENT", fragmentShaderPath);

  // Create a shader linker program and attach the shader references
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShaderRef);
  glAttachShader(shaderProgram, fragShaderRef);
  glLinkProgram(shaderProgram);
  
  // Check for errors and clean-up unused shaders
  ShaderReader::checkLinkTimeErrors(shaderProgram);
  glDeleteShader(vertexShaderRef);
  glDeleteShader(fragShaderRef);
}

void ShaderReader::use() {
  glUseProgram(shaderProgram);
}

void ShaderReader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value); 
}

void ShaderReader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);     
}

void ShaderReader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value); 
}


/* Check shader compilation errors */
void ShaderReader::checkShaderCompileTimeErrors(unsigned int shaderId, std::string shaderType, std::string path){
  int  success;
  char infoLog[512];
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
  if(!success) {
      glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::" << shaderType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
      std::cout << "ERROR::SHADER::" << shaderType << "Shader path: \n" << path << std::endl;
      std::cout << " " << std::endl;
  }
}

void ShaderReader::checkLinkTimeErrors(unsigned int linkProgramID) {
  int  success;
  char infoLog[512];
  glGetProgramiv(linkProgramID, GL_LINK_STATUS, &success);
  if(!success) {
    glGetProgramInfoLog(linkProgramID, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::LINK_PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
}