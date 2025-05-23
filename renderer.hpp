#pragma once
#include "vector.hpp"
#include "face.hpp"
#include <SDL2/SDL.h>
#include <cmath>
#include "quaternion.hpp"
#include <vector>
#include "viewer.hpp"


class renderer{
public:
    viewer& camera;
    vector<face3d>& scene;
    SDL_Renderer* screen;
    int zoom;
    int windowx;
    int windowy;


    renderer(viewer&  cam, vector<face3d>& inputscene, SDL_Renderer* sdl, int windowx, int windowy,int zoom = 100)
       : camera(cam), scene(inputscene), screen(sdl), zoom(zoom), windowx(windowx), windowy(windowy) {}


   void renderframe() {
    int cx = windowx/2;
    int cy = windowy/2;

    vector<face2d> projected = camera.project_scene(scene);

    SDL_SetRenderDrawColor(screen, 0,0,0,255);
    SDL_RenderClear(screen);

    for (const face2d& f : projected) {
        int x1 = int(f.p1.x * zoom) + cx;
        int y1 = -int(f.p1.y * zoom) + cy;
        int x2 = int(f.p2.x * zoom) + cx;
        int y2 = -int(f.p2.y * zoom) + cy;
        int x3 = int(f.p3.x * zoom) + cx;
        int y3 = -int(f.p3.y * zoom) + cy;
        SDL_SetRenderDrawColor(screen, f.color.r, f.color.g, f.color.b, f.color.a);
        SDL_RenderDrawLine(screen, x1, y1, x2, y2);
        SDL_RenderDrawLine(screen, x2, y2, x3, y3);
        SDL_RenderDrawLine(screen, x3, y3, x1, y1);
    }
    SDL_SetRenderDrawColor(screen,255,0,0,255);
    SDL_RenderDrawLine(screen ,cx,cy+10,cx,cy-10);
    SDL_RenderDrawLine(screen ,cx+10,cy,cx-10,cy);
    SDL_RenderPresent(screen);
}

};