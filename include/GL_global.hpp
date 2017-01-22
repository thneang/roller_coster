#ifndef ROLLER_COSTER_GL_GLOBAL_HPP
#define ROLLER_COSTER_GL_GLOBAL_HPP

using namespace glm;

const static GLint VERTEX_ATTRIB_POSITION = 0;
const static GLint VERTEX_ATTRIB_POSITION_SIZE = 3;
const static GLint VERTEX_ATTRIB_NORMAL = 1;
const static GLint VERTEX_ATTRIB_NORMAL_SIZE = 3;
const static GLint VERTEX_ATTRIB_TEXTURE_COORD = 2;
const static GLint VERTEX_ATTRIB_TEXTURE_COORD_SIZE = 2;
static GLint WIN_WIDTH = 800;
static GLint WIN_HEIGTH = 600;
static float NEAR = 0.1f;
static float FAR = 100.f;
// Plus tard pour gérer des mouvements, pour la trajectoire surement
//static float TIME;

/************************ Matrices de reference de la scène, les objets sont tous dessiner par rapport à ça **************************/
// Modifier ces variables les modifies pour tous les objets Drawable
// Matrice ID
static mat4 ModelMatrix;

// convention, dessine l'objet vers le négatif de l'axe des Z
static mat4 ProjMatrix = perspective(radians(70.f), (float)WIN_WIDTH/WIN_HEIGTH, NEAR, FAR);
static mat4 MVMatrix = translate(ModelMatrix, vec3(0.f,0.f,-5.0f));
static mat4 NormalMatrix = transpose(inverse(MVMatrix));

/******************************************************************************************************************/
#endif //ROLLER_COSTER_GL_GLOBAL_HPP
