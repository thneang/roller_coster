#include <Environnement.hpp>
#include <glimac/Geometry.hpp>

using namespace glimac;


void Environnement::init(const FilePath& filepath) {
    this->environnement.loadOBJ(
            filepath.dirPath() + "assets/3D_models/SnowTerrain/SnowTerrain.obj",
            filepath.dirPath() + "assets/3D_models/SnowTerrain/SnowTerrain.mtl",
            true
    );

}

// TODO
void Environnement::init_texture() {
// créer un buffer pour notre texture
    glGenTextures(1, &texture);

    // on bind la texture
    glBindTexture(GL_TEXTURE_2D, this->texture);

    // On envoie l'image
//    this->environnement.
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_FLOAT, image->getPixels());
}

// TODO
void Environnement::init_vbo() {
    // création du buffer
    glGenBuffers(1, &vbo);

    // bind le buffer créer pour mettre nos données
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Envoie les donnés
    glBufferData(GL_ARRAY_BUFFER, this->environnement.getVertexCount()*sizeof(Geometry::Vertex), this->environnement.getVertexBuffer(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

// TODO
void Environnement::init_vao() {

}

void Environnement::draw() {

}