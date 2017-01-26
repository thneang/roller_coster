#include <World.hpp>
#include <RollPath.hpp>
#include <Environnement.hpp>
#include <Vehicle.hpp>

using namespace global;
using namespace glm;
using namespace glimac;

void World::init(const FilePath& filepath) {
    Environnement *environnement = new Environnement();
    world.push_back(std::move(environnement));

    RollPath *rollPath = new RollPath();
    world.push_back(std::move(rollPath));

    Vehicle *vehicle = new Vehicle();
    world.push_back(std::move(vehicle));

    for (Drawable *object : world) {
        object->init(filepath);
    }
}

void World::draw() {
    for (Drawable *object : world) {
        object->draw();
    }
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
    mat4 translate = glm::translate(ProjMatrix,v);
    ProjMatrix = translate;
    NormalMatrix *= translate;
}

void World::scale(vec3 v){
    MVMatrix = glm::scale(MVMatrix,v);
    ProjMatrix *= MVMatrix;
    NormalMatrix *= MVMatrix;
}

// TODO utilise le roll de vehicle et pas passe par world
void World::roll(float time){
//    vehicle.roll(time);
}

void World::free() {
    for (Drawable *object : world) {
        object->free();
    }
}
