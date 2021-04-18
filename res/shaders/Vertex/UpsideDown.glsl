#version 330 core
/* Shader processing geometry upside down
  \* specified vertices in location 0
  \* Color in location 1
  \* Output = input color
*/
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform float offset;
out vec3 vertexColor;
void main()
{
  gl_Position = vec4(aPos.xyz * offset - offset/2, 1.0);
  vertexColor = aColor;
}