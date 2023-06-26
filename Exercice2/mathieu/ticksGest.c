#include "ticksGest.h"


void mainTickGest(ecran *screen) {}

void createApple(ecran *screen){
  int nbPossible = 0;
  for(int i = 0; i < screen->taille_Ter_x; i++){
    for(int j = 0; j < screen->taille_Ter_y; j++){
      if(screen->Ter[i][j] == 0){
	nbPossible++;
      }
    }
  }
  if(nbPossible == 0){
    screen->etapeDuJeu = 5;
  }else{
    int ou = rand()%nbPossible;
    nbPossible = 0;
    for(int i = 0; i < screen->taille_Ter_x && ou != -1; i++){
      for(int j = 0; j < screen->taille_Ter_y && ou != -1; j++){
	if(screen->Ter[i][j] == 0){
	  if(nbPossible == ou){
	    screen->Ter[i][j] = -1;
	    ou = -1;
	  }
	  nbPossible++;
	}
      }
    }
  }
  
}
