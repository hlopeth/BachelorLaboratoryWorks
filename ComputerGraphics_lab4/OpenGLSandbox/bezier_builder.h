#ifndef BEZIER_H
#define BEZIER_H

#include <vector>
#include <glm/gtc/type_ptr.hpp>

class BezierBuilder
{
public:
    BezierBuilder()
    {}

    std::vector<glm::vec2>* generateBezierCurve(std::vector<glm::vec2>& linePoints, std::vector<glm::vec2>& directingPoints)
    {
        std::vector<glm::vec2>* leBezierCurve = new std::vector<glm::vec2>;
        for(int i =1, j=0; i< linePoints.size();i++)
        {
            glm::vec2 p0 = linePoints[i-1];
            glm::vec2 p1 = directingPoints[j++];
            glm::vec2 p2 = directingPoints[j++];
            glm::vec2 p3 = linePoints[i];
            for(float t =0; t<=1; t+=0.02)
            {
                float mt = (1-t);
                vec2 a = vec2( mt*mt*mt*p0.x,  mt*mt*mt*p0.y);
                vec2 b = vec2(3*t*mt*mt*p1.x, 3*t*mt*mt*p1.y);
                vec2 c = vec2( 3*t*t*mt*p2.x,  3*t*t*mt*p2.y);
                vec2 d = vec2(    t*t*t*p3.x,     t*t*t*p3.y);
                leBezierCurve->push_back(a + b + c + d);
            }
        }
        return leBezierCurve;
    }

    std::vector<glm::vec2>* generateBezierCurve(glm::vec2 p0, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3)
    {
        std::vector<glm::vec2>* leBezierCurve = new std::vector<glm::vec2>;
        for(float t =0; t<=1; t+=0.02)
        {
            float mt = (1-t);
            vec2 a = vec2(mt*mt*mt*p0.x,t*t*t*p0.y);
            vec2 b = vec2(3*t*mt*mt*p1.x,3*t*mt*mt*p1.y);
            vec2 c = vec2(3*t*t*mt*p2.x,3*t*t*mt*p2.y);
            vec2 d = vec2(t*t*t*p3.x,t*t*t*p3.y);
            leBezierCurve->push_back(a + b + c + d);
        }
        return leBezierCurve;
    }

    std::vector<glm::vec2>* generateBezierNorms(std::vector<glm::vec2>& linePoints, std::vector<glm::vec2>& directingPoints)
    {
        std::vector<glm::vec2>* leBezierCurve = new std::vector<glm::vec2>;
        for(int i =1, j=0; i< linePoints.size();i++)
        {
            glm::vec2 p0 = linePoints[i-1];
            glm::vec2 p1 = directingPoints[j++];
            glm::vec2 p2 = directingPoints[j++];
            glm::vec2 p3 = linePoints[i];
            for(float t =0; t<=1; t+=0.02)
            {
                float mt = (1-t);
                vec2 a = vec2( -3*mt*mt*p0.x,  -3*mt*mt*p0.y);
                vec2 b = vec2((3*mt*mt-6*t*mt)*p1.x, (3*mt*mt-6*t*mt)*p1.y);
                vec2 c = vec2( (6*t*mt-3*t*t)*p2.x,  (6*t*mt-3*t*t)*p2.y);
                vec2 d = vec2(    9*t*t*p3.x,     9*t*t*p3.y);
                leBezierCurve->push_back(glm::normalize(a + b + c + d));
            }
        }
        return leBezierCurve;
    }
};

#endif // BEZIER_H
