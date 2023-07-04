#ifndef TRAINIA_HEADER_
#define TRAINIA_HEADER_

#include "renderingBase.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

void startIAtraining(ecran * screen);

int testfct(ecran * screen);
int * CreateTab1(int taille);
int ** CreateTab2(int Nbregle, int Nbparam);
int *** CreateTab3(int Nbindiv, int Nbregle, int Nbparam);
int * genreglealea(int Nbpram);
int dist(ecran * screen, int self, int other);
int distobj(ecran * screen, int self, int other);
float carre(float x);
int orient(ecran * screen, int self, int other);
int orientobj(ecran * screen, int self, int other);
int compareN(int * tab1, int* tab2, int N);

#endif /* TRAINIA_HEADER_ */