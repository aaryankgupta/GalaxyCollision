#ifndef V2
#define V2
#include<cmath>

//IMPORTANT:: reference from stack overflow used for v2 
class v2{
    public:
    double x,y;

    //constructors
    v2();
    v2(double,double);
    v2(const v2 &);

    //member functions
    v2 operator+(const v2 &);
    v2 operator-(const v2 &);
    v2 operator*(double);
    double operator*(const v2 &);//dot product
    v2 operator/(double);
    v2 &operator+=(const v2 &);
    v2 &operator-=(const v2 &);
    v2 &operator*=(double);
    v2 &operator/=(double);
    v2 &operator=(const v2 &);
    v2 orthonormal(int);
    double square();
    double magnitude();
    v2 normalization();//normalised vector
    double distance(const v2 &); //distance between 2 vectors
    double getX();
    double getY();
    void print();//prints vector on console
};

#endif