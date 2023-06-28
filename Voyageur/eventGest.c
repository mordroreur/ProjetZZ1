#include "eventGest.h"

void keyUp(SDL_KeyboardEvent key, ecran *screen) {
  int etat = screen->etapeDuJeu;
  switch (key.keysym.sym)
  {
    case SDLK_ESCAPE:
      if (etat == 1 || etat == 2)
        screen->etapeDuJeu = 0;
      else if (etat == 4 || etat == 5 || etat == 6)
        screen->etapeDuJeu = 7; 
      else if (etat == 666 || etat == 667)
        screen->etapeDuJeu = 2;
      else if (etat == 668)
        screen->etapeDuJeu = 666;
      else if (etat == 669)
        screen->etapeDuJeu = 667;
      else
        screen->etapeDuJeu = 0;
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
      else if (etat == 667)
        screen->etapeDuJeu = 666;
      else if (etat == 668)
        screen->niveau.nbSommets += 10;
      else if (etat == 669 && screen->niveau.proba + 0.1 -1 <= 0.0002)
        screen->niveau.proba += 0.1;
    break;
    case SDLK_DOWN:
      if (etat == 666)
        screen->etapeDuJeu = 667;
      else if (etat == 667)
        screen->etapeDuJeu = 666;
      else if (etat == 668 && screen->niveau.nbSommets - 10 >= 2)
        screen->niveau.nbSommets -= 10;
      else if (etat == 669 && screen->niveau.proba - 0.1 >= 0)
        screen->niveau.proba -= 0.1;
    break;
    case SDLK_RIGHT:
      if (etat == 668)
        screen->niveau.nbSommets += 1;
      else if (etat == 669 && screen->niveau.proba + 0.01 -1 <= 0.0002)
        screen->niveau.proba += 0.01;
    break;
    case SDLK_LEFT:
      if (etat == 668 && screen->niveau.nbSommets - 1 >= 2)
        screen->niveau.nbSommets -= 1;
      else if (etat == 669 && screen->niveau.proba - 0.01 >= 0)
        screen->niveau.proba -= 0.01;
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
    else if (isInButton(50, 75, 30, 20, 'c', posMX, posMY, screen)){
      screen->etapeDuJeu = 0;
    }
  }
}


void RightClick(ecran *screen) {
  int posMX, posMY;
  SDL_GetMouseState(&posMX, &posMY);
 
}
