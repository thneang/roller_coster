#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <World.hpp>
#include <FreeFlyCamera.hpp>
#include <TrackballCamera.hpp>
#include <GL/glut.h>

using namespace glimac;
using namespace global;
using namespace std;
using namespace glm;
int main(int argc, char** argv) {
    // Initialize SDL and open a window
//    int width = glutGet(GLUT_SCREEN_WIDTH);
//    int height = glutGet(GLUT_SCREEN_HEIGHT);
    SDLWindowManager windowManager(/*width, height*/800,600, "GLImac");
    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    FilePath applicationPath(argv[0]);


    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    static bool GLOBAL = true;
    TrackballCamera trackballCamera;
    FreeFlyCamera freeFlyCamera;
    Camera *camera = &trackballCamera;
    World world;
    world.init(applicationPath);

    // Application loop:
    bool done = false;
    while(!done) {
        // Mets a jour les matrices du monde
        MVMatrix = camera->getViewMatrix();
        NormalMatrix = transpose(inverse(MVMatrix));
        //utiliser pour avancer le véhicule
        float time = windowManager.getTime();
        // Event loop:
        SDL_Event e;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            if(windowManager.isKeyPressed(SDLK_ESCAPE)){
                done = true;
            }
            if(windowManager.isKeyPressed(SDLK_n)){
                //jour/nuit
            }
            if(windowManager.isKeyPressed(SDLK_c)){
                //caméra global/centré
                if (GLOBAL) {
                    camera = &freeFlyCamera;
                    GLOBAL = false;
                } else {
                    camera = &trackballCamera;
                    GLOBAL = true;
                }
            }
            if(windowManager.isKeyPressed(SDLK_s)){
                cout << time << endl;
                //véhicule arret/marche
            }

            if(windowManager.isKeyPressed(SDLK_LEFT)) {
                camera->moveLeft(CAMERA_TRANSLATE_SPEED);
            }
            if(windowManager.isKeyPressed(SDLK_RIGHT)) {
                camera->moveLeft(-CAMERA_TRANSLATE_SPEED);
            }
            if(windowManager.isKeyPressed(SDLK_UP)) {
                camera->moveFront(CAMERA_TRANSLATE_SPEED);
            }
            if(windowManager.isKeyPressed(SDLK_DOWN)) {
                camera->moveFront(-CAMERA_ANGLE_SPEED);
            }
            if(windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
                SDL_WM_GrabInput(SDL_GRAB_ON);
                if(e.type == SDL_MOUSEMOTION) {
                    camera->rotateUp(e.motion.yrel);
                    camera->rotateLeft(e.motion.xrel);
                }
            }
            SDL_WM_GrabInput(SDL_GRAB_OFF);


        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        world.draw();

        // Update the display
        windowManager.swapBuffers();
    }
    world.free();

    return EXIT_SUCCESS;
}
