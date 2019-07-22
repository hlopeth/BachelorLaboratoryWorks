#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Rotation_body
{
public:
    Rotation_body(const vector<vec2> &points, const vector<vec2> &normals, const GLuint lines_count)
        {
            const GLfloat degrees_per_rotation = 360.0f / lines_count;

            for (int i = 0; i < lines_count; ++i)
            {
                for (int j = 0; j < points.size(); ++j)
                {
                    mat4 transform = mat4(1.0f);
                    transform = translate(transform, vec3(points[j], 0.0f));
                    transform = rotate(transform, radians(i * degrees_per_rotation), vec3(1.0f, 0.0f, 0.0f));
                    transform = translate(transform, vec3(0.0f, 0.0f, 0.0f));
                    const vec3 vertex = vec3(vec4(points[j], 0.0f, 0.0f) * transform);
                    const vec3 normal = vec3(vec4(normals[j], 0.0f, 0.0f) * transform);
                    vertices.push_back(vertex.x);
                    vertices.push_back(vertex.y);
                    vertices.push_back(vertex.z);
                    vertices.push_back(normal.x);
                    vertices.push_back(normal.y);
                    vertices.push_back(normal.z);
                }
            }
            const GLuint line_size = points.size();

            for (int i = 0; i < lines_count; i++)
            {
                for (int j = 0; j < line_size - 1; ++j)
                {
                    indices.push_back(j + i * line_size);
                    indices.push_back(j + 1 + i * line_size);
                    indices.push_back((j + 1 + line_size + i * line_size) % (line_size * lines_count));
                    indices.push_back(j + i * line_size);
                    indices.push_back((j + line_size + i * line_size) % (line_size * lines_count));
                    indices.push_back((j + 1 + line_size + i * line_size) % (line_size * lines_count));
                }
            }
        }

	~Rotation_body() { }

	vector<GLfloat> get_vertices() const
	{
		return vertices;
	}

	vector<GLuint> get_indices() const
	{
		return indices;
	}

private:
	vector<GLfloat> vertices;
	vector<GLuint> indices;
};
