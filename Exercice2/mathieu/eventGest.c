#include "eventGest.h"

void keyUp(SDL_KeyboardEvent key, ecran *screen) {
  if(key.keysym.sym == SDLK_ESCAPE){
    screen->etapeDuJeu = 0;
  }
}

void keyDown(SDL_KeyboardEvent key, ecran *screen) {
  if(screen->etapeDuJeu == 2){
    if(key.keysym.sym == 1073741904){
      screen->serpDir = 1;
      screen->etapeDuJeu = 3;
      screen->lastDep = WAITTIME;
    }else if(key.keysym.sym == 1073741906){
      screen->serpDir = 2;
      screen->etapeDuJeu = 3;
      screen->lastDep = WAITTIME;
    }else if(key.keysym.sym == 1073741903){
      screen->serpDir = 3;
      screen->etapeDuJeu = 3;
      screen->lastDep = WAITTIME;
    }else if(key.keysym.sym == 1073741905){
      screen->serpDir = 4;
      screen->etapeDuJeu = 3;
      screen->lastDep = WAITTIME;
    }
    //printf("%d\n", key.keysym.sym);
  }else if(screen->etapeDuJeu == 3){
    if(key.keysym.sym == 1073741904){
      screen->serpDir = 1;
    }else if(key.keysym.sym == 1073741906){
      screen->serpDir = 2;
    }else if(key.keysym.sym == 1073741903){
      screen->serpDir = 3;
    }else if(key.keysym.sym == 1073741905){
      screen->serpDir = 4;
    }
    //printf("%d\n", key.keysym.sym);
  }
}

void LeftClick(ecran *screen) {
  int posMX, posMY;
  SDL_GetMouseState(&posMX, &posMY);

  if(screen->etapeDuJeu == 8 || screen->etapeDuJeu == 15){
    if(posMX > screen->sizeX/5.0 && posMX < screen->sizeX/5.0 + screen->sizeX/5.0 * 3.0 && posMY > screen->sizeY/5.0 * 3.0 && posMY < screen->sizeY/5.0 *3.0 + screen->sizeY/5.0){
      screen->etapeDuJeu = 0;
    }else if(posMX > screen->sizeX/5.0 && posMX < screen->sizeX/5.0 + screen->sizeX/5.0 * 3.0 && posMY > screen->sizeY/5.0 && posMY < screen->sizeY/5.0 + screen->sizeY/5.0){
      screen->etapeDuJeu = 42;
    }
  }
 
}


void RightClick(ecran *screen) {
  int posMX, posMY;
  SDL_GetMouseState(&posMX, &posMY);
 
}
