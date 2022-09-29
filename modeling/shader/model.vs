#version 410

layout(location = 0) vec3	aPos;
layout(location = 1) vec3	aNor;
layout(location = 2) vec2	aTex;

out vec2	TexCoords;

uniform mat4	model;
uniform mat4	view;
uniform mat4	projection;

int main(void)
{
	TexCoords = aTex;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
};