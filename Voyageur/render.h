#ifndef RENDER_HEADER_
#define RENDER_HEADER_

#include "renderingUtil.h"


void mainRendering(ecran *screen);
void drawMenu(ecran *screen);
void drawParametre(ecran *screen);
void loadingScreen(ecran *screen);
void drawGraph(ecran *screen);

void enlargeButton(ecran *screen, int posMX, int posMY, int numIm, int xIm, int yIm, int wIm, int hIm, char c, int * large);
void rotateButton(ecran *screen, int posMX, int posMY, int numIm, int xIm, int yIm, int wIm, int hIm, char c, int * angle);
void drawFillCircle(SDL_Renderer * renderer, SDL_Point p, float radius);
float toRad(float deg);
void drawArc(SDL_Renderer * renderer, SDL_Point p, float radius, float startAngle, float endAngle);
void drawCircle(SDL_Renderer * renderer, SDL_Point p, float radius);

#endif /* RENDER_HEADER_ */
