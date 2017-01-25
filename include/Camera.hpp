#ifndef ROLLER_COSTER_CAMERA_HPP
#define ROLLER_COSTER_CAMERA_HPP


class Camera {
protected:
    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;
    glm::vec3 m_Position;
    float m_fPhi;
    float m_fTheta;
    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;
    float sensitivity;
public:
    virtual void moveLeft(float t){};
    virtual void moveFront(float t){};
    virtual float rotateLeft(float degrees){return 0.0f;};
    virtual float rotateUp(float degrees){return 0.0f;};

    virtual glm::mat4 getViewMatrix(){
        glm::mat4 res;
        return res;
    }
};


#endif //ROLLER_COSTER_CAMERA_HPP
