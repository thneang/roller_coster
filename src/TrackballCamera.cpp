#include <TrackballCamera.hpp>

void TrackballCamera::moveFront(float delta) {
    m_fDistance += delta;
}
void TrackballCamera::rotateLeft(float degrees) {
    m_fAngleY += degrees;
}
void TrackballCamera::rotateUp(float degrees) {
    m_fAngleX += degrees;
}
glm::mat4 TrackballCamera::getViewMatrix() const {
    glm::mat4 VMatrix;
    VMatrix *= glm::translate(VMatrix, glm::vec3(0.0f, 0.0f, m_fDistance));
    VMatrix *= glm::rotate(VMatrix, glm::radians(m_fAngleX), glm::vec3(1.0f,0.0f,0.0f));
    VMatrix *= glm::rotate(VMatrix, glm::radians(m_fAngleY), glm::vec3(0.0f,1.0f,0.0f));
    return VMatrix;
}