#include <GL_global.hpp>
using namespace glm;
namespace global {
    const GLint VERTEX_ATTRIB_POSITION = 0;
    const GLint VERTEX_ATTRIB_POSITION_SIZE = 3;
    const GLint VERTEX_ATTRIB_NORMAL = 1;
    const GLint VERTEX_ATTRIB_NORMAL_SIZE = 3;
    const GLint VERTEX_ATTRIB_TEXTURE_COORD = 2;
    const GLint VERTEX_ATTRIB_TEXTURE_COORD_SIZE = 2;
    GLint WIN_WIDTH = 800;
    GLint WIN_HEIGTH = 600;
    float NEAR = 0.1f;
    float FAR = 99999.f;
// Plus tard pour gérer des mouvements, pour la trajectoire surement
//static float TIME;

/************************ Matrices de reference de la scène, les objets sont tous dessiner par rapport à ça **************************/
// Modifier ces variables les modifies pour tous les objets Drawable
// Matrice ID
    mat4 ModelMatrix;

// convention, dessine l'objet vers le négatif de l'axe des Z
    mat4 ProjMatrix = perspective(radians(70.f), (float)WIN_WIDTH/WIN_HEIGTH, NEAR, FAR);
    mat4 MVMatrix = translate(ModelMatrix, vec3(0.f,0.f,-5.0f));
    mat4 NormalMatrix = transpose(inverse(MVMatrix));

/******************************************************************************************************************/
}
