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
  float res;
  int value;
  int nbAcRegle;
  int nbParam;
  int * uti;
}simIO;

typedef struct simulation_I_OBubble{
  ecran * sc;
  int ***lois;
  int * classement;
  int nbregle;
  int nbparam;
  int trnid;
  int mode;
  int ** uti;
}simIObb;


void startIALoupMoutontraining(ecran * screen);
void startBubbleTraining(ecran * screen, int mode);


int trainLoup(ecran *screen);
void playLoup(ecran * screen);
int * genreglealea(int Nbpram, int * possible, float probamu);

void *GetLoupScore(void*);
void printIA(int **Mainloi, int nbregles, int nbParam ,int nbEcriture, int type);

void *GetTournoisClassement(void *arg);
int ***createMatrice(int ligne, int colonne, int profondeur);
int alea(int min, int max);
int ***creationFils(int ***peres, int ligne, int colonne, int nbrParametre, int nbrFils);
int *** creationFils2(int *** peres, int ligne, int colonne, int nbrParametre, int nbrFils);



#endif /* TRAINIA_HEADER_ */
