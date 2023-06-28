#include "eventGest.h"

void keyUp(SDL_KeyboardEvent key, ecran *screen) {
  if(key.keysym.sym == SDLK_ESCAPE){
    screen->etapeDuJeu = 0;
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
  }
}


void RightClick(ecran *screen) {
  int posMX, posMY;
  SDL_GetMouseState(&posMX, &posMY);
 
}
