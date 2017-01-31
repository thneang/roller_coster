#ifndef ROLLER_COSTER_SKY_HPP
#define ROLLER_COSTER_SKY_HPP

#include <Drawable.hpp>

class Sky : public Drawable {

private :
    glimac::Geometry sky;
    glm::mat4 scale = glm::scale(global::MatrixID, glm::vec3(50.f, 50.f, 50.f));


public :

    void init(const glimac::FilePath& filepath = nullptr);

    void init_texture();

    void init_vbo();

    void init_vao();

    void init_index();

    void draw();

    void free();
};


#endif //ROLLER_COSTER_SKY_HPP
