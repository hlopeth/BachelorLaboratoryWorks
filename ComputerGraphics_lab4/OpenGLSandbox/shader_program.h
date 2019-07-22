#pragma once

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

enum type
{
	shader,
	program
};

class Shader_program
{
public:
	GLuint id;

    Shader_program(const char* vertex_path, const char* fragment_path);

	~Shader_program()
	{
		if (id != 0)
			glDeleteProgram(id);
	}

	void use() const
	{
		glUseProgram(id);
	}

    // utility uniform functions
    void set(const string& name, const bool value) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), int(value));
	}

    void set(const string& name, const int value) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	}

    void set(const string& name, const float value) const
	{
		glUniform1f(glGetUniformLocation(id, name.c_str()), value);
	}

    void set(const string& name, const glm::vec2& value) const
	{
        glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
	}

    void set(const string& name, const glm::vec3& value) const
	{
        glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
	}

    void set(const string& name, const glm::vec4& value) const
	{
        glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
	}

    void set(const string& name, const glm::mat2& mat) const
	{
        glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}

    void set(const string& name, const glm::mat3& mat) const
	{
        glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}

    void set(const string& name, const glm::mat4& mat) const
	{
        glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}

private:
    static void check_compile_errors(const unsigned int shader, const type _type);
};
