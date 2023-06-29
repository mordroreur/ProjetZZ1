#include "render.h"

void mainRendering(ecran *screen){
  switch(screen->etapeDuJeu){
  case 1: loadingScreen(screen);break;
  case 2: DrawMenu(screen);break;
  case 4: DrawGame(screen);break;
  default: loadingScreen(screen);break;
  }
}


void DrawGame(ecran *screen){
  if(screen->whichBack == 0){
    SDL_SetRenderDrawColor(screen->renderer, 255, 255, 255, 0);
    SDL_RenderFillRect(screen->renderer, NULL);
  }

  for(int i = 0; i < screen->nbPlayer; i++){
    DrawImage(0, screen->pla[i].pos.x, screen->pla[i].pos.y, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', 0, 0, 0, 0, 0, 0, screen);

    for(int j = 0; j < screen->maxBoule; j++){
      if(screen->pla[i].boubou[j].vie >= 0){
	DrawImage(0, screen->pla[i].boubou[j].pos.x, screen->pla[i].boubou[j].pos.y, screen->pla[i].boubou[j].pos.w, screen->pla[i].boubou[j].pos.h, 'c', 0, 0, 0, 0, 0, 0, screen);
      }
    }
  }

  
}

void DrawMenu(ecran *screen){
  int posMX, posMY;
  //  int nbT = SDL_GetTicks()/500;
  SDL_GetMouseState(&posMX, &posMY);

  SDL_SetRenderDrawColor(screen->renderer, 255, 255, 255, 0);
  SDL_RenderFillRect(screen->renderer, NULL);
  SDL_Rect rect;
  
  
  if(isInButton(25, 50, 50, 100, 'c', posMX, posMY, screen)){
    SDL_SetRenderDrawColor(screen->renderer, 0, 255, 0, 0);
    rect.x = 0;
    rect.y = 0;
    rect.w = screen->sizeX/2;
    rect.y = screen->sizeY;
    SDL_RenderFillRect(screen->renderer, &rect);
    DrawString("Play", 25, 25, 10, 'c', 0, 0, 0, screen);
  }
}


void loadingScreen(ecran *screen){
  
  int nb3 = SDL_GetTicks()/10;
  int nb = (nb3) % 100 - 50;
  int nb2 = (nb3+35)% 98 - 49;
  nb3 = (nb3+65)% 96 - 48;

  
  SDL_SetRenderDrawColor(screen->renderer, 255, 255, 255, 0);
  SDL_RenderFillRect(screen->renderer, NULL);

  //DrawImage(0, 25, 25, 25, 25, 'n', 0, 0, 0, 0, screen);
  
  DrawString("Loading", 50, 50, 10, 'c', 0, 0, 0, screen);
  DrawString("                .", 50, 47.5 + abs(nb)/10.0, 10, 'c', 0, 0, 0, screen);
  DrawString("                  .", 50, 47.5 + abs(nb2)/10.0, 10, 'c', 0, 0, 0, screen);
  DrawString("                    .", 50, 47.5 + abs(nb3)/10.0, 10, 'c', 0, 0, 0, screen);

  //DrawImage(int imagenb, float x, float y, float sizeX, float sizeY, char center, int etatPremier, float TimebeforeNext, int flip, int angle, ecran *screen)
}
