#ifndef TICKGEST_HEADER_
#define TICKGEST_HEADER_

#include "renderingUtil.h"
#include "listeFloat.h"

void mainTickGest(ecran *screen);
void *ChercheMinGraphe(void *param);
float ** CreateTab(int haut, int larg);
float *** CreateTab3(int haut, int larg, int prof);
void resosimple(graphe *G, graphe * GC);
float ** TransfGraphCompl(graphe * G);
float TestSolution(liste *solu, graphe * GC);
float rechfourmi(graphe * G, graphe * GC,int nbfourmi, int nbjour, int pos, int dureepherom);
void choixchemin(graphe * GC, float *** pheromone,int dureepherom, int posdep, float ** pheromtmp);
void majpheromone(graphe * GC, float ***pheromone, int dureepherom, float ** pheromtmp);
float ** addpheromone(graphe * GC, liste *solutemp, float ** pheromtmp);
int choixsommet(graphe * GC, int pos, float *** pheromone, int dureepherom, int *Tabou, int position);
float pheromij(float *** pheromone, int i, int j, int dureepherom);


float recuitsimul(graphe * G, graphe * GC, float tinit, float tfin, int nbiter, int nblistinit);
liste * choixlistdep(int nblistinit,graphe * GC);
liste * genlistalea(graphe * GC);
liste * genlistvois(liste * listeact, graphe * GC);

void generateTree(graphe* g, int bas, int haut);
void generateGraphe(graphe* g, float proba);
void changeArreteSize(graphe *g);
void positionneGraphe(graphe *g);
void libererGraphe(graphe *g);

  
#endif /* TICKGEST_HEADER_ */
