#include "Program.hpp"

std::vector<Vertex> vertices = {
// FRONT
	// Position				// Color			// Texture		// Normal
	{{0.5f, 0.5f, 0.5f},	{1.0f, 0.0f, 0.0f},	{1.0f, 1.0f},	{0.0f, 0.0f, 1.0f}},	// right_top
	{{0.5f, -0.5f, 0.5f},	{0.0f, 1.0f, 0.0f},	{1.0f, 0.0f},	{0.0f, 0.0f, 1.0f}},	// right_bottom
	{{-0.5f, -0.5f, 0.5f},	{0.0f, 0.0f, 1.0f},	{0.0f, 0.0f},	{0.0f, 0.0f, 1.0f}},	// left_bottom
	{{-0.5f, 0.5f, 0.5f},	{1.0f, 1.0f, 0.0f},	{0.0f, 1.0f},	{0.0f, 0.0f, 1.0f}},	// left_top
// BACK
	// Position				// Color			// Texture
	{{-0.5f, 0.5f, -0.5f},	{1.0f, 0.0f, 0.0f},	{1.0f, 1.0f},	{0.0f, 0.0f, -1.0f}},	// right_top
	{{-0.5f, -0.5f, -0.5f},	{0.0f, 1.0f, 0.0f},	{1.0f, 0.0f},	{0.0f, 0.0f, -1.0f}},	// right_bottom
	{{0.5f, -0.5f, -0.5f},	{0.0f, 0.0f, 1.0f},	{0.0f, 0.0f},	{0.0f, 0.0f, -1.0f}},	// left_bottom
	{{0.5f, 0.5f, -0.5f},	{1.0f, 1.0f, 0.0f},	{0.0f, 1.0f},	{0.0f, 0.0f, -1.0f}},	// left_top
// TOP
	// Position				// Color			// Texture
	{{0.5f, 0.5f, -0.5f},	{1.0f, 0.0f, 0.0f},	{1.0f, 1.0f},	{0.0f, 1.0f, 0.0f}},	// right_top
	{{0.5f, 0.5f, 0.5f},	{0.0f, 1.0f, 0.0f},	{1.0f, 0.0f},	{0.0f, 1.0f, 0.0f}},	// right_bottom
	{{-0.5f, 0.5f, 0.5f},	{0.0f, 0.0f, 1.0f},	{0.0f, 0.0f},	{0.0f, 1.0f, 0.0f}},	// left_bottom
	{{-0.5f, 0.5f, -0.5f},	{1.0f, 1.0f, 0.0f},	{0.0f, 1.0f},	{0.0f, 1.0f, 0.0f}},	// left_top
// BOTTOM
	// Position				// Color			// Texture
	{{0.5f, -0.5f, 0.5f},	{1.0f, 0.0f, 0.0f},	{1.0f, 1.0f},	{0.0f, -1.0f, 0.0f}},	// right_top
	{{0.5f, -0.5f, -0.5f},	{0.0f, 1.0f, 0.0f},	{1.0f, 0.0f},	{0.0f, -1.0f, 0.0f}},	// right_bottom
	{{-0.5f, -0.5f, -0.5f},	{0.0f, 0.0f, 1.0f},	{0.0f, 0.0f},	{0.0f, -1.0f, 0.0f}},	// left_bottom
	{{-0.5f, -0.5f, 0.5f},	{1.0f, 1.0f, 0.0f},	{0.0f, 1.0f},	{0.0f, -1.0f, 0.0f}},	// left_top
// LEFT
	// Position				// Color			// Texture
	{{-0.5f, 0.5f, 0.5f},	{1.0f, 0.0f, 0.0f},	{1.0f, 1.0f},	{-1.0f, 0.0f, 0.0f}},	// right_top
	{{-0.5f, -0.5f, 0.5f},	{0.0f, 1.0f, 0.0f},	{1.0f, 0.0f},	{-1.0f, 0.0f, 0.0f}},	// right_bottom
	{{-0.5f, -0.5f, -0.5f},	{0.0f, 0.0f, 1.0f},	{0.0f, 0.0f},	{-1.0f, 0.0f, 0.0f}},	// left_bottom
	{{-0.5f, 0.5f, -0.5f},	{1.0f, 1.0f, 0.0f},	{0.0f, 1.0f},	{-1.0f, 0.0f, 0.0f}},	// left_top
// RIGHT
	// Position				// Color			// Texture
	{{0.5f, 0.5f, -0.5f},	{1.0f, 0.0f, 0.0f},	{1.0f, 1.0f},	{1.0f, 0.0f, 0.0f}},	// right_top
	{{0.5f, -0.5f, -0.5f},	{0.0f, 1.0f, 0.0f},	{1.0f, 0.0f},	{1.0f, 0.0f, 0.0f}},	// right_bottom
	{{0.5f, -0.5f, 0.5f},	{0.0f, 0.0f, 1.0f},	{0.0f, 0.0f},	{1.0f, 0.0f, 0.0f}},	// left_bottom
	{{0.5f, 0.5f, 0.5f},	{1.0f, 1.0f, 0.0f},	{0.0f, 1.0f},	{1.0f, 0.0f, 0.0f}}	// left_top
};
std::vector<GLuint> indices = {
	0, 1, 3,
	1, 2, 3,

	4, 5, 7,
	5, 6, 7,

	8, 9, 11,
	9, 10, 11,

	12, 13, 15,
	13, 14, 15,

	16, 17, 19,
	17, 18, 19,

	20, 21, 23,
	21, 22, 23
};

glm::vec3 cubePositions[] = {
	glm::vec3( 0.0f,  0.0f,  0.0f),
};

int main()
{
	Program	program(glm::vec3(0.0f, 0.0f, 10.0f));
	std::vector<std::string>	texture;
	std::vector<glm::vec3>		pos;

	texture.push_back("./photo/wall.jpg");
	texture.push_back("./photo/me.jpeg");
	
	for (auto& position : cubePositions)
		pos.push_back(position);

	program.chooseShader("./shader/shader.vs", "./shader/shader.fs");
	program.chooseObject(vertices, indices, pos);
	program.chooseTextrue(texture);
	program.render(0.1f, 0.1f, 0.1f);
    return 0;
}