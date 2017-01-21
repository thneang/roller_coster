#include <World.hpp>

void World::init(const FilePath& filepath) {
    environnement.init(filepath);
}

void World::draw() {
    environnement.draw();
}

void World::free() {
    environnement.free();
}