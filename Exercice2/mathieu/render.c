#include "render.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

void mainRendering(ecran *screen){
  switch(screen->etapeDuJeu){
  case 1: loadingScreen(screen);break;
  case 2: DrawTer(screen);break;
  case 3: DrawTer(screen);break;
  case 15: DrawVictoryMenu(screen); break;
  case 8: DrawMenu(screen); break;
  case 69: DrawAllocErreur(screen);break;
  default: loadingScreen(screen);break;
  }
}


void DrawVictoryMenu(ecran *screen){
  DrawMenu(screen);
  DrawString("VICTOIRE", 50, 50, 15, 'c', 160, 255, 160, screen);
}


void DrawAllocErreur(ecran *screen){
  SDL_SetRenderDrawColor(screen->renderer, 70, 70, 255, 0);
  SDL_RenderFillRect(screen->renderer, NULL);
  DrawString("ERREUR DE MALLOC!!!", 50, 30, 8, 'c', 255, 255, 255, screen);
}

void DrawMenu(ecran *screen){
  SDL_SetRenderDrawColor(screen->renderer, 0, 200, 0, 0);
  SDL_RenderFillRect(screen->renderer, NULL);

  int posMX;
  int posMY;
  SDL_GetMouseState(&posMX, &posMY);

  SDL_Rect Rect;
  
  Rect.x = screen->sizeX/5.0;
  Rect.y = screen->sizeY/5.0;
  Rect.h = screen->sizeY/5.0;
  Rect.w = screen->sizeX/5.0 * 3.0;
  int isSouris = (posMX > screen->sizeX/5.0 && posMX < screen->sizeX/5.0 + screen->sizeX/5.0 * 3.0 && posMY > screen->sizeY/5.0 && posMY < screen->sizeY/5.0 + screen->sizeY/5.0)?1:0;

  SDL_SetRenderDrawColor(screen->renderer, 0 + 50*isSouris, 90+ 50*isSouris, 0+ 50*isSouris, 0);
  SDL_RenderFillRect(screen->renderer, &Rect);

  DrawString("Play", 50, 30, 8, 'c', 255*isSouris, 255*isSouris, 255*isSouris, screen);


  Rect.x = screen->sizeX/5.0;
  Rect.y = screen->sizeY/5.0 * 3.0;
  Rect.h = screen->sizeY/5.0;
  Rect.w = screen->sizeX/5.0 * 3.0;
  isSouris = (posMX > screen->sizeX/5.0 && posMX < screen->sizeX/5.0 + screen->sizeX/5.0 * 3.0 && posMY > screen->sizeY/5.0 * 3.0 && posMY < screen->sizeY/5.0 *3.0 + screen->sizeY/5.0)?1:0;

  SDL_SetRenderDrawColor(screen->renderer, 90 + 50*isSouris, 0+ 50*isSouris, 0+ 50*isSouris, 0);
  SDL_RenderFillRect(screen->renderer, &Rect);

  DrawString("Quit", 50, 70, 8, 'c', 255*isSouris, 255*isSouris, 255*isSouris, screen);

  
}


void DrawTer(ecran *screen){
  SDL_SetRenderDrawColor(screen->renderer, 0, 200, 0, 0);
  SDL_RenderFillRect(screen->renderer, NULL);

  SDL_Rect rect;
  rect.h = ((float)(screen->sizeY) / screen->taille_Ter_y) * 0.9;
  rect.w = ((float)(screen->sizeX) / screen->taille_Ter_x) * 0.9;

  
  for(int i = 0; i < screen->taille_Ter_x; i++){
    for(int j = 0; j < screen->taille_Ter_y; j++){
      if(screen->Ter[i][j] == -1){
	SDL_SetRenderDrawColor(screen->renderer, 255, 0, 0, 0);
	rect.x = ((float)(screen->sizeX) / screen->taille_Ter_x)*i;
	rect.y = ((float)(screen->sizeY) / screen->taille_Ter_y)*j;
	SDL_RenderFillRect(screen->renderer, &rect);
      }else if (screen->Ter[i][j] == 1) {
	SDL_SetRenderDrawColor(screen->renderer, 0, 90, 0, 0);
	rect.x = ((float)(screen->sizeX) / screen->taille_Ter_x)*i;
	rect.y = ((float)(screen->sizeY) / screen->taille_Ter_y)*j;
	SDL_RenderFillRect(screen->renderer, &rect);
      }else if (screen->Ter[i][j] > 1) {
	SDL_SetRenderDrawColor(screen->renderer, 0, 130, 0, 0);
	rect.x = ((float)(screen->sizeX) / screen->taille_Ter_x)*i;
	rect.y = ((float)(screen->sizeY) / screen->taille_Ter_y)*j;
	SDL_RenderFillRect(screen->renderer, &rect);
      }
    }
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
