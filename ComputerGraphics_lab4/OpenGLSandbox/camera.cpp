#include "camera.h"

Camera::Camera(const vec3 position, const vec3 front, const vec3 world_up)
{
    this->position = position;
    this->front = front;
    this->world_up = world_up;
    update_camera_vectors();
}

mat4 Camera::get_lookat_matrix()
{
    const mat4 rud_part
    (
        vec4(right, 0.0f),
        vec4(up, 0.0f),
        vec4(-front, 0.0f),
        vec4(0.0f, 0.0f, 0.0f, 1.0f)
    );
    const mat4 position_part
    (
        vec4(1.0f, 0.0f, 0.0f, -position[0]),
        vec4(0.0f, 1.0f, 0.0f, -position[1]),
        vec4(0.0f, 0.0f, 1.0f, -position[2]),
        vec4(0.0f, 0.0f, 0.0f, 1.0f)
    );
    return transpose(position_part * rud_part);
    //return lookAt(position, position + front, up);
}

void Camera::process_keyboard(const camera_movement direction, const GLfloat delta_time)
{
    const float velocity = movement_speed * delta_time;
    if (direction == camera_movement::forward)
        position += front * velocity;
    if (direction == camera_movement::backward)
        position -= front * velocity;
    if (direction == camera_movement::left)
        position -= right * velocity;
    if (direction == camera_movement::right)
        position += right * velocity;
    if (!god_mod)
        position.y = 0;
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::process_mouse_movement(const GLfloat x_offset, const GLfloat y_offset)
{
    yaw += x_offset * mouse_sensitivity;
    pitch += y_offset * mouse_sensitivity;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    // Update Front, Right and Up Vectors using the updated Euler angles
    update_camera_vectors();
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::process_mouse_scroll(const GLfloat y_offset)
{
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= y_offset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}

// Calculates the front vector from the Camera's (updated) Euler Angles
void Camera::update_camera_vectors()
{
    vec3 new_front;
    new_front.x = cos(radians(yaw)) * cos(radians(pitch));
    new_front.y = sin(radians(pitch));
    new_front.z = sin(radians(yaw)) * cos(radians(pitch));
    front = normalize(new_front);
    right = normalize(cross(front, world_up));
    up = normalize(cross(right, front));
}
