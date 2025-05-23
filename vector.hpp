#pragma once
#include <cmath>


// struct for vector in R3
struct vec;
inline float inner(const vec& v, const vec&w);

struct vec{
    float  x,y,z;

    vec (float a = 0, float b = 0 , float c= 0) {
        x = a;
        y = b;
        z = c;
    }
    // addition
    vec operator+(const vec& v) const{
        return vec(x + v.x, y+v.y, z+v.z);
    }
    // difference 
    vec operator- (const vec& v) const{
        return vec(x-v.x,y-v.y,z-v.z);
    }
    // scalar product
    vec operator*(const float a) const{
        return vec(a*x,a*y,a*z);
    }
    // returns norm of vector
    float len() const{
        return sqrt(x*x +y*y+ z*z);
    }
    //returns normalized self
    vec normal() const{
        float l = len();
        if (l == 0){
            return *this;
        }
        return *this * (1.0/l);
    }

    // projection of self onto span(v)
    vec  proj(const vec& v) const{
        return v * (inner(*this,v)/inner(v,v));
    }

    // returns normal part in decomposition of self onto span(v)
    vec npart(const vec& v) const{
        return *this - proj(v);
    }
    // recflects self with repsect to the plane in R3 orthogonal to plane_normal 
    vec reflect(const vec& plane_normal) const{
        return *this - (plane_normal * (2 *  inner(*this,plane_normal)/inner(plane_normal,plane_normal)));
    }
    // compares equality between vectors
    bool operator== (const vec& v)const{
        return (x == v.x && y == v.y && z == v.z);
    }
    

};

// VECTOR FUNCTIONS, 
const vec i(1.0, 0.0, 0.0);
const vec j(0.0, 1.0, 0.0);
const vec k(0.0, 0.0, 1.0);

// inner product on R3
inline float inner(const vec& v, const vec& w){
    return v.x * w.x + v.y * w.y + v.z * w.z;
};

// cross product R3
inline vec cross(const vec& v, const vec& w){
    return vec(
        v.y * w.z - v.z * w.y,
        v.z * w.x - v.x * w.z,
        v.x * w.y - v.y * w.x
    );
}






