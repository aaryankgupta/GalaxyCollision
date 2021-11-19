#include "v2.h"
#include<iostream>

class star{
    public:
    double m;
    v2 s,v,a;
    star(){}
    star(double m,v2 s, v2 v){
        this->m=m;
        this->s=s;
        this->v=v;
        this->a=v2(0,0);
    }
    star(double m,v2 s, v2 v, v2 a){
        this->m=m;
        this->s=s;
        this->v=v;
        this->a=a;
    }
};