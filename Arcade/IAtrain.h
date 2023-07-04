#ifndef TRAINIA_HEADER_
#define TRAINIA_HEADER_

#include "renderingBase.h"
#include "IAreflexion.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

void startIALoupMoutontraining(ecran * screen);

int trainLoup(ecran *screen);
void playLoup(ecran * screen);
int * genreglealea(int Nbpram, int * possible);
void readIAFile(char *name, int **tab);


#endif /* TRAINIA_HEADER_ */
