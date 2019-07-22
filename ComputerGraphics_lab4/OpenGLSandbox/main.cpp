#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_program.h"
#include "camera.h"
#include "object.h"
#include "texture.h"
#include "line_builder.h"
#include "bezier_builder.h"
#include "rotation_body.h"

using namespace std;
using namespace glm;

GLFWwindow* window;

GLuint scr_width  = 1280;
GLuint scr_height = 500;

// Camera
Camera main_camera(vec3(0.0f, 0.0f, 3.0f));
GLfloat last_x =  scr_width / 2.0f;
GLfloat last_y = scr_height / 2.0f;
GLboolean mouse_button_pressed = false;
GLfloat fov = 45.0f;

mat4 right_view(1.0f);

// Timing
GLfloat delta_time = 0.0f;
GLfloat last_frame = 0.0f;

//Points
vector<vec2> pointCoords;

//Bezier
vector<vec2> bezierCoords;

//BezierBuilder
BezierBuilder bezierBuilder;

//lineBuilder
LineBuilder *lineBuilder;


int selectedPointIndex=-1;
vector<vec2>* selectedCoordVector = nullptr;

mat4 body_model(1.0f);


void RecalcBezierCoords(int pointIndex=-1)
{
    if(pointCoords.size()< 2)
    {
        bezierCoords.clear();
        return;
    }

    if(pointIndex == -1)//new point was add
    {
        vec2 coord = pointCoords[pointCoords.size()-2];
        vec2 coord_next = pointCoords[pointCoords.size()-1];
        GLfloat dist = coord_next.x - coord.x;
        vec2 p1 = vec2(coord.x + dist/3.0f, coord.y - 0.08f);
        vec2 p2 = vec2(coord_next.x - dist/3.0f, coord_next.y + 0.08f);
        bezierCoords.push_back(p1);
        bezierCoords.push_back(p2);
        return;
    }

    if(pointIndex == 0)//first point was deleted
    {
        bezierCoords.erase(bezierCoords.begin());
        bezierCoords.erase(bezierCoords.begin());
        return;
    }
    if(pointIndex == pointCoords.size())//last point was deleted
    {
        bezierCoords.erase(bezierCoords.end()-1);
        bezierCoords.erase(bezierCoords.end()-1);
        return;
    }
    if(pointIndex > 0 && pointIndex < pointCoords.size())//point in the middle was deleted
    {
        bezierCoords.erase(bezierCoords.end()+2*pointIndex);
        bezierCoords.erase(bezierCoords.end()+2*pointIndex);
        vec2 coord = pointCoords[pointIndex-1];
        vec2 coord_next = pointCoords[pointIndex];
        GLfloat dist = coord_next.x - coord.x;
        vec2 p1 = vec2(coord.x + dist/3.0f, coord.y - 0.08f);
        vec2 p2 = vec2(coord_next.x - dist/3.0f, coord_next.y + 0.08f);
        bezierCoords[2*pointIndex-2] = p1;
        bezierCoords[2*pointIndex-1] = p2;
        return;
    }
}

static void reshape_callback(GLFWwindow* window, const GLint width, const GLint height)
{
    //glViewport(0, 0, width, height);
    scr_width = width;
    scr_height = height;
}


vec2 cursorPos;


mat4 calc_rotation(const mat4 view, const GLfloat x_offset, const GLfloat y_offset)
{
    const GLuint slow_modifier = 10;
    mat4 new_view = rotate(view, radians(x_offset / slow_modifier), vec3(0.0f, 1.0f, 0.0f) * mat3(view)); // mat3(right_view)[1];
    new_view = rotate(new_view, radians(y_offset / slow_modifier), vec3(1.0f, 0.0f, 0.0f) * mat3(new_view)); // mat3(new_view)[0];
    return new_view;
}

