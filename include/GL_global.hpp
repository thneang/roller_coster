#ifndef ROLLER_COSTER_GL_GLOBAL_HPP
#define ROLLER_COSTER_GL_GLOBAL_HPP

#include <GL/glew.h>
#include <glimac/glm.hpp>

namespace global {
    extern const GLint VERTEX_ATTRIB_POSITION;
    extern const  GLint VERTEX_ATTRIB_POSITION_SIZE;
    extern const  GLint VERTEX_ATTRIB_NORMAL;
    extern const  GLint VERTEX_ATTRIB_NORMAL_SIZE;
    extern const  GLint VERTEX_ATTRIB_TEXTURE_COORD;
    extern const  GLint VERTEX_ATTRIB_TEXTURE_COORD_SIZE;
    extern GLint WIN_WIDTH;
    extern GLint WIN_HEIGTH;
    extern float CAMERA_TRANSLATE_SPEED;
    extern float CAMERA_ANGLE_SPEED;
    extern float NEAR;
    extern float FAR;
// Plus tard pour gérer des mouvements, pour la trajectoire surement
// float TIME;

/************************ Matrices de reference de la scène, les objets sont tous dessiner par rapport à ça **************************/
// Modifier ces variables les modifies pour tous les objets Drawable
// Matrice ID
    extern  glm::mat4 ModelMatrix;

// convention, dessine l'objet vers le négatif de l'axe des Z
    extern  glm::mat4 ProjMatrix;
    extern  glm::mat4 MVMatrix;
    extern  glm::mat4 NormalMatrix;

/******************************************************************************************************************/
}

#endif //ROLLER_COSTER_GL_GLOBAL_HPP
