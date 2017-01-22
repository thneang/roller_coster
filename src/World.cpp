#include <World.hpp>

void World::init(const FilePath& filepath) {
    environnement.init(filepath);
}

void World::draw() {
    environnement.draw();
}

void World::translate(vec3 v){
    environnement.translate(v);
}

void World::rotate(vec2 v){
    environnement.rotate(v);
}
void World::free() {
    environnement.free();
}