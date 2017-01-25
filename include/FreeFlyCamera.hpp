#ifndef ROLLER_COSTER_FREEFLYCAMERA_HPP
#define ROLLER_COSTER_FREEFLYCAMERA_HPP

#include <cmath>
#include <glimac/glm.hpp>
#include <Camera.hpp>
class FreeFlyCamera : public Camera{
private:

    void computeDirectionVectors();

public:
    FreeFlyCamera() {
        m_Position = glm::vec3(0.0f,25.0f,0.0f);
        m_fPhi= M_PI;
        m_fTheta = 0.0f;
        sensitivity = 0.3f;
        computeDirectionVectors();
    }
    void moveLeft(float t);
    void moveFront(float t);
    float rotateLeft(float degrees);
    float rotateUp(float degrees);

    glm::mat4 getViewMatrix();
};

#endif //ROLLER_COSTER_FREEFLYCAMERA_HPP
