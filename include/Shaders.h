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
  static const std::string getExampleVertShader();
  static const std::string getExampleFragmentShader();
  static void checkCompileTimeVertexErrors(unsigned int shaderId);
  static void checkCompileTimeFragErrors(unsigned int shaderId);
  static void checkLinkTimeErrors(unsigned int linkProgramId);
};