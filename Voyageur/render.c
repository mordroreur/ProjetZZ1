#include "render.h"
#include "liste.h"
#include <math.h>

#define VITTESSE 2

extern int debugging;

void mainRendering(ecran *screen){
  switch(screen->etapeDuJeu){
  case 1: loadingScreen(screen);break;
  case 2: drawMenu(screen); break;
  case 4: drawGraph(screen); break;
  case 5: drawGraph(screen); break;
  case 6: drawGraphSoluce(screen);break;
  case 666: drawParametre(screen); break;
  case 667: drawParametre(screen); break;
  case 668: drawParametre(screen); break;
  case 669: drawParametre(screen); break;
  default: loadingScreen(screen); break;
  }
}


void drawGraphSoluce(ecran *screen) {

  SDL_SetRenderDrawColor(screen->renderer, 0, 0, 0, 0);
  SDL_RenderFillRect(screen->renderer, NULL);
  SDL_Point p;
  char tmp[12];

  int * trouve = (int *)malloc(sizeof(int) * screen->niveau.nbSommets);
  if(trouve){
    float x, y;
    int lastCase = screen->niveau.startCase;
    int nbLasteCase = 0;
    int dejaDraw = 0;
    int NextCase = LL_get_n(screen->niveau.PlayerReso, LL_size(screen->niveau.PlayerReso) - nbLasteCase -1);

    for(int i = 0; i < screen->niveau.nbSommets; i++){
      trouve[i] = 0;
    }
    
    while (nbLasteCase < LL_size((screen->niveau.PlayerReso)) && dejaDraw + screen->niveau.arretes[lastCase][NextCase] < (screen->niveau.drawFinal)/VITTESSE) {
      nbLasteCase++;
      dejaDraw += screen->niveau.arretes[lastCase][NextCase];
      lastCase = NextCase;
      trouve[lastCase] = 1;
      NextCase = LL_get_n((screen->niveau.PlayerReso), LL_size((screen->niveau.PlayerReso)) - nbLasteCase -1);
    }
    
    if(nbLasteCase >= LL_size((screen->niveau.PlayerReso))){
      x = screen->niveau.Sommets[screen->niveau.startCase][0];
      y = screen->niveau.Sommets[screen->niveau.startCase][1];
    }else{
      x = (screen->niveau.Sommets[lastCase][0] - screen->niveau.Sommets[NextCase][0])* ((dejaDraw - (screen->niveau.drawFinal)/VITTESSE) / screen->niveau.arretes[lastCase][NextCase]) + screen->niveau.Sommets[lastCase][0];
      y = (screen->niveau.Sommets[lastCase][1] - screen->niveau.Sommets[NextCase][1])* ((dejaDraw - (screen->niveau.drawFinal)/VITTESSE) / screen->niveau.arretes[lastCase][NextCase]) + screen->niveau.Sommets[lastCase][1];
    }

    //printf("%d %d %f\n", dejaDraw, screen->niveau.drawFinal, screen->niveau.arretes[lastCase][NextCase]);
   
    for(int i = 0; i < screen->niveau.nbSommets; i++){
      for(int j = i; j < screen->niveau.nbSommets; j++){
	if(screen->niveau.arretes[i][j] > 0){
	    SDL_SetRenderDrawColor(screen->renderer, 255, 255, 255, 0);

	  SDL_RenderDrawLine(screen->renderer,
			     screen->sizeX * screen->niveau.Sommets[i][0]/100,
			     screen->sizeY * screen->niveau.Sommets[i][1]/100,
			     screen->sizeX * screen->niveau.Sommets[j][0]/100,
			     screen->sizeY * screen->niveau.Sommets[j][1]/100);
	}
      }
    }


    for(int i = 0; i < screen->niveau.nbSommets; i++){
      if(trouve[i]){
	SDL_SetRenderDrawColor(screen->renderer, 120, 255, 120, 0);
      }else{
	SDL_SetRenderDrawColor(screen->renderer, 190, 10, 10, 0);
      }
    
      p.x = screen->sizeX * screen->niveau.Sommets[i][0]/100;
      p.y = screen->sizeY * screen->niveau.Sommets[i][1]/100;
      drawFillCircle(screen->renderer, p, screen->sizeY/30.0);
	
    
      if(debugging){
	sprintf(tmp, "%d", i+1);
	DrawString(tmp, screen->niveau.Sommets[i][0], screen->niveau.Sommets[i][1], 4, 'c', 64, 64, 64, screen);
      }
    }

    DrawImage(0, x, y, 3, 3, 'c', 0, 0, 0, 0, 0, NULL, screen);

    screen->niveau.drawFinal++;
    free(trouve); 
  }
  
  
  

  

  /* DrawImage(0, screen->niveau.Sommets[screen->niveau.playerCase][0],
	    screen->niveau.Sommets[screen->niveau.playerCase][1], 3, 3,
	    'c', 0, 0, 0, 0, 0, NULL, screen);*/
  
}

