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
    ivec2 mouse = windowManager.getMousePosition();
    bool done = false;
    while(!done) {
        //utiliser pour avancer le véhicule
        float time = windowManager.getTime();
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
                //jour/nuit
            }
            if(windowManager.isKeyPressed(SDLK_c)){
                //caméra global/centré
            }
            if(windowManager.isKeyPressed(SDLK_s)){
                cout << time << endl;
                //véhicule arret/marche
            }
            ivec2 new_mouse = windowManager.getMousePosition();
            int diff_x = new_mouse.x - mouse.x;
            int diff_y = new_mouse.y - mouse.y;
            if((diff_x != 0 || diff_y != 0) && windowManager.isKeyPressed(SDLK_r)){
                vec2 rotate = {diff_x,diff_y};
                world.rotate(diff_x/2,vec3(0.0f,1.0f,0.0f));
            }
            mouse = windowManager.getMousePosition();
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
