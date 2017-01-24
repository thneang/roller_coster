#ifndef ROLLER_COSTER_CAMERA_HPP
#define ROLLER_COSTER_CAMERA_HPP

#include <GL_global.hpp>

class TrackballCamera{
public:
    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;

public:
    TrackballCamera() : m_fDistance(5.0f), m_fAngleX(0.0f), m_fAngleY(0.0f){};
    void moveFront(float delta);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    glm::mat4 getViewMatrix() const;
};

#endif //ROLLER_COSTER_CAMERA_HPP
