//Yoongbok Lee
//CSCI312

#include "vec.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double dot (VEC_T v1, VEC_T v2){
		//the dot product of two vectors.
    double dp = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    return dp;
}

VEC_T normalize(VEC_T v) {
		//make the length of the vector to 1.
    double length = sqrt( pow(v.x,2) + pow(v.y, 2) + pow(v.z , 2.0) );
    VEC_T result = (VEC_T) {  .x = v.x / length , 
    													.y = v.y / length, 
    													.z = v.z / length};
    return result;
}
