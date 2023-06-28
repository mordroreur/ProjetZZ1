#include "render.h"

void mainRendering(ecran *screen){
  switch(screen->etapeDuJeu){
  case 1: loadingScreen(screen);break;
  case 2: drawMenu(screen); break;
  case 4: drawGraph(screen); break;
  case 5: drawGraph(screen); break;
  default: loadingScreen(screen);break;
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

void drawMenu(ecran *screen)
{
  
int posMX, posMY;
SDL_GetMouseState(&posMX, &posMY);
  
  DrawString("Voyageur", 50, 10, 25, 'c', 64, 64, 64, screen);
  DrawString("voyage, voyage...", 50, 27, 10, 'c', 64, 64, 64, screen);
  DrawImage(1, 50, 75, 30, 20, 'c', 0, 0, 0, 0, 0, 0, screen);
  DrawImage(2, 10, 90, 7, 7, 'c', 0, 0, 0, 0, 0, 0, screen);

  if (isInButton(50, 50, 30, 20, 'c', posMX, posMY, screen))
  {
    DrawImage(0, 50, 50, 35, 25, 'c', 0, 0, 0, 0, 0, 0, screen);
  } else {
    DrawImage(0, 50, 50, 30, 20, 'c', 0, 0, 0, 0, 0, 0, screen);
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
