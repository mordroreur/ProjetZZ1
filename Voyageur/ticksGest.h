#ifndef TICKGEST_HEADER_
#define TICKGEST_HEADER_

#include "renderingUtil.h"

void mainTickGest(ecran *screen);
void *ChercheMinGraphe(void *param);
void generateTree(graphe* g, int bas, int haut);
void generateGraphe(graphe* g, float proba);
void changeArreteSize(graphe *g);
void positionneGraphe(graphe *g);
void libererGraphe(graphe *g);

  
#endif /* TICKGEST_HEADER_ */
