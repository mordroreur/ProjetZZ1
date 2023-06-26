#include "ticksGest.h"


void mainTickGest(ecran *screen) {
  if(screen->etapeDuJeu == 3){
    if(screen->lastDep == 0){
      screen->lastDep = 60;
      if(screen->serpDir == 1){
	if(screen->serpX == 0 || screen->Ter[screen->serpX-1][screen->serpY] > 0){
	  screen->etapeDuJeu = 6;
	}else {
	  if(screen->Ter[screen->serpX-1][screen->serpY] == -1){
	    screen->tailleSerp++;
	    createApple(screen);
	  }
	  for(int i = 0; i < screen->taille_Ter_x; i++){
	    for(int j = 0; j < screen->taille_Ter_y; j++){
	      if(screen->Ter[i][j] > 0){
		screen->Ter[i][j]++;
		if(screen->Ter[i][j] > screen->tailleSerp){
		  screen->Ter[i][j] = 0;
		}
	      }
	    }
	  }
	  screen->serpX--;
	  screen->Ter[screen->serpX][screen->serpY] = 1;
	}
	
      }else if(screen->serpDir == 2){
	if(screen->serpY == 0 || screen->Ter[screen->serpX][screen->serpY-1] > 0){
	  screen->etapeDuJeu = 6;
	}else {
	  if(screen->Ter[screen->serpX][screen->serpY-1] == -1){
	    screen->tailleSerp++;
	    createApple(screen);
	  }
	  for(int i = 0; i < screen->taille_Ter_x; i++){
	    for(int j = 0; j < screen->taille_Ter_y; j++){
	      if(screen->Ter[i][j] > 0){
		screen->Ter[i][j]++;
		if(screen->Ter[i][j] > screen->tailleSerp){
		  screen->Ter[i][j] = 0;
		}
	      }
	    }
	  }
	  screen->serpY--;
	  screen->Ter[screen->serpX][screen->serpY] = 1;
	  
	}	
      } else if(screen->serpDir == 3){
	if(screen->serpX == screen->taille_Ter_x-1 || screen->Ter[screen->serpX+1][screen->serpY] > 0){
	  screen->etapeDuJeu = 6;
	}else {
	  if(screen->Ter[screen->serpX+1][screen->serpY] == -1){
	    screen->tailleSerp++;
	    createApple(screen);
	  }
	  for(int i = 0; i < screen->taille_Ter_x; i++){
	    for(int j = 0; j < screen->taille_Ter_y; j++){
	      if(screen->Ter[i][j] > 0){
		screen->Ter[i][j]++;
		if(screen->Ter[i][j] > screen->tailleSerp){
		  screen->Ter[i][j] = 0;
		}
	      }
	    }
	  }
	  screen->serpX++;
	  screen->Ter[screen->serpX][screen->serpY] = 1;
	}
	
      }else if(screen->serpDir == 4){
	if(screen->serpY == screen->taille_Ter_y-1 || screen->Ter[screen->serpX][screen->serpY+1] > 0){
	  screen->etapeDuJeu = 6;
	}else {
	  if(screen->Ter[screen->serpX][screen->serpY+1] == -1){
	    screen->tailleSerp++;
	    createApple(screen);
	  }
	  for(int i = 0; i < screen->taille_Ter_x; i++){
	    for(int j = 0; j < screen->taille_Ter_y; j++){
	      if(screen->Ter[i][j] > 0){
		screen->Ter[i][j]++;
		if(screen->Ter[i][j] > screen->tailleSerp){
		  screen->Ter[i][j] = 0;
		}
	      }
	    }
	  }
	  screen->serpY++;
	  screen->Ter[screen->serpX][screen->serpY] = 1;
	}
	
      }
    }else{
      screen->lastDep--;
    }
  }
}

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
