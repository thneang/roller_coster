#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <World.hpp>
#include <FreeFlyCamera.hpp>
using namespace glimac;
using namespace global;
using namespace std;
using namespace glm;
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

    FreeFlyCamera camera;
    World world;
    world.init(applicationPath);

    // Application loop:
    bool done = false;
    ivec2 mouse = windowManager.getMousePosition();
    float old_time =0.0f;
    while(!done) {
        // Mets a jour les matrices du monde
        MVMatrix = camera.getViewMatrix();
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
            }
            if(windowManager.isKeyPressed(SDLK_s)){
                cout << time << endl;
                //véhicule arret/marche
            }

            if(windowManager.isKeyPressed(SDLK_LEFT)) {
                camera.moveLeft(CAMERA_TRANSLATE_SPEED);
            }
            if(windowManager.isKeyPressed(SDLK_RIGHT)) {
                camera.moveLeft(-CAMERA_TRANSLATE_SPEED);
            }
            if(windowManager.isKeyPressed(SDLK_UP)) {
                camera.moveFront(CAMERA_TRANSLATE_SPEED);
            }
            if(windowManager.isKeyPressed(SDLK_DOWN)) {
                camera.moveFront(-CAMERA_ANGLE_SPEED);
            }
            if(windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
//                cout << "Right" << endl;
                // permet de garder la souris dans la fenetre
//                if(time - old_time > 0.02f){
//                    SDL_WM_GrabInput(SDL_GRAB_ON);
//                     cache la souris
//                    SDL_ShowCursor(0);
//                    ivec2 new_mouse = windowManager.getMousePosition();
//                    int diff_x = new_mouse.x - mouse.x;
//                    int diff_y = new_mouse.y - mouse.y;
//                    /*(diff_x != 0 || diff_y != 0) &&*/
//                    if((diff_x != 0 || diff_y != 0))
//                        camera.rotateLeft(diff_x);
//                    camera.rotateUp(diff_y);
//                    old_time = time;
//                }
//                mouse = windowManager.getMousePosition();
                SDL_WM_GrabInput(SDL_GRAB_ON);
                if(e.type == SDL_MOUSEMOTION) {
                    cout << "motion" << endl;
                    cout << camera.m_fPhi << endl;
                    cout << camera.m_fTheta << endl;
                    camera.rotateUp(e.motion.yrel);
                    camera.rotateLeft(e.motion.xrel);
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
