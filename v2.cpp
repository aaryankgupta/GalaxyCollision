#include "v2.h"
#include<iostream>
v2::v2(){
    x=0;
    y=0;
}

v2::v2(double a,double b){
    x = a;
    y = b;
}

v2::v2(const v2 &b){
    x = b.x;
    y = b.y;
}

v2 v2::operator+ (const v2 &b){
    return v2(x+b.x,y+b.y);
}

v2 v2::operator- (const v2 &b){
    return v2(x-b.x,y-b.y);
}

double v2::operator* (const v2 &b){
    return x*b.x+y*b.y;
}

v2 v2::operator* (double b){
    return v2(b*x,b*y);
}

v2 v2::operator/ (double b){
    return v2(x/b,y/b);
}

v2& v2::operator+=(const v2 &b){
    x+=b.x;
    y+=b.y;
    return *this;
}

v2& v2::operator-=(const v2 &b){
    x-=b.x;
    y-=b.y;
    return *this;
}

v2& v2::operator*=(double b){
    x*=b;
    y*=b;
    return *this;
}

v2& v2::operator/=(double b){
    x/=b;
    y/=b;
    return *this;
}

v2& v2::operator=(const v2 &b){
    x=b.x;
    y=b.y;
    return *this;
}
v2 v2::orthonormal(int i){
    v2 vec;
    if(i==1){
        vec = this->normalization();
        return v2(-vec.getY(),vec.getX());
    }
    if(i==-1){
         vec = this->normalization();
        return v2(vec.getY(),-vec.getX());
    }
}
double v2::square(){
    return x*x+y*y;
}

double v2::magnitude(){
    return sqrt(square());
}

v2 v2::normalization(){
    return *this/magnitude();
}

double v2::distance(const v2 &b){
    return (*this-b).magnitude();
}

double v2::getX(){
    return x;
}

double v2::getY(){
    return y;
}

void v2::print(){
    std::cout<<"("<<x<<","<<y<<")\n";
}