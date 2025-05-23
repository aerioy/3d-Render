#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <cmath>

#include "vector.hpp"
#include "quaternion.hpp"
#include "face.hpp"
#include "viewer.hpp"
#include "renderer.hpp"

using namespace std;

int main() {
    SDL_Window*   window       = nullptr;
    SDL_Renderer* sdl_renderer = nullptr;
    SDL_CreateWindowAndRenderer(800, 600, 0, &window, &sdl_renderer);

    viewer camera(vec(0, 0, 5), quat(1,0,0,0));
    vector<face3d> scene;
    renderer game(camera, scene, sdl_renderer,800,600);
  
    for (double i = 0; i <= 10; i++){
      for (double j = 0; j<= 10; j++) {
        scene.push_back(face3d(vec(i,j,0),vec(i+1,j,0),vec(i,j+1,0)));
      }

    }



    float movespeed= 0.2;
    float turnspeed= 0.03;
    int   gridradius = 10;
    float cellsize   = 1.0;
    SDL_Color gridcolor{200,200,200,255};

    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.scancode) {
                  // move forward and backward 
                  case SDL_SCANCODE_W:
                    camera.updateposition(movespeed,0);
                    break;
                  case SDL_SCANCODE_S:
                    camera.updateposition(-movespeed,0);
                    break;
                  // move to left and right
                  case SDL_SCANCODE_A:
                    camera.updateposition(0,-movespeed);
                    break;
                  case SDL_SCANCODE_D:
                    camera.updateposition(0,movespeed);
                    break;
                  // look around based on arrow keys
                  case SDL_SCANCODE_LEFT:
                    camera.updateview(-turnspeed, 0);
                    break;
                  case SDL_SCANCODE_RIGHT:
                    camera.updateview(turnspeed, 0);
                    break;
                  case SDL_SCANCODE_UP:
                    camera.updateview(0, -turnspeed);
                    break;
                  case SDL_SCANCODE_DOWN:
                    camera.updateview(0, turnspeed);
                    break;

                  default: break;
                }
            }
        }

        game.renderframe();
        SDL_Delay(16); 
    }

   
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}