#include "eventGest.h"
#include "serveurHost.h"
#include "serveurJoin.h"

void keyUp(SDL_KeyboardEvent key, ecran *screen) {
  if(key.keysym.sym == SDLK_ESCAPE){
    screen->etapeDuJeu = 0;
  }
}

void keyDown(SDL_KeyboardEvent key, ecran *screen) {}

void LeftClick(ecran *screen) {
  int posMX, posMY;
  SDL_GetMouseState(&posMX, &posMY);
  if(screen->etapeDuJeu == 2){
     if(isInButton(25, 50, 50, 100, 'c', posMX, posMY, screen)){
       launchServeur(screen);
       screen->etapeDuJeu = 6;
     }else  if(isInButton(75, 50, 50, 100, 'c', posMX, posMY, screen)){
       ConnectServeur(screen);
       screen->etapeDuJeu = 6;
     }
  }
 
}


void RightClick(ecran *screen) {
  int posMX, posMY;
  SDL_GetMouseState(&posMX, &posMY);
 
}
