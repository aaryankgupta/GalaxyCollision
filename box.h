#include <iostream>
#include "v2.h"
#define WINDOW_SIZE 1024
using namespace std;

struct box{
    v2 coord;
    double size;
    box(v2 coord){
        this->coord=coord;
        this->size= WINDOW_SIZE;
    }
    box(v2 coord, double size){
        this->coord=coord;
        this->size=size;
    }
    box childbox(int quadrant){
        if(quadrant==0){
            return box(coord + v2(-size/4,-size/4),size/2);
        }
        else if(quadrant==1){
            return box(coord + v2(size/4,-size/4),size/2);
        }
        else if(quadrant==2){
            return box(coord + v2(size/4,size/4),size/2);
        }
        else if(quadrant==3){
            return box(coord + v2(-size/4,size/4),size/2);
        }
    }
};