#ifndef TICKGEST_HEADER_
#define TICKGEST_HEADER_

#include "renderingUtil.h"
#include "listeFloat.h"

void mainTickGest(ecran *screen);
void *ChercheMinGraphe(void *param);
float ** CreateTab(int haut, int larg);
void resosimple(graphe *G, graphe * GC);
liste * rechemin(graphe * G, int deb, int fin);
float ** TransfGraphCompl(graphe * G);
float TestSolution(liste *solu, graphe * GC);
float rechfourmi(graphe * G, int nbfourmi, int nbjour, graphe * GC, int pos, int dureepherom);
void choixchemin(graphe * GC, float ** pheromone, int pos, float ** pheromtmp);
void majpheromone(graphe * GC, float **pheromone, int dureepherom, float ** pheromtmp);
void addpheromone(graphe * GC, liste *solutemp, float ** pheromtmp);
int choixsommet(graphe * GC, int pos, float ** pheromone, liste *Tabou);
liste *listsommet(graphe * GC, int pos, liste *Tabou);
float SpheromSommet(float ** pheromone, int taille, int i);
listef probasommetposs(graphe * GC, liste *cheminposs, float ** pheromone);

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
