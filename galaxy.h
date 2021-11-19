#include "node.h"
#include<cmath>
#include<vector>

class galaxy{
    public:
    star* blackhole;
    vector<star*> satellites;
    int n;
    int r;
    galaxy(int n, int r){
        blackhole= new star(10000+rand()%5000, 
            v2(300+rand()%500,300+rand()%600), v2(rand()%80-40,rand()%80-40));
        this->n=n;
        this->r=r;
        for(int i=0; i<n; i++){
            double rad= rand()%r;
            double angle= rand()%360;
            double x= blackhole->s.x+rad*cos(angle);
            double y= blackhole->s.y+rad*sin(angle);
            star* temp= new star(rand()%50, v2(x,y) , v2(rand()%80-40,rand()%80-40));
            satellites.push_back(temp);
        }
    }
};