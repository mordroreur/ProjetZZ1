#ifndef TICKGEST_HEADER_
#define TICKGEST_HEADER_

#include "renderingUtil.h"

void mainTickGest(ecran *screen);
void *ChercheMinGraphe(void *param);
void generateLaby(ecran *screen);
void poseBanane(ecran *screen, int index);
void Deplace(ecran *screen, int index, float depx, float depy);

#endif /* TICKGEST_HEADER_ */
