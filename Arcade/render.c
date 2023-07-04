#include "render.h"
#include "renderingUtil.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>


void mainRendering(ecran *screen){
  switch(screen->etapeDuJeu){
  case 1: loadingScreen(screen);break;
  case 2: DrawMenu(screen);break;
  case 4: DrawGame(screen);break;
  case 5: DrawGame(screen);DrawVictoire(screen);break;
  case 8: DrawPreface(screen); break;
  case 9: DrawPreface2(screen); break;
  case 10: DrawParametre(screen); break;
  case 11: BackParametre(screen); break;
  default: loadingScreen(screen);break;
  }
}

void enlargeButton(ecran *screen, int posMX, int posMY, int numIm, int * xIm, int * yIm, int wIm, int hIm, char c, int * large)
{
  if (*yIm < 18)
    (*yIm) += 2;

  if (*xIm > 80)
    (*xIm) -= 2;

  if (isInButton(*xIm, *yIm, wIm, hIm, c, posMX, posMY, screen))
  {
    if (*large < 5)
      (*large)++;
  }
  else
  {
    if (*large > 0)
      (*large)--;
  }
  DrawImage(numIm, *xIm, *yIm, wIm + *large, hIm + *large, c, 0, 0, 0, 0, 0, 0, screen);
}

void DrawPreface(ecran * screen)
{
  imagePreface(screen, screen->etapeMenu++);
  if (screen->etapeMenu >= 112)
  {
    screen->etapeDuJeu = 2;
    Mix_PlayMusic(screen->musique[0], -1);
  }
  SDL_Delay(20);
}

void DrawMenu(ecran *screen)
{
  static int large = 0;  int * plarge = &large;
  static int large2 = 0; int * plarge2 = &large2;
  static int large3 = 0; int * plarge3 = &large3;
  int posY1 = 50; int posY2 = 80; int posX3 = 18;
  int posMX, posMY;
  SDL_GetMouseState(&posMX, &posMY);
 
  imagePreface(screen, screen->etapeMenu++);
  SDL_Delay(20);
  if (screen->etapeMenu >= 193)
    screen->etapeMenu = 113;
  //DrawImage(10, 50, 50, 100, 100, 'c', 0, 0, 0, 0, 0, 0, screen);
  enlargeButton(screen, posMX, posMY, 10,  &(screen->decalageB1), &posY1, 30, 20, 'c', plarge);
  enlargeButton(screen, posMX, posMY, 11,  &(screen->decalageB2), &posY2, 30, 20, 'c', plarge2);
  enlargeButton(screen, posMX, posMY, 12, &posX3, &(screen->decalageB3), 30, 20, 'c', plarge3);
}

void DrawParametre(ecran *screen)
{
  int posMX, posMY;
  char volume[30]; char bonus[30] = ""; char trouNoir[30] = "";
  if (screen->bonus == 0) 
    strcpy(bonus, "Bonus: OFF");
  else 
    strcpy(bonus, "Bonus: ON");
  if (screen->trousNoir == 0)
    strcpy(trouNoir, "Trous Noirs: OFF");
  else
    strcpy(trouNoir, "Trous Noirs: ON");
  
  sprintf(volume, "volume: %d", Mix_VolumeMusic(-1));
  SDL_GetMouseState(&posMX, &posMY);
  imagePreface(screen, screen->etapeMenu++);
  SDL_Delay(20);
  if (screen->etapeMenu >= 193) {screen->etapeMenu = 113;}
  if (screen->decalageB1 < 116) {screen->decalageB1 += 2;}
  if (screen->decalageB2 < 130) {screen->decalageB2 += 2;}
  if (screen->decalageB3 > -30) {screen->decalageB3 -= 2;}
  if (screen->decalageB4 > 50) {screen->decalageB4 -= 2;}
  DrawImage(10, screen->decalageB1, 50, 30, 20, 'c', 0, 0, 0, 0, 0, 0, screen);
  DrawImage(11, screen->decalageB2, 80, 30, 20, 'c', 0, 0, 0, 0, 0, 0, screen);
  DrawImage(12, 18, screen->decalageB3, 30, 20, 'c', 0, 0, 0, 0, 0, 0, screen);
  DrawImage(13, 50, screen->decalageB4, 50, 60, 'c', 0, 0, 0, 0, 0, 0, screen);
  if (screen->etapeParam == 0)
  {
    DrawString(volume, 50, screen->decalageB4-10 , 5, 'c', 253, 212, 4, screen);
    DrawString(bonus, 50, screen->decalageB4, 5, 'c', 255, 255, 255, screen);
    DrawString(trouNoir, 50, screen->decalageB4+10, 5, 'c', 255, 255, 255, screen);
  }
  else if (screen->etapeParam == 1)
  {
    DrawString(volume, 50, screen->decalageB4-10 , 5, 'c', 255, 255, 255, screen);
    DrawString(bonus, 50, screen->decalageB4, 5, 'c', 253, 212, 4, screen);
    DrawString(trouNoir, 50, screen->decalageB4+10, 5, 'c', 255, 255, 255, screen);
  }
  else if (screen->etapeParam == 2)
  {
    DrawString(volume, 50, screen->decalageB4-10 , 5, 'c', 255, 255, 255, screen);
    DrawString(bonus, 50, screen->decalageB4, 5, 'c', 255, 255, 255, screen);
    DrawString(trouNoir, 50, screen->decalageB4+10, 5, 'c', 253, 212, 4, screen);
  }
}

