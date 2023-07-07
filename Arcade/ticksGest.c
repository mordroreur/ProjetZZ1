#include "ticksGest.h"
#include "IAreflexion.h"
#include "renderingUtil.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 3
#define NBRMOUT 32

int **AI1 = NULL;
int nbParam1;
int nbRegle1;
int **AI2 = NULL;
int nbParam2;
int nbRegle2;
int **AI3 = NULL;
int nbParam3;
int nbRegle3;
int **AI4 = NULL;
int nbParam4;
int nbRegle4;

int mode;

void mainTickGest(ecran *screen){
  if(screen->etapeDuJeu == 3){
    screen->whichBack = rand()%6;
    screen->whichBack += 4;
    if(screen->modePlay == 0){
      screen->pla = (player *)malloc(sizeof(player)*screen->nbPlayer);
      for(int i = 0; i < screen->nbPlayer; i++){
		screen->pla[i].pos.x = rand()%100;
		screen->pla[i].pos.y = rand()%100;
		screen->pla[i].pos.w = SIZE;
		screen->pla[i].pos.h = SIZE*0.5625;
		screen->pla[i].vitesse = 0.25;
		screen->pla[i].IAType = i+1;
		screen->pla[i].kill = 0;
		screen->pla[i].mort = 0;
		screen->pla[i].vitTire = 2;
	
		screen->pla[i].vie = screen->maxVie;
		screen->pla[i].index = 0;

		screen->pla[i].maxBouleVie = 300;

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
      screen->nbObjetsMax = 10;
      screen->tbObjet = (objet *)malloc(sizeof(objet) * screen->nbObjetsMax);
      screen->tbObjet[0].vie = -1;
      screen->TrouNoirTime = -15*60;
      
      // JEU MOUTON!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }else if(screen->modePlay == 1){	  
      screen->nbPlayer = screen->nbProie + screen->nbPreda;
      screen->pla = (player *)malloc(sizeof(player)*screen->nbPlayer);
      for(int i = 0; i < screen->nbPlayer; i++){
		screen->pla[i].pos.x = rand()%100;
		screen->pla[i].pos.y = rand()%100;
		screen->pla[i].pos.w = SIZE;
		screen->pla[i].pos.h = SIZE*0.5625;
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

	
		screen->pla[i].IAType = (i <screen->nbPreda)?2:1;

		screen->pla[i].equipe = (i < screen->nbPreda)?0:1;
      
		screen->pla[i].nbBoule = 0;
		screen->pla[i].dirX = rand()%3 - 1;
		screen->pla[i].dirY = rand()%3 - 1;
	
		for(int j = 0; j < 5; j++){
		  screen->pla[i].input[j] = 0;
		}      
      }
      
      screen->nbBananes = 0;
      screen->nbObjetsMax = rand()%8 + 4 + screen->nbBananes;
      screen->tbObjet = (objet *)malloc(sizeof(objet) * screen->nbObjetsMax);
      for(int i = 0; i < screen->nbObjetsMax-screen->nbBananes; i++){
		screen->tbObjet[i].id = 1;
		int pose = 0;
		while (pose == 0) {
		  pose = 1;
		  screen->tbObjet[i].pos.x = (rand()%80) + 10;
		  screen->tbObjet[i].pos.y = (rand()%80) + 10;
		  screen->tbObjet[i].pos.w = rand()%6 + 3;
		  screen->tbObjet[i].pos.h = rand()%6 + 3;
		  for(int j = 0; j < screen->nbPlayer; j++){
			if((screen->pla[j].pos.x - screen->pla[j].pos.w/2.4 < screen->tbObjet[i].pos.x + screen->tbObjet[i].pos.w && screen->pla[j].pos.x - screen->pla[j].pos.w/2.4 > screen->tbObjet[i].pos.x && screen->pla[j].pos.y - screen->pla[j].pos.h/1.3 < screen->tbObjet[i].pos.y + screen->tbObjet[i].pos.h && screen->pla[j].pos.y - screen->pla[j].pos.h/1.3 > screen->tbObjet[i].pos.y)
			   || (screen->pla[j].pos.x + screen->pla[j].pos.w/2.5 < screen->tbObjet[i].pos.x + screen->tbObjet[i].pos.w && screen->pla[j].pos.x +screen->pla[j].pos.w/2.5  > screen->tbObjet[i].pos.x && screen->pla[j].pos.y +screen->pla[j].pos.h < screen->tbObjet[i].pos.y + screen->tbObjet[i].pos.h && screen->pla[j].pos.y +screen->pla[j].pos.h > screen->tbObjet[i].pos.y)
			   || (screen->pla[j].pos.x + screen->pla[j].pos.w/2.4 < screen->tbObjet[i].pos.x + screen->tbObjet[i].pos.w && screen->pla[j].pos.x + screen->pla[j].pos.w/2.4 > screen->tbObjet[i].pos.x && screen->pla[j].pos.y - screen->pla[j].pos.h/1.3 < screen->tbObjet[i].pos.y + screen->tbObjet[i].pos.h && screen->pla[j].pos.y - screen->pla[j].pos.h/1.3 > screen->tbObjet[i].pos.y)
			   || (screen->pla[j].pos.x - screen->pla[j].pos.w/2.5 < screen->tbObjet[i].pos.x + screen->tbObjet[i].pos.w && screen->pla[j].pos.x -screen->pla[j].pos.w/2.5 > screen->tbObjet[i].pos.x && screen->pla[j].pos.y +screen->pla[j].pos.h  < screen->tbObjet[i].pos.y + screen->tbObjet[i].pos.h && screen->pla[j].pos.y +screen->pla[j].pos.h > screen->tbObjet[i].pos.y)){
			  pose = 0;
			}
		  }


		}
		screen->tbObjet[i].vie = 1;
      }
      for(int i = screen->nbObjetsMax-screen->nbBananes; i < screen->nbObjetsMax; i++){
		poseBanane(screen, i);
      }

    }


    screen->etapeDuJeu = 4;
    
  }else if(screen->etapeDuJeu == 4){

    if(screen->modePlay == 0){
      
      for(int i = 0; i < screen->nbPlayer; i++){

		if(screen->nbPlayer == 2){
		  if(screen->pla[i].IAType == 1){
			int * paramworld = getBooble1v1World(screen, i, nbParam1);
			setIAInput(screen, i, paramworld, AI1, nbRegle1, nbParam1, NULL);	  
			free(paramworld); 
		  }else if(screen->pla[i].IAType == 2){
			int * paramworld = getBooble1v1World(screen, i, nbParam2);
			setIAInput(screen, i, paramworld, AI2, nbRegle2, nbParam2, NULL);	  
			free(paramworld); 
		  }
		}else{
		  if(screen->pla[i].IAType == 1){
			int * paramworld = getBooble2vWorld(screen, i, nbParam1, mode);
			setIAInput(screen, i, paramworld, AI1, nbRegle1, nbParam1, NULL);	  
			free(paramworld); 
		  }else if(screen->pla[i].IAType == 2){
			int * paramworld = getBooble2vWorld(screen, i, nbParam2, mode);
			setIAInput(screen, i, paramworld, AI2, nbRegle2, nbParam2, NULL);	  
			free(paramworld); 
		  }else if(screen->pla[i].IAType == 3){
			int * paramworld = getBooble2vWorld(screen, i, nbParam1, mode);
			setIAInput(screen, i, paramworld, AI1, nbRegle1, nbParam1, NULL);	  
			free(paramworld); 
		  }else if(screen->pla[i].IAType == 4){
			int * paramworld = getBooble2vWorld(screen, i, nbParam2, mode);
			setIAInput(screen, i, paramworld, AI2, nbRegle2, nbParam2, NULL);	  
			free(paramworld); 
		  }
		}


	
		int nbDep = abs(screen->pla[i].input[0]-screen->pla[i].input[2]) + abs(screen->pla[i].input[1]-screen->pla[i].input[3]);
		float depx = 0;
		float depy = 0;
		if(nbDep == 1){
		  if(screen->pla[i].input[0]) {depx -= screen->pla[i].vitesse; screen->pla[i].dirX = -1; screen->pla[i].dirY = 0;}
		  if(screen->pla[i].input[1]) {depy -= screen->pla[i].vitesse;screen->pla[i].dirX = 0; screen->pla[i].dirY = -1;}
		  if(screen->pla[i].input[2]) {depx += screen->pla[i].vitesse;screen->pla[i].dirX = 1; screen->pla[i].dirY = 0;}
		  if(screen->pla[i].input[3]) {depy += screen->pla[i].vitesse;screen->pla[i].dirX = 0; screen->pla[i].dirY = 1;}
		}else if(nbDep == 2){
		  if(screen->pla[i].input[0]) {depx -= 1/sqrt(2) * screen->pla[i].vitesse;screen->pla[i].dirX = -1;}
		  if(screen->pla[i].input[1]) {depy -= 1/sqrt(2) * screen->pla[i].vitesse;screen->pla[i].dirY = -1;}
		  if(screen->pla[i].input[2]) {depx += 1/sqrt(2) * screen->pla[i].vitesse;screen->pla[i].dirX = 1;}
		  if(screen->pla[i].input[3]) {depy += 1/sqrt(2) * screen->pla[i].vitesse;screen->pla[i].dirY = 1;}
		}

		Deplace(screen, i, depx, depy);
		
		if(screen->pla[i].shoot != 0){
		  screen->pla[i].shoot--;
		}

		if(screen->pla[i].input[4]){
		  screen->pla[i].input[4] = 0;
		  if(screen->pla[i].peuTirer == 1 && screen->pla[i].nbBouleActive < screen->pla[i].nbBoule){
			screen->pla[i].boubou[screen->pla[i].index].pos.x = screen->pla[i].pos.x;
			screen->pla[i].boubou[screen->pla[i].index].pos.y = screen->pla[i].pos.y;
			screen->pla[i].boubou[screen->pla[i].index].pos.w = screen->pla[i].pos.w*0.4;
			screen->pla[i].boubou[screen->pla[i].index].pos.h = screen->pla[i].pos.h*0.8;
			screen->pla[i].boubou[screen->pla[i].index].vie = screen->pla[i].maxBouleVie;
			//screen->pla[i].boubou[screen->pla[i].index].speed = 1*;
			screen->pla[i].boubou[screen->pla[i].index].vitX = screen->pla[i].dirX*(float) screen->pla[i].vitesse*screen->pla[i].vitTire;
			screen->pla[i].boubou[screen->pla[i].index].vitY = screen->pla[i].dirY*(float) screen->pla[i].vitesse*screen->pla[i].vitTire;
			screen->pla[i].index = (screen->pla[i].index+1)%screen->pla[i].nbBoule;
			screen->pla[i].nbBouleActive++;
			screen->pla[i].shoot = 36;
		  }
		}


		for(int j = screen->pla[i].debBoule; j < screen->pla[i].debBoule+screen->pla[i].nbBouleActive; j++){
		  boule *b = &(screen->pla[i].boubou[j%screen->pla[i].nbBoule]);

		  
		  int nbDep = ((b->vitX!=0)?1:0) + ((b->vitY!=0)?1:0);
		  //printf("%d\n", nbDep);
		  if(nbDep == 1){
		    if(b->vitX != 0) {b->pos.x += b->vitX;  if(b->pos.x < 0){b->pos.x += 100;}else if(b->pos.x > 100){b->pos.x -= 100;}}
		    else if(b->vitY != 0) {b->pos.y += b->vitY;  if(b->pos.y < 0){b->pos.y += 100;}else if(b->pos.y > 100){b->pos.y -= 100;}}
		  }else if(nbDep == 2){
		    if(b->vitX != 0) {b->pos.x += 1/sqrt(2)*b->vitX;  if(b->pos.x < 0){b->pos.x += 100;}else if(b->pos.x > 100){b->pos.x -= 100;}}
		    if(b->vitY != 0) {b->pos.y += 1/sqrt(2)*b->vitY;  if(b->pos.y < 0){b->pos.y += 100;}else if(b->pos.y > 100){b->pos.x -= 100;}}
		  }

		  float diffx = (b->pos.x - screen->tbObjet[0].pos.x);
		  if(fabs(diffx) > 50){diffx = 100-fabs(diffx);}
		  float diffy = (b->pos.y - screen->tbObjet[0].pos.y);
		  if(fabs(diffy) > 50){diffy = 100-fabs(diffy);}
		  float valdist2 = sqrt(carre(diffx)+carre(diffy));
		  float theta = orientobj(screen, i, 0)*3.14159/4;
		  float X = (1.0-((float)screen->sizeY/screen->sizeX))*screen->tbObjet[0].pos.h/2;
		  float RayonTrou = screen->tbObjet[0].pos.h/2.0 - X*fabs(sin(theta));
		  if(valdist2 < RayonTrou/2 + (b->pos.w+b->pos.h)/3){
			b->vie = 0;
		  }

		  for(int k = 0; k < screen->nbPlayer; k++){
			if(screen->pla[i].equipe != screen->pla[k].equipe && screen->pla[k].vie != 0){
			  if(sqrt(pow(b->pos.x - screen->pla[k].pos.x, 2) + pow(b->pos.y - screen->pla[k].pos.y, 2)) < (b->pos.w+b->pos.h)/3 + (screen->pla[k].pos.w + screen->pla[k].pos.h)/6){
	      
				screen->pla[k].mort++;
				screen->pla[k].vie--;

				if(screen->pla[k].vie == 0){
				  int nbequipe = 0;
				  int equipe = -1;
				  for(int i = 0; i < screen->nbPlayer; i++){
					if(screen->pla[i].vie != 0 && screen->pla[i].equipe != equipe){
					  nbequipe++;
					  equipe = screen->pla[i].equipe;
					}
				  }
				  if(nbequipe < 2){
					screen->etapeDuJeu = 5;
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
      if(screen->TrouNoirTime == 0){
		if(screen->tbObjet[0].vie == -1){
		  screen->tbObjet[0].vie = 0;
		  int pose = 0;
		  while(pose == 0){
			pose = 1;
			screen->tbObjet[0].pos.x = rand()%100;
			screen->tbObjet[0].pos.y = rand()%100;
			screen->tbObjet[0].pos.h = rand()%6 + 4;
			screen->tbObjet[0].pos.w = 0;
			for(int j = 0; j < screen->nbPlayer; j++){
			  float diffx = (screen->pla[j].pos.x - screen->tbObjet[0].pos.x);
			  if(fabs(diffx) > 50){diffx = 100-fabs(diffx);}
			  float diffy = (screen->pla[j].pos.y - screen->tbObjet[0].pos.y);
			  if(fabs(diffy) > 50){diffy = 100-fabs(diffy);}
			  float valdist2 = sqrt(carre(diffx)+carre(diffy));
			  if(valdist2 < (screen->tbObjet[0].pos.h) + (screen->pla[j].pos.w + screen->pla[j].pos.h)){
				pose = 0;
			  }
			}
		  }
		}
      }else if(screen->TrouNoirTime % (6*60) == 0){
		screen->tbObjet[0].pos.h+=1;
	  }
	  screen->TrouNoirTime++;

	  

      if(screen->TrouNoirTime > 0){
		for(int j = 0; j < screen->nbPlayer; j++){
		  if(screen->pla[j].vie != 0){
			float diffx = (screen->pla[j].pos.x - screen->tbObjet[0].pos.x);
			if(fabs(diffx) > 50){diffx = 100-fabs(diffx);}
			float diffy = (screen->pla[j].pos.y - screen->tbObjet[0].pos.y);
			if(fabs(diffy) > 50){diffy = 100-fabs(diffy);}
			float valdist2 = sqrt(carre(diffx)+carre(diffy));
			float theta = orientobj(screen, j, 0)*3.14159/4;
			float X = (1.0-((float)screen->sizeY/screen->sizeX))*screen->tbObjet[0].pos.h/2;
			float RayonTrou = screen->tbObjet[0].pos.h/2.0 - X*fabs(sin(theta));

			if(valdist2 < RayonTrou/2 + (screen->pla[j].pos.w + screen->pla[j].pos.h)/6.0){
			  screen->pla[j].vie--;

			  int nbequipe = 0;
			  int equipe = -1;
			  for(int i = 0; i < screen->nbPlayer; i++){
				if(screen->pla[i].vie != 0 && screen->pla[i].equipe != equipe){
				  nbequipe++;
				  equipe = screen->pla[i].equipe;
				}
			  }
			  if(nbequipe < 2){
				screen->etapeDuJeu = 5;
			  }
			}
		  }
		}
	  }

    }else if(screen->modePlay == 1){

      for(int i = 0; i < screen->nbPlayer; i++){
		
		if(screen->pla[i].IAType == 1){
		  int * paramworld = getMoutonWorld(screen, i, nbParam1);
		  setIAInput(screen, i, paramworld, AI1, nbRegle1, nbParam1, NULL);	  
		  free(paramworld); 
		}else if(screen->pla[i].IAType == 2){
		  int * paramworld = getLoupWorld(screen, i, nbParam2);
		  setIAInput(screen, i, paramworld, AI2, nbRegle2, nbParam2, NULL);	  
		  free(paramworld); 
		}
		
		int nbDep = abs(screen->pla[i].input[0]-screen->pla[i].input[2]) + abs(screen->pla[i].input[1]-screen->pla[i].input[3]);
		float depx = 0;
		float  depy = 0;
		if(nbDep == 1){
		  if(screen->pla[i].input[0]) {depx -= screen->pla[i].vitesse; screen->pla[i].dirX = -1; screen->pla[i].dirY = 0;}
		  if(screen->pla[i].input[1]) {depy -= screen->pla[i].vitesse;screen->pla[i].dirX = 0; screen->pla[i].dirY = -1;}
		  if(screen->pla[i].input[2]) {depx += screen->pla[i].vitesse;screen->pla[i].dirX = 1; screen->pla[i].dirY = 0;}
		  if(screen->pla[i].input[3]) {depy += screen->pla[i].vitesse;screen->pla[i].dirX = 0; screen->pla[i].dirY = 1;}
		}else if(nbDep == 2){
		  if(screen->pla[i].input[0]) {depx -= 1/sqrt(2) * screen->pla[i].vitesse;screen->pla[i].dirX = -1;}
		  if(screen->pla[i].input[1]) {depy -= 1/sqrt(2) * screen->pla[i].vitesse;screen->pla[i].dirY = -1;}
		  if(screen->pla[i].input[2]) {depx += 1/sqrt(2) * screen->pla[i].vitesse;screen->pla[i].dirX = 1;}
		  if(screen->pla[i].input[3]) {depy += 1/sqrt(2) * screen->pla[i].vitesse;screen->pla[i].dirY = 1;}
		}

		Deplace(screen, i, depx, depy);
	  }
      
      for(int i = screen->nbPreda; i < screen->nbProie+screen->nbPreda; i++){
		for(int j = 0; j < screen->nbPreda; j++){
		  if(sqrt(pow(screen->pla[i].pos.x - screen->pla[j].pos.x, 2) + pow(screen->pla[i].pos.y - screen->pla[j].pos.y, 2)) < (screen->pla[i].pos.w+screen->pla[i].pos.h)/4 + (screen->pla[j].pos.w + screen->pla[j].pos.h)/4){
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

	if(screen->modePlay == 0){
	  for(int i = 0; i < screen->nbPlayer; i++){
		free(screen->pla[i].boubou);
	  }
	}
	free(screen->pla);


	screen->etapeDuJeu = 2;
  }
}




void poseBanane(ecran *screen, int index){
  screen->tbObjet[index].id = 4;
  int pose = 0;
  while(pose == 0){
    screen->tbObjet[index].pos.x = rand()%100;
    screen->tbObjet[index].pos.y = rand()%100;

    pose = 1;
    for(int i = 0; i < screen->nbObjetsMax-screen->nbBananes; i++){
      if(screen->tbObjet[index].pos.x < screen->tbObjet[i].pos.x + screen->tbObjet[i].pos.w && screen->tbObjet[index].pos.x > screen->tbObjet[i].pos.x && screen->tbObjet[index].pos.y < screen->tbObjet[i].pos.y + screen->tbObjet[i].pos.h && screen->tbObjet[index].pos.y > screen->tbObjet[i].pos.y ){
		pose = 0;
      }
    }

  }

  screen->tbObjet[index].pos.w = 4;
  screen->tbObjet[index].pos.h = 4;
  screen->tbObjet[index].vie = 1;
  
}



void Deplace(ecran *screen, int index, float depx, float depy){
  int move = 1;
  for(int i = 0; i < screen->nbObjetsMax; i++){
	if((screen->pla[index].pos.x - screen->pla[index].pos.w/2.4+ depx < screen->tbObjet[i].pos.x + screen->tbObjet[i].pos.w && screen->pla[index].pos.x - screen->pla[index].pos.w/2.4 + depx > screen->tbObjet[i].pos.x && screen->pla[index].pos.y - screen->pla[index].pos.h/1.3 + depy < screen->tbObjet[i].pos.y + screen->tbObjet[i].pos.h && screen->pla[index].pos.y - screen->pla[index].pos.h/1.3 + depy > screen->tbObjet[i].pos.y)
	   || (screen->pla[index].pos.x + screen->pla[index].pos.w/2.5 + depx < screen->tbObjet[i].pos.x + screen->tbObjet[i].pos.w && screen->pla[index].pos.x +screen->pla[index].pos.w/2.5 + depx > screen->tbObjet[i].pos.x && screen->pla[index].pos.y +screen->pla[index].pos.h + depy < screen->tbObjet[i].pos.y + screen->tbObjet[i].pos.h && screen->pla[index].pos.y +screen->pla[index].pos.h + depy > screen->tbObjet[i].pos.y)
	   || (screen->pla[index].pos.x + screen->pla[index].pos.w/2.4+ depx < screen->tbObjet[i].pos.x + screen->tbObjet[i].pos.w && screen->pla[index].pos.x + screen->pla[index].pos.w/2.4 + depx > screen->tbObjet[i].pos.x && screen->pla[index].pos.y - screen->pla[index].pos.h/1.3 + depy < screen->tbObjet[i].pos.y + screen->tbObjet[i].pos.h && screen->pla[index].pos.y - screen->pla[index].pos.h/1.3 + depy > screen->tbObjet[i].pos.y)
	   || (screen->pla[index].pos.x - screen->pla[index].pos.w/2.5 + depx < screen->tbObjet[i].pos.x + screen->tbObjet[i].pos.w && screen->pla[index].pos.x -screen->pla[index].pos.w/2.5 + depx > screen->tbObjet[i].pos.x && screen->pla[index].pos.y +screen->pla[index].pos.h + depy < screen->tbObjet[i].pos.y + screen->tbObjet[i].pos.h && screen->pla[index].pos.y +screen->pla[index].pos.h + depy > screen->tbObjet[i].pos.y)){
	  if(screen->tbObjet[i].id == 1){
		move = 0;
	  }else if(screen->pla[index].equipe == 1 && screen->tbObjet[i].id == 1){
		poseBanane(screen, i);
		screen->pla[index].kill++;
	  }
	}
  }
  if(move == 1){
    screen->pla[index].pos.x += depx;
    if(screen->pla[index].pos.x < 0){screen->pla[index].pos.x +=100;}else if(screen->pla[index].pos.x > 100){screen->pla[index].pos.x -= 100;} 
    screen->pla[index].pos.y += depy;
    if(screen->pla[index].pos.y < 0){screen->pla[index].pos.y +=100;}else if(screen->pla[index].pos.y > 100){screen->pla[index].pos.y -= 100;}
  }
}


void initMout(){
  nbParam1 = 2;
  nbRegle1 = 16;
  AI1 = (int **)malloc(sizeof(int*)*NBRMOUT);
  for(int i = 0; i < NBRMOUT; i++){
    AI1[i] = (int*)malloc(sizeof(int)*4);
  }
  for(int i = 0; i < 8; i++){
    AI1[i*2][0] = 0;
    AI1[i*2][1] = i;
    AI1[i*2][2] = (4+i)%8;
    AI1[i*2][3] = 5;

    AI1[i*2+1][0] = 1;
    AI1[i*2+1][1] = i;
    AI1[i*2+1][2] = (4+i)%8;
    AI1[i*2+1][3] = 5;

    // mouton[i*4+1][0] = k;
    // mouton[i*4+1][1] = i;
    // mouton[i*4+1][2] = (6+i)%8;
    // mouton[i*4+1][3] = 3;

    // mouton[i*4+2][0] = k;
    // mouton[i*4+2][1] = i;
    // mouton[i*4+2][2] = (4+i)%8;
    // mouton[i*4+2][3] = 3;

    // mouton[i*3 +2][0] = -1;
    // mouton[i*3 +2][1] = -1;
    // mouton[i*3 +2][2] = i;
    // mouton[i*3 +2][3] = 1;
  }
}

void loadIALout(ecran* screen){
  if(AI2 != NULL){
    for(int i = 0; i < nbRegle2; i++){
      free(AI2[i]);
    }
    free(AI2);
  }
  nbRegle2 = -1;
  char name[30];
  sprintf(name, "Ressources/IALoupLast.txt");
  AI2 = readIAFile(name, &nbRegle2, &nbParam2);
  if(AI2 == NULL || nbRegle2 == -1){
    screen->etapeDuJeu = 2;
    fprintf(stderr, "Pas d'ia entrainée");
  }
}





void loadBubbleIA1(ecran* screen){
  if(AI1 != NULL){
    for(int i = 0; i < nbRegle1; i++){
      free(AI1[i]);
    }
    free(AI1);
  }
  nbRegle1 = -1;
  char name[30];
  sprintf(name, "Ressources/IABobble%d.txt", rand()%10);
  AI1 = readIAFile(name, &nbRegle1, &nbParam1);
  if(AI1 == NULL || nbRegle1 == -1){
    screen->etapeDuJeu = 2;
    fprintf(stderr, "Pas d'ia entrainée");
  }
}

void loadBubbleIA2(ecran* screen){
  if(AI2 != NULL){
    for(int i = 0; i < nbRegle2; i++){
      free(AI2[i]);
    }
    free(AI2);
  }
  nbRegle2 = -1;
  char name[30];
  sprintf(name, "Ressources/IABobble%d.txt", rand()%10);
  AI2 = readIAFile(name, &nbRegle2, &nbParam2);
  if(AI2 == NULL || nbRegle2 == -1){
    screen->etapeDuJeu = 2;
    fprintf(stderr, "Pas d'ia entrainée");
  }
}


void loadBubble2V2IA1(ecran* screen){
  if(AI1 != NULL){
    for(int i = 0; i < nbRegle1; i++){
      free(AI1[i]);
    }
    free(AI1);
  }
  nbRegle1 = -1;
  char name[30];
  sprintf(name, "Ressources/IA2V2Bobble%d.txt", rand()%10);
  AI1 = readIAFile(name, &nbRegle1, &nbParam1);
  if(AI1 == NULL || nbRegle1 == -1){
    screen->etapeDuJeu = 2;
    fprintf(stderr, "Pas d'ia entrainée");
  }
  mode = 1;
}

void loadBubble2V2IA2(ecran* screen){
  if(AI2 != NULL){
    for(int i = 0; i < nbRegle2; i++){
      free(AI2[i]);
    }
    free(AI2);
  }
  nbRegle2 = -1;
  char name[30];
  sprintf(name, "Ressources/IA2V2Bobble%d.txt", rand()%10);
  AI2 = readIAFile(name, &nbRegle2, &nbParam2);
  if(AI2 == NULL || nbRegle2 == -1){
    screen->etapeDuJeu = 2;
    fprintf(stderr, "Pas d'ia entrainée");
  }
  mode = 1;
}
