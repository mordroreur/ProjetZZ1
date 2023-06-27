#ifndef RENDER_HEADER_
#define RENDER_HEADER_

#include "renderingUtil.h"


void mainRendering(ecran *screen);
void drawMenu(ecran *screen);
void loadingScreen(ecran *screen);
int isInButton(int x, int y, int sizeX, int sizeY, char center, int posMX, int posMY, ecran* screen);

#endif /* RENDER_HEADER_ */