void drawGraph(ecran *screen){
  int posMX, posMY;
  int nbT = SDL_GetTicks()/500;
    
  SDL_GetMouseState(&posMX, &posMY);
  
  SDL_SetRenderDrawColor(screen->renderer, 0, 0, 0, 0);
  SDL_RenderFillRect(screen->renderer, NULL);
  SDL_Point p;
  char tmp[12];
  
  
  for(int i = 0; i < screen->niveau.nbSommets; i++){
    for(int j = i; j < screen->niveau.nbSommets; j++){
      if(screen->niveau.arretes[i][j] > 0){
	if(i == screen->niveau.playerCase || j == screen->niveau.playerCase){
	  SDL_SetRenderDrawColor(screen->renderer, 130, 130, 255, 0);
	}else{
	  SDL_SetRenderDrawColor(screen->renderer, 255, 255, 255, 0);
	}

	SDL_RenderDrawLine(screen->renderer,
			   screen->sizeX * screen->niveau.Sommets[i][0]/100,
			   screen->sizeY * screen->niveau.Sommets[i][1]/100,
			   screen->sizeX * screen->niveau.Sommets[j][0]/100,
			   screen->sizeY * screen->niveau.Sommets[j][1]/100);
      }
    }
  }

  for(int i = 0; i < screen->niveau.nbSommets; i++){
    if(LL_contains(screen->niveau.PlayerReso, i)){
      SDL_SetRenderDrawColor(screen->renderer, 120, 255, 120, 0);
    }else{
      SDL_SetRenderDrawColor(screen->renderer, 190, 10, 10, 0);
    }
    
    p.x = screen->sizeX * screen->niveau.Sommets[i][0]/100;
    p.y = screen->sizeY * screen->niveau.Sommets[i][1]/100;
    if(i != screen->niveau.playerCase && screen->niveau.arretes[screen->niveau.playerCase][i] > 0 && sqrt(pow(posMX-p.x, 2) + pow(posMY-p.y, 2)) < screen->sizeY/25.0){
      if(nbT%2){
	drawFillCircle(screen->renderer, p, screen->sizeY/28.0);
      }else{
	drawFillCircle(screen->renderer, p, screen->sizeY/25.0);
      }
      
    }else{
      drawFillCircle(screen->renderer, p, screen->sizeY/30.0);
    }
    
    if(debugging){
      sprintf(tmp, "%d", i+1);
      DrawString(tmp, screen->niveau.Sommets[i][0], screen->niveau.Sommets[i][1], 4, 'c', 64, 64, 64, screen);
    }
  }

  DrawImage(0, screen->niveau.Sommets[screen->niveau.playerCase][0],
	    screen->niveau.Sommets[screen->niveau.playerCase][1], 3, 3,
	    'c', 0, 0, 0, 0, 0, NULL, screen);

  
}

void enlargeButton(ecran *screen, int posMX, int posMY, int numIm, int xIm, int yIm, int wIm, int hIm, char c)
{
  if (isInButton(xIm, yIm, wIm, hIm, c, posMX, posMY, screen))
  {
    DrawImage(numIm, xIm, yIm, wIm + 5, hIm + 5, c, 0, 0, 0, 0, 0, 0, screen);
  } else {
    DrawImage(numIm, xIm, yIm, wIm, hIm, c, 0, 0, 0, 0, 0, 0, screen);
  }
}

void rotateButton(ecran *screen, int posMX, int posMY, int numIm, int xIm, int yIm, int wIm, int hIm, char c, int * angle)
{
  if (isInButton(xIm, yIm, wIm, hIm, c, posMX, posMY, screen))
  {
    if (*angle < 180)
      (*angle) += 5;
  } else {
    if (*angle > 0)
      (*angle) -= 5;
  }
  DrawImage(numIm, xIm, yIm, wIm , hIm , c, 0, 0, 0, *angle, 0, 0, screen);
}

