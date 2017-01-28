#include <World.hpp>
#include <RollPath.hpp>
#include <Environnement.hpp>
#include <Vehicle.hpp>
#include <Sky.hpp>

using namespace global;
using namespace glm;
using namespace glimac;

void World::init(const FilePath& filepath) {
    Environnement *environnement = new Environnement();
    world.push_back(std::move(environnement));

    RollPath *rollPath = new RollPath();
    world.push_back(std::move(rollPath));

    vehicle = new Vehicle();


//    Sky *sky = new Sky();
//    world.push_back(std::move(sky));

    for (Drawable *object : world) {
        object->init(filepath);
    }
    vehicle->init(filepath);
}

void World::draw() {
    if(isRolling()){
        RollPath *r  = (RollPath*)world[1];
        clock_t a = clock();
        vec3 vec = r->getPointOfTime(a - clock_start + timeRolled);
        vehicle->roll(vec);
    }
    for (Drawable *object : world) {
        object->draw();
    }
    vehicle->draw();
}

//void World::rotateCamera(vec2 v){
//    ProjMatrix = glm::rotate(ProjMatrix,v.x/100,vec3(0,1,0));
//    NormalMatrix *= ProjMatrix;
//    ProjMatrix = glm::rotate(ProjMatrix,v.y/100,vec3(1,0,0));
//    NormalMatrix *= ProjMatrix;
//}

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
void World::vehicleStart(){
    vehicleIsRolling = true;
    clock_start = clock();
}

void World::vehicleStop() {
    vehicleIsRolling = false;
    clock_t c = clock();
    timeRolled += c - clock_start;
}

bool World::isRolling() {
    return vehicleIsRolling;
}

void World::free() {
    for (Drawable *object : world) {
        object->free();
    }
    vehicle->free();
}
