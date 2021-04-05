#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Shaders
{
private:
  /* data */
  const static std::string ExampleVertShader;
  const static std::string ExampleFragShader;
public:
  Shaders();
  ~Shaders();
  static unsigned int getExampleVertShader();
  static unsigned int getExampleFragmentShader();
  static unsigned int getExampleLinkProgram();
  static void checkShaderCompileTimeErrors(unsigned int shaderId, std::string shaderType);
  static void checkLinkTimeErrors(unsigned int linkProgramId);
};