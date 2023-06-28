#include "render.h"

void mainRendering(ecran *screen){
  switch(screen->etapeDuJeu){
  case 1: loadingScreen(screen);break;
  case 2: drawMenu(screen); break;
  case 4: drawGraph(screen); break;
  case 5: drawGraph(screen); break;
  case 666: drawParametre(screen); break;
  default: loadingScreen(screen); break;
  }
}


void drawGraph(ecran *screen){

  SDL_SetRenderDrawColor(screen->renderer, 0, 0, 0, 0);
  SDL_RenderFillRect(screen->renderer, NULL);
  SDL_Point p;
  char tmp[12];
  

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
    SDL_SetRenderDrawColor(screen->renderer, 255, 255, 255, 0);
    p.x = screen->sizeX * screen->niveau.Sommets[i][0]/100;
    p.y = screen->sizeY * screen->niveau.Sommets[i][1]/100;
    drawFillCircle(screen->renderer, p, screen->sizeY/20);
    sprintf(tmp, "%d", i+1);
    DrawString(tmp, screen->niveau.Sommets[i][0], screen->niveau.Sommets[i][1], 2, 'c', 64, 64, 64, screen);
  }
  
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
  char nbSom[20];
  sprintf(nbSom, "%d", nbSom);
  SDL_SetRenderDrawColor(screen->renderer, 50, 50, 50, 100);
  DrawString("Nombre de sommets: ", 50, 10, 5, 'c', 255, 255, 255, screen);
  
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

  
  SDL_SetRenderDrawColor(screen->renderer, 255, 255, 255, 0);
  SDL_RenderFillRect(screen->renderer, NULL);

  //DrawImage(0, 25, 25, 25, 25, 'n', 0, 0, 0, 0, screen);
  
  DrawString("Loading", 50, 50, 10, 'c', 0, 0, 0, screen);
  DrawString("                .", 50, 47.5 + abs(nb)/10.0, 10, 'c', 0, 0, 0, screen);
  DrawString("                  .", 50, 47.5 + abs(nb2)/10.0, 10, 'c', 0, 0, 0, screen);
  DrawString("                    .", 50, 47.5 + abs(nb3)/10.0, 10, 'c', 0, 0, 0, screen);

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
