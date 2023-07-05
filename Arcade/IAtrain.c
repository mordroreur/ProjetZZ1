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
#define PROBAMUT 0.05
#define NBMATCH 3


void startIALoupMoutontraining(ecran * screen){
  trainLoup(screen);

  //playLoup(screen);


}

void startBubbleTraining(ecran * screen){
  int nbRegle = 20;
  int nbParam = 23;
  int possibilites[25] = {3, 8, 3, 8, 3, 8, 3, 8, 3, 8, 8, 8 ,8 ,8 ,8 ,8, 8, 8, 8, 8, 8, 8, 5, 16, 5};

  int nbLoi = 40;
  int nbPoule = 10;

  int *** allLoi = (int ***)malloc(sizeof(int**) * nbLoi);
  for(int i = 0; i < nbLoi; i++){
    allLoi[i] = (int **)malloc(sizeof(int *) * nbRegle);
    for(int j = 0; j < nbRegle; j++){
      allLoi[i][j] = genreglealea(nbParam, possibilites);
    }
  }

  
  for(int i = 0; i < nbRegle; i++){
    for(int j = 0; j < nbParam+2; j++){
      printf("%d ", allLoi[4][i][j]);
    }
    printf("\n");
  }
  //simIObb sc, lois, classement, nbregle, nbparam, trnid
  
  pthread_t *allThread = (pthread_t*)malloc(sizeof(pthread_t)*(COEURNUMBER-3));
  simIObb *allInput = (simIObb*)malloc(sizeof(simIObb) * (COEURNUMBER-3));
  
  ecran** allScreen = (ecran **)malloc(sizeof(ecran*) * (COEURNUMBER-3));
  for(int i = 1; i < (COEURNUMBER-3); i++){
    allScreen[i] = (ecran *)malloc(sizeof(ecran));
    allInput[i].sc = allScreen[i];
  }
  allScreen[0] = screen;
  
  int nbThread = 0;
  int contiGen = 1;
  int nbEcriture = 0;
  
  while (contiGen) {
    int *listPrems = (int *)malloc(sizeof(int) * nbPoule);
    for(int i = 0; i < nbPoule; i++){
      listPrems[i] = i;
    }

    /*for(int trn = 0; trn < nbPoule; trn++){
      if(nbThread < COEURNUMBER-3){
	allInput[nbThread].lois = allLoi + (trn*4);
	allInput[nbThread].nbregle = nbRegle;
	allInput[nbThread].nbparam = nbParam;
	allInput[nbThread].trnid = trn;
	int retour = pthread_create(&allThread[nbThread], NULL, GetTournoisClassement,  &allInput[nbThread]);
	nbThread++;
      }else{
	int boucleVal = nbThread;
	for(int i = 0; i < boucleVal; i++){
	  pthread_join(allThread[i], NULL);
	  nbThread--;
	  listPrems[allInput[i].trnid] = allInput[i].trnid * (nbLoi/nbPoule) + allInput[i].classement[0];
	  free(allInput[i].classement);
	}
	trn--;
      }
      }*/

    int boucleVal = nbThread;
    for(int i = 0; i < boucleVal; i++){
      pthread_join(allThread[i], NULL);
      nbThread--;
      listPrems[allInput[i].trnid] = allInput[i].trnid * (nbLoi/nbPoule) + allInput[i].classement[0];
      free(allInput[i].classement);
    }	  

    //listprems = tout les premiers des tournois
    int *** pere = (int ***)malloc(sizeof(int**) * nbPoule);
    for(int i = 0; i < nbPoule; i++){
      pere[i] = (int **)malloc(sizeof(int *) * nbRegle);
      for(int j = 0; j < nbRegle; j++){
	pere[i][j] = (int *)malloc(sizeof(int)*(nbParam+2));
	for(int k = 0; k < nbParam+2; k++){
	  pere[i][j][k] = allLoi[listPrems[i]][j][k];
	}
      }
    }

    for(int i = 0; i < nbPoule; i++){
      printIA(allLoi[listPrems[i]], nbRegle, nbParam, nbEcriture++, 1);
    }

    if(allLoi != NULL){
      for(int i = 0; i < nbLoi; i++){
	if(allLoi[i] != NULL){
	  for(int j = 0; j < nbRegle; j++){
	    free(allLoi[i][j]);
	  }
	  free(allLoi[i]);
	}
      }
      free(allLoi);
    }

    
    allLoi = creationFils(pere, nbPoule, nbRegle, nbParam+2, 40);

    printf("Apres  : \n");
    for(int i = 0; i < nbRegle; i++){
      for(int j = 0; j < nbParam+2; j++){
	printf("%d ", allLoi[4][i][j]);
      }
      printf("\n");
    }
    
    
    for(int i = 0; i < nbLoi; i++){
      if(PROBAMUT > (rand()%100)/100.0){
	int rg = rand()%nbRegle;
	int rp = rand()%(nbParam+2);
	float proba = (rand()%100)/100.0;
	int nwVal = (rp == nbParam+1)?(rand()%5 + 1):rand()%(possibilites[i]+1)-1;
      }
    }
    
    //PROBAMUT
    if(pere != NULL){
      for(int i = 0; i < nbPoule; i++){
	if(pere[i] != NULL){
	  for(int j = 0; j < nbRegle; j++){
	    free(pere[i][j]);
	  }
	  free(pere[i]);
	}
      }
      free(pere);
    }
    break;
  }


  free(allThread);
  
  if(allLoi != NULL){
    for(int i = 0; i < (COEURNUMBER-3); i++){
      if(allLoi[i] != NULL){
	for(int j = 0; j < nbRegle; j++){
	  free(allLoi[i][j]);
	}
	free(allLoi[i]);
      }
    }
    free(allLoi);
  }
  
  if(allScreen != NULL){
    for(int i = 1; i < COEURNUMBER-3; i++){
      free(allScreen[i]);
    }
    free(allScreen);
  }

    
  
}



