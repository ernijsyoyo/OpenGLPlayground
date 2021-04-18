#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class [[deprecated]] Shaders
{
public:
  Shaders();
  ~Shaders();
  enum vertShaders {dfltVertShdr, colorsInVertexArray};
  enum fragShaders {dfltFragShdr, fragShader_Uniform};

  static unsigned int getExampleLinkProgram(Shaders::vertShaders vertexShadeMode, 
                                            Shaders::fragShaders fragShaderMode);
  static void checkShaderCompileTimeErrors(unsigned int shaderId, std::string shaderType);
  static void checkLinkTimeErrors(unsigned int linkProgramId);

private:
  static unsigned int getVertShader(Shaders::vertShaders vertexShadeMode);
  static unsigned int getFragShader(Shaders::fragShaders fragmentShaderMode);
  const static std::string ExampleVertShader;
  const static std::string VertShaderColors;
  const static std::string ExampleFragShader;
  const static std::string FragShader_Uniform;
};