#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "vector.hpp"
#include "quaternion.hpp"
#include "face.hpp"
#include "viewer.hpp"
#include "renderer.hpp"

using namespace std;


int main() {
    SDL_Window*   window       = nullptr;
    SDL_Renderer* sdl_renderer = nullptr;
    SDL_CreateWindowAndRenderer(1000, 700, 0, &window, &sdl_renderer);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    bool toggle = true;

    viewer camera(vec(-5, 5, 5), quat(1,0,0,0));
    vector<face3d> scene;
    renderer game(camera, scene, sdl_renderer,1000,700);
  
    for (double i = -10; i <= 10; i+= 0.5){
      for (double j = -10; j<= 10; j+= 0.5) {
        scene.push_back(face3d((vec(i,j,0)),(vec(i+1,j,0)),(vec(i,j+1,0))));
      }

    }
    // x axis, y axis, z axis 
    for (double i = 0; i<200; i++){
      scene.push_back(face3d(vec(-100+i,0,0),vec(-100+i,0,0),vec(-100+i+1,0,0),SDL_Color{255,0,0,255}));
      scene.push_back(face3d(vec(0,-100+i,0),vec(0,-100+i,0),vec(0,-100+i+1,0),SDL_Color{0,0,255,255}));
      scene.push_back(face3d(vec(0,0,-100+i),vec(0,0,-100+i),vec(0,0,-100+i+1),SDL_Color{0,255,0,255}));
    }


    float movespeed= 1;
    float turnspeed= 0.1;
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
                    camera.updateposition(movespeed,0,0);
                    break;
                  case SDL_SCANCODE_S:
                    camera.updateposition(-movespeed,0,0);
                    break;
                  // move to left and right
                  case SDL_SCANCODE_A:
                    camera.updateposition(0,-movespeed,0);
                    break;
                  case SDL_SCANCODE_D:
                    camera.updateposition(0,movespeed,0);
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
                  //controls up and down movement
                  case SDL_SCANCODE_SPACE:
                    camera.updateposition(0,0,movespeed);
                    break;
                  case SDL_SCANCODE_V:
                    camera.updateposition(0,0,-movespeed);
                    break;
                  case SDL_SCANCODE_ESCAPE:
                    if (toggle){
                      SDL_SetRelativeMouseMode(SDL_FALSE);
                      toggle = false;
                    }
                    else{
                      SDL_SetRelativeMouseMode(SDL_TRUE);
                      toggle = true;
                    }
                    break;
                  // controls fov  
                  case SDL_SCANCODE_Z:
                    camera.fov += 1;
                    break;
                  case SDL_SCANCODE_X:
                    camera.fov = max(camera.fov-1.f,1.f);
                    break;
                  default: break;

                }
            }
            else if (e.type == SDL_MOUSEMOTION){
              float dx = float(e.motion.xrel)/100;
              float dy = float(e.motion.yrel)/100;
              camera.updateview(dx,dy);
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