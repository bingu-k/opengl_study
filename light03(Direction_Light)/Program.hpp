#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "Shader.hpp"
#include "Camera.hpp"
#include "Object.hpp"
#include "Texture.hpp"

GLuint	WIDTH = 800, HEIGHT = 600;
Camera	camera = Camera();

void	framebuffer_size_callback(GLFWwindow* window, int width, int height);
void	mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void	scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

class Program
{
	GLFWwindow*	window;
	Shader	shader;
	Object	object;
	Texture	textures;

	std::vector<glm::vec3>	objectPos;
public:
	Program(glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 0.0f)) : shader(), object(), textures()
	{
		camera.setPosition(camPos);

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		this->window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
		if (this->window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
		}
		glfwMakeContextCurrent(this->window);
		
		glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
		glfwSetCursorPosCallback(this->window, mouse_callback);
		glfwSetScrollCallback(this->window, scroll_callback);
		
		glEnable(GL_DEPTH_TEST);

    	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	};
	
	// initial function
	void	chooseShader(std::string VshaderPath, std::string FshaderPath);
	void	chooseObject(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<glm::vec3> positions);
	void	chooseTextrue(std::vector<std::string> texture);
	void	render(float r, float g, float b);

	// event function
	void	processInput(float deltaTime);
	~Program() { glfwTerminate(); };
};

void	Program::chooseShader(std::string VshaderPath, std::string FshaderPath)
{ shader.initShader(VshaderPath.c_str(), FshaderPath.c_str()); };

void	Program::chooseObject(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<glm::vec3> positions)
{	object.init(vertices, indices, positions); };

void	Program::chooseTextrue(std::vector<std::string> texture)
{
	for (auto& t : texture)
		textures.addTexture(t);
	
	shader.use();
	shader.setInt("material.diffuse", 0);
	shader.setInt("material.specular", 1);
	// for (int i = 0; i < texture.size(); ++i)
	// 	shader.setInt("texture" + std::to_string(i), i);
}

void	Program::render(float r, float g, float b)
{
	Shader	lightShader;
	lightShader.initShader("./shader/lightShader.vs", "./shader/lightShader.fs");
	// glm::vec3 lightPos(1.0f, 1.0f, -0.3f);
	
	float	lastFrame = 0.0f;
	while (!glfwWindowShouldClose(this->window))
    {
        // input
        processInput(glfwGetTime() - lastFrame);
		lastFrame = glfwGetTime();
        // render
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures.getTexture(0));
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures.getTexture(1));

		glm::mat4 model	= glm::mat4(1.0f);
        glm::mat4 view			= camera.getCamView();
        glm::mat4 projection	= glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.zoom),
									static_cast<float>(WIDTH) / static_cast<float>(HEIGHT),
									0.1f,
									100.0f);

		glDrawElements(GL_TRIANGLES, object.indices.size(), GL_UNSIGNED_INT, nullptr);
		shader.use();

		glm::vec3	objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
		shader.setVec3("objectColor", objectColor);

		// lightPos.x = sin(glfwGetTime()) * 2;
		// lightPos.z = cos(glfwGetTime()) * 2;
		// shader.setVec3("light.position", lightPos);
		shader.setVec3("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
		// glm::vec3	lightColor = glm::vec3(sin(glfwGetTime() * 2.0f), sin(glfwGetTime() * 0.7f), sin(glfwGetTime() * 1.3f));
		glm::vec3	lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
		shader.setVec3("light.color", lightColor);
		shader.setVec3("light.ambient", lightColor * glm::vec3(1.0f));
		shader.setVec3("light.diffuse", lightColor * glm::vec3(1.0f));
		shader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		
		shader.setVec3("viewPos", camera.position);

		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		shader.setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
		// shader.setVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
		// shader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
		shader.setFloat("material.shineness", 32.0f);

		glBindVertexArray(object.VAO);
		for(int i = 0; i < object.positions.size(); ++i)
		{
			model	= glm::mat4(1.0f);
			float	angle = 20.0f * i;
			model	= glm::translate(model, object.positions.at(i));
			model	= glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader.setMat4("model", model);
			glDrawElements(GL_TRIANGLES, object.indices.size(), GL_UNSIGNED_INT, nullptr);
		}
		// light object
		lightShader.use();
        lightShader.setVec3("lightColor",  glm::vec3(1.0f, 1.0f, 1.0f));

		model = glm::mat4(1.0f);
		// model = glm::translate(glm::mat4(1.0f), lightPos);
		model = glm::rotate(model, static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		lightShader.setMat4("model", model);
		lightShader.setMat4("view", view);
		lightShader.setMat4("projection", projection);

        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
}

void	Program::processInput(float deltaTime)
{
    if(glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->window, true);
	else if(glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
		camera.pressKeyBoard(FORWARD, deltaTime);
	else if(glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
		camera.pressKeyBoard(BACKWARD, deltaTime);
	else if(glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
		camera.pressKeyBoard(LEFT, deltaTime);
	else if(glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
		camera.pressKeyBoard(RIGHT, deltaTime);
};

void	framebuffer_size_callback(GLFWwindow* window, int width, int height)
{ glViewport(0, 0, width, height); };

void	mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	static float	lastX = WIDTH / 2.0f;
	static float	lastY = HEIGHT / 2.0f;
	static bool firstMouse = true;

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
};

void	scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{ camera.ProcessMouseScroll(static_cast<float>(yoffset)); };

#endif