void BackParametre(ecran *screen)
{
  int posMX, posMY;
  char volume[30]; char bonus[30] = ""; char trouNoir[30] = "";
  if (screen->bonus == 0) 
    strcpy(bonus, "Bonus: OFF");
  else 
    strcpy(bonus, "Bonus: ON");
  if (screen->trousNoir == 0)
    strcpy(trouNoir, "Trous Noirs: OFF");
  else
    strcpy(trouNoir, "Trous Noirs: ON");
  
  sprintf(volume, "volume: %d", Mix_VolumeMusic(-1));
  SDL_GetMouseState(&posMX, &posMY);
  imagePreface(screen, screen->etapeMenu++);
  SDL_Delay(20);
  if (screen->etapeMenu >= 193) {screen->etapeMenu = 113;}
  if (screen->decalageB1 > 80) {screen->decalageB1 -= 2;}  
  if (screen->decalageB2 > 80) {screen->decalageB2 -= 2;}
  if (screen->decalageB3 < 18) {screen->decalageB3 += 2;}
  if (screen->decalageB4 < 150) {screen->decalageB4 += 2;}
  DrawImage(10, screen->decalageB1, 50, 30, 20, 'c', 0, 0, 0, 0, 0, 0, screen);
  DrawImage(11, screen->decalageB2, 80, 30, 20, 'c', 0, 0, 0, 0, 0, 0, screen);
  DrawImage(12, 18, screen->decalageB3, 30, 20, 'c', 0, 0, 0, 0, 0, 0, screen);
  DrawImage(13, 50, screen->decalageB4, 50, 60, 'c', 0, 0, 0, 0, 0, 0, screen);
  if (screen->etapeParam == 0)
  {
    DrawString(volume, 50, screen->decalageB4-10 , 5, 'c', 253, 212, 4, screen);
    DrawString(bonus, 50, screen->decalageB4, 5, 'c', 255, 255, 255, screen);
    DrawString(trouNoir, 50, screen->decalageB4+10, 5, 'c', 255, 255, 255, screen);
  }
  else if (screen->etapeParam == 1)
  {
    DrawString(volume, 50, screen->decalageB4-10 , 5, 'c', 255, 255, 255, screen);
    DrawString(bonus, 50, screen->decalageB4, 5, 'c', 253, 212, 4, screen);
    DrawString(trouNoir, 50, screen->decalageB4+10, 5, 'c', 255, 255, 255, screen);
  }
  else if (screen->etapeParam == 2)
  {
    DrawString(volume, 50, screen->decalageB4-10 , 5, 'c', 255, 255, 255, screen);
    DrawString(bonus, 50, screen->decalageB4, 5, 'c', 255, 255, 255, screen);
    DrawString(trouNoir, 50, screen->decalageB4+10, 5, 'c', 253, 212, 4, screen);
  }
  if (screen->decalageB1 == 80 && screen->decalageB2 == 80 && screen->decalageB3 == 18 && screen->decalageB4 == 150)
    screen->etapeDuJeu = 2;
}

