//Yoongbok Lee
//CSCI312

#ifndef VEC_H_INCLUDED
#define VEC_H_INCLUDED

//typedef struct for vector type.
typedef struct {
    double x;
    double y;
    double z;
}VEC_T;


//prototypes for two functions: dot product and normalize.
double dot(VEC_T v1, VEC_T v2);

VEC_T normalize(VEC_T v);

#endif // VEC_H_INCLUDED
