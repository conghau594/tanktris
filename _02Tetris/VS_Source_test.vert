#version 450
const vec2 quadVertices[4] = { vec2(-0.8, -0.8), vec2(0.0, -0.8), vec2(0.0, 0.8), vec2(-0.8, 0.8) };
uniform float time;
void main()
{
   gl_PointSize=100;
   gl_Position = vec4(quadVertices[gl_VertexID], 0.0, 1.0);
}