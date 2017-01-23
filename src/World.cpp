#include <World.hpp>
#include <zconf.h>

using namespace global;

void World::init(const FilePath& filepath) {
//    environnement.init(filepath);
    vehicle.init(filepath);
    // J'ai déplacé le monde très loin pour avoir une vue global
    translate(vec3(0.0f,0.0f,-1000.0f));
    rotate(90.0f,vec3(0.0f,1.0f,0.0f));
}

void World::draw() {
//    environnement.draw();
    vehicle.draw();
}

void World::rotateCamera(vec2 v){
    ProjMatrix = glm::rotate(ProjMatrix,v.x/100,vec3(0,1,0));
    NormalMatrix *= ProjMatrix;
    ProjMatrix = glm::rotate(ProjMatrix,v.y/100,vec3(1,0,0));
    NormalMatrix *= ProjMatrix;
}

void World::rotate(float angle, vec3 v){
    MVMatrix = glm::rotate(MVMatrix,angle,v);
    ProjMatrix *= MVMatrix;
    NormalMatrix *= MVMatrix;
}

void World::translate(vec3 v){
    mat4 translate = glm::translate(MVMatrix,v);
    ProjMatrix *= translate;
    NormalMatrix *= translate;
}

void World::scale(vec3 v){
    mat4 scale = glm::scale(MVMatrix,v);
    ProjMatrix *= scale;
    NormalMatrix *= scale;
}

void World::free() {
//    environnement.free();
    vehicle.free();
}