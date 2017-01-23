#ifndef ROLLER_COSTER_WORLD_HPP
#define ROLLER_COSTER_WORLD_HPP

#include <Drawable.hpp>
//#include <Environnement.hpp>
#include <Vehicle.hpp>
#include <RollPath.hpp>

using namespace glimac;

class World : public Drawable {

private :
    // TODO Pouvoir faire un array de drawable pour mettre tout nos éléments
//    Environnement environnement;
    Vehicle vehicle;
    RollPath roll_path;
public :

    void init(const FilePath& filepath = nullptr);

    void draw();

    void rotate(float angle,vec3 v);

    void rotateCamera(vec2 v);

    void translate(vec3 v);

    void scale(vec3 v);

    void roll(float time);

    void free();
};


#endif //ROLLER_COSTER_WORLD_HPP
