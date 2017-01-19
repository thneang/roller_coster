#include <glimac/SDLWindowManager.hpp>
#include <glimac/Geometry.hpp>
#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/common.hpp>
#include <iostream>
#include "ground.hpp"

using namespace glimac;
using namespace glm;


const GLint VERTEX_ATTRIB_POSITION = 0;
const GLint VERTEX_ATTRIB_POSITION_SIZE = 2;
const GLint VERTEX_ATTRIB_TEXTURE_COORD = 2;
const GLint VERTEX_ATTRIB_TEXTURE_COORD_SIZE = 2;
GLint WIN_WIDTH = 1920;
GLint WIN_HEIGTH = 1080;

struct Vertex2DUV
{
    glm::vec2 position;
    glm::vec2 t_coord;

    Vertex2DUV();
    Vertex2DUV(glm::vec2 val, glm::vec2 val2) {position = val; t_coord = val2;};
};

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(WIN_WIDTH, WIN_HEIGTH, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    FilePath applicationPath(argv[0]);
    if (argc < 3) {
        std::cerr << "Error, missing params" << std::endl;
        return EXIT_FAILURE;
    }
    glEnable(GL_DEPTH_TEST);

    Program program = loadProgram(applicationPath.dirPath() + argv[1],
                                  applicationPath.dirPath() + argv[2]);
    program.use();
    Geometry g = Geometry();
//    g.loadOBJ("objet","materiel");

    GLuint uMVPMatrixId = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLuint uMVMatrixId = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLuint uNormalMatrixId = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

    Ground ground(10, 10, 32, 16);

    GLuint vbo;
    // création du buffer
    glGenBuffers(1, &vbo);

    // bind le buffer créer pour mettre nos données
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    const ShapeVertex *vertices = ground.getDataPointer();

    // Envoie les donnés
    glBufferData(GL_ARRAY_BUFFER, ground.getVertexCount()*sizeof(ShapeVertex), vertices, GL_STATIC_DRAW);*/

    // Pour les coordonnées de texture
    // Le coin haut-gauche a pour coordonnées (0,0) et le coin bas-droit (1,1) (quelque soit les dimensions de l'image d'entrée).
//
//    Vertex2DUV vertices [] = {
//            Vertex2DUV(glm::vec2(-1.0, -1.0), glm::vec2(0.0, 1.0)),
//            Vertex2DUV(glm::vec2(1.0, -1.0), glm::vec2(1.0, 1.0)),
//            Vertex2DUV(glm::vec2(0.0, 1.0), glm::vec2(0.5, 0.0)),
//    };

    // Envoie les donnés
//    glBufferData(GL_ARRAY_BUFFER, 3*sizeof(Vertex2DUV), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vao;

    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glEnableVertexAttribArray(VERTEX_ATTRIB_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTRIB_TEXTURE_COORD);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(VERTEX_ATTRIB_POSITION, VERTEX_ATTRIB_POSITION_SIZE, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid *) offsetof(Vertex2DUV, position));
    glVertexAttribPointer(VERTEX_ATTRIB_TEXTURE_COORD, VERTEX_ATTRIB_TEXTURE_COORD_SIZE, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid *) offsetof(Vertex2DUV, t_coord));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            if(windowManager.isKeyPressed(SDLK_ESCAPE)){
                done = true;
            }
            if(windowManager.isKeyPressed(SDLK_n)){

            }
            if(windowManager.isKeyPressed(SDLK_c)){

            }
            if(windowManager.isKeyPressed(SDLK_s)){

            }
        }
        glBindVertexArray(vao);
        glUniformMatrix4fv(uMVPMatrixId, 1, GL_FALSE, value_ptr(ProjMatrix * Matrix_Spere_Rotatation));
        glUniformMatrix4fv(uMVMatrixId, 1, GL_FALSE, value_ptr(Matrix_Spere_Rotatation));
        glUniformMatrix4fv(uNormalMatrixId, 1, GL_FALSE, value_ptr(NormalMatrix * Matrix_Spere_Rotatation));

        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
