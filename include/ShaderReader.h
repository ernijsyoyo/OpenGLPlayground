#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
  

class ShaderReader
{
private:
  const char* vShaderCode;
  const char* fShaderCode;
  const char* vertexShaderPath;
  const char* fragmentShaderPath;
  void compileShaderProgram();
  void checkShaderCompileTimeErrors(unsigned int shaderId, std::string shaderType, std::string path);
  void checkLinkTimeErrors(unsigned int linkProgramID);

public:
    // the program ID
    unsigned int shaderProgram;
  
    /**
     * Read two shader files and compile shader program
     * @param vertexPath Relative path binary to vertex shader
     * @param fragmentPath Relative path from binary to fragment shader
    */
    ShaderReader(const char* vertexPath, const char* fragmentPath);
    ~ShaderReader();

    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
};
  
#endif