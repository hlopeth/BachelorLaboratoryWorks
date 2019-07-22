#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;
out vec3 fragment_pos;
out vec2 tex_coord;

void main()
{
   tex_coord = a_texCoord;
   gl_Position = projection * view * model * vec4(a_pos, 1.0f);
   fragment_pos = vec3(model * vec4(a_pos, 1.0f));
   normal = mat3(transpose(inverse(model))) * a_normal;
}