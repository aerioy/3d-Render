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
    float cx = windowx/2;
    float cy = windowy/2;

    vector<face2d> projected = camera.project_scene(scene);

    SDL_SetRenderDrawColor(screen, 0,0,0,255);
    SDL_RenderClear(screen);

    for (const face2d& f : projected) {
        float x1 = (f.p1.x * zoom) + cx;
        float y1 = -(f.p1.y * zoom) + cy;
        float x2 = (f.p2.x * zoom) + cx;
        float y2 = -(f.p2.y * zoom) + cy;
        float x3 = (f.p3.x * zoom) + cx;
        float y3 = -(f.p3.y * zoom) + cy;
        SDL_SetRenderDrawColor(screen, f.color.r, f.color.g, f.color.b, f.color.a);
        SDL_RenderDrawLine(screen, x1, y1, x2, y2);
        SDL_RenderDrawLine(screen, x2, y2, x3, y3);
        SDL_RenderDrawLine(screen, x3, y3, x1, y1);
        SDL_Vertex vertex[3];
        SDL_Color color = f.color;
        vertex[0].position = {float(x1),float(y1)};
        vertex[1].position = {float(x2),float(y2)};
        vertex[2].position = {float(x3),float(y3)};
        vertex[0].color = color;
        vertex[1].color = color;
        vertex[2].color = color;
        vertex[0].tex_coord = {0.0f, 0.0f};
        vertex[1].tex_coord = {0.0f, 0.0f};
        vertex[2].tex_coord = {0.0f, 0.0f};
        int indices[3] = {0,1,2};
        SDL_RenderGeometry(screen,nullptr,vertex,3,indices,3);


    }
    SDL_SetRenderDrawColor(screen,255,255,0,255);
    SDL_RenderDrawLine(screen ,cx,cy+10,cx,cy-10);
    SDL_RenderDrawLine(screen ,cx+10,cy,cx-10,cy);
    SDL_RenderPresent(screen);
}

};