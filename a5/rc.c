//Yoongbok Lee
//CSCI312

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vec.h"
#include "rc.h"

void read_objs(OBJ_T **list){

    double spherex,spherey,spherez;
    double radius;
    double red,green,blue;
    OBJ_T *new;
    *list = NULL;
    
    while (scanf("%lf %lf %lf %lf %lf %lf %lf",
    							&spherex,&spherey,&spherez,
    							&radius,&red,&green,&blue) == 7){
    	//store the values read from the file to variables.
    	//allocate memory space for new.
        new = (OBJ_T *) malloc (sizeof(OBJ_T));
        
        //assign variables to new.
        new->sphere.center = (VEC_T) {  .x = spherex, 
        																.y = spherey, 
        																.z = spherez };
        new->sphere.radius = (double) radius;
        new->color = (COLOR_T) { .R = red, .G = green, .B = blue};
        
        //new.next points to list, and list points to new. then go back to 
        //begining of while loop
        //next object type comes before the current one.
        new->next = *list;
        *list = new;
    }
}

int intersect_sphere (RAY_T ray, SPHERE_T sphere, double *t){
    /*double temp = dot(sphere.center, ray.direction);

    if (temp < 0) {
    	return 0;
    }

    double dsquared = dot(sphere.center,sphere.center) - pow(temp,2);
    double temp2 = sqrt(pow(sphere.radius,2) - dsquared);
    double temp3 = sqrt(dot(sphere.center,sphere.center) - dsquared);

    if (dsquared > pow(sphere.radius,2)) {
    
        return 0;
        
    }else if (dsquared <= pow(sphere.radius,2)) {
    
        *t = temp3 - temp2;
        return 1;
        
    }*/
    double r = sphere.radius;
    double t2;
    
    //variables needed for the intersection calculation
    double a = 1;
    double b = 2 * ( ray.direction.x * (ray.origin.x - sphere.center.x)
    								 + ray.direction.y * (ray.origin.y - sphere.center.y) 
    								 + ray.direction.z * (ray.origin.z - sphere.center.z) );
    double c = pow((ray.origin.x - sphere.center.x),2) 
    					+ pow((ray.origin.y-sphere.center.y),2) 
    					+ pow((ray.origin.z - sphere.center.z),2) - pow(sphere.radius,2);
    
    double deter = pow(b,2) - 4 * a * c;
    
    //if determinant < 0, return 0. otherwise, calculate t and return 1.
    if (deter <= 0) return 0;
    else {
    	*t = (-b - sqrt(deter)) / (2 * a);
    	return 1;
    }
}

COLOR_T cast (RAY_T ray, OBJ_T *list) {
	//cast color of the sphere that is firstly intersected with the ray.
	
    OBJ_T *current;
    
    double t;
    double min_t = 1000;
    
    COLOR_T result = (COLOR_T) {.R = 1, .G = 1, .B = 1};
    
    for ( current = list; current != NULL; current = current->next) {
    	//traverse through the list.
    	if ((intersect_sphere (ray, current->sphere, &t)) && (t < min_t)){
			//when t is smaller than min_t, change min_t to t and
			//update color according to current sphere's color
			min_t = t;
			result = current->color;
    	};
    };
    	
    return result;
}

int main()
{
	//initialize variables, object and ray, and pixel and screen.
    double i,j;
    OBJ_T *new;
    RAY_T ray;
    COLOR_T pixel = (COLOR_T) { .R = 1, .G = 1, .B = 1};
    printf("P6\n 1000 1000\n 255\n");
    
    read_objs(&new);
	
	//traverse through each pixel on the screen.
    for (i = 0; i < 1000; i++) {
        for (j = 0; j < 1000; j++ ) {
            //set ray, normalize it
            ray.origin = (VEC_T) { .x = 0, .y = 0, .z = 0};
            ray.direction = (VEC_T) { .x = (-0.5 + j / 1000.0), 
            													.y = (0.5 - i / 1000.0), 
            													.z = 1};
            ray.direction = (VEC_T) normalize(ray.direction);
            
            // update pixel color according to the color cast.
            pixel = cast(ray,new);
            
            //print on the image
            printf("%c%c%c", (unsigned char)(pixel.R * 255),
                                (unsigned char)(pixel.G * 255),
                                (unsigned char)(pixel.B * 255));
        }
    }
    return 0;
}
