#include "object.h"

Object::Object(const vector<GLfloat> &vertices,const  vector<GLuint> &vertices_structure, const GLuint shader_program_id)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    const GLuint stride = vertices_structure.back();

    GLuint index = 0;
    GLuint shift = 0;
    for (auto i=0; i < vertices_structure.size()-1;i++)
    {
        GLuint element = vertices_structure[i];
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, element, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*)(shift * sizeof(GLfloat)));
        index++;
        shift += element;
    }

    glBindVertexArray(0);

    this->shader_program_id = shader_program_id;
}



Object::Object(const vector<GLfloat> &vertices, const vector<GLuint> &vertices_structure, const vector<GLuint> &indices, const GLuint shader_program_id) : index_count(indices.size())
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    const GLuint stride = vertices_structure.back();

    GLuint index = 0;
    GLuint shift = 0;
    for (auto i=0; i < vertices_structure.size()-1;i++)
    {
        GLuint element = vertices_structure[i];
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, element, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*)(shift * sizeof(GLfloat)));
        index++;
        shift += element;
    }

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLfloat), &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);

    this->shader_program_id = shader_program_id;
}

Object::Object(const vector<GLfloat> &vertices,const  vector<GLuint> &vertices_structure, const GLuint shader_program_id, const GLuint texture_id)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    const GLuint stride = vertices_structure.back();

    GLuint index = 0;
    GLuint shift = 0;
    for (auto i=0; i < vertices_structure.size()-1;i++)
    {
        GLuint element = vertices_structure[i];
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, element, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*)(shift * sizeof(GLfloat)));
        index++;
        shift += element;
    }

    glBindVertexArray(0);

    this->shader_program_id = shader_program_id;
    this->texture_id = texture_id;
}

Object::Object(const vector<GLfloat> &vertices,const  vector<GLuint> &vertices_structure,const  vector<GLuint> &indices, const GLuint shader_program_id, const GLuint texture_id):index_count(indices.size())
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    const GLuint stride = vertices_structure.back();

    GLuint index = 0;
    GLuint shift = 0;
    for (auto i=0; i < vertices_structure.size()-1;i++)
    {
        GLuint element = vertices_structure[i];
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, element, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*)(shift * sizeof(GLfloat)));
        index++;
        shift += element;
    }

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLfloat), &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);

    this->shader_program_id = shader_program_id;
    this->texture_id = texture_id;
}

Object::~Object()
{
    if (vao != 0)
        glDeleteVertexArrays(1, &vao);
    if (vbo != 0)
        glDeleteBuffers(1, &vbo);
    if (ebo != 0)
        glDeleteBuffers(1, &ebo);
}

void Object::use() const
{
    glBindVertexArray(vao);

    glUseProgram(shader_program_id);

    if (texture_id != 0)
    {
        glActiveTexture(GL_TEXTURE0 + texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);
    }
}

void Object::draw() const
{
    use();
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, NULL);
}
