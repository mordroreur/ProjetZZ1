#ifndef RENDERING_BASE_HEADER_
#define RENDERING_BASE_HEADER_

#include "renderingUtil.h"
#include "render.h"
#include "ticksGest.h"
#include "eventGest.h"
#include <pthread.h>

ecran createScreen(int sizex, int sizey, int fullscreen);
void end_sdl(int ok, char const *msg, ecran screen);
void startMainBoucle(ecran *screen);
void *BouclePrincipaleDesTicks(void *unEcran);

void writeParamFile(int sizex, int sizey, int isFullscreen);

#define FPS_TO_GET 60
#define TICK_TO_GET 60

#define PARAM_NAME "Ressources/parametres"

#endif /* RENDERING_BASE_HEADER_ */
