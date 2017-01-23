#ifndef ROLLER_COSTER_WORLD_HPP
#define ROLLER_COSTER_WORLD_HPP

#include <Drawable.hpp>
//#include <Environnement.hpp>
#include <Vehicle.hpp>

using namespace glimac;

class World : public Drawable {

private :
    // TODO Pouvoir faire un array de drawable pour mettre tout nos éléments
//    Environnement environnement;
    Vehicle vehicle;
public :

    void init(const FilePath& filepath = nullptr);

    void draw();

    void free();
};


#endif //ROLLER_COSTER_WORLD_HPP
