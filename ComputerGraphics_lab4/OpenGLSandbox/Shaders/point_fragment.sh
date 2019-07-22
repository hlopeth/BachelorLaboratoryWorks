#version 330 core

uniform vec3 pointColor;

in vec2 o_pos;
layout(location = 0) out vec4 frag_color;

void main()
{
	//vec3 color = (1-step(0.8, distance(vec2(0.0f), o_pos))) * vec3(0.0f, 0.0f, 1.0f);
	frag_color = vec4(pointColor, 1.0f);
};