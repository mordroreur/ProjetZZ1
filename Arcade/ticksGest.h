#ifndef TICKGEST_HEADER_
#define TICKGEST_HEADER_

#include "renderingUtil.h"
#include "IAreflexion.h"

void mainTickGest(ecran *screen);
void *ChercheMinGraphe(void *param);
void generateLaby(ecran *screen);
void poseBanane(ecran *screen, int index);
void Deplace(ecran *screen, int index, float depx, float depy);

void initMout();
void loadBubbleIA2(ecran* screen);
void loadBubbleIA1(ecran* screen);
void loadBubble2V2IA1(ecran* screen);
void loadBubble2V2IA2(ecran* screen);
void loadIALout(ecran* screen);

void loadBubble4VIA1(ecran *screen);
void loadBubble4VIA2(ecran* screen);
void loadBubble4VIA3(ecran* screen);
void loadBubble4VIA4(ecran* screen);


#endif /* TICKGEST_HEADER_ */