bool moving_point = false;
void cursor_position_callback(GLFWwindow* window, const GLdouble x, const GLdouble y)
{
    // LEFT WINDOW PART
    if (x < scr_width / 2)
    {
        cursorPos.x = 2 * GLfloat(x) / scr_width * 2 - 1;
        cursorPos.y = 1 - 2 * GLfloat(y) / scr_height;
        if (moving_point == true)
        {
            //END OF MOOVING
            (*selectedCoordVector)[selectedPointIndex] = cursorPos;
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
            {
                moving_point = false;
            }
        }
        else
        {
            //SELECTING A POINT
            selectedPointIndex = -1;
            selectedCoordVector = nullptr;
            for (int i = 0; i<pointCoords.size(); i++)
            {
                if (glm::distance(cursorPos, pointCoords[i]) < 0.02)
                {
                    selectedPointIndex = i;
                    selectedCoordVector = &pointCoords;
                    break;
                }
            }
            for (int i = 0; i<bezierCoords.size() && selectedPointIndex == -1; i++)
            {
                if (glm::distance(cursorPos, bezierCoords[i]) < 0.02)
                {
                    selectedPointIndex = i;
                    selectedCoordVector = &bezierCoords;
                    break;
                }
            }
        }
    }
    // RIGHT WINDOW PART
    else
    {
        if (mouse_button_pressed)
        {
            const GLfloat x_offset = x - last_x;
            const GLfloat y_offset = y - last_y;
            body_model = calc_rotation(body_model, x_offset, y_offset);
        }
        last_x = x;
        last_y = y;
    }
}


double x;
double y;
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    // LEFT WINDOW PART
    glfwGetCursorPos(window, &x, &y);
    if (x < scr_width / 2)
    {
        if (selectedPointIndex == -1)
        {
            //NEW POINT
            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            {
                pointCoords.push_back(vec2(2 * GLfloat(x) / scr_width * 2 - 1, 1 - 2 * GLfloat(y) / scr_height));
                RecalcBezierCoords();
            }
        }
        else
        {
            //MOVING A POINT
            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            {
                moving_point = true;
            }
            //DELETING A POINT
            if (selectedCoordVector == &pointCoords && button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
            {
                pointCoords.erase(pointCoords.begin() + selectedPointIndex);
                RecalcBezierCoords(selectedPointIndex);
                selectedPointIndex = -1;
            }
        }
    }
    // RIGHT WINDOW PART
    else
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            mouse_button_pressed = true;
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
            mouse_button_pressed = false;
    }
}

void mouse_scroll_callback(GLFWwindow* window, double x_offset, double y_offset)
{
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= y_offset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}

void process_input(GLFWwindow* window)
{
    // Exit by ESC.
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    // Polygon mode ON/OFF.
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}


