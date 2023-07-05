#ifndef __H__GUARDIAN_IAREFLEXTION__
#define __H__GUARDIAN_IAREFLEXTION__

#include "renderingUtil.h"

int *getLoupWorld(ecran *screen, int k, int paramNb);
int *getMoutonWorld(ecran *screen, int k, int paramNb);
void setIAInput(ecran *screen, int k, int * paramworld, int **loi, int Nbregle, int Nbparam);
int dist(ecran * screen, int self, int other);
int distobj(ecran * screen, int self, int other);
float carre(float x);
int orient(ecran * screen, int self, int other);
int orientobj(ecran * screen, int self, int other);
int compareN(int *tab1, int *tab2, int N);
int *getBooble1v1World(ecran *screen, int k, int paramNb);


#endif /*__H__GUARDIAN_IAREFLEXTION__*/
