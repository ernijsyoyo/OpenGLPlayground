#version 330 core
/* Example vertex shaders with
  \* specified vertices in location 0
  \* Color in location 1
  \* Output = input color
*/
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 vertexColor;
void main()
{
  vertexColor = aColor;
}