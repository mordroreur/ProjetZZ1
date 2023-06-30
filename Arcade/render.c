#include "render.h"
#include "renderingUtil.h"
#include <stdio.h>

void mainRendering(ecran *screen){
  switch(screen->etapeDuJeu){
  case 1: loadingScreen(screen);break;
  case 2: DrawMenu(screen);break;
  case 4: DrawGame(screen);break;
  case 5: DrawGame(screen);DrawVictoire(screen);break;
  case 8: DrawPreface(screen); break;
  default: loadingScreen(screen);break;
  }
}

void enlargeButton(ecran *screen, int posMX, int posMY, int numIm, int xIm, int yIm, int wIm, int hIm, char c, int * large)
{
  if (isInButton(xIm, yIm, wIm, hIm, c, posMX, posMY, screen))
  {
    if (*large < 5)
      (*large)++;
  }
  else
  {
    if (*large > 0)
      (*large)--;
  }
  DrawImage(numIm, xIm, yIm, wIm + *large, hIm + *large, c, 0, 0, 0, 0, 0, 0, screen);
}

void DrawPreface(ecran * screen)
{
  imagePreface(screen, screen->etapeMenu++);
  if (screen->etapeMenu == 112)
    screen->etapeDuJeu = 2;
}

void DrawVictoire(ecran *screen)
{
  int equipe = 0;
  for(int i = 0; i < screen->nbPlayer; i++){
    if(screen->pla[i].vie != 0){
      equipe = screen->pla[i].equipe;
    }
  }
  char tmp[30];
  sprintf(tmp, "victoire de l'equipe %d!!!", equipe);

  if (equipe == 0) {
    int order[1] = {19};
    DrawImage(1, 50, 50, 100, 100, 'c', 0, 1, 0, 0, 1, order, screen);
  }else {
    int order[1] = {19};
    DrawImage(2, 50, 50, 100, 100, 'c', 0, 1, 0, 0, 1, order, screen);
  }
    

  DrawString(tmp, 50, 50, 10, 'c', 120, 255, 120, screen);
}

void DrawGame(ecran *screen){
  if(screen->whichBack == 0){
    SDL_SetRenderDrawColor(screen->renderer, 255, 255, 255, 0);
    SDL_RenderFillRect(screen->renderer, NULL);
  }

  for(int i = 0; i < screen->nbPlayer; i++){
    DrawImage(0, screen->pla[i].pos.x, screen->pla[i].pos.y, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', 0, 0, 0, 0, 0, 0, screen);

    if(screen->pla[i].pos.x < 3){
      DrawImage(0, screen->pla[i].pos.x+100, screen->pla[i].pos.y, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', 0, 0, 0, 0, 0, 0, screen);
      if(screen->pla[i].pos.y < 3){
	DrawImage(0, screen->pla[i].pos.x+100, screen->pla[i].pos.y+100, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', 0, 0, 0, 0, 0, 0, screen);
      }else if (screen->pla[i].pos.y > 97) {
	DrawImage(0, screen->pla[i].pos.x+100, screen->pla[i].pos.y-100, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', 0, 0, 0, 0, 0, 0, screen);
      }
    }else if (screen->pla[i].pos.x > 97) {
      DrawImage(0, screen->pla[i].pos.x-100, screen->pla[i].pos.y, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', 0, 0, 0, 0, 0, 0, screen);
      if(screen->pla[i].pos.y < 3){
	DrawImage(0, screen->pla[i].pos.x-100, screen->pla[i].pos.y+100, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', 0, 0, 0, 0, 0, 0, screen);
      }else if (screen->pla[i].pos.y > 97) {
	DrawImage(0, screen->pla[i].pos.x-100, screen->pla[i].pos.y-100, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', 0, 0, 0, 0, 0, 0, screen);
      }
    }

    if(screen->pla[i].pos.y < 3){
      DrawImage(0, screen->pla[i].pos.x, screen->pla[i].pos.y+100, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', 0, 0, 0, 0, 0, 0, screen);
    }else if (screen->pla[i].pos.y > 97) {
      DrawImage(0, screen->pla[i].pos.x, screen->pla[i].pos.y-100, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', 0, 0, 0, 0, 0, 0, screen);
    }

    for(int j = screen->pla[i].debBoule; j < screen->pla[i].debBoule+screen->pla[i].nbBouleActive; j++){
      boule *b = &(screen->pla[i].boubou[j%screen->pla[i].nbBoule]);
      if(screen->pla[i].boubou[j].vie >= 0){
	DrawImage(0, screen->pla[i].boubou[j].pos.x, screen->pla[i].boubou[j].pos.y, screen->pla[i].boubou[j].pos.w, screen->pla[i].boubou[j].pos.h, 'c', 0, 0, 0, 0, 0, 0, screen);
	if(b->pos.x < 3){
	  DrawImage(0, b->pos.x+100, b->pos.y, b->pos.w, b->pos.h, 'c', 0, 0, 0, 0, 0, 0, screen);
	  if(b->pos.y < 3){
	    DrawImage(0, b->pos.x+100, b->pos.y+100, b->pos.w, b->pos.h, 'c', 0, 0, 0, 0, 0, 0, screen);
	  }else if (b->pos.y > 97) {
	    DrawImage(0, b->pos.x+100, b->pos.y-100, b->pos.w, b->pos.h, 'c', 0, 0, 0, 0, 0, 0, screen);
	  }
	}else if (b->pos.x > 97) {
	  DrawImage(0, b->pos.x-100, b->pos.y, b->pos.w, b->pos.h, 'c', 0, 0, 0, 0, 0, 0, screen);
	  if(b->pos.y < 3){
	    DrawImage(0, b->pos.x-100, b->pos.y+100, b->pos.w, b->pos.h, 'c', 0, 0, 0, 0, 0, 0, screen);
	  }else if (b->pos.y > 97) {
	    DrawImage(0, b->pos.x-100, b->pos.y-100, b->pos.w, b->pos.h, 'c', 0, 0, 0, 0, 0, 0, screen);
	  }
	}

	if(b->pos.y < 3){
	  DrawImage(0, b->pos.x, b->pos.y+100, b->pos.w, b->pos.h, 'c', 0, 0, 0, 0, 0, 0, screen);
	}else if (b->pos.y > 97) {
	  DrawImage(0, b->pos.x, b->pos.y-100, b->pos.w, b->pos.h, 'c', 0, 0, 0, 0, 0, 0, screen);
	}
      }
    }
  }

  
}

void DrawMenu(ecran *screen){
  static int large = 0;
  static int large2 = 0;
  int posMX, posMY;
  SDL_GetMouseState(&posMX, &posMY);
  int * plarge = &large;
  int * plarge2 = &large2;
  printf("test, %d\n", screen->etapeDuJeu);
  DrawImage(1, 50, 50, 100, 100, 'c', 0, 0, 0, 0, 0, 0, screen);
  enlargeButton(screen, posMX, posMY, 2,  80, 50, 30, 20, 'c', plarge);
  enlargeButton(screen, posMX, posMY, 3,  80, 80, 30, 20, 'c', plarge2);
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
