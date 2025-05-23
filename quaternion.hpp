#pragma once
#include <cmath>
#include "vector.hpp"


struct quat{
    float w,x,y,z;

    
    // initializes based on angle and rotation axis, this is for defining rotation vectors to multiply q'vq. q := cos(a/2)
    quat(float theta, const vec& v ){
        vec axis = v.normal();
        float s = sin(theta/2.0);
        w = cos(theta/2.0);
        x = axis.x * s;
        y = axis.y * s;
        z = axis.z * s;
    }

    // just initlalizes normally component wise 
    quat (float a = 1, float b = 0 , float c = 0, float d = 0){
        w = a;
        x = b;
        y = c;
        z = d;
    }
    // automatic typecast from vec to quat for rotation calculations later
    quat (const vec& v){
        w = 0;
        x = v.x;
        y = v.y;
        z = v.z;
    }

    // norm of quaternion
    float len() const{
        return sqrt(w*w + x*x + y*y + z*z);
    }

    // quaternion additoin
    quat operator+ (const quat& q)const{
        return quat(w+q.w,x+q.x,y+q.y,z+q.z);
    }

    // quaternion multiplication 
    quat operator* (const quat& q) const{
        return quat(
            w * q.w - x * q.x - y * q.y - z * q.z,
            w * q.x + x * q.w + y * q.z - z * q.y,
            w * q.y - x * q.z + y * q.w + z * q.x,
            w * q.z + x * q.y - y * q.x + z * q.w
        );
    }
    
    // returns normalized quaternion
    quat normalize() const{
        float l = len();
        return quat(w/l,x/l,y/l,z/l);
   }

    // conjugate quaternion
    quat conj () const{
        return quat(w,-x,-y,-z);
    }
    
    // uses quaternion multiplication to rotate vec clockwise from perspective of viewer looking along the (i,j,k) part of q (which is the rotation axis)
    vec rotate(const vec& v) const{
        quat qinv(w,-x,-y,-z);
        quat vquat(0,v.x,v.y,v.z);
        quat out = (*this) * vquat * qinv;
        return vec(out.x,out.y,out.z);
    }

 
};





