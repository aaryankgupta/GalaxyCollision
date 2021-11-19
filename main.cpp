#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include "galaxy.h"
#define DELTA_T 0.0001
using namespace sf;

//g++ *.cpp -lsfml-graphics -lsfml-window -lsfml-system
int main(){
	int N;cin>>N;
	string mode;
	std::cin>>mode;
	if(mode=="nlogn"){
		galaxy g(N,200+rand()%200);
		//galaxy h(N,200+rand()%200);

		std::vector<CircleShape> bodies;
		
		for(int i=0; i<N;i++){
			int siz= rand()%2+1;
			CircleShape temp=CircleShape(siz);
			temp.setPosition(g.satellites[i]->s.x,g.satellites[i]->s.y);
			bodies.push_back(temp);
		}
		// for(int i=0; i<N;i++){
		// 	int siz= rand()%2+1;
		// 	CircleShape temp=CircleShape(siz);
		// 	temp.setPosition(h.satellites[i]->s.x,h.satellites[i]->s.y);
		// 	bodies.push_back(temp);
		// }
		RenderWindow Galaxy_Collision(VideoMode(1024,1024), "Galaxy Collision Project");

		while(Galaxy_Collision.isOpen()){
			Event event;
			while (Galaxy_Collision.pollEvent(event)){
				if (event.type ==Event::Closed){
					Galaxy_Collision.close();
				}
			}
			Galaxy_Collision.clear();
			
			v2 mid(WINDOW_SIZE/2, WINDOW_SIZE/2);
			node* tree= new node(g.blackhole, mid, WINDOW_SIZE);
			//insert(tree, h.blackhole);
			for(int i=0;i<N;i++){insert(tree, g.satellites[i]);}
			//for(int i=0;i<N;i++){insert(tree, h.satellites[i]);}
			for(int i=0;i<N;i++){
				Galaxy_Collision.draw(bodies[i]);
				v2 accl= force(g.satellites[i],tree)/g.satellites[i]->m*(-1);
				g.satellites[i]->v+= accl*DELTA_T;
				g.satellites[i]->s+=g.satellites[i]->v*DELTA_T;
				bodies[i].setPosition(g.satellites[i]->s.x,g.satellites[i]->s.y);
			}
			// for(int i=0;i<N;i++){
			// 	Galaxy_Collision.draw(bodies[N+i]);
			// 	v2 accl= force(h.satellites[i],tree)/h.satellites[i]->m*(-1);
			// 	h.satellites[i]->v+= accl*DELTA_T;
			// 	h.satellites[i]->s+=h.satellites[i]->v*DELTA_T;
			// 	bodies[i].setPosition(h.satellites[i]->s.x,h.satellites[i]->s.y);
			// }

			v2 accl_blckh= force(g.blackhole,tree)/g.blackhole->m*(-1);
			g.blackhole->v+= accl_blckh*DELTA_T;
			g.blackhole->s+=g.blackhole->v*DELTA_T;

			// v2 accl_blckh2= force(h.blackhole,tree)/h.blackhole->m*(-1);
			// h.blackhole->v+= accl_blckh2*DELTA_T;
			// h.blackhole->s+=h.blackhole->v*DELTA_T;

			Galaxy_Collision.display();
		}
	}
	/*else if(mode=="n2"){
		vector<star*> stars;
		
		for(int i=0;i<N;i++){
			bool p = rand()%100>50;
			v2 s_rand(p*rand()%(WINDOW_SIZE/3)+ (1-p)*(WINDOW_SIZE-rand()%(WINDOW_SIZE/3)),p*rand()%(WINDOW_SIZE/3)+ (1-p)*(WINDOW_SIZE-rand()%(WINDOW_SIZE/3)));
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
	}*/
}
