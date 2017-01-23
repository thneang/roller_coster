#include <World.hpp>
#include <zconf.h>

using namespace global;

void World::init(const FilePath& filepath) {
//    environnement.init(filepath);
    vehicle.init(filepath);
    // J'ai déplacé le monde très loin pour avoir une vue global

    mat4 translate = glm::translate(MVMatrix, vec3(0.0f,0.0f,-1000.0f));
    mat4 rotate = glm::rotate(MVMatrix, 90.0f, vec3(0.0f,1.0f,0.0f));

    ProjMatrix = ProjMatrix * translate * rotate;
    NormalMatrix = NormalMatrix * translate * rotate;
}

void World::draw() {
//    environnement.draw();

    vehicle.draw();
}

// TODO effacer les translates de environnement
void World::translate(vec3 v){
//    environnement.translate(v);
}

void World::rotate(vec2 v){
//    environnement.rotate(v);
}
void World::free() {
//    environnement.free();
    vehicle.free();
}