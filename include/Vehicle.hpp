#ifndef ROLLER_COSTER_VEHICLE_HPP
#define ROLLER_COSTER_VEHICLE_HPP

#include <glimac/Geometry.hpp>
#include <Drawable.hpp>
#include <RollPath.hpp>

class Vehicle : public Drawable {

private :
    glimac::Geometry vehicle;

    glm::vec3 vCenter = glm::vec3(0.710f,13.802f,0.0f);

    glm::mat4 RollMatrix;

    glm::mat4 scale = glm::scale(global::MatrixID, glm::vec3(2.f, 2.f, 2.f));

public :

    void init(const glimac::FilePath& filepath = nullptr);

    void init_texture();

    void init_vbo();

    void init_vao();

    void init_index();

    void draw();

    void roll(glm::vec3 v);

    glm::vec3 getCenter();

    void free();
};


#endif //ROLLER_COSTER_VEHICLE_HPP