void drawParametre(ecran *screen)
{
  int nbreSommet = screen->niveau.nbSommets;
  float probabilite = screen->niveau.proba;
  char nbSom[30]; char proba[60]; char nbSom2[10]; char proba2[30];
  if (screen->etapeDuJeu == 666 || screen->etapeDuJeu == 667)
  {
    sprintf(nbSom, "Nombre de sommets: %d", nbreSommet);
    sprintf(proba, "Probabilite de liaison: %.5f", probabilite);
  }
  else
  {
    strcpy(nbSom, "Nombre de sommets:");
    strcpy(proba, "Probabilite de liaison:");
    sprintf(nbSom2, "%d", nbreSommet);
    sprintf(proba2, "%.5f", probabilite);
  }

  SDL_SetRenderDrawColor(screen->renderer, 50, 50, 50, 100);
  if (screen->etapeDuJeu == 666)
  {
    DrawString(nbSom, 50, 40, 5, 'c', 253, 212, 4, screen);
    DrawString(proba, 50, 60, 5, 'c', 255, 255, 255, screen);
  }
  else if (screen->etapeDuJeu == 667)
  {
    DrawString(nbSom, 50, 40, 5, 'c', 255, 255, 255, screen);
    DrawString(proba, 50, 60, 5, 'c', 253, 212, 4, screen);
  }
  else if (screen->etapeDuJeu == 668)
  {
    DrawString(nbSom, 50, 40, 5, 'c', 255, 255, 255, screen);
    DrawString(proba, 50, 60, 5, 'c', 255, 255, 255, screen);
    DrawString(nbSom2, 70, 40, 5, 'c', 253, 212, 4, screen);
    DrawString(proba2, 70, 60, 5, 'c', 255, 255, 255, screen);
  }
  else
  {
    DrawString(nbSom, 50, 40, 5, 'c', 255, 255, 255, screen);
    DrawString(proba, 50, 60, 5, 'c', 255, 255, 255, screen);
    DrawString(nbSom2, 70, 40, 5, 'c', 255, 255, 255, screen);
    DrawString(proba2, 70, 60, 5, 'c', 253, 212, 4, screen);
  }
}

void drawMenu(ecran *screen)
{
  
  int posMX, posMY;
  SDL_GetMouseState(&posMX, &posMY);
  static int angle = 0;
  int * pangle = &angle;
  
  DrawString("Voyageur", 50, 10, 25, 'c', 64, 64, 64, screen);
  DrawString("voyage, voyage...", 50, 27, 10, 'c', 64, 64, 64, screen);

  enlargeButton(screen, posMX, posMY, 0,  50, 50, 30, 20, 'c');
  enlargeButton(screen, posMX, posMY, 1,  50, 75, 30, 20, 'c');
  rotateButton(screen, posMX, posMY, 2,  10, 90, 7, 7, 'c', pangle);
}

void loadingScreen(ecran *screen){
  
  int nb3 = SDL_GetTicks()/10;
  int nb = (nb3) % 100 - 50;
  int nb2 = (nb3+35)% 98 - 49;
  nb3 = (nb3+65)% 96 - 48;

  
  SDL_SetRenderDrawColor(screen->renderer, 0, 0, 0, 0);
  SDL_RenderFillRect(screen->renderer, NULL);

  //DrawImage(0, 25, 25, 25, 25, 'n', 0, 0, 0, 0, screen);
  
  DrawString("Loading", 50, 50, 10, 'c', 255, 255, 255, screen);
  DrawString("                .", 50, 47.5 + abs(nb)/10.0, 10, 'c', 255, 255, 255, screen);
  DrawString("                  .", 50, 47.5 + abs(nb2)/10.0, 10, 'c', 255, 255, 255, screen);
  DrawString("                    .", 50, 47.5 + abs(nb3)/10.0, 10, 'c', 255, 255, 255, screen);

  //DrawImage(int imagenb, float x, float y, float sizeX, float sizeY, char center, int etatPremier, float TimebeforeNext, int flip, int angle, ecran *screen)
}






void drawFillCircle(SDL_Renderer * renderer, SDL_Point p, float radius){
  
  int stepPrecision = 2;
  for(int rx = 0; rx <= radius; rx+=stepPrecision){
      int height = ((float)(radius))*sqrt(1-(1-rx/(float)radius)*(1-rx/(float)radius));
      SDL_FRect Prem = {p.x-radius+rx, p.y-height, stepPrecision, 2*height};
      SDL_FRect Deux = {p.x+radius-rx, p.y-height, stepPrecision, 2*height};
      SDL_RenderFillRectF(renderer, &Prem);
      SDL_RenderFillRectF(renderer, &Deux);
    }
}

float toRad(float deg){
  return deg * (M_PI / 180);
}

void drawArc(SDL_Renderer * renderer, SDL_Point p, float radius, float startAngle, float endAngle){
  
  int precision = (int)sqrtf((radius*radius)/10)+4;
  if(precision > 0){
    #define PEN_DRAW_CIRCLE_MAX_PRECISION 500
    if(precision > PEN_DRAW_CIRCLE_MAX_PRECISION){
      precision = PEN_DRAW_CIRCLE_MAX_PRECISION;
    }
    int old_x = cosf(toRad(startAngle))*radius;
    int old_y = sinf(toRad(startAngle))*radius;
    float a = toRad(startAngle);
    
    while(a < toRad(endAngle)){
      if(a+toRad(360.0f/precision) < toRad(endAngle)){
    a += toRad(360.0f/precision);
      }else{
    a = toRad(endAngle);
      }
      
      int new_x = cosf(a)*radius;
      int new_y = sinf(a)*radius;
      SDL_RenderDrawLine(renderer, p.x+old_x, p.y+old_y, p.x+new_x, p.y+new_y);
      old_x = new_x;
      old_y = new_y;
    }
  }
}

void drawCircle(SDL_Renderer * renderer, SDL_Point p, float radius){
  drawArc(renderer, p, radius, 0, 360);
}
