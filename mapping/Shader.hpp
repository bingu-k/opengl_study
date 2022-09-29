#ifndef SHADER_HPP
# define SHADER_HPP

#include "header.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
public:
	// Program ID
	unsigned int	ID;

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
		checkCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShader, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	~Shader()
	{ glDeleteProgram(ID); }

	void checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
	}

	void	use()
	{ glUseProgram(ID); };

	void	setBool(const std::string &name, bool value) const
	{ glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); };
	void	setInt(const std::string &name, int value) const
	{ glUniform1i(glGetUniformLocation(ID, name.c_str()), value); };
	void	setFloat(const std::string &name, float value) const
	{ glUniform1f(glGetUniformLocation(ID, name.c_str()), value); };
	void	setVec3(const std::string &name, glm::vec3 value) const
	{ glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value)); };
	void	setMat4(const std::string &name, glm::mat4 value) const
	{ glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value)); };
};

#endif