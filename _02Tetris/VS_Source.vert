#version 450 core
//#extension GL_ARB_shading_language_include : require

#define TIME_LOC  0
#define SPEED_LOC 1

layout (location = TIME_LOC)  uniform float time;
layout (location = SPEED_LOC) uniform float speed;

//float time1 = 0;
layout (location = 0) in vec2 aPos;

//out vec2 aPos_out;

/*
mat2 rotation = mat2(
	1.5*cos(time), -1.5*sin(time),
	1.5*sin(time),  1.5*cos(time)
);
*/

//vec2 point3 = vec2(0.5f, 0.7f);
void main(void) {
	//rotate around point 3
	//aPos_out = aPos;
	//vec2 tmp = aPos; //rotation*(aPos);
	gl_Position = vec4( aPos, 0.0f, 1.0f );
}