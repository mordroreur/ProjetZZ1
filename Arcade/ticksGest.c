#include "ticksGest.h"
#include "renderingUtil.h"
#include <math.h>

#define SIZE 3

void mainTickGest(ecran *screen){
  if(screen->etapeDuJeu == 3){
    screen->whichBack = rand()%6;
    screen->whichBack += 4;
    if(screen->modePlay == 0){
      screen->pla = (player *)malloc(sizeof(player)*screen->nbPlayer);
      for(int i = 0; i < screen->nbPlayer; i++){
	screen->pla[i].pos.x = 100*i + 5.0 * (1-(2*i));
	screen->pla[i].pos.y = 100*i + 5.0 *(1-(2*i));
	screen->pla[i].pos.w = SIZE;
	screen->pla[i].pos.h = SIZE*0.7;
	screen->pla[i].vitesse = 0.25;
  
	screen->pla[i].kill = 0;
	screen->pla[i].mort = 0;

	screen->pla[i].vie = screen->maxVie;
	screen->pla[i].index = 0;

	screen->pla[i].maxBouleVie = 100;

	screen->pla[i].peuTirer = 1;
	  
	screen->pla[i].debBoule = 0;
	screen->pla[i].nbBouleActive = 0;
	screen->pla[i].shoot = 0;

	screen->pla[i].equipe = i;
      
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
      // JEU MOUTON!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }else if(screen->modePlay == 1){
      screen->nbPreda = 3;
      screen->nbProie = 10;
      screen->nbPlayer = screen->nbProie + screen->nbPreda;
      screen->pla = (player *)malloc(sizeof(player)*screen->nbPlayer);
      for(int i = 0; i < screen->nbPlayer; i++){
	screen->pla[i].pos.x = rand()%100;
	screen->pla[i].pos.y = rand()%100;
	screen->pla[i].pos.w = SIZE;
	screen->pla[i].pos.h = SIZE*0.7;
	screen->pla[i].vitesse = 0.25;
  
	screen->pla[i].kill = 0;
	screen->pla[i].mort = 0;

	screen->pla[i].vie = 1;
	screen->pla[i].index = 0;

	screen->pla[i].maxBouleVie = 0;

	screen->pla[i].peuTirer = 0;
	  
	screen->pla[i].debBoule = 0;
	screen->pla[i].nbBouleActive = 0;
	screen->pla[i].shoot = 0;

	screen->pla[i].equipe = (i < 3)?0:1;
      
	screen->pla[i].nbBoule = 0;
	screen->pla[i].boubou = (boule *)malloc(sizeof(boule) * screen->pla[i].nbBoule);
	for(int j = 0; j < screen->pla[i].nbBoule; j++){
	  screen->pla[i].boubou[j].vie = -1;
	}
	screen->pla[i].dirX = rand()%3 - 1;
	screen->pla[i].dirY = rand()%3 - 1;

	for(int j = 0; j < 5; j++){
	  screen->pla[i].input[j] = 0;
	}      
      }
    }
    screen->etapeDuJeu = 4;
  }if(screen->etapeDuJeu == 4){
    if(screen->modePlay == 0){
      for(int i = 0; i < screen->nbPlayer; i++){
	int nbDep = abs(screen->pla[i].input[0]-screen->pla[i].input[2]) + abs(screen->pla[i].input[1]-screen->pla[i].input[3]);
	if(nbDep == 1){
	  if(screen->pla[i].input[0]) {screen->pla[i].pos.x -= screen->pla[i].vitesse; screen->pla[i].dirX = -1; screen->pla[i].dirY = 0; if(screen->pla[i].pos.x < 0){screen->pla[i].pos.x += 100;}}
	  if(screen->pla[i].input[1]) {screen->pla[i].pos.y -= screen->pla[i].vitesse;screen->pla[i].dirX = 0; screen->pla[i].dirY = -1;if(screen->pla[i].pos.y < 0){screen->pla[i].pos.y += 100;}}
	  if(screen->pla[i].input[2]) {screen->pla[i].pos.x += screen->pla[i].vitesse;screen->pla[i].dirX = 1; screen->pla[i].dirY = 0;if(screen->pla[i].pos.x > 100){screen->pla[i].pos.x -= 100;}}
	  if(screen->pla[i].input[3]) {screen->pla[i].pos.y += screen->pla[i].vitesse;screen->pla[i].dirX = 0; screen->pla[i].dirY = 1;if(screen->pla[i].pos.y > 100){screen->pla[i].pos.y -= 100;}}
	}else if(nbDep == 2){
	  if(screen->pla[i].input[0]) {screen->pla[i].pos.x -= 1/sqrt(2) * screen->pla[i].vitesse;screen->pla[i].dirX = -1;if(screen->pla[i].pos.x < 0){screen->pla[i].pos.x += 100;}}
	  if(screen->pla[i].input[1]) {screen->pla[i].pos.y -= 1/sqrt(2) * screen->pla[i].vitesse;screen->pla[i].dirY = -1;if(screen->pla[i].pos.y < 0){screen->pla[i].pos.y += 100;}}
	  if(screen->pla[i].input[2]) {screen->pla[i].pos.x += 1/sqrt(2) * screen->pla[i].vitesse;screen->pla[i].dirX = 1;if(screen->pla[i].pos.x > 100){screen->pla[i].pos.x -= 100;}}
	  if(screen->pla[i].input[3]) {screen->pla[i].pos.y += 1/sqrt(2) * screen->pla[i].vitesse;screen->pla[i].dirY = 1;if(screen->pla[i].pos.y > 100){screen->pla[i].pos.y -= 100;}}
	}

	if(screen->pla[i].shoot != 0){
	  screen->pla[i].shoot--;
	}

	if(screen->pla[i].input[4]){
	  screen->pla[i].input[4] = 0;
	  if(screen->pla[i].peuTirer == 1){
	    screen->pla[i].boubou[screen->pla[i].index].pos.x = screen->pla[i].pos.x;
	    screen->pla[i].boubou[screen->pla[i].index].pos.y = screen->pla[i].pos.y;
	    screen->pla[i].boubou[screen->pla[i].index].pos.w = screen->pla[i].pos.w;
	    screen->pla[i].boubou[screen->pla[i].index].pos.h = screen->pla[i].pos.h;
	    screen->pla[i].boubou[screen->pla[i].index].vie = screen->pla[i].maxBouleVie;
	    screen->pla[i].boubou[screen->pla[i].index].speed = 2*screen->pla[i].vitesse;
	    screen->pla[i].boubou[screen->pla[i].index].vitX = screen->pla[i].dirX;
	    screen->pla[i].boubou[screen->pla[i].index].vitY = screen->pla[i].dirY;
	    screen->pla[i].index = (screen->pla[i].index+1)%screen->pla[i].nbBoule;
	    screen->pla[i].nbBouleActive++;
	    screen->pla[i].shoot = 36;
	  }
	}


	for(int j = screen->pla[i].debBoule; j < screen->pla[i].debBoule+screen->pla[i].nbBouleActive; j++){
	  boule *b = &(screen->pla[i].boubou[j%screen->pla[i].nbBoule]);

	  int nbDep = abs(b->vitX) + abs(b->vitY);
	  if(nbDep == 1){
	    if(b->vitX != 0) {b->pos.x += b->vitX;  if(b->pos.x < 0){b->pos.x += 100;}else if(b->pos.x > 100){b->pos.x -= 100;}}else if(b->vitY != 0) {b->pos.y += b->vitY;  if(b->pos.y < 0){b->pos.y += 100;}else if(b->pos.y > 100){b->pos.y -= 100;}}

	  }else if(nbDep == 2){
	    if(b->vitX != 0) {b->pos.x += 1/sqrt(2)*b->vitX;  if(b->pos.x < 0){b->pos.x += 100;}else if(b->pos.x > 100){b->pos.x -= 100;}}
	    if(b->vitY != 0) {b->pos.y += 1/sqrt(2) * b->vitY;  if(b->pos.y < 0){b->pos.y += 100;}else if(b->pos.y > 100){b->pos.x -= 100;}}
	  }

	  for(int k = 0; k < screen->nbPlayer; k++){
	    if(screen->pla[i].equipe != screen->pla[k].equipe){
	      if(sqrt(pow(b->pos.x - screen->pla[k].pos.x, 2) + pow(b->pos.y - screen->pla[k].pos.y, 2)) < (b->pos.w+b->pos.h)/3 + (screen->pla[k].pos.w + screen->pla[k].pos.h)/3){
	      
		screen->pla[k].mort++;
		screen->pla[k].vie--;

		if(screen->pla[k].vie == 0){
		  int nbequipe = -1;
		  for(int l = 0; l < screen->nbPlayer; l++){
		    if(screen->pla[l].vie != 0){
		      if(nbequipe == -1){
			nbequipe = screen->pla[l].equipe;
		      }else if(nbequipe != screen->pla[l].equipe){
			nbequipe = -2;
		      }
		      if(nbequipe != -2){
			screen->etapeDuJeu = 5;
		      }
		    }
		  }
		
		}
	      
		screen->pla[i].kill++;
		b->vie = 0;
	      }
	    }
	  }
	
	
	  b->vie--;
	  if(b->vie == -1){
	    if(j == screen->pla[i].debBoule){
	      int tmp = j;
	      while(screen->pla[i].boubou[tmp%screen->pla[i].nbBoule].vie == -1 && screen->pla[i].nbBouleActive != 0){
		screen->pla[i].debBoule++;
		screen->pla[i].nbBouleActive--;
		tmp++;
	      }
	      screen->pla[i].debBoule = screen->pla[i].debBoule%screen->pla[i].nbBoule;
	    }
	  }
	}

      }
	      
    }else if(screen->modePlay == 1){

      for(int i = 0; i < screen->nbPlayer; i++){
	int nbDep = abs(screen->pla[i].input[0]-screen->pla[i].input[2]) + abs(screen->pla[i].input[1]-screen->pla[i].input[3]);
	if(nbDep == 1){
	  if(screen->pla[i].input[0]) {screen->pla[i].pos.x -= screen->pla[i].vitesse; screen->pla[i].dirX = -1; screen->pla[i].dirY = 0; if(screen->pla[i].pos.x < 0){screen->pla[i].pos.x += 100;}}
	  if(screen->pla[i].input[1]) {screen->pla[i].pos.y -= screen->pla[i].vitesse;screen->pla[i].dirX = 0; screen->pla[i].dirY = -1;if(screen->pla[i].pos.y < 0){screen->pla[i].pos.y += 100;}}
	  if(screen->pla[i].input[2]) {screen->pla[i].pos.x += screen->pla[i].vitesse;screen->pla[i].dirX = 1; screen->pla[i].dirY = 0;if(screen->pla[i].pos.x > 100){screen->pla[i].pos.x -= 100;}}
	  if(screen->pla[i].input[3]) {screen->pla[i].pos.y += screen->pla[i].vitesse;screen->pla[i].dirX = 0; screen->pla[i].dirY = 1;if(screen->pla[i].pos.y > 100){screen->pla[i].pos.y -= 100;}}
	}else if(nbDep == 2){
	  if(screen->pla[i].input[0]) {screen->pla[i].pos.x -= 1/sqrt(2) * screen->pla[i].vitesse;screen->pla[i].dirX = -1;if(screen->pla[i].pos.x < 0){screen->pla[i].pos.x += 100;}}
	  if(screen->pla[i].input[1]) {screen->pla[i].pos.y -= 1/sqrt(2) * screen->pla[i].vitesse;screen->pla[i].dirY = -1;if(screen->pla[i].pos.y < 0){screen->pla[i].pos.y += 100;}}
	  if(screen->pla[i].input[2]) {screen->pla[i].pos.x += 1/sqrt(2) * screen->pla[i].vitesse;screen->pla[i].dirX = 1;if(screen->pla[i].pos.x > 100){screen->pla[i].pos.x -= 100;}}
	  if(screen->pla[i].input[3]) {screen->pla[i].pos.y += 1/sqrt(2) * screen->pla[i].vitesse;screen->pla[i].dirY = 1;if(screen->pla[i].pos.y > 100){screen->pla[i].pos.y -= 100;}}
	}
      }
      
      for(int i = screen->nbPreda; i < screen->nbProie+screen->nbPreda; i++){
	for(int j = 0; j < screen->nbPreda; j++){
	  if(sqrt(pow(screen->pla[i].pos.x - screen->pla[j].pos.x, 2) + pow(screen->pla[i].pos.y - screen->pla[j].pos.y, 2)) < (screen->pla[i].pos.w+screen->pla[i].pos.h)/5 + (screen->pla[j].pos.w + screen->pla[j].pos.h)/5){
	    screen->pla[i].vie = 0;
	  }
	}
      }

      int perdu = 1;
      for(int i = screen->nbPreda; i < screen->nbProie+screen->nbPreda; i++){
	if(screen->pla[i].vie != 0){
	  perdu = 0;
	}
      }
      if(perdu == 1){
	screen->etapeDuJeu = 5;
      }


      
    }       
  }else if(screen->etapeDuJeu == 12){

	for(int i = 0; i < screen->nbPlayer; i++){
	  free(screen->pla[i].boubou);
	}
	free(screen->pla);


	screen->etapeDuJeu = 2;
  }
}


