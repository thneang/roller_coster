#ifndef ROLLER_COSTER_FREEFLYCAMERA_HPP
#define ROLLER_COSTER_FREEFLYCAMERA_HPP

#include <cmath>
#include <glimac/glm.hpp>

class FreeFlyCamera {
private:
    glm::vec3 m_Position;
    float m_fPhi;
    float m_fTheta;
    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;
    float sensitivity;

    void computeDirectionVectors();

public:
    FreeFlyCamera() : m_Position(glm::vec3(0.0f,0.0f,0.0f)), m_fPhi(M_PI), m_fTheta(0.0f), sensitivity(0.3f) {
        computeDirectionVectors();
    }
    void moveLeft(float t);
    void moveFront(float t);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);

    glm::mat4 getViewMatrix() const;
};

#endif //ROLLER_COSTER_FREEFLYCAMERA_HPP
