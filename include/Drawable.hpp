#ifndef ROLLER_COSTER_DRAWABLE_HPP
#define ROLLER_COSTER_DRAWABLE_HPP

#include <glimac/Image.hpp>
#include <glimac/Program.hpp>
#include <iostream>

using namespace glimac;
using namespace std;

class Drawable {
protected :

    // ensemble des "ID" de texture
    GLuint *texture;
    // "ID" du buffer de vertex
    GLuint vbo;
    //"ID" du buffer attribut
    GLuint vao;

    // Contient les "ID" de nos meshes
    GLuint elements[2];

    // Nos images utilisé par les textures
    // TODO passer en pointeur pour plusieurs textures
    unique_ptr<Image> images[1];

    // Program pour utiliser les shaders
    Program program;

public :
    // Init l'objet (allocation), envoie les données au gpu et demarre un programme pour les shaders
    virtual void init(const FilePath& filepath = nullptr) = 0;

    // envoie l'image au gpu
    virtual void init_texture() {};

    // envoie les sommets au gpu
    virtual void init_vbo() {};

    // decrit les données pour le gpu
    virtual void init_vao() {};

    // permet d'utiliser l'indexation des sommets pour draw
    // cela permet de d'éviter de duppliquer des sommets
    // lorsqu'on dessine nos triangles pour les objets
    virtual void init_index() {}

    // Demande de dessin a openGL
    virtual void draw() = 0;

    // libere l'espace allouée, doit être appelé à la fin du programme
    virtual void free() = 0;

};


#endif //ROLLER_COSTER_DRAWABLE_HPP
