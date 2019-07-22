#pragma once

#include <iostream>
#include <string>

#include <GL/glew.h>


using namespace std;

class Texture
{
public:
	GLuint id;

    Texture(const string file_name, const GLint wrapping_mode = GL_REPEAT, const GLint filtering_mode = GL_LINEAR);

	// Используется только для wrapping_mode = GL_CLAMP_TO_BORDER.
    Texture(const string file_name, const GLfloat border_color[4], const GLint filtering_mode = GL_LINEAR);

	~Texture()
	{
		if (id != 0)
			glDeleteTextures(1, &id);
	}

	void use() const
	{
		glActiveTexture(GL_TEXTURE0 + id);
		glBindTexture(GL_TEXTURE_2D, id);
	}

private:
    static void load_texture(string file_name);
};
