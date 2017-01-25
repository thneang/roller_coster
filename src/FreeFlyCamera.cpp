#include <FreeFlyCamera.hpp>

using namespace glm;

void FreeFlyCamera::computeDirectionVectors() {
    // F⃗ =(cos(θ)sin(ϕ), sin(θ), cos(θ)cos(ϕ))
    m_FrontVector = vec3(cos(m_fTheta) * sin(m_fPhi), sin(m_fTheta), cos(m_fTheta) * cos(m_fPhi));

    // L =(sin(ϕ+π/2), 0, cos(ϕ+π/2))
    m_LeftVector = vec3(sin(m_fPhi + M_PI / 2.0f), 0.f, cos(m_fPhi + M_PI / 2.f));

    // U = F * L
    m_UpVector = cross(m_FrontVector, m_LeftVector);
}

void FreeFlyCamera::moveLeft(float t) {
    m_Position += t * m_LeftVector;
}

void FreeFlyCamera::moveFront(float t) {
    m_Position += t * m_FrontVector;
}

float FreeFlyCamera::rotateLeft(float degrees) {
    m_fPhi += radians(degrees * sensitivity);
    return m_fPhi;
}
float FreeFlyCamera::rotateUp(float degrees) {
    if(m_fTheta + radians(degrees * sensitivity) > 45){
        m_fTheta = 45.0f;
    }
    else if(m_fTheta + radians(degrees * sensitivity) < -45){
        m_fTheta = -45.0f;
    }
    else{
        m_fTheta += radians(degrees * sensitivity);
    }
    return m_fTheta;
}

glm::mat4 FreeFlyCamera::getViewMatrix() {
    //  glm::lookAt(eye, point, up).
    // Le premier argument est simplement la position de la caméra exprimée dans le monde.
    // Le deuxième argument est un point que la caméra regarde. Le dernier argument est l'axe vertical de la caméra.

//    V=P+F
    computeDirectionVectors();
    return lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
}