void DrawPreface2(ecran * screen)
{
  imagePreface(screen, screen->etapeMenu++);
  if (screen->etapeMenu >= 261)
  {
    screen->etapeDuJeu = 3;
    Mix_PlayMusic(screen->musique[1], -1);
    screen->etapeMenu = 0;
  }
  SDL_Delay(10);
}

// void DrawParametre(ecran * screen)
// {

// }

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
    DrawImage(0, 50, 60, 60, 30, 'c', 0, 1, 0, 0, 1, order, screen);
  }else {
    int order[1] = {19};
    DrawImage(1, 50, 60, 60, 30, 'c', 0, 1, 0, 0, 1, order, screen);
  }
    

  DrawString(tmp, 50, 90, 10, 'c', 120, 255, 120, screen); 


}

void DrawGame(ecran *screen){
  
  DrawImage(screen->whichBack, 50, 50, 100, 100, 'c', 0, 0, 0, 0, 0, NULL, screen);

  int angle = 0;
  int flip = 0;
  int nbSprite = 12;

  int orderNormal[12] = {0, 1, 2, 3, 4, 4, 4, 3, 2, 1, 0, 0};
  int orderTire[12] = {4, 6, 7, 8, 9, 10, 12, 14, 16, 18, 20, 10};
  int *order = orderNormal;
  float decalX = 0;
  float decalY = 0;

  for(int i = 0; i < screen->nbObjetsMax; i++){
    if(screen->tbObjet[i].vie != 0){
      if(screen->tbObjet[i].id == 4){
	SDL_SetRenderDrawColor(screen->renderer, 255, 255, 0, 0);
      }else if(screen->tbObjet[i].id == 1){
	SDL_SetRenderDrawColor(screen->renderer, 40, 40, 40, 0);
      }
      SDL_Rect rect;
      rect.x = screen->tbObjet[i].pos.x * (screen->sizeX)/100.0;
      rect.y = screen->tbObjet[i].pos.y * (screen->sizeY)/100.0;
      rect.w = screen->tbObjet[i].pos.w * (screen->sizeX)/100.0;
      rect.h = screen->tbObjet[i].pos.h * (screen->sizeY)/100.0;

      SDL_RenderFillRect(screen->renderer, &rect);
    }
  }
  
  
  for(int i = 0; i < screen->nbPlayer; i++){
    if(screen->pla[i].vie != 0){

      angle = 0;
      flip = 0;
      order = orderNormal;
      decalX = 0;
      decalY = 0;
      
      if(screen->pla[i].shoot != 0){
	order = orderTire;
      }


      
      if(screen->pla[i].dirX == -1 && screen->pla[i].dirY == -1){angle = 45; flip = 1; decalX = -screen->pla[i].pos.w *0.2;}
      else if(screen->pla[i].dirX == -1 && screen->pla[i].dirY == 0){flip = 1;decalX = -screen->pla[i].pos.w *0.2; decalY = screen->pla[i].pos.h *0.3;}
      else if(screen->pla[i].dirX == -1 && screen->pla[i].dirY == 1){angle = -45;flip = 1;decalY = screen->pla[i].pos.h *0.8; decalX = -screen->pla[i].pos.w *0.2;}
      else if(screen->pla[i].dirX == 0 && screen->pla[i].dirY == -1){angle = 90; flip = 1;}
      else if(screen->pla[i].dirX == 0 && screen->pla[i].dirY == 1){angle = -90; flip = 1;decalY = screen->pla[i].pos.h *0.8;}
      else if(screen->pla[i].dirX == 1 && screen->pla[i].dirY == -1){angle = -45;}
      else if(screen->pla[i].dirX == 1 && screen->pla[i].dirY == 0){decalX = screen->pla[i].pos.w *0.2; decalY = screen->pla[i].pos.h *0.3;}
      else if(screen->pla[i].dirX == 1 && screen->pla[i].dirY == 1){angle = 45;decalY = screen->pla[i].pos.h *0.7; decalX = screen->pla[i].pos.w *0.2;}

      float drawX = screen->pla[i].pos.x + decalX;
      float drawY = screen->pla[i].pos.y + decalY;
      
      

      DrawImage(screen->pla[i].equipe, drawX, drawY, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', screen->pla[i].shoot/3, (screen->pla[i].shoot == 0)?0.1:0, flip, angle, nbSprite, order, screen);
      
      
      if(screen->pla[i].pos.x < 3){
	DrawImage(screen->pla[i].equipe, drawX+100, drawY, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', screen->pla[i].shoot/3, (screen->pla[i].shoot == 0)?0.1:0, flip, angle, nbSprite, order, screen);
	if(screen->pla[i].pos.y < 3){
	  DrawImage(screen->pla[i].equipe, drawX+100, drawY+100, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', screen->pla[i].shoot/3, (screen->pla[i].shoot == 0)?0.1:0, flip, angle, nbSprite, order, screen);
	}else if (screen->pla[i].pos.y > 97) {
	  DrawImage(screen->pla[i].equipe, drawX+100, drawY-100, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', screen->pla[i].shoot/3, (screen->pla[i].shoot == 0)?0.1:0, flip, angle,nbSprite, order, screen);
	}
      }else if (screen->pla[i].pos.x > 97) {
	DrawImage(screen->pla[i].equipe, drawX-100, drawY, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', screen->pla[i].shoot/3, (screen->pla[i].shoot == 0)?0.1:0, flip, angle, nbSprite, order, screen);
	if(screen->pla[i].pos.y < 3){
	  DrawImage(screen->pla[i].equipe, drawX-100, drawY+100, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', screen->pla[i].shoot/3, (screen->pla[i].shoot == 0)?0.1:0, flip, angle, nbSprite, order, screen);
	}else if (screen->pla[i].pos.y > 97) {
	  DrawImage(screen->pla[i].equipe, drawX-100, drawY-100, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', screen->pla[i].shoot/3, (screen->pla[i].shoot == 0)?0.1:0, flip, angle, nbSprite, order, screen);
	}
      }

      if(screen->pla[i].pos.y < 3){
	DrawImage(screen->pla[i].equipe, drawX, drawY+100, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', screen->pla[i].shoot/3, (screen->pla[i].shoot == 0)?0.1:0, flip, angle, nbSprite, order, screen);
      }else if (screen->pla[i].pos.y > 97) {
	DrawImage(screen->pla[i].equipe, drawX, drawY-100, screen->pla[i].pos.w, screen->pla[i].pos.h, 'c', screen->pla[i].shoot/3, (screen->pla[i].shoot == 0)?0.1:0, flip, angle, nbSprite, order, screen);
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

  //DrawImage(int imagenb, float x, float y, float sizeX, float sizeY, char
  //center, int etatPremier, float TimebeforeNext, int flip, int angle, ecran
  //*screen)
  }

  void loadingScreenWithBarre(ecran *screen, int max, int actu){
  
  int nb3 = SDL_GetTicks()/10;
  int nb = (nb3) % 100 - 50;
  int nb2 = (nb3+35)% 98 - 49;
  nb3 = (nb3+65)% 96 - 48;

  SDL_SetRenderDrawColor(screen->renderer, 255, 255, 255, 0);
  SDL_RenderFillRect(screen->renderer, NULL);

  //DrawImage(0, 25, 25, 25, 25, 'n', 0, 0, 0, 0, screen);
  
  DrawString("Loading", 50, 32, 10, 'c', 0, 0, 0, screen);
  DrawString("                .", 50, 29.5 + abs(nb)/10.0, 10, 'c', 0, 0, 0, screen);
  DrawString("                  .", 50, 29.5 + abs(nb2)/10.0, 10, 'c', 0, 0, 0, screen);
  DrawString("                    .", 50, 29.5 + abs(nb3)/10.0, 10, 'c', 0, 0, 0, screen);


  SDL_Rect rect;
  rect.x = screen->sizeX/10;
  rect.y = screen->sizeY/8 *5;
  rect.h = screen->sizeY/10;
  if(max != actu){
    rect.w = screen->sizeX/10.0*(actu*8.0/max);
  }else{
    rect.w = screen->sizeX/10*8;
  }
  
  
  SDL_SetRenderDrawColor(screen->renderer, 100, 255, 100, 0);
  SDL_RenderFillRect(screen->renderer, &rect);


  rect.w = screen->sizeX/10*8;
  SDL_SetRenderDrawColor(screen->renderer, 0, 0, 0, 0);
  SDL_RenderDrawRect(screen->renderer, &rect);

  char tmp[10];
  sprintf(tmp, "%d%%", (int)((float)(actu)/max*100));
  DrawString(tmp, 50, 85, 10, 'c', 0, 0, 0, screen);

}