int ** MoutonLoi;

void playLoup(ecran *screen){
  int Nbregle = 0;
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
    

  int **loi = readIAFile("Ressources/IALoup4.txt", &Nbregle);

  for(int i = 0; i < Nbregle; i++){
    for(int j = 0; j < PARAMLOUP+2; j++){
      printf("%d ", loi[i][j]);
    }
    printf("\n");
  }

  
  screen->etapeDuJeu = 3;
  screen->modePlay = 1;
  mainTickGest(screen);

  int Nbpreda = screen->nbPreda;
  int Nbproie = screen->nbProie;

  for(int i = 0; i < screen->nbPlayer; i++){
	screen->pla[i].IAType = 0;
  }
  for(int tick=0; tick<60000; tick++){
    //Acquisition de données

    for(int k = 0; k < Nbpreda; k++){

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
	MoutonLoi[(i*4)][2] = -1;//(5+i)%8;
	MoutonLoi[(i*4)][3] = 5;

	MoutonLoi[(i*4)+1][0] = 0;
	MoutonLoi[(i*4)+1][1] = i;
	MoutonLoi[(i*4)+1][2] = -1;//(6+i)%8;
	MoutonLoi[(i*4)+1][3] = 3;

	MoutonLoi[(i*4)+2][0] = 0;
	MoutonLoi[(i*4)+2][1] = i;
	MoutonLoi[(i*4)+2][2] = -1;//(4+i)%8;
	MoutonLoi[(i*4)+2][3] = 3;

	MoutonLoi[(i*4) +3][0] = -1;
	MoutonLoi[(i*4) +3][1] = -1;
	MoutonLoi[(i*4) +3][2] = -1;//i;
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

  screen->etapeDuJeu = 777;
  
  //printf("Screen %d %d\n", NbActuRegle, PARAMLOUP);
  printIA(Mainloi,  NbActuRegle, PARAMLOUP, nbEcriture++, 0);

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

	  //printf("%d\n", allCase[para]);
	  
	  int laRegle = allCase[para]/(PARAMLOUP+2);
	  int leParam = allCase[para]%(PARAMLOUP+2);

	  int *resValue = (int *)malloc(sizeof(int) * (possibilites[leParam]+1));
	  for(int i = 0; i < possibilites[leParam]+1; i++){
		resValue[i] = 0;
	  }
	  for(int value = (leParam == PARAMLOUP+1)?1:-1; value < possibilites[leParam]; value++){
		if(nbThread < COEURNUMBER-3){
		  allArgs[nbThread].loi[laRegle][leParam] = value;
		  allArgs[nbThread].value = value;
		  allArgs[nbThread].nbAcRegle = NbActuRegle;
		  //printf("debut Thread\n");
		  int retour = pthread_create(&allThread[nbThread], NULL, GetLoupScore,  &allArgs[nbThread]);
		  //printf("Fin debut Thread\n");
		  if(retour != 0){
		  }
		  nbThread++;
		}else{
		  int boucleVal = nbThread;
		  for(int i = 0; i < boucleVal; i++){
		    //printf("Fin 2\n");
		    pthread_join(allThread[i], NULL);
		    //printf("FIn 2 FIn\n");
		    nbThread--;
		    resValue[allArgs[i].value+1] = allArgs[i].res;
		  }
		  value--;
		}
	  }

	  int boucleVal = nbThread;
	  for(int i = 0; i < boucleVal; i++){
	    //printf("Fin\n");
	    pthread_join(allThread[i], NULL);
	    //printf("FIn FIn\n");
	    nbThread--;
	    //printf("%d\n", i);
	    //int tmp = allArgs[i].res;
	    //printf("%d   val = %d\n", (possibilites[leParam]+1), allArgs[i].value+1);
	    resValue[allArgs[i].value+1] = allArgs[i].res;
	  }
	  int max = (leParam == PARAMLOUP+1)?2:0;
	  for(int i = (leParam == PARAMLOUP+1)?3:1; i<possibilites[leParam]+1; i++){
		if(resValue[max] > resValue[i])
		  max = i;
	  }
          int nbMax = 0;
	  for(int i = (leParam == PARAMLOUP+1)?2:0; i<possibilites[leParam]+1; i++){
	    if(resValue[max] == resValue[i])
	      nbMax++;
	  }
	  
	  int quelMax = (rand()%nbMax)+1;
	  if(leParam == PARAMLOUP && quelMax == 1 && nbMax != 1){
	    quelMax = (rand()%(nbMax-1))+2;
	  }
	  int nvmax = 0;
	  int it = 0;
	  while (quelMax != 0) {
	    if(resValue[it] == resValue[max]){
	      nvmax=max;
	      quelMax--;
	    }
	    it++;
	  }
	  

	  Mainloi[laRegle][leParam] = nvmax-1;
	  for(int i = 0; i < (COEURNUMBER-3); i++){
		allArgs[i].loi[laRegle][leParam] = nvmax-1;
	  }
	  //printf("Fin boucle\n");
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
	  //printf("Fin autre event\n");
	}
	printIA(Mainloi, NbActuRegle, PARAMLOUP, nbEcriture++, 0);
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

  screen->etapeDuJeu = 2;
  
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

int ** readIAFile(char *name, int *nbR){
  int nbParam;
  FILE* f = fopen(name, "r");
  if(f){
  fscanf(f, "%d %d\n",nbR, &nbParam);
  int ** res = (int **)malloc(sizeof(int *)*(*nbR));
  for(int i = 0; i < *nbR; i++){
    res[i] = (int *)malloc(sizeof(int) * (nbParam+2));
    for(int j = 0; j < nbParam+2; j++){
      fscanf(f, "%d ", &res[i][j]);
    }
  }

  /*  for(int i = 0; i < *nbR; i++){
    for(int j = 0; j < nbParam+2; j++){
      printf("%d ", res[i][j]);
    }
    printf("\n");
    } */ 

  
  fclose(f);
  return res; 
  }
  return NULL;
}



void printIA(int **Mainloi, int nbregles, int nbParam ,int nbEcriture, int type){
  char name[25];
  if(type == 0){
    sprintf(name, "Ressources/IALoup%d.txt", nbEcriture);
  }else if(type == 1){
    sprintf(name, "Ressources/IABobble%d.txt", nbEcriture);
  }

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


// Tournois pour 4 ia
void *GetTournoisClassement(void *arg){
  int nbIA = 4;
  simIObb* input = (simIObb *)arg;
  input->classement = (int *)malloc(sizeof(int) * nbIA);
  for(int i = 0; i < nbIA; i++){
    input->classement[i] = i;
  }
  float *score =(float *)malloc(sizeof(int) * nbIA);
  for(int i = 0; i < nbIA; i++){
    score[i] = 0;
  }

  for(int i = 0; i < nbIA-1; i++){
    for(int j = i; j < nbIA; j++){


      for(int ite = 0; ite < NBMATCH; ite++){
	input->sc->maxVie = 1;
	input->sc->etapeDuJeu = 3;
	input->sc->modePlay = 0;
	mainTickGest(input->sc);
	for(int i = 0; i < input->sc->nbPlayer; i++){
	  input->sc->pla[i].IAType = 0;
	}
	for(int tick=0; tick<60000; tick++){
	  //Acquisition de données
	  /*	  
	  int * paramworld = getBooble1v1World(input->sc, 0, input->nbparam);
	  setIAInput(input->sc, 0, paramworld, input->lois[i], input->nbregle, input->nbparam);
	  free(paramworld);

	  paramworld = getBooble1v1World(input->sc, 1, input->nbparam);
	  setIAInput(input->sc, 1, paramworld, input->lois[i], input->nbregle, input->nbparam);
	  free(paramworld);
	  */
	  
	  mainTickGest(input->sc);
	  if(input->sc->etapeDuJeu == 5){
	    tick = 100000000;
	  }
	}

	if(input->sc->pla[0].vie == 0){
	  score[i] -= 1;
	  score[j] += 1;
	}else if(input->sc->pla[1].vie == 0){
	  score[i] += 1;
	  score[j] -= 1;
	}
	

	input->sc->etapeDuJeu = 12;
	mainTickGest(input->sc);
	
      }
    }
  }

  int i, j;
  for (i = 0; i < nbIA-1; i++) {
    for (j = 0; j < nbIA-i-1; j++) {
      if (score[j] > score[j+1]) {
	float tem = score[j];
	score[j] = score[j+1];
	score[j+1] = tem;
	int tmp = input->classement[j];
	input->classement[j] = input->classement[j+1];
	input->classement[j+1] = tmp;
      }
    }
  }
  
  
  free(score);
  return NULL;
}


int alea(int min, int max) 
{
    int nombreAleatoire = (rand() % (max - min + 1)) + min;
    return nombreAleatoire;
}

int *** createMatrice(int ligne, int colonne, int profondeur)
{
  int *** map;
  map = (int ***) malloc(sizeof(int **)*ligne);
  if(!map) exit(0) ; // map == NULL alors erreur allocation donc appelle fonction (message + exit prog)

  for(int i = 0 ; i < ligne; i++)
  {
    map[i] = (int **) malloc(sizeof(int *)*colonne);
    if(!map[i]) 
    {               // si erreur allocation en cours dans la map free proprement + quit prog
      for(int l = 0; l < i; l++) { free(map[l]); map[l] = NULL; }
      free(map); map = NULL;
      exit(0) ;
    }

    for(int j = 0; j < colonne; j++) 
    {
      map[i][j] = (int *) malloc(sizeof(int) * profondeur);
      if(!map[i][j]) {   // si erreur allocation en cours dans la map free proprement + quit prog
        for(int m = 0; m < j; m++) { free(map[i][m]); map[i][m] = NULL; }
        for(int n = 0; n < i; n++) { free(map[n]); map[n] = NULL; }
        free(map); map = NULL;
        exit(0) ;
      }
    }
  }
  return map ; // return la map
}

int *** creationFils(int *** peres, int ligne, int colonne, int nbrParametre, int nbrFils)
{
    //ligne = nbr IA vainqueur
    //colonne = nbr Règle
    int *** fils = createMatrice(nbrFils, colonne, nbrParametre);
    int ia, ia1, ia2, ia3, max, index;
    for (int i = 0; i < nbrFils; i++)
    {
        /*Selection aléatoire des IA vainqueur*/
        ia1 = alea(0, ligne-1);
        ia2 = alea(0, ligne-1);
        ia3 = alea(0, ligne-1);
        index = 0;
        /*Selection des x parametrez de la premiere IA, second et troisième IA*/
        for (int ez = 0; ez < 3; ez++)
	  {
	    int oldInd = 0;
            index += alea(-1, (colonne*nbrParametre)-1 - index);
            if (index == -1 && ez != 2){
	      index = 0;
	    }else{
	      index = (ez == 2) ? (colonne*nbrParametre) : index;
	      ia = (ez == 0) ? ia1 : (ez == 1) ? ia2 : ia3;
	      for (int j = oldInd; j < index; j++)
                fils[i][j/nbrParametre][j%nbrParametre] = peres[ia][j/nbrParametre][j%nbrParametre];
	      oldInd = index;
	    }
        }
    }
    return fils;
}
