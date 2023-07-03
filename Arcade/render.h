#ifndef RENDER_HEADER_
#define RENDER_HEADER_

#include "renderingUtil.h"


void mainRendering(ecran *screen);
void loadingScreen(ecran *screen);
void DrawPreface(ecran * screen);
void DrawPreface2(ecran * screen);
void DrawMenu(ecran *screen);
void DrawGame(ecran *screen);
void DrawParametre(ecran *screen);
void DrawVictoire(ecran *screen);
void loadingScreenWithBarre(ecran *screen, int max, int actu);


#endif /* RENDER_HEADER_ */
