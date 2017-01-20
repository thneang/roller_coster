#ifndef ROLLER_COSTER_DRAWABLE_HPP
#define ROLLER_COSTER_DRAWABLE_HPP
#include <glimac/Program.hpp>
#include <iostream>

using namespace glimac;

class Drawable {
public :

    GLuint texture;
    GLuint vbo;
    GLuint vao;
    // Init l'objet, envoie les données au gpu et demarre un programme pour les shaders
    virtual void init(const FilePath& filepath = nullptr) = 0;

    // Demande de dessin a openGL
    virtual void draw() = 0;

};


#endif //ROLLER_COSTER_DRAWABLE_HPP
