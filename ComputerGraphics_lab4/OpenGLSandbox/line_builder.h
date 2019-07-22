#ifndef LINE_H
#define LINE_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "object.h"
#include "shader_program.h"

class LineBuilder
{
public:
    Shader_program* shaderProgram;
    double line_width;
    LineBuilder()
    {
        line_width = 0.02;
        shaderProgram = new Shader_program("D:/Qt Progects/OpenGLSandbox/OpenGLSandbox/Shaders/line_vertex.sh", "D:/Qt Progects/OpenGLSandbox/OpenGLSandbox/Shaders/line_fragment.sh");

    }
    LineBuilder(double width) : line_width(width)
    {
        shaderProgram = new Shader_program("D:/Qt Progects/OpenGLSandbox/OpenGLSandbox/Shaders/line_vertex.sh", "D:/Qt Progects/OpenGLSandbox/OpenGLSandbox/Shaders/line_fragment.sh");
    }


    Object* generateLine(vector<vec2> &controlPoints)
    {
        vector<GLfloat> vertices_line;
        vector<GLuint> indices_line;
        const int step = 4;
        for(int i = 0; i<int(controlPoints.size())-1;i++)
        {
            vec2 coord = controlPoints[i];
            vec2 coord_next = controlPoints[i+1];

            double A = coord.y - coord_next.y;
            double B = coord_next.x - coord.x;
            vec2 norm = glm::normalize(vec2(A,B));
            if(i > 0)
            {
                double A = controlPoints[i-1].y - coord_next.y;
                double B = coord_next.x - controlPoints[i-1].x;
                norm = glm::normalize(vec2(A,B));
            }
            vec2 norm_next = glm::normalize(vec2(A,B));
            if(i+2<controlPoints.size())
            {
                double A = coord.y - controlPoints[i+2].y;
                double B = controlPoints[i+2].x - coord.x;;
                norm_next = glm::normalize(vec2(A,B));
            }

            mat4 model = translate(mat4(1.0f), vec3(coord.x,coord.y,0.0f));
            model = scale(model,vec3(0.01f));
            mat4 model_next = translate(mat4(1.0f), vec3(coord_next.x,coord_next.y,0.0f));
            model_next = scale(model_next,vec3(0.01f));

            vec2 p1, p2, p3, p4;

            vec2 shift = vec2(line_width/2);
            p1 = coord + norm*shift;
            p2 = coord - norm*shift;
            p3 = coord_next + norm_next*shift;
            p4 = coord_next - norm_next*shift;

            vertices_line.push_back(p1.x);
            vertices_line.push_back(p1.y);
            vertices_line.push_back(p2.x);
            vertices_line.push_back(p2.y);
            vertices_line.push_back(p3.x);
            vertices_line.push_back(p3.y);
            vertices_line.push_back(p4.x);
            vertices_line.push_back(p4.y);

            indices_line.push_back(i*step+0);
            indices_line.push_back(i*step+1);
            indices_line.push_back(i*step+2);
            indices_line.push_back(i*step+2);
            indices_line.push_back(i*step+3);
            indices_line.push_back(i*step+1);
        }
        vector<GLuint> vertices_structure_line = { 2, 2 };
        Object* line = new Object(vertices_line,vertices_structure_line,indices_line,shaderProgram->id);
        return line;
    }
};

#endif // LINE_H
