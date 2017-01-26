#ifndef ROLLER_COSTER_VEHICLE_HPP
#define ROLLER_COSTER_VEHICLE_HPP

#include <glimac/Geometry.hpp>
#include <Drawable.hpp>
#include <RollPath.hpp>

class Vehicle : public Drawable {

private :
    glimac::Geometry vehicle;


public :

    void init(const glimac::FilePath& filepath = nullptr);

    void init_texture();

    void init_vbo();

    void init_vao();

    void init_index();

    void draw();

    void roll(float time);

    void free();
};


#endif //ROLLER_COSTER_VEHICLE_HPP
