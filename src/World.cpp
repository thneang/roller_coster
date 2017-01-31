#include <World.hpp>
#include <Environnement.hpp>
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


    /************************ à commenter pour voir la trajectoire ****************************************************/
    Sky *sky = new Sky();
    world.push_back(std::move(sky));
    /******************************************************************************************************************/


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

glm::vec3 World::vehiclePosition() {
    return vehicle->getCenter();
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
