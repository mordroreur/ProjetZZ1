#ifndef TICKGEST_HEADER_
#define TICKGEST_HEADER_

#include "renderingUtil.h"

void mainTickGest(ecran *screen);
void *ChercheMinGraphe(void *param);
float ** CreateTab(int taille);
float ** TransfGraphCompl(graphe * G);
float TestSolution(liste solu, graphe * GC);
float rechfourmi(graphe * G, int nbfourmi, graphe * GC);
void choixchemin(graphe * GC, float ** pheromone);
void majpheromone(graphe * GC, liste solutemp, float **pheromone);
int choixsommet(graphe * GC, int pos, float ** pheromone, liste Tabou);
liste listsommet(graphe * GC, int pos, liste Tabou);
float SpheromSommet(float ** pheromone, int taille, int i);
liste probasommetposs(graphe * GC, liste cheminposs, float ** pheromone);

void generateTree(graphe* g, int bas, int haut);
void generateGraphe(graphe* g, float proba);
void changeArreteSize(graphe *g);
void positionneGraphe(graphe *g);


  
#endif /* TICKGEST_HEADER_ */
