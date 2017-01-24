#ifndef ROLLER_COSTER_ENVIRONNEMENT_HPP
#define ROLLER_COSTER_ENVIRONNEMENT_HPP

#include <glimac/Geometry.hpp>
#include <Drawable.hpp>
#include <RollPath.hpp>

class Vehicle : public Drawable {

private :
    glimac::Geometry vehicle;


public :

    void init(const glimac::FilePath& filepath = nullptr);

    void init_texture();

    void duplicate_vertex();

    void init_vbo();

    void init_vao();

    void init_index();

    void draw();

    void roll(glm::vec3 direction);

    void free();
};


#endif //ROLLER_COSTER_ENVIRONNEMENT_HPP
