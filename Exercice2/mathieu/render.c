#include "render.h"
#include "renderingUtil.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

void mainRendering(ecran *screen){
  switch(screen->etapeDuJeu){
  case 1: loadingScreen(screen);break;
  case 2: DrawTer(screen);break;
  case 3: DrawTer(screen);break;
  case 15: DrawVictoryMenu(screen); break;
  case 16: DrawLooseMenu(screen); break;
  case 8: DrawMenu(screen); break;
  case 69: DrawAllocErreur(screen);break;
  default: loadingScreen(screen);break;
  }
}


void DrawLooseMenu(ecran *screen){
  DrawMenu(screen);
  DrawString("PERDU ", 50, 50, 15, 'c', 255, 20, 20, screen);
  char tmp[40];
  sprintf(tmp, "score : %d", screen->tailleSerp);
  DrawString(tmp, 50, 90, 8, 'c', 160, 255, 160, screen);
}

void DrawVictoryMenu(ecran *screen){
  DrawMenu(screen);
  DrawString("VICTOIRE", 50, 50, 15, 'c', 160, 255, 160, screen);
  char tmp[40];
  sprintf(tmp, "en %d coups", screen->time);
  DrawString(tmp, 50, 90, 8, 'c', 160, 255, 160, screen);
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
      }else if (screen->Ter[i][j] > 255 && screen->Ter[i][j] < 511) {

	if((screen->Ter[i][j] & 16) && (screen->serpDir == 1)){
	  DrawImage(0, (i+0.5)*100.0 / screen->taille_Ter_x, (j+0.5)*100.0 / screen->taille_Ter_y, 100.0 / screen->taille_Ter_x * screen->sizeY/screen->sizeX, 100.0 / screen->taille_Ter_y * screen->sizeX/screen->sizeY, 'c', 0, 0.1, 0, -90, screen);
	}else if((screen->Ter[i][j] & 32) && (screen->serpDir == 2)){
	  DrawImage(0, i*100.0 / screen->taille_Ter_x, j*100.0 / screen->taille_Ter_y, 100.0 / screen->taille_Ter_x, 100.0 / screen->taille_Ter_y, 'n', 0, 0.1, 0, 0, screen);
	}else if((screen->Ter[i][j] & 64) && (screen->serpDir == 3)){
	  DrawImage(0, (i+0.5)*100.0 / screen->taille_Ter_x, (j+0.5)*100.0 / screen->taille_Ter_y, 100.0 / screen->taille_Ter_x * screen->sizeY/screen->sizeX, 100.0 / screen->taille_Ter_y * screen->sizeX/screen->sizeY, 'c', 0, 0.1, 2, -90, screen);
	}else if((screen->Ter[i][j] & 128) && (screen->serpDir == 4)){
	  	  DrawImage(0, i*100.0 / screen->taille_Ter_x, j*100.0 / screen->taille_Ter_y, 100.0 / screen->taille_Ter_x, 100.0 / screen->taille_Ter_y, 'n', 0, 0.1, 0, 180, screen);
	}else{
	  DrawImage(0, i*100.0 / screen->taille_Ter_x, j*100.0 / screen->taille_Ter_y, 100.0 / screen->taille_Ter_x, 100.0 / screen->taille_Ter_y, 'n', 0, 0.1, 0, 0, screen);
	}
	
	


	
      }else if (screen->Ter[i][j] > 256) {
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
