#pragma once

#include <glm/glm.hpp>
#include <GL/gl.h>

using namespace glm;

enum camera_movement
{
	forward,
	backward,
	left,
	right
};

class Camera
{
public:
	vec3 position;
	vec3 front;
	vec3 world_up;
	vec3 up;
	vec3 right;

	GLfloat yaw = -90.0f;
	GLfloat pitch = 0.0f;

	GLfloat movement_speed = 2.5f;
	GLfloat mouse_sensitivity = 0.1f;
	GLfloat fov = 45.0f;

	GLboolean god_mod = false;

    Camera(const vec3 position = vec3(0.0f, 0.0f, 0.0f), const vec3 front = vec3(0.0f, 0.0f, -1.0f), const vec3 world_up = vec3(0.0f, 1.0f, 0.0f));

    mat4 get_lookat_matrix();

    void process_keyboard(const camera_movement direction, const GLfloat delta_time);

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void process_mouse_movement(const GLfloat x_offset, const GLfloat y_offset);

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void process_mouse_scroll(const GLfloat y_offset);

private:
	// Calculates the front vector from the Camera's (updated) Euler Angles
    void update_camera_vectors();
};
