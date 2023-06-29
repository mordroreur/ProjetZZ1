#include "eventGest.h"
#include "serveurHost.h"
#include "serveurJoin.h"
#include <pthread.h>



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
       pthread_t threadServ;
       int RetourDuThreadDuServ = pthread_create(&threadServ, NULL, launchServeur,  screen);
       if(RetourDuThreadDuServ){
	 screen->etapeDuJeu = 69;
       }else{
	 screen->etapeDuJeu = 6;
       }
       
       screen->etapeDuJeu = 6;
     }else  if(isInButton(75, 50, 50, 100, 'c', posMX, posMY, screen)){
       pthread_t threadclient;
       int RetourDuThreadDuClient = pthread_create(&threadclient, NULL, ConnectServeur,  screen);
       if(RetourDuThreadDuClient){
	 screen->etapeDuJeu = 69;
       }else{
	 screen->etapeDuJeu = 6;
       }
     }
  }
 
}


void RightClick(ecran *screen) {
  int posMX, posMY;
  SDL_GetMouseState(&posMX, &posMY);
 
}
