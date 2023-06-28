#include "eventGest.h"

void keyUp(SDL_KeyboardEvent key, ecran *screen) {
  switch (key.keysym.sym)
  {
    case SDLK_ESCAPE:
      if (screen->etapeDuJeu == 1 || screen->etapeDuJeu == 2)
        screen->etapeDuJeu = 0;
      if (screen->etapeDuJeu == 3 || screen->etapeDuJeu == 4 || screen->etapeDuJeu == 5)
        screen->etapeDuJeu = 7; 
      if (screen->etapeDuJeu == 666)
        screen->etapeDuJeu = 2;
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
  }
}


void RightClick(ecran *screen) {
  int posMX, posMY;
  SDL_GetMouseState(&posMX, &posMY);
 
}
