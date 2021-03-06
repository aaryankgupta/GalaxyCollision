#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include "node.h"
#define DELTA_T 0.0001
using namespace sf;

//g++ *.cpp -lsfml-graphics -lsfml-window -lsfml-system
int main(){

	int N;cin>>N;
	string mode;
	std::cin>>mode;
	if(mode=="nlogn"){
		int x=rand();
		int y=rand();
		vector<star*> stars;
		v2 s_rand1(rand()%(WINDOW_SIZE/2),rand()%(WINDOW_SIZE/2));
		v2 s_rand2(WINDOW_SIZE-rand()%(WINDOW_SIZE/2),WINDOW_SIZE-rand()%(WINDOW_SIZE/2));
		v2 v_rand1(rand()%40,rand()%40);
		v2 v_rand2(-rand()%40,-rand()%40);
		v2 mid(WINDOW_SIZE/2, WINDOW_SIZE/2);
		star* sun1= new star(1000+rand()%20, s_rand1, v_rand1);
		stars.push_back(sun1);

		star* sun2= new star(1000+rand()%20, s_rand2, v_rand2);
		stars.push_back(sun2);
		
		for(int i=0;i<N-2;i++){
			bool p = rand()%100>50;
			double xr,yr;
			xr=p*rand()%(WINDOW_SIZE/3)+ (1-p)*(WINDOW_SIZE-rand()%(WINDOW_SIZE/3));
			yr=p*rand()%(WINDOW_SIZE/3)+ (1-p)*(WINDOW_SIZE-rand()%(WINDOW_SIZE/3));
			while((xr-sun1->s.x)*(xr-sun1->s.x)+(yr-sun1->s.y)*(yr-sun1->s.y)>50000 && 
			(xr-sun2->s.x)*(xr-sun2->s.x)+(yr-sun2->s.y)*(yr-sun2->s.y)>50000 ){
				xr=p*rand()%(WINDOW_SIZE/3)+ (1-p)*(WINDOW_SIZE-rand()%(WINDOW_SIZE/3));
				yr=p*rand()%(WINDOW_SIZE/3)+ (1-p)*(WINDOW_SIZE-rand()%(WINDOW_SIZE/3));
			}
			v2 s_rand(xr,yr);
			v2 v_rand(rand()%50-(1-p)*50,rand()%50-(1-p)*50);
			star* s= new star(10+rand()%20, s_rand, v_rand);
			stars.push_back(s);
		}

		std::vector<CircleShape> bodies;
		for(int i=0; i<N;i++){
			int siz=1;
			if(i<2)siz=5;
			CircleShape temp=CircleShape(siz);
			temp.setPosition(stars[i]->s.x,stars[i]->s.y);
			bodies.push_back(temp);
		}

		RenderWindow Galaxy_Collision(VideoMode(1024,1024), "Galaxy Collision Project");

		while(Galaxy_Collision.isOpen()){
			Event event;
			while (Galaxy_Collision.pollEvent(event)){
				if (event.type ==Event::Closed){
					Galaxy_Collision.close();
				}
			}
			Galaxy_Collision.clear();
			node* tree= new node(sun1, mid, WINDOW_SIZE);
			for(int i=1;i<N;i++){insert(tree, stars[i]);}
			for(int i=0;i<N;i++){
				Galaxy_Collision.draw(bodies[i]);
				v2 accl= force(stars[i],tree)/stars[i]->m*(-1);
				stars[i]->v+= accl*DELTA_T;
				stars[i]->s+=stars[i]->v*DELTA_T;
				bodies[i].setPosition(stars[i]->s.x,stars[i]->s.y);
			}
			Galaxy_Collision.display();
		}
	}
	else if(mode=="n2"){
		vector<star*> stars;
		
		for(int i=0;i<N;i++){
			bool p = rand()%100>50;
			double xr,yr;
			xr=p*rand()%(WINDOW_SIZE/3)+ (1-p)*(WINDOW_SIZE-rand()%(WINDOW_SIZE/3));
			yr=p*rand()%(WINDOW_SIZE/3)+ (1-p)*(WINDOW_SIZE-rand()%(WINDOW_SIZE/3));
			while((xr-150)*(xr-150)+(yr-150)*(yr-150)>50000 && 
			(xr-850)*(xr-850)+(yr-850)*(yr-850)>50000 ){
				xr=p*rand()%(WINDOW_SIZE/3)+ (1-p)*(WINDOW_SIZE-rand()%(WINDOW_SIZE/3));
				yr=p*rand()%(WINDOW_SIZE/3)+ (1-p)*(WINDOW_SIZE-rand()%(WINDOW_SIZE/3));
			}
			v2 s_rand(xr,yr);
			v2 v_rand(rand()%50-(1-p)*50,rand()%50-(1-p)*50);
			star* s= new star(10+rand()%20, s_rand, v_rand);
			stars.push_back(s);
		}

		std::vector<CircleShape> bodies;
		for(int i=0; i<N;i++){
			int siz=1;
			CircleShape temp=CircleShape(siz);
			temp.setPosition(stars[i]->s.x,stars[i]->s.y);
			bodies.push_back(temp);
		}

		RenderWindow Galaxy_Collision(VideoMode(1024,1024), "Galaxy Collision Project");

		while(Galaxy_Collision.isOpen()){
			Event event;
			while (Galaxy_Collision.pollEvent(event)){
				if (event.type ==Event::Closed){
					Galaxy_Collision.close();
				}
			}
			Galaxy_Collision.clear();
			for(int i=0;i<N;i++){
				Galaxy_Collision.draw(bodies[i]);
				v2 accl= naive_force(stars[i],stars)/stars[i]->m*(-1);
				stars[i]->v+= accl*DELTA_T;
				stars[i]->s+=stars[i]->v*DELTA_T;
				bodies[i].setPosition(stars[i]->s.x,stars[i]->s.y);
			}
			Galaxy_Collision.display();
		}
	}
}