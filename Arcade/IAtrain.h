#ifndef TRAINIA_HEADER_
#define TRAINIA_HEADER_

#include "renderingBase.h"
#include "IAreflexion.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>


typedef struct simulation_I_O{
  ecran * sc;
  int **loi;
  int res;
  int value;
  int nbAcRegle;
}simIO;


void startIALoupMoutontraining(ecran * screen);

int trainLoup(ecran *screen);
void playLoup(ecran * screen);
int * genreglealea(int Nbpram, int * possible);
int ** readIAFile(char *name, int *regles);

void *GetLoupScore(void*);
void printIA(int **Mainloi, int nbregles, int nbParam ,int nbEcriture);


#endif /* TRAINIA_HEADER_ */
