#ifndef ROLLER_COSTER_DRAWABLE_HPP
#define ROLLER_COSTER_DRAWABLE_HPP


class Drawable {
public :

    // Init l'objet, envoie les données au gpu et demarre un programme pour les shaders
    virtual void init(char []) = 0;

    // Demande de dessin a openGL
    virtual void draw() = 0;

};


#endif //ROLLER_COSTER_DRAWABLE_HPP
