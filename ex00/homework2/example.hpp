#ifndef EXAMPLE_HPP
# define EXAMPLE_HPP

# define GL_SILENCE_DEPRECATION

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include <iostream>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char*	vertex_shader_source = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char*	fragment_shader_source = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"	color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

float vertices1[] = {
	// first
	-0.5f, -0.5f, 0.0f,	// left_bottom
	0.0f, -0.5f, 0.0f,	// right_bottom
	-0.5f, 0.5f, 0.0f	// top
};

float vertices2[] = {
	// second
	0.0f, -0.5f, 0.0f,	// left_bottom
	0.5f, -0.5f, 0.0f,	// right_bottom
	0.5f, 0.5f, 0.0f,	// top
};

#endif