#version 330 core
/* Example shaders with a uniform variable for an example
   of changing a color from the CPU calls
*/
uniform vec4 controllableColor; // controllable
out vec4 FragColor; // output color
void main()
{
   FragColor = controllableColor;
}