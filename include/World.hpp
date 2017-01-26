#ifndef ROLLER_COSTER_WORLD_HPP
#define ROLLER_COSTER_WORLD_HPP

#include <Drawable.hpp>

class World : public Drawable {

private :
    // TODO Pouvoir faire un array de drawable pour mettre tout nos éléments
    std::vector<Drawable*> world;
public :

    void init(const glimac::FilePath& filepath = nullptr);

    void draw();

    void rotate(float angle,glm::vec3 v);

    void rotateCamera(glm::vec2 v);

    void translate(glm::vec3 v);

    void scale(glm::vec3 v);

    void roll(float time);

    void free();
};


#endif //ROLLER_COSTER_WORLD_HPP
