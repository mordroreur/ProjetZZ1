#include "IAtrain.h"
#include "ticksGest.h"
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <stdlib.h>


#define COEURNUMBER 8
#define PARAMLOUP 10
#define PARAMMOUTON 2
#define NBITERMAX 5

void startIALoupMoutontraining(ecran * screen){
  trainLoup(screen);

  //playLoup(screen);


}

int ** MoutonLoi;

void playLoup(ecran *screen){
  int Nbregle = 0;
  int Nbpreda = screen->nbPreda;
  int Nbproie = screen->nbProie;
  int slow = 1;

  MoutonLoi = (int **)malloc(sizeof(int*)*32);
    for(int i = 0; i < 32; i++){
      MoutonLoi[i] = (int*)malloc(sizeof(int)*4);
    }
    for(int i = 0; i < 8; i++){
      MoutonLoi[i*4][0] = 0;
      MoutonLoi[i*4][1] = i;
      MoutonLoi[i*4][2] = (5+i)%8;
      MoutonLoi[i*4][3] = 5;

      MoutonLoi[i*4+1][0] = 0;
      MoutonLoi[i*4+1][1] = i;
      MoutonLoi[i*4+1][2] = (6+i)%8;
      MoutonLoi[i*4+1][3] = 3;

      MoutonLoi[i*4+2][0] = 0;
      MoutonLoi[i*4+2][1] = i;
      MoutonLoi[i*4+2][2] = (4+i)%8;
      MoutonLoi[i*4+2][3] = 3;

      MoutonLoi[i*4 +3][0] = -1;
      MoutonLoi[i*4 +3][1] = -1;
      MoutonLoi[i*4 +3][2] = i;
      MoutonLoi[i*4 +3][3] = 1;
    }
    

  int **loi = readIAFile("Ressources/MatIA.txt", &Nbregle);

  for(int i = 0; i < Nbregle; i++){
    for(int j = 0; j < PARAMLOUP; j++){
      printf("%d ", loi[i][j]);
    }
    printf("\n");
  }

  screen->etapeDuJeu = 3;
  screen->modePlay = 1;
  mainTickGest(screen);
  for(int i = 0; i < screen->nbPlayer; i++){
	screen->pla[i].IAType = 0;
  }
  
  for(int tick=0; tick<60000; tick++){
    //Acquisition de données
    for(int k=0; k<Nbpreda; k++){
	  
      int * paramworld = getLoupWorld(screen, k, PARAMLOUP);//CreateTab1(Nbparam);
      setIAInput(screen, k, paramworld, loi, Nbregle, PARAMLOUP);
	  
      free(paramworld);
	  
    }
    for(int i=0; i<Nbproie; i++){
      int * paramworld = getMoutonWorld(screen, screen->nbPreda + i, 2);//CreateTab1(Nbparam);
      setIAInput(screen, screen->nbPreda + i, paramworld, MoutonLoi, 32, 2);
	  
      free(paramworld);
    }
	
    SDL_Event event;
    while (SDL_PollEvent(&event)){
      switch (event.type){
      case SDL_KEYUP:
	if(event.key.keysym.sym == SDLK_ESCAPE){
	  tick = 100000;
	}else if(event.key.keysym.sym == SDLK_SPACE){
	  slow = !slow;
	}break;
      default:break;
      }  
    }
    if(slow){
      SDL_Delay(1);
    }

    
    mainTickGest(screen);
	if(screen->etapeDuJeu == 5){
      tick = 100000000;
    }
  }
  screen->etapeDuJeu = 12;
  mainTickGest(screen);
}