GLboolean init_opengl()
{
    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(scr_width, scr_height, "OpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, reshape_callback);
    glfwSetMouseButtonCallback(window,mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetScrollCallback(window, mouse_scroll_callback);

    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        cout << "Failed to initialize GLEW" << endl;
        return false;
    }

    glEnable(GL_DEPTH_TEST);

    return true;
}

inline void shutdown_opengl()
{
    glfwTerminate();
}

int main()
{
    if (!init_opengl())
        return -1;

    const vector<GLfloat> vertices = {
        // Coords
        -1.0f, -1.0f,  -1.0f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
        -1.0f,  1.0f,  -1.0f, 0.0f, 0.0f, 1.0f,  0.0f,  1.0f,
         1.0f, -1.0f,  -1.0f, 0.0f, 0.0f, 1.0f,  1.0f,  0.0f,
         1.0f,  1.0f,  -1.0f, 0.0f, 0.0f, 1.0f,  1.0f,  1.0f
    };
    const vector<GLuint> indices = {
        0, 1, 2, 2, 3, 1
    };

    //LineBuilder
    lineBuilder = new LineBuilder(0.02);

    // OBJECT
    Texture texture("D:/Qt Progects/OpenGLSandbox/OpenGLSandbox/notebook_texture.jpg");
    Shader_program object_shader_program("D:/Qt Progects/OpenGLSandbox/OpenGLSandbox/Shaders/object_vertex.sh", "D:/Qt Progects/OpenGLSandbox/OpenGLSandbox/Shaders/object_fragment.sh");
    vector<GLuint> vertices_structure = { 3, 3, 2, 8 };
    Object object(vertices, vertices_structure, indices, object_shader_program.id, texture.id);

    // POINTS
    const vector<GLfloat> vertices_point = {
        // Coords
        -1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f,
    };

    Shader_program point_shader_program("D:/Qt Progects/OpenGLSandbox/OpenGLSandbox/Shaders/point_vertex.sh", "D:/Qt Progects/OpenGLSandbox/OpenGLSandbox/Shaders/point_fragment.sh");
    vertices_structure = { 2, 2 };
    Object point(vertices_point, vertices_structure, indices, point_shader_program.id);

    const Shader_program rotation_shader_program("D:/Qt Progects/OpenGLSandbox/OpenGLSandbox/Shaders/body_vertex.sh", "D:/Qt Progects/OpenGLSandbox/OpenGLSandbox/Shaders/body_fragment.sh");

    mat4 projection;
    right_view = translate(right_view, vec3(0.0f, 0.0f, -3.0f));


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const GLfloat current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        std::vector<vec2>* bezierLine = nullptr;
        if(pointCoords.size()>1 && bezierCoords.size()>1)
        {
            vec2 p0=pointCoords[0],p1=bezierCoords[0],p2=bezierCoords[1],p3=pointCoords[1];
            bezierLine = bezierBuilder.generateBezierCurve(pointCoords,bezierCoords);
        }

        process_input(window);

        const mat4 view = translate(mat4(1.0f),vec3(0.0f,0.0f,-0.5f));//main_camera.get_lookat_matrix();

        glViewport(0, 0, scr_width/2, scr_height);
        projection = ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f );
        // OBJECTS
        object.use();
        object_shader_program.set("light_color", vec3(1.0f, 1.0f, 1.0f));
        object_shader_program.set("object_color", vec3(1.0f));
        object_shader_program.set("light_pos", vec3(0.0f, 0.0f, 1.0f));
        object_shader_program.set("camera_pos", main_camera.position);
        mat4 model = mat4(1.0f);
        object_shader_program.set("model", model);
        object_shader_program.set("view", view);
        object_shader_program.set("projection", projection);
        object.draw();

        //LINE
        if(pointCoords.size()>1)
        {
            Object* line = lineBuilder->generateLine(*bezierLine);
            line->use();
            lineBuilder->shaderProgram->set("model", mat4(1.0f));
            lineBuilder->shaderProgram->set("view", view);
            lineBuilder->shaderProgram->set("projection", projection);
            line->draw();
            delete(line);
        }

        //POINTS
        point.use();
        point_shader_program.set("view", view);
        point_shader_program.set("projection", projection);
        for(int i=0;i<pointCoords.size();i++)
        {
            if(selectedCoordVector == &pointCoords && i==selectedPointIndex)
                point_shader_program.set("pointColor", vec3(1.0f,1.0f,0.0f));
            else
                point_shader_program.set("pointColor", vec3(0.0f));

            vec2 coord = pointCoords[i];
            model = translate(mat4(1.0f), vec3(coord.x,coord.y,0.0f));
            model = scale(model,vec3(0.01f));
            point_shader_program.set("model", model);
            point.draw();
        }
        for(int i=0;i<bezierCoords.size();i++)
        {
            if(selectedCoordVector == &bezierCoords && i==selectedPointIndex)
                point_shader_program.set("pointColor", vec3(1.0f,1.0f,0.0f));
            else
                point_shader_program.set("pointColor", vec3(0.0f));
            vec2 coord = bezierCoords[i];
            model = translate(mat4(1.0f), vec3(coord.x,coord.y,0.0f));
            model = scale(model,vec3(0.01f));
            point_shader_program.set("model", model);
            point.draw();
        }

        glViewport(scr_width/2, 0, scr_width/2, scr_height);
        //rotationBody
        if (bezierLine != nullptr)
                {
                    std::vector<glm::vec2>* bezier_normals = bezierBuilder.generateBezierNorms(pointCoords, bezierCoords);
                    Rotation_body rotationBody(*bezierLine, *bezier_normals, 100);
                    Object body(rotationBody.get_vertices(), vector<GLuint> { 3, 3, 6 }, rotationBody.get_indices(), rotation_shader_program.id);
                    body.use();
                    const mat4 mvp = projection * right_view * body_model;
                    rotation_shader_program.set("model", body_model);
                    rotation_shader_program.set("mvp", mvp);
                    rotation_shader_program.set("object_color", vec3(0.5f));
                    rotation_shader_program.set("view_pos", right_view);
                    body.draw();
                }

        delete(bezierLine);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    delete(lineBuilder);
    shutdown_opengl();

    return 0;
}
