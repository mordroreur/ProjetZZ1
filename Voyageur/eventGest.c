#include "eventGest.h"
#include "liste.h"

void keyUp(SDL_KeyboardEvent key, ecran *screen) {
  int etat = screen->etapeDuJeu;
  switch (key.keysym.sym)
  {
    case SDLK_ESCAPE:
      if (etat == 1 || etat == 2)
        screen->etapeDuJeu = 0;
      else if (etat == 4 || etat == 5)
        screen->etapeDuJeu = 7; 
      else if (etat == 666 || etat == 667)
        screen->etapeDuJeu = 2;
      else if (etat == 668)
        screen->etapeDuJeu = 666;
      else if (etat == 669)
        screen->etapeDuJeu = 667;
    break;
    case SDLK_RETURN:
      if (etat == 668)
        screen->etapeDuJeu = 666;
      else if (etat == 669)
        screen->etapeDuJeu = 667;
      else if (etat == 666)
        screen->etapeDuJeu = 668;
      else if (etat == 667)
        screen->etapeDuJeu = 669;
    break;
    case SDLK_UP:
      if (etat == 666)
        screen->etapeDuJeu = 667;
      if (etat == 667)
        screen->etapeDuJeu = 666;
    break;
    case SDLK_DOWN:
      if (etat == 666)
        screen->etapeDuJeu = 667;
      if (etat == 667)
        screen->etapeDuJeu = 666;
    break;
  }
}

void keyDown(SDL_KeyboardEvent key, ecran *screen) {}

void LeftClick(ecran *screen) {
  int posMX, posMY;
  SDL_GetMouseState(&posMX, &posMY);
  if(screen->etapeDuJeu == 2)
  {
    if (isInButton(50, 50, 30, 20, 'c', posMX, posMY, screen)){
      screen->etapeDuJeu = 3;
    }
    else if (isInButton(10, 90, 7, 7, 'c', posMX, posMY, screen)){
      screen->etapeDuJeu = 666; // paramètre
    }
  }else if(screen->etapeDuJeu == 4 || screen->etapeDuJeu == 5){
    for(int i = 0; i < screen->niveau.nbSommets; i++){
      if(i != screen->niveau.playerCase && screen->niveau.arretes[screen->niveau.playerCase][i] > 0 && sqrt(pow(posMX-screen->sizeX * screen->niveau.Sommets[i][0]/100.0, 2) + pow(posMY-screen->sizeY * screen->niveau.Sommets[i][1]/100.0, 2)) < screen->sizeY/25.0){
	screen->niveau.playerCase = i;
	LL_add_first(screen->niveau.PlayerReso, screen->niveau.playerCase);
	if (screen->niveau.playerCase == screen->niveau.startCase) {
	  int all = 1;
	  for(int j = 0; j < screen->niveau.nbSommets; j++){
	    if(!LL_contains(screen->niveau.PlayerReso, j)){
	      all = 0;
	    }
	  }
	  if(all){
	    screen->etapeDuJeu = 6;
	    screen->niveau.drawFinal = 0;
	  }
	}
      }
    }
  }
}


void RightClick(ecran *screen) {
  int posMX, posMY;
  SDL_GetMouseState(&posMX, &posMY);
 
}
