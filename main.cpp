#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <World.hpp>

using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

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

//    Environnement environnement;
    World world;
    world.init(applicationPath);

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
