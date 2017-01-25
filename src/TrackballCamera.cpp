#include <TrackballCamera.hpp>

void TrackballCamera::moveFront(float delta) {
    m_fDistance += delta;
}
float TrackballCamera::rotateLeft(float degrees) {

    m_fAngleY += degrees;
    return m_fAngleY;
}
float TrackballCamera::rotateUp(float degrees) {
    if(m_fAngleX+degrees > 45){
        m_fAngleX = 45.0f;
    }
    else if(m_fAngleX+degrees < -45){
        m_fAngleX = -45.0f;
    }
    else{
        m_fAngleX += degrees;
    }
    return m_fAngleX;
}
glm::mat4 TrackballCamera::getViewMatrix() {
    glm::mat4 VMatrix;
    VMatrix *= glm::translate(VMatrix, glm::vec3(0.0f, 0.0f, m_fDistance));
    VMatrix *= glm::rotate(VMatrix, glm::radians(m_fAngleX), glm::vec3(1.0f,0.0f,0.0f));
    VMatrix *= glm::rotate(VMatrix, glm::radians(m_fAngleY), glm::vec3(0.0f,1.0f,0.0f));
    return VMatrix;
}