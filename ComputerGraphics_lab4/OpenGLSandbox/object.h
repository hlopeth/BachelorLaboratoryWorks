#pragma once

#include <vector>

#include <GL/glew.h>

using namespace std;

class Object
{
public:
	GLuint vao;
	GLuint vbo;
	GLuint ebo = 0;
    GLuint index_count = 0;
	GLuint shader_program_id;
	GLuint texture_id = 0;

    Object(const vector<GLfloat> &vertices, const vector<GLuint> &vertices_structure, const GLuint shader_program_id);
    Object(const vector<GLfloat> &vertices, const vector<GLuint> &vertices_structure, const vector<GLuint> &indices,  const GLuint shader_program_id);
    Object(const vector<GLfloat> &vertices, const vector<GLuint> &vertices_structure, const GLuint shader_program_id, const GLuint texture_id);
    Object(const vector<GLfloat> &vertices, const vector<GLuint> &vertices_structure, const vector<GLuint> &indices,  const GLuint shader_program_id, const GLuint texture_id);
    ~Object();


    void  use() const;
    void draw() const;
};