int trainLoup(ecran * screen){
  
  int NbActuRegle = 20;
  //  int NbMaxRegle = 30;
    
  int ContinueTrain = 1;
  
  int possibilites[12] = {3, 8, 3, 8, 3, 8, 3, 8, 3, 8, 8, 5};
  
  //setup basic sheep IA
  MoutonLoi = (int **)malloc(sizeof(int*)*32);
  for(int i = 0; i < 32; i++){
	MoutonLoi[i] = (int*)malloc(sizeof(int)*4);
  }
  for(int i = 0; i < 8; i++){
	MoutonLoi[(i*4)][0] = 0;
	MoutonLoi[(i*4)][1] = i;
	MoutonLoi[(i*4)][2] = (5+i)%8;
	MoutonLoi[(i*4)][3] = 5;

	MoutonLoi[(i*4)+1][0] = 0;
	MoutonLoi[(i*4)+1][1] = i;
	MoutonLoi[(i*4)+1][2] = (6+i)%8;
	MoutonLoi[(i*4)+1][3] = 3;

	MoutonLoi[(i*4)+2][0] = 0;
	MoutonLoi[(i*4)+2][1] = i;
	MoutonLoi[(i*4)+2][2] = (4+i)%8;
	MoutonLoi[(i*4)+2][3] = 3;

	MoutonLoi[(i*4) +3][0] = -1;
	MoutonLoi[(i*4) +3][1] = -1;
	MoutonLoi[(i*4) +3][2] = i;
	MoutonLoi[(i*4) +3][3] = 1;
	}

  int ** Mainloi = (int **)malloc(sizeof(int*)*NbActuRegle);
  for(int w=0; w<NbActuRegle; w++){
	Mainloi[w] = genreglealea(PARAMLOUP, possibilites);
  }
  
  int ***SousLoi = (int ***)malloc(sizeof(int **)*(COEURNUMBER-3));
  for(int k = 0; k < (COEURNUMBER - 3); k++){
	SousLoi[k] = (int **)malloc(sizeof(int*)*NbActuRegle);
	for(int i=0; i<NbActuRegle; i++){
	  SousLoi[k][i] = (int *)malloc(sizeof(int) * (PARAMLOUP+2));
	  for(int j = 0; j < (PARAMLOUP+2); j++){
		SousLoi[k][i][j] = Mainloi[i][j];
	  }
	}
  }

  
  ecran** allScreen = (ecran **)malloc(sizeof(ecran*) * (COEURNUMBER-3));
  for(int i = 1; i < (COEURNUMBER-3); i++){
	allScreen[i] = (ecran *)malloc(sizeof(ecran));
  }
  allScreen[0] = screen;


  pthread_t *allThread = (pthread_t*)malloc(sizeof(pthread_t)*(COEURNUMBER-3));
  simIO* allArgs = (simIO*)malloc(sizeof(simIO)*(COEURNUMBER-3));
  for(int i = 0; i < (COEURNUMBER-3); i++){
	allArgs[i].sc = allScreen[i];
	allArgs[i].loi = SousLoi[i];
  }
  int nbThread = 0;
  int nbEcriture = 0;

  //printf("Screen %d %d\n", NbActuRegle, PARAMLOUP);
  printIA(Mainloi,  NbActuRegle, PARAMLOUP, nbEcriture++);

  while(ContinueTrain){
	int *allCase = (int*)malloc(sizeof(int) * NbActuRegle*(PARAMLOUP+2));
	for(int i = 0; i < NbActuRegle*(PARAMLOUP+2); i++){
	  allCase[i] = i;
	}
	for(int i = 0; i < 3*NbActuRegle*(PARAMLOUP+2); i++){
	  int c1 = rand()%(NbActuRegle*(PARAMLOUP+2));
	  int c2 = rand()%(NbActuRegle*(PARAMLOUP+2));
	  int tmp = allCase[c1];
	  allCase[c1] = allCase[c2];
	  allCase[c2] = tmp;
	}

	for(int para = 0; para < NbActuRegle*(PARAMLOUP+2); para++){
	  
	  int laRegle = allCase[para]/(PARAMLOUP+2);
	  int leParam = allCase[para]%(PARAMLOUP+2);

	  int *resValue = (int *)malloc(sizeof(int) * (possibilites[leParam]+1));
	  for(int i = 0; i < possibilites[leParam]+1; i++){
		resValue[i] = 0;
	  }
	  for(int value = (leParam == PARAMLOUP+1)?1:-1; value < possibilites[leParam]+1; value++){
		if(nbThread < COEURNUMBER-3){
		  allArgs[nbThread].loi[laRegle][leParam] = value;
		  allArgs[nbThread].value = value;
		  allArgs[nbThread].nbAcRegle = NbActuRegle;
		  int retour = pthread_create(&allThread[nbThread], NULL, GetLoupScore,  &allArgs[nbThread]);
		  if(retour != 0){
		  }else{
		  }
		  nbThread++;
		}else{
		  int boucleVal = nbThread;
		  for(int i = 0; i < boucleVal; i++){
			pthread_join(allThread[i], NULL);
			nbThread--;
			resValue[allArgs[i].value+1] = allArgs[i].res;
		  }
		}
	  }

	  int boucleVal = nbThread;
	  for(int i = 0; i < boucleVal; i++){
		pthread_join(allThread[i], NULL);
		nbThread--;
		resValue[allArgs[i].value+1] = allArgs[i].res;
	  }
	  int max = 0;
	  for(int i = 1; i<possibilites[leParam]+1; i++){
		if(resValue[max] > resValue[i])
		  max = i;
	  }
	  Mainloi[laRegle][leParam] = max-1;
	  for(int i = 0; i < (COEURNUMBER-3); i++){
		allArgs[i].loi[laRegle][leParam] = max-1;
	  }

	  free(resValue);
	  
	  SDL_Event event;
	  while (SDL_PollEvent(&event)){
		switch (event.type){
		case SDL_KEYUP:
		  if(event.key.keysym.sym == SDLK_ESCAPE){
			ContinueTrain = 0;
			para = 100000;
		  }break;
		default:break;
		}  
	  }
	}
	printIA(Mainloi, NbActuRegle, PARAMLOUP, nbEcriture++);
	free(allCase);
  }

  if(MoutonLoi != NULL){
	for(int i = 0; i < 32; i++){
	  free(MoutonLoi[i]);
	}
	free(MoutonLoi);
  }
     
  if(Mainloi != NULL){
	for(int i = 0; i < NbActuRegle; i++){
	  free(Mainloi[i]);
	}
	free(Mainloi);
  }

  if(SousLoi != NULL){
	for(int i = 0; i < (COEURNUMBER-3); i++){
	  if(SousLoi[i] != NULL){
		for(int j = 0; j < NbActuRegle; j++){
		  free(SousLoi[i][j]);
		}
		free(SousLoi[i]);
	  }
	}
	free(SousLoi);
  }
  
  if(allScreen != NULL){
	for(int i = 1; i < COEURNUMBER-3; i++){
	  free(allScreen[i]);
	}
	free(allScreen);
  }

  free(allThread);
  free(allArgs);
  
    return 0;    
}




