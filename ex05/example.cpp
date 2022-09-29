#include <math.h>

#include "Shader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float	vertices[] = {
	// Position				// Texture
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,		1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,		1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3( 0.0f,  0.0f,  0.0f),
	glm::vec3( 2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3( 2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3( 1.3f, -2.0f, -2.5f),
	glm::vec3( 1.5f,  2.0f, -2.5f),
	glm::vec3( 1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions.
	// note that width and height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
	glEnable(GL_DEPTH_TEST);

	Shader	shader("./shader/shader.vs", "./shader/shader.fs");

	unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

	unsigned int	texture0;
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char*	data = stbi_load("./photo/wall.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	stbi_image_free(data);

	unsigned int	texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("./photo/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	stbi_image_free(data);
	
	shader.use(); // uniform을 설정하기 전에 shader를 활성화해야 한다는 것을 잊지마세요!  
	shader.setInt("texture0", 0); // 직접 설정
	shader.setInt("texture1", 1); // 혹은 shader 클래스를 활용

	glm::vec3	camPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3	camFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3	camUp = glm::vec3(0.0f, 1.0f, 0.0f);
	
	float	deltaTime = 0.0f;
	float	lastTime = 0.0f;

	// render loop
    while (!glfwWindowShouldClose(window))
    {
		deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();
        // input
		float	camSpeed = 2.5f * deltaTime;
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
		else if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			camPos += camSpeed * camFront;
		else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			camPos -= camSpeed * camFront;
		else if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			camPos -= glm::normalize(glm::cross(camFront, camUp)) * camSpeed;
		else if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			camPos += glm::normalize(glm::cross(camFront, camUp)) * camSpeed;

        // render
        glClearColor(0.4f, 0.0f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture0);
		glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);

		shader.use();

		glm::mat4	projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(60.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		shader.setMat4("projection", projection);
		glm::mat4 view = glm::lookAt(camPos, camFront + camPos, camUp);
		shader.setMat4("view", view);

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; ++i)
		{
			glm::mat4  model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float	angle = 20.0f * i;
			if (i % 3 == 0)
				angle = 20.0f * glfwGetTime();
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}