#include <World.hpp>
#include <zconf.h>

using namespace global;

void World::init(const FilePath& filepath) {
//    environnement.init(filepath);
    vehicle.init(filepath);
    // J'ai déplacé le monde très loin pour avoir une vue global
    translate(vec3(0.0f,0.0f,-1000.0f));
    rotate(90.0f,vec3(0.0f,1.0f,0.0f));

    ProjMatrix *= ProjMatrixMul;
    NormalMatrix *= NormalMatrixMul;
}

void World::draw() {
//    environnement.draw();
    vehicle.draw();
}

void World::rotate(float angle,vec3 v){
    mat4 rotate = glm::rotate(MVMatrix,angle,v);
    ProjMatrix *= rotate;
    NormalMatrix *= rotate;
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