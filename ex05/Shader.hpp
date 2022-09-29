#ifndef SHADER_HPP
# define SHADER_HPP

#define GL_SILENCE_DEPRECATION

#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
public:
	// Program ID
	unsigned int	ID;

	Shader() {};
	Shader(const GLchar* vertexPath, const GLchar* FragmentPath)
	{
		std::string	vertexCode, fragmentCode;
		std::ifstream	vShaderFile, fShaderFile;
		vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(FragmentPath);

			std::stringstream	vShaderStream, fShaderStream;
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch(const std::exception& e)
		{
        	std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		
		const char*	vShader = vertexCode.c_str();
		const char*	fShader = fragmentCode.c_str();
		
		unsigned int vertex, fragment;
		
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShader, NULL);
		glCompileShader(vertex);
		std::cout << "VERTEX SHADER : ";
		check_shader(vertex);

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShader, NULL);
		glCompileShader(fragment);
		std::cout << "FRAGMENT SHADER : ";
		check_shader(fragment);

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		std::cout << "PROGRAM : ";
		check_program();

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	~Shader()
	{ glDeleteProgram(ID); }

	void	check_shader(unsigned int shader)
	{
		int  success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if(!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		else
			std::cout << "SUCCESS" << std::endl;
	}

	void	check_program(void)
	{
		int  success;
		char infoLog[512];
		glGetProgramiv(ID, GL_COMPILE_STATUS, &success);
		if(!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		else
			std::cout << "SUCCESS" << std::endl;
	};

	void	use()
	{ glUseProgram(ID); };

	void	setBool(const std::string &name, bool value) const
	{ glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); };
	void	setInt(const std::string &name, int value) const
	{ glUniform1i(glGetUniformLocation(ID, name.c_str()), value); };
	void	setFloat(const std::string &name, float value) const
	{ glUniform1f(glGetUniformLocation(ID, name.c_str()), value); };
	void	setMat4(const std::string &name, glm::mat4 value) const
	{ glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value)); };
};

#endif