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
  sprintf(tmp, "victoire de l'equipe %s!!!", (equipe == 0)?"rouge":"bleu");

  if (equipe == 0) {
    int order[1] = {19};
    DrawImage(0, 50, 40, 100, 100, 'c', 0, 1, 0, 0, 1, order, screen);
  }else {
    int order[1] = {19};
    DrawImage(1, 50, 40, 100, 100, 'c', 0, 1, 0, 0, 1, order, screen);
  }
    

  DrawString(tmp, 50, 90, 10, 'c', 120, 255, 120, screen);
  
  
}

void DrawGame(ecran *screen){
  if(screen->whichBack == 0){
    SDL_SetRenderDrawColor(screen->renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(screen->renderer, NULL);
  }else{
    DrawImage(screen->whichBack, 50, 50, 100, 100, 'c', 0, 0, 0, 0, 0, NULL, screen);
  }

  for(int i = 0; i < screen->nbPlayer; i++){
   
    int angle = 0;
    int flip = 0;
    int nbSprite = 12;

    int orderNormal[12] = {0, 1, 2, 3, 4, 4, 4, 3, 2, 1, 0, 0};
    int orderTire[12] = {4, 6, 7, 8, 9, 10, 12, 14, 16, 18, 20, 10};
    int *order = orderNormal;
    if(screen->pla[i].shoot != 0){
      order = orderTire;
    }
    

    
    if(screen->pla[i].dirX == -1 && screen->pla[i].dirY == -1){angle = 45; flip = 1;}
    else if(screen->pla[i].dirX == -1 && screen->pla[i].dirY == 0){flip = 1;}
    else if(screen->pla[i].dirX == -1 && screen->pla[i].dirY == 1){angle = -45;flip = 1;}
    else if(screen->pla[i].dirX == 0 && screen->pla[i].dirY == -1){angle = 90; flip = 1;}
    else if(screen->pla[i].dirX == 0 && screen->pla[i].dirY == 1){angle = -90; flip = 1;}
    else if(screen->pla[i].dirX == 1 && screen->pla[i].dirY == -1){angle = -45;}
    else if(screen->pla[i].dirX == 1 && screen->pla[i].dirY == 1){angle = 45;}

    //printf("dirX %d\n", angle);

    DrawImage(i, screen->pla[i].pos.x, screen->pla[i].pos.y, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', screen->pla[i].shoot/3, (screen->pla[i].shoot == 0)?0.1:0, flip, angle, nbSprite, order, screen);
    
    if(screen->pla[i].pos.x < 3){
      DrawImage(i, screen->pla[i].pos.x+100, screen->pla[i].pos.y, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', screen->pla[i].shoot/3, (screen->pla[i].shoot == 0)?0.1:0, flip, angle, nbSprite, order, screen);
      if(screen->pla[i].pos.y < 3){
	DrawImage(i, screen->pla[i].pos.x+100, screen->pla[i].pos.y+100, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', screen->pla[i].shoot/3, (screen->pla[i].shoot == 0)?0.1:0, flip, angle, nbSprite, order, screen);
      }else if (screen->pla[i].pos.y > 97) {
	DrawImage(i, screen->pla[i].pos.x+100, screen->pla[i].pos.y-100, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', screen->pla[i].shoot/3, (screen->pla[i].shoot == 0)?0.1:0, flip, angle,nbSprite, order, screen);
      }
    }else if (screen->pla[i].pos.x > 97) {
      DrawImage(i, screen->pla[i].pos.x-100, screen->pla[i].pos.y, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', screen->pla[i].shoot/3, (screen->pla[i].shoot == 0)?0.1:0, flip, angle, nbSprite, order, screen);
      if(screen->pla[i].pos.y < 3){
	DrawImage(i, screen->pla[i].pos.x-100, screen->pla[i].pos.y+100, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', screen->pla[i].shoot/3, (screen->pla[i].shoot == 0)?0.1:0, flip, angle, nbSprite, order, screen);
      }else if (screen->pla[i].pos.y > 97) {
	DrawImage(i, screen->pla[i].pos.x-100, screen->pla[i].pos.y-100, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', screen->pla[i].shoot/3, (screen->pla[i].shoot == 0)?0.1:0, flip, angle, nbSprite, order, screen);
      }
    }

    if(screen->pla[i].pos.y < 3){
      DrawImage(i, screen->pla[i].pos.x, screen->pla[i].pos.y+100, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', screen->pla[i].shoot/3, (screen->pla[i].shoot == 0)?0.1:0, flip, angle, nbSprite, order, screen);
    }else if (screen->pla[i].pos.y > 97) {
      DrawImage(i, screen->pla[i].pos.x, screen->pla[i].pos.y-100, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', screen->pla[i].shoot/3, (screen->pla[i].shoot == 0)?0.1:0, flip, angle, nbSprite, order, screen);
    }

    for(int j = screen->pla[i].debBoule; j < screen->pla[i].debBoule+screen->pla[i].nbBouleActive; j++){
      boule *b = &(screen->pla[i].boubou[j%screen->pla[i].nbBoule]);
      int orderBal[5] = {0, 1, 2, 3, 4};
      int nbImBoule = 5;
      angle = 0;
      flip = 0;
      
      if(b->vitX == 1 && b->vitY == 1){angle = 45; flip = 1;}
      else if(b->vitX == 1 && b->vitY == 0){flip = 1;}
      else if(b->vitX == 1 && b->vitY == -1){angle = -45;flip = 1;}
      else if(b->vitX == 0 && b->vitY == 1){angle = 90; flip = 1;}
      else if(b->vitX == 0 && b->vitY == -1){angle = -90; flip = 1;}
      else if(b->vitX == -1 && b->vitY == 1){angle = -45;}
      else if(b->vitX == -1 && b->vitY == -1){angle = 45;}
      
      if(screen->pla[i].boubou[j].vie >= 0){
	DrawImage(2+i, screen->pla[i].boubou[j].pos.x, screen->pla[i].boubou[j].pos.y, screen->pla[i].boubou[j].pos.w, screen->pla[i].boubou[j].pos.h, 'c', 0, 0.1 ,flip, angle, nbImBoule, orderBal, screen);
	if(b->pos.x < 3){
	  DrawImage(2+i, b->pos.x+100, b->pos.y, b->pos.w, b->pos.h, 'c', 0, 0.1 ,flip, angle, nbImBoule, orderBal, screen);
	  if(b->pos.y < 3){
	    DrawImage(2+i, b->pos.x+100, b->pos.y+100, b->pos.w, b->pos.h, 'c', 0, 0.1 ,flip, angle, nbImBoule, orderBal, screen);
	  }else if (b->pos.y > 97) {
	    DrawImage(2+i, b->pos.x+100, b->pos.y-100, b->pos.w, b->pos.h, 'c', 0, 0.1 ,flip, angle, nbImBoule, orderBal, screen);
	  }
	}else if (b->pos.x > 97) {
	  DrawImage(2+i, b->pos.x-100, b->pos.y, b->pos.w, b->pos.h, 'c', 0, 0.1 ,flip, angle, nbImBoule, orderBal, screen);
	  if(b->pos.y < 3){
	    DrawImage(2+i, b->pos.x-100, b->pos.y+100, b->pos.w, b->pos.h, 'c', 0, 0.1 ,flip, angle, nbImBoule, orderBal, screen);
	  }else if (b->pos.y > 97) {
	    DrawImage(2+i, b->pos.x-100, b->pos.y-100, b->pos.w, b->pos.h, 'c', 0, 0.1 ,flip, angle, nbImBoule, orderBal,  screen);
	  }
	}

	if(b->pos.y < 3){
	  DrawImage(0, b->pos.x, b->pos.y+100, b->pos.w, b->pos.h, 'c', 0, 0.1 ,flip, angle, nbImBoule, orderBal, screen);
	}else if (b->pos.y > 97) {
	  DrawImage(0, b->pos.x, b->pos.y-100, b->pos.w, b->pos.h, 'c', 0, 0.1 ,flip, angle, nbImBoule, orderBal, screen);
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
  DrawImage(10, 50, 50, 100, 100, 'c', 0, 0, 0, 0, 0, 0, screen);
  enlargeButton(screen, posMX, posMY, 11,  80, 50, 30, 20, 'c', plarge);
  enlargeButton(screen, posMX, posMY, 12,  80, 80, 30, 20, 'c', plarge2);
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
