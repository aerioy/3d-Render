#pragma once
#include "vector.hpp"
#include "face.hpp"
#include <SDL2/SDL.h>
#include <cmath>
#include "quaternion.hpp"
#include <vector>

using namespace std;

class viewer{
public:
    vec position;
    quat view;
    float fov;

    viewer(vec initialposition = vec(0,0,0) ,quat initialview = quat(1,0,0,0), float initialfov = 1){
        position = initialposition;
        view = initialview;
        fov = initialfov;
    }

    void updateposition (float forward, float horizontal, float vertical){
        vec localx = view.rotate(i);
        vec localy = view.rotate(j);
        vec localz = view.rotate(k);
        position = position + localx.npart(k).normal() * forward;
        position = position + localy * horizontal;
        position = position + k * vertical;
    }

    // updates view based on horizontal and vertical change in angle.
    //horizontal updates are doune about the global z axis, 
    // vertical are done about local y axis
    void updateview (float horizontal, float vertical ){
        quat horizontal_update(horizontal,k);
        view = horizontal_update * view;
        quat vertical_update(vertical,view.rotate(j));
        view = vertical_update * view;
        view = view.normalize();
    }



    void updatefov (){

    }

    //takes point in R3 and projects it based on viewer reference frame (in R2) 
    //(imagines plane with lengh fov away from viewer positoin, paralell to the screen and returns intersectino point with that plane)
    vec project_point(const vec& v)const{
        vec localx = view.rotate(i);
        vec localy = view.rotate(j);
        vec localz = view.rotate(k);
        vec diff = v - position;
        if (inner(diff,localx) <= 0){
          return vec();
        }
        float a = fov/inner(diff,localx);
        float yout = inner((diff*a) - (localx * fov),localy);
        float zout = inner((diff*a) - (localx * fov),localz);
        
        return vec(yout,zout);

    }
    // takes array of 3d faces, and returns array of 2d faces. 
    vector<face2d> project_scene(const vector<face3d>& scene)const {
        vector<face2d> out;
        for (const face3d& s3 : scene){
            face2d s2;
            s2.color = s3.color;
            s2.p1 = project_point(s3.p1);
            s2.p2 = project_point(s3.p2);
            s2.p3 = project_point(s3.p3);
            if (!(s2.p1 == vec() || s2.p2 == vec() || s2.p3 == vec())){
                out.push_back(s2);
            }
        }
        return out;
    
    }










private:



};