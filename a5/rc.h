//Yoongbok Lee
//CSCI312

#ifndef RC_H_INCLUDED
#define RC_H_INCLUDED
#include "vec.h"

/*
	defining struct for ray, color, sphere, and object types.
	they will be used in the rc.c file, which will calculate and print
	image of spheres on a ppm file.
*/

typedef struct {
    VEC_T origin;
    VEC_T direction;
}RAY_T;

typedef struct {
    double R;
    double G;
    double B;
}COLOR_T;

typedef struct {
    VEC_T center;
    double radius;
}SPHERE_T;

typedef struct OBJ{
    SPHERE_T sphere;
    COLOR_T color;
    struct OBJ *next;
}OBJ_T;

#endif // RC_H_INCLUDED
