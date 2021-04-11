#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Shaders
{
public:
  Shaders();
  ~Shaders();
  enum vertShaders {dfltVertShdr};
  enum fragShaders {dfltFragShdr};

  static unsigned int getExampleLinkProgram(Shaders::vertShaders vertexShadeMode, 
                                            Shaders::fragShaders fragShaderMode);
  static void checkShaderCompileTimeErrors(unsigned int shaderId, std::string shaderType);
  static void checkLinkTimeErrors(unsigned int linkProgramId);

private:
  static unsigned int getVertShader(Shaders::vertShaders vertexShadeMode);
  static unsigned int getFragShader(Shaders::fragShaders fragmentShaderMode);
  const static std::string ExampleVertShader;
  const static std::string ExampleFragShader;

};