#include <iostream>
#include "star.h"
#include "box.h"
#define WINDOW_SIZE 1024
#define G 5000.0
#define THETA 1000.0

class node{
    public:
    double m;
    v2 com;
    bool isStar;
    star* leaf;
    node* child[4];
    struct box* square;
    node(star* STAR,v2 coord, double size){
        com=STAR->s;
        m=STAR->m;
        isStar=true;
        leaf=STAR;
        square = new box(coord, size);
        for(int i=0; i<4; i++){
            child[i]=NULL;
        }
    }
    node(){
        for(int i=0; i<4; i++){
            child[i]=NULL;
        }
        leaf=NULL;
        isStar=true;
        m=0;
    }
};

int quadrant(node* parent, star* STAR){
    int q=-1;

        //calculation of quadrant to call recursion
        double x0 = parent->square->coord.x;
        double y0 = parent->square->coord.y;
        double x1 = STAR->s.x;
        double y1 = STAR->s.y;
        if(x0>x1){
            if(y0>y1)q=0;
            else{q=3;}
        }
        else{
            if(y0>y1)q=1;
            else{q=2;}
        }
    
    return q;
}

void insert(node* parent,star* STAR){

    //when parent is empty
    if(parent==NULL){
        v2 origin(WINDOW_SIZE/2,WINDOW_SIZE/2 );
        parent= new node(STAR,origin, WINDOW_SIZE);
        parent->com = STAR->s;
        parent->m = STAR->m;
        parent->isStar=true;
    }

    //when parent is a star
    else if(parent->isStar==true){

        parent->isStar=false;
        star* oldSTAR= parent->leaf;
        v2 old_coord=parent->square->coord;
        double old_size= parent->square->size;

        //calculation of oldquadrant to call recursion
        //int oldquadrant=quadrant(parent, oldSTAR);
        int oldquadrant=1;
        int newquadrant=quadrant(parent, STAR);

        //copying old data to child and destroying old node
        parent->child[oldquadrant]= new node(oldSTAR, parent->square->childbox(oldquadrant).coord, old_size/2);

        //inserting the new star now
        if(oldquadrant!=newquadrant){
            parent->child[newquadrant]= new node(STAR,parent->square->childbox(newquadrant).coord, old_size/2);
        }
        else{
            insert(parent, STAR);
        }

        parent->com = (STAR->s*STAR->m + oldSTAR->s*oldSTAR->m)/(STAR->m + oldSTAR->m); 
        parent->m =oldSTAR->m + STAR->m;
    }

    //when parent is an internal node
    else{
        //calculation of quadrant to call recursion
        int quad=quadrant(parent, STAR);

        //tail recursion step
        insert(parent->child[quad], STAR);
        parent->com = (STAR->s*STAR->m + parent->com*parent->m)/(STAR->m + parent->m); 
        parent->m += STAR->m;
    }

}

v2 force(star* STAR, node* root){
    v2 F(0,0);
    if(root==NULL)return F;
    else if(root!=NULL && root->isStar){
        if((STAR->s-root->com).magnitude()<0.1){
            F= (STAR->s-root->com)*((G*(STAR->m)*(root->m))/
            (STAR->s.distance(root->com)*STAR->s.distance(root->com)*STAR->s.distance(root->com)));
        }
    }
    else{
        double r= STAR->s.distance(root->com);
        double d= root->square->size;
        if(d/r<THETA){
            F= (STAR->s-root->com)*((G*(STAR->m)*(root->m))/
            (STAR->s.distance(root->com)*STAR->s.distance(root->com)*STAR->s.distance(root->com)));
        }
        else{
            for(int itr=0;itr<4;itr++){
                F+=force(STAR, root->child[itr]);
            }
        }
    }
    return F;
}