#version 330 core
/* Simple example shader which sets output color equal to
   input color from vertex shader
*/

in vec3 vertexColor;
out vec4 FragColor;
void main()
{
    FragColor = vec4(vertexColor, 1.0f);
}