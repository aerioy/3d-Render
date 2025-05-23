#pragma once
#include <cmath>
#include "vector.hpp"
#include <SDL2/SDL.h>
#include "quaternion.hpp"
#include <vector>




struct face3d{
    vec p1,p2,p3;
    vec normal;
    SDL_Color color;

    // face defined by 3 points. orientation determines the direction to orient the normal vector, so 1 is in the direction of the cross product, -1 flips it. 
    face3d (const vec& x1,  const vec& x2,  const vec& x3,  float orientation = 1,  SDL_Color col = {255,255,255,255}){
        p1 = x1;
        p2 = x2;
        p3 = x3;
        normal = cross(x2-x1, x3-x1).normal() * orientation;
        color = col;
    }
};


// 2d version of above for screen
struct face2d{
    vec p1,p2,p3;
    SDL_Color color;
    face2d() = default;
    face2d(const vec& x1, const vec& x2,const vec&x3, SDL_Color col = {255,255,255,255} ){
        p1 = x1;
        p2 = x2;
        p3 = x3;
        color = col;
    }

};




