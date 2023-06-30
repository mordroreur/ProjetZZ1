#include "eventGest.h"


void keyUp(SDL_KeyboardEvent key, ecran *screen) {
  if(key.keysym.sym == SDLK_ESCAPE){

	if (screen->etapeDuJeu == 5)
	{
		Mix_PlayMusic(screen->musique[0], -1);
		SDL_Delay(50);
		screen->etapeDuJeu = 12;
		screen->decalageB1 = 116;
		screen->decalageB2 = 130;
	}
	else
	    screen->etapeDuJeu = 0;
  }else if(screen->etapeDuJeu == 4){
    switch (key.keysym.sym)
          {
            /* Joueur 2*/
	  case SDLK_UP: if(screen->nbPlayer > 1) screen->pla[1].input[1] = 0; break;
	  case SDLK_LEFT: if(screen->nbPlayer > 1) screen->pla[1].input[0] = 0; break;
	  case SDLK_DOWN: if(screen->nbPlayer > 1) screen->pla[1].input[3] = 0; break;
	  case SDLK_RIGHT: if(screen->nbPlayer > 1) screen->pla[1].input[2] = 0; break;
	  case SDLK_o: if(screen->nbPlayer > 1) screen->pla[1].input[1] = 0; break;
	  case SDLK_k: if(screen->nbPlayer > 1) screen->pla[1].input[0] = 0; break;
	  case SDLK_l: if(screen->nbPlayer > 1) screen->pla[1].input[3] = 0; break;
	  case SDLK_m: if(screen->nbPlayer > 1) screen->pla[1].input[2] = 0; break;
	  case SDLK_RSHIFT: if(screen->nbPlayer > 1) screen->pla[1].input[4] = 0; break;
            /* Joueur 1 */
	  case SDLK_q: if(screen->nbPlayer > 0) screen->pla[0].input[0] = 0; break;
	  case SDLK_z: if(screen->nbPlayer > 0) screen->pla[0].input[1] = 0; break;
	  case SDLK_s: if(screen->nbPlayer > 0) screen->pla[0].input[3] = 0; break;
	  case SDLK_d: if(screen->nbPlayer > 0) screen->pla[0].input[2] = 0; break;
	  case SDLK_SPACE: if(screen->nbPlayer > 0) screen->pla[0].input[4] = 0; break;
	  default:
            break;
          }
  }
}

void keyDown(SDL_KeyboardEvent key, ecran *screen) {
  if(screen->etapeDuJeu == 4){
    switch (key.keysym.sym)
          {
            /* Joueur 2*/
	  case SDLK_UP: if(screen->nbPlayer > 1) screen->pla[1].input[1] = 1; break;
	  case SDLK_LEFT: if(screen->nbPlayer > 1) screen->pla[1].input[0] = 1; break;
	  case SDLK_DOWN: if(screen->nbPlayer > 1) screen->pla[1].input[3] = 1; break;
	  case SDLK_RIGHT: if(screen->nbPlayer > 1) screen->pla[1].input[2] = 1; break;
	  case SDLK_o: if(screen->nbPlayer > 1) screen->pla[1].input[1] = 1;; break;
	  case SDLK_k: if(screen->nbPlayer > 1) screen->pla[1].input[0] = 1; break;
	  case SDLK_l: if(screen->nbPlayer > 1) screen->pla[1].input[3] = 1; break;
	  case SDLK_m: if(screen->nbPlayer > 1) screen->pla[1].input[2] = 1; break;
	  case SDLK_RSHIFT: if(screen->nbPlayer > 1) screen->pla[1].input[4] = 1; break;
            /* Joueur 1 */
	  case SDLK_q: if(screen->nbPlayer > 0) screen->pla[0].input[0] = 1; break;
	  case SDLK_z: if(screen->nbPlayer > 0) screen->pla[0].input[1] = 1; break;
	  case SDLK_s: if(screen->nbPlayer > 0) screen->pla[0].input[3] = 1; break;
	  case SDLK_d: if(screen->nbPlayer > 0) screen->pla[0].input[2] = 1; break;
	  case SDLK_SPACE: if(screen->nbPlayer > 0) screen->pla[0].input[4] = 1; break;
	  default:
            break;
          }
  }
}

void LeftClick(ecran *screen) {
  int posMX, posMY;
  SDL_GetMouseState(&posMX, &posMY);
  if(screen->etapeDuJeu == 2){
     if(isInButton(80, 50, 30, 20, 'c', posMX, posMY, screen)){
       screen->etapeDuJeu = 9;
     }
	 else if (isInButton(80, 80, 30, 20, 'c', posMX, posMY, screen))
	 {
		screen->etapeDuJeu = 0;
	 }
  }
 
}


void RightClick(ecran *screen) {
  int posMX, posMY;
  SDL_GetMouseState(&posMX, &posMY);
 
}
