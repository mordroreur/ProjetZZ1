#include "ticksGest.h"


void mainTickGest(ecran *screen){
  if(screen->etapeDuJeu == 3){
    screen->whichBack = 0;
    screen->pla = (player *)malloc(sizeof(player)*screen->nbPlayer);
    for(int i = 0; i < screen->nbPlayer; i++){
      screen->pla[i].pos.x = 100*i + 5.0 * (1-(2*i));
      screen->pla[i].pos.y = 100*i + 5.0 *(1-(2*i));
      screen->pla[i].pos.w = 5;
      screen->pla[i].pos.h = 5;
      screen->pla[i].vitesse = 0.25;
  
      screen->pla[i].kill = 0;
      screen->pla[i].mort = 0;

      screen->pla[i].vie = 5;
      screen->pla[i].index = 0;

      screen->pla[i].maxBouleVie = 100;
      
      screen->pla[i].nbBoule = 100;
      screen->pla[i].boubou = (boule *)malloc(sizeof(boule) * screen->pla[i].nbBoule);
      for(int j = 0; j < screen->pla[i].nbBoule; j++){
	screen->pla[i].boubou[j].vie = -1;
      }
      screen->pla[i].dirX = 1 - 2*i;
      screen->pla[i].dirY = 1 -2*i;

      for(int j = 0; j < 5; j++){
	screen->pla[i].input[j] = 0;
      }
      
    }
    screen->etapeDuJeu = 4;
  }if(screen->etapeDuJeu == 4){
    for(int i = 0; i < screen->nbPlayer; i++){
      int nbDep = abs(screen->pla[i].input[0]-screen->pla[i].input[2]) + abs(screen->pla[i].input[1]-screen->pla[i].input[3]);
      if(nbDep == 1){
	if(screen->pla[i].input[0]) {screen->pla[i].pos.x -= screen->pla[i].vitesse; screen->pla[i].dirX = -1; screen->pla[i].dirY = 0;}
	if(screen->pla[i].input[1]) {screen->pla[i].pos.y -= screen->pla[i].vitesse;screen->pla[i].dirX = 0; screen->pla[i].dirY = -1;}
	if(screen->pla[i].input[2]) {screen->pla[i].pos.x += screen->pla[i].vitesse;screen->pla[i].dirX = 1; screen->pla[i].dirY = 0;}
	if(screen->pla[i].input[3]) {screen->pla[i].pos.y += screen->pla[i].vitesse;screen->pla[i].dirX = 0; screen->pla[i].dirY = 1;}
      }else if(nbDep == 2){
	if(screen->pla[i].input[0]) {screen->pla[i].pos.x -= 1/sqrt(2) * screen->pla[i].vitesse;screen->pla[i].dirX = -1;}
	if(screen->pla[i].input[1]) {screen->pla[i].pos.y -= 1/sqrt(2) * screen->pla[i].vitesse;screen->pla[i].dirY = -1;}
	if(screen->pla[i].input[2]) {screen->pla[i].pos.x += 1/sqrt(2) * screen->pla[i].vitesse;screen->pla[i].dirX = 1;}
	if(screen->pla[i].input[3]) {screen->pla[i].pos.y += 1/sqrt(2) * screen->pla[i].vitesse;screen->pla[i].dirY = 1;}
      }


      if(screen->pla[i].input[4]){
	screen->pla[i].input[4] = 0;
	screen->pla[i].boubou[screen->pla[i].index].pos = screen->pla[i].pos;
	screen->pla[i].boubou[screen->pla[i].index].vie = screen->pla[i].maxBouleVie;
	screen->pla[i].boubou[screen->pla[i].index].speed = 2*screen->pla[i].vitesse;
	screen->pla[i].boubou[screen->pla[i].index].vitX = screen->pla[i].dirX;
	screen->pla[i].boubou[screen->pla[i].index].vitY = screen->pla[i].dirY;
	screen->pla[i].index = (screen->pla[i].index+1)%screen->pla[i].nbBoule;
      }


      for(int j = 0; j < screen->pla[i].nbBoule; j++){
	screen->pla[i].boubou[j].vie--;
      }
      
    }
  }
}


