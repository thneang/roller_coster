#ifndef ROLLER_COSTER_ENVIRONNEMENT_HPP
#define ROLLER_COSTER_ENVIRONNEMENT_HPP

#include <glimac/Geometry.hpp>
#include <Drawable.hpp>

using namespace glimac;

class Environnement : public Drawable {

private :
    glimac::Geometry environnement;

public :

    void init(const FilePath& filepath = nullptr);

    void init_texture();

    void duplicate_vertex();

    void init_vbo();

    void init_vao();

    void init_index();

    void translate(vec3 v);

    void rotate(vec2 v);

    void draw();

    void free();
};


#endif //ROLLER_COSTER_ENVIRONNEMENT_HPP