void * GetLoupScore(void *param){
  simIO *input = (simIO*) param;
  int score = 0;


  for(int ite = 0; ite < NBITERMAX; ite++){
	int lastTue = -1;
	int nbMorts = 0;
	input->sc->etapeDuJeu = 3;
	input->sc->modePlay = 1;
	mainTickGest(input->sc);
	for(int i = 0; i < input->sc->nbPlayer; i++){
	  input->sc->pla[i].IAType = 0;
	}
	for(int tick=0; tick<60000; tick++){
	  //Acquisition de données
	  for(int k=0; k<input->sc->nbPreda; k++){
	  
		int * paramworld = getLoupWorld(input->sc, k, PARAMLOUP);
		setIAInput(input->sc, k, paramworld, input->loi, input->nbAcRegle, PARAMLOUP);
		free(paramworld);
	  
	  }
	  for(int i=0; i<input->sc->nbProie; i++){
		int * paramworld = getMoutonWorld(input->sc, input->sc->nbPreda + i, 2);//CreateTab1(Nbparam);
		setIAInput(input->sc, input->sc->nbPreda + i, paramworld, MoutonLoi, 32, 2);
	  
		free(paramworld);
	  }
	
	
	  int nbd = 0;
	  for(int i = input->sc->nbPreda; i < input->sc->nbProie+input->sc->nbPreda; i++){
		if(input->sc->pla[i].vie == 0){
		  nbd++;
		}
	  }
	  mainTickGest(input->sc);
	  if(nbd != nbMorts){
		nbMorts = nbd;
		lastTue = tick;
	  }
	  if(input->sc->etapeDuJeu == 5){
		tick = 100000000;
	  }
	}

	input->sc->etapeDuJeu = 12;
	mainTickGest(input->sc);
	
	if(lastTue == -1){
	  score += 0;
	}else{
	  score += nbMorts + 1.0/lastTue;
	}
  }
  input->res = score;
  return NULL;
}





int * genreglealea(int Nbparam, int * possible){
  //printf("p : %d\n", (Nbparam + 2));
  int * result = (int *)malloc(sizeof(int) * (Nbparam + 2));
  if(result == NULL){
	printf("O connais le pb\n");
  }
  for(int i = 0; i < Nbparam +1; i++){
	float proba = (rand()%100)/100.0;
	if(proba < 0.25){
	  result[i] = rand()%possible[i];
	}else{
	  result[i] = -1;
	}
  }
  
  result[Nbparam+1]=rand()%5 + 1;
  return(result);
}

int dist(ecran * screen, int self, int other){
    int dist = -1;
    float diffx = (screen->pla[other].pos.x - screen->pla[self].pos.x);
    if(diffx > 50){diffx -= 50;}
    float diffy = screen->pla[other].pos.y - screen->pla[self].pos.y;
    if(diffy > 50){diffy -= 50;}
    float valdist = sqrtf(carre(diffx)+carre(diffy));
    if(valdist<15) {dist = 0;}
    else if(valdist<40) {dist = 1;}
    else {dist = 2;}
    return dist;
}


int ** readIAFile(char *name, int *tab){
  (void) name;
  (void) tab;
  /*
  FILE* f = fopen(name, "r");
  for(int i = 0; i < 20; i++){
    fscanf(f, "%d %d %d %d %d %d %d %d %d %d %d\n", &(tab[i][0]),  &(tab[i][1]),  &(tab[i][2]),  &(tab[i][3]),  &(tab[i][4]),  &(tab[i][5]), &(tab[i][6]), &(tab[i][7]), &(tab[i][8]), &(tab[i][9]), &(tab[i][10]));
  }
  fclose(f);*/
  return NULL;
}



void printIA(int **Mainloi, int nbregles, int nbParam ,int nbEcriture){
  char name[25];
  sprintf(name, "Ressources/IALoup%d.txt", nbEcriture);
  FILE * f = fopen(name, "w");
  fprintf(f, "%d %d\n", nbregles, nbParam);
  for(int i = 0; i < nbregles; i++){
	for(int j =  0; j < nbParam + 2; j++){
	  fprintf(f, "%d ", Mainloi[i][j]);
	}
	fprintf(f, "\n");
  }
  fclose(f);
}
