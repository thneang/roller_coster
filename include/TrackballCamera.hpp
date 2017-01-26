#ifndef ROLLER_COSTER_TRACKBALLCAMERA_HPP
#define ROLLER_COSTER_TRACKBALLCAMERA_HPP

#include <GL_global.hpp>
#include <Camera.hpp>

class TrackballCamera : public Camera {


public:
    TrackballCamera() {
        m_fDistance = -200.0f;
        m_fAngleX = 13.0f;
        m_fAngleY = 32.0f;
    };
    void moveFront(float delta);
    float rotateLeft(float degrees);
    float rotateUp(float degrees);
    glm::mat4 getViewMatrix();
};

#endif //ROLLER_COSTER_CAMERA_HPP
