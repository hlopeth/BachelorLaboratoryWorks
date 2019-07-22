#version 330 core

uniform vec3 light_color;
uniform vec3 object_color;
uniform vec3 light_pos;
uniform vec3 camera_pos;
uniform sampler2D texture1;

layout(location = 0) out vec4 frag_color;
in vec3 normal;
in vec3 fragment_pos;
in vec2 tex_coord;

void main()
{
	// AMBIANT
	float ambient_power = 0.1f;
	vec3 ambient = ambient_power * light_color;
	
	// DIFFUSE
	vec3 normal_vector = normalize(normal);
	vec3 ray_vector = normalize(light_pos - fragment_pos);
	float diffuse_power = max(dot(normal_vector, ray_vector), 0.0f); // If negative then 0
	vec3 diffuse = diffuse_power * light_color;
	
	// SPECULAR
	vec3 viewer_pos = camera_pos; 
	vec3 view_vector = normalize(viewer_pos - fragment_pos);
	vec3 reflect_vector = reflect(-ray_vector, normal_vector);
	float specular_power = 0.0f;
	if (diffuse_power > 0.0f)
		specular_power = 0.5f * pow(max(dot(view_vector, reflect_vector), 0.0f), 64);
	vec3 specular = specular_power * light_color;
	
	//TEXTURE
	vec4 texelColor = texture(texture1, tex_coord);
	
	frag_color = vec4((ambient + diffuse + specular) * object_color, 1.0f) * texelColor;
};