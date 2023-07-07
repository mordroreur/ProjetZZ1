#include "IAtrain.h"
#include "renderingUtil.h"
#include "ticksGest.h"
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <stdlib.h>



#define COEURNUMBER 4
#define NBITERMAX 5
#define PROBAMUT 0.6
#define NBMATCH 5


void startIALoupMoutontraining(ecran * screen){
  trainLoup(screen);

  //playLoup(screen);
}



void startBubbleTraining(ecran * screen, int mode){
  int nbRegle = 20;
  int nbParam = 27;
  int possibilites[29] = {3, 8, 3, 8, 3, 8, 3, 8, 3, 3, 8, 3, 3, 3, 3, 3 ,3 ,3 ,3 ,3, 3, 3, 3, 3, 3, 3, 3, 16, 5};
  if(mode == 0){
	nbParam = 23;
	possibilites[0] = 3;
	possibilites[1] = 8;
	possibilites[2] = 3;
	possibilites[3] = 8;
	possibilites[4] = 3;
	possibilites[5] = 3;
	possibilites[6] = 8;
	possibilites[7] = 3;
	possibilites[8] = 3;
	possibilites[9] = 3;
	possibilites[10] = 3;
	possibilites[11] = 3;
	possibilites[12] = 3;
	possibilites[13] = 3;
	possibilites[14] = 3;
	possibilites[15] = 3;
	possibilites[16] = 3;
	possibilites[17] = 3;
	possibilites[18] = 3;
	possibilites[19] = 3;
	possibilites[20] = 3;
	possibilites[21] = 3;
	possibilites[22] = 3;
	possibilites[23] = 16;
	possibilites[24] = 5;
  }
  //dist adv, dir adv, dist bon, dir bon, dist bon:adv ,dist tn, dir tn + 16 densités
  
  int nbLoi = 40;
  int nbPoule = 10;

  int *** allLoi = (int ***)malloc(sizeof(int**) * nbLoi);
  for(int i = 0; i < nbLoi; i++){
    allLoi[i] = (int **)malloc(sizeof(int *) * nbRegle);
    for(int j = 0; j < nbRegle; j++){
      allLoi[i][j] = genreglealea(nbParam, possibilites, 0.1);
    }
  }

  /*  
  for(int i = 0; i < nbRegle; i++){
    for(int j = 0; j < nbParam+2; j++){
      printf("%d ", allLoi[4][i][j]);
    }
    printf("\n");
    }*/
  //simIObb sc, lois, classement, nbregle, nbparam, trnid
  
  pthread_t *allThread = (pthread_t*)malloc(sizeof(pthread_t)*(COEURNUMBER-3));
  simIObb *allInput = (simIObb*)malloc(sizeof(simIObb) * (COEURNUMBER-3));

  int **uti = (int **)malloc(sizeof(int *) * nbPoule);
  for(int i = 0; i < nbPoule; i++){
    uti[i] = (int *)malloc(sizeof(int) * nbRegle);
  }
  
  ecran** allScreen = (ecran **)malloc(sizeof(ecran*) * (COEURNUMBER-3));
  for(int i = 1; i < (COEURNUMBER-3); i++){
    allScreen[i] = (ecran *)malloc(sizeof(ecran));
  }
  allScreen[0] = screen;
  
  for(int i = 0 ; i < (COEURNUMBER-3); i++){
	allInput[i].sc = allScreen[i];
  }
  
  int nbThread = 0;
  int contiGen = 1;
  int nbEcriture = 0;
  
  while (contiGen) {
    int *listPrems = (int *)malloc(sizeof(int) * nbPoule);
    for(int i = 0; i < nbPoule; i++){
      listPrems[i] = i;
    }
    for(int i = 0; i < nbPoule; i++){
      for(int j = 0; j < nbRegle; j++){
	uti[i][j] = 0;
      }
    }

    for(int trn = 0; trn < nbPoule; trn++){
      if(nbThread < COEURNUMBER-3){
		allInput[nbThread].lois = allLoi + (trn*4);
		allInput[nbThread].nbregle = nbRegle;
		allInput[nbThread].nbparam = nbParam;
		allInput[nbThread].trnid = trn;
		allInput[nbThread].mode = mode;
		//		printf("Creer pthe\n");
		pthread_create(&allThread[nbThread], NULL, GetTournoisClassement,  &allInput[nbThread]);
		//		printf("fin crea\n");
		nbThread++;
      }else{
		int boucleVal = nbThread;
		for(int i = 0; i < boucleVal; i++){
		  //		  printf("Libe\n");
		  pthread_join(allThread[i], NULL);
		  nbThread--;
		  listPrems[allInput[i].trnid] = allInput[i].trnid * (nbLoi/nbPoule) + allInput[i].classement[0];
		  for(int j = 0; j < nbRegle; j++){
		    uti[allInput[i].trnid][j] = allInput[i].uti[allInput[i].classement[0]][j];
		  }
		  for(int j = 0; j < nbLoi/nbPoule; j++){
		    free(allInput[i].uti[j]);
		  }
		  free(allInput[i].uti);
		  free(allInput[i].classement);
		}
		trn--;
      }
	}

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
      printIA(allLoi[listPrems[i]], nbRegle, nbParam, nbEcriture++, mode+1);
    }

    
	for(int i = 0; i < nbPoule; i++){
      for(int j = 0; j < nbRegle; j++){
		if(uti[i][j] == 0){
		  free(pere[i][j]);
		  pere[i][j] = genreglealea(nbParam, possibilites, 0.1);
		}
      }
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

    
    allLoi = creationFils2(pere, nbPoule, nbRegle, nbParam+2, 40);

    /*
	  printf("Apres  : \n");
	  for(int i = 0; i < nbRegle; i++){
      for(int j = 0; j < nbParam+2; j++){
	  printf("%d ", allLoi[4][i][j]);
      }
      printf("\n");
      }*/
    
    
    for(int i = 0; i < nbLoi; i++){
      if(PROBAMUT > (rand()%100)/100.0){
	int rg = rand()%nbRegle;
	int rp = rand()%(nbParam+2);
	//float proba = (rand()%100)/100.0;
	int nwVal = (rp == nbParam+1)?(rand()%5 + 1):rand()%(possibilites[i]+1)-1;
	allLoi[i][rg][rp] = nwVal;
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

	SDL_Event event;
    while (SDL_PollEvent(&event)){
      switch (event.type){
      case SDL_KEYUP:
	if(event.key.keysym.sym == SDLK_ESCAPE){
	  contiGen = 0;
	}break;
      default:break;
      }  
    }
    nbEcriture = 0;
    //break;
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
  int nbParam = 0;
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
    

    int **loi = readIAFile("Ressources/IALoup1.txt", &Nbregle, &nbParam);

  for(int i = 0; i < Nbregle; i++){
    for(int j = 0; j < nbParam+2; j++){
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


      int * paramworld = getLoupWorld(screen, k, nbParam);//CreateTab1(Nbparam);      
      setIAInput(screen, k, paramworld, loi, Nbregle, nbParam, NULL);
      free(paramworld);
	  
    }

    for(int i=0; i<Nbproie; i++){
      int * paramworld = getMoutonWorld(screen, screen->nbPreda + i, 2);//CreateTab1(Nbparam);
      setIAInput(screen, screen->nbPreda + i, paramworld, MoutonLoi, 32, 2, NULL);
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
  int nbParam = 12;
  int ContinueTrain = 1;
  
  int possibilites[14] = {3, 8, 3, 8, 3, 8, 3, 8, 3, 8, 3, 8, 8, 5};
  
  //setup basic sheep IA
  MoutonLoi = (int **)malloc(sizeof(int*)*32);
  for(int i = 0; i < 32; i++){
	MoutonLoi[i] = (int*)malloc(sizeof(int)*4);
  }
  for(int i = 0; i < 8; i++){
	MoutonLoi[(i*4)][0] = 0;
	MoutonLoi[(i*4)][1] = i;
	MoutonLoi[(i*4)][2] = (5+i)%8;//
	MoutonLoi[(i*4)][3] = 5;

	MoutonLoi[(i*4)+1][0] = 0;
	MoutonLoi[(i*4)+1][1] = i;
	MoutonLoi[(i*4)+1][2] = (6+i)%8;//
	MoutonLoi[(i*4)+1][3] = 3;

	MoutonLoi[(i*4)+2][0] = 0;
	MoutonLoi[(i*4)+2][1] = i;
	MoutonLoi[(i*4)+2][2] = (4+i)%8;//;
	MoutonLoi[(i*4)+2][3] = 3;

	MoutonLoi[(i*4) +3][0] = -1;
	MoutonLoi[(i*4) +3][1] = -1;
	MoutonLoi[(i*4) +3][2] = i;//
	MoutonLoi[(i*4) +3][3] = 1;

    // MoutonLoi[i*2][0] = 0;
    // MoutonLoi[i*2][1] = i;
    // MoutonLoi[i*2][2] = (4+i)%8;
    // MoutonLoi[i*2][3] = 5;

    // MoutonLoi[i*2+1][0] = 1;
    // MoutonLoi[i*2+1][1] = i;
    // MoutonLoi[i*2+1][2] = (4+i)%8;
    // MoutonLoi[i*2+1][3] = 5;
	}


  //Generation aleatoire de la loi principale
  int ** Mainloi = (int **)malloc(sizeof(int*)*NbActuRegle);
  for(int w=0; w<NbActuRegle; w++){
    Mainloi[w] = genreglealea(nbParam, possibilites, 0.25);
  }

  //generation par fichier de la loi principale
  //int **Mainloi = readIAFile("Ressources/IALoup1.txt", &NbActuRegle);




  
  int ***SousLoi = (int ***)malloc(sizeof(int **)*(COEURNUMBER-3));
  for(int k = 0; k < (COEURNUMBER - 3); k++){
	SousLoi[k] = (int **)malloc(sizeof(int*)*NbActuRegle);
	for(int i=0; i<NbActuRegle; i++){
	  SousLoi[k][i] = (int *)malloc(sizeof(int) * (nbParam+2));
	  for(int j = 0; j < (nbParam+2); j++){
		SousLoi[k][i][j] = Mainloi[i][j];
	  }
	}
  }

  int * utilisation = (int*) malloc(sizeof(int)*NbActuRegle);


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
  printIA(Mainloi,  NbActuRegle, nbParam, nbEcriture++, 0);

  while(ContinueTrain){
	int *allCase = (int*)malloc(sizeof(int) * NbActuRegle*(nbParam+2));
	for(int i = 0; i < NbActuRegle*(nbParam+2); i++){
	  allCase[i] = i;
	}
	for(int i = 0; i < 3*NbActuRegle*(nbParam+2); i++){
	  int c1 = rand()%(NbActuRegle*(nbParam+2));
	  int c2 = rand()%(NbActuRegle*(nbParam+2));
	  int tmp = allCase[c1];
	  allCase[c1] = allCase[c2];
	  allCase[c2] = tmp;
	}

	for(int para = 0; para < NbActuRegle*(nbParam+2); para++){
	  for(int i = 0; i < NbActuRegle; i++){
	    utilisation[i]= 0;
	  }
	  //printf("%d\n", allCase[para]);
	  
	  int laRegle = allCase[para]/(nbParam+2);
	  int leParam = allCase[para]%(nbParam+2);

	  float *resValue = (float *)malloc(sizeof(float) * (possibilites[leParam]+1));
	  for(int i = 0; i < possibilites[leParam]+1; i++){
		resValue[i] = 0;
	  }
	  for(int value = (leParam == nbParam+1)?1:-1; value < possibilites[leParam]; value++){
		if(nbThread < COEURNUMBER-3){
		  allArgs[nbThread].loi[laRegle][leParam] = value;
		  allArgs[nbThread].value = value;
		  allArgs[nbThread].nbAcRegle = NbActuRegle;
		  allArgs[nbThread].nbParam = nbParam;
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
        for(int j = 0; j < NbActuRegle; j++){
          utilisation[j] += allArgs[i].uti[j];
        }
        free(allArgs[i].uti);
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
      for(int j = 0; j < NbActuRegle; j++){
          utilisation[j] += allArgs[i].uti[j];
        }
        free(allArgs[i].uti);
	  }

	  
	  int max = (leParam == nbParam+1)?2:0;
	  for(int i = (leParam == nbParam+1)?3:1; i<possibilites[leParam]+1; i++){
		if(resValue[max] < resValue[i])
		  max = i;
	  }
          int nbMax = 0;
	  for(int i = (leParam == nbParam+1)?2:0; i<possibilites[leParam]+1; i++){
	    if(resValue[max] == resValue[i])
	      nbMax++;
	  }
	  
	  int quelMax = (rand()%nbMax)+1;
	  if(leParam == nbParam && quelMax == 1 && nbMax != 1){
	    quelMax = (rand()%(nbMax-1))+2;
	  }

	  
	  int nvmax = 0;
	  int it = 0;
	  while (quelMax != 0) {
	    if(resValue[it] == resValue[max]){
	      nvmax=it;
	      quelMax--;
	    }
	    it++;
	  }


	  Mainloi[laRegle][leParam] = nvmax-1;
	  for(int i = 0; i < (COEURNUMBER-3); i++){
		allArgs[i].loi[laRegle][leParam] = nvmax-1;
	  }
	  //printf("Fin boucle\n");

	  printf("%f\n", resValue[nvmax]);

	  for(int i=0; i<NbActuRegle; i++){
	    //printf("%d ", utilisation[i]);
      if(utilisation[i]==0){
        free(Mainloi[i]);
        Mainloi[i]=genreglealea(nbParam, possibilites, 0.25);
        for(int j=0; j<COEURNUMBER-3; j++){
          for(int k=0; k<nbParam+2; k++){
            SousLoi[j][i][k] = Mainloi[i][k];
          }
        }
      }
    }
    
	  //printf("\n");

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
	printIA(Mainloi, NbActuRegle, nbParam, nbEcriture++, 0);
	free(allCase);
  }
  free(utilisation);
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
  float score = 0;
  for(int ite = 0; ite < NBITERMAX; ite++){
	int lastTue = -1;
	int nbMorts = 0;
  input->uti = (int*) malloc(sizeof(int)* input->nbAcRegle);
  for(int i=0; i<input->nbAcRegle; i++){
    input->uti[i]=0;
  }
  input->sc->nbPreda = 3;
  input->sc->nbProie = 10;
	input->sc->etapeDuJeu = 3;
	input->sc->modePlay = 1;
	mainTickGest(input->sc);
	for(int i = 0; i < input->sc->nbPlayer; i++){
	  input->sc->pla[i].IAType = 0;
	}
	for(int tick=0; tick<60000; tick++){
	  //Acquisition de données
	  for(int k=0; k<input->sc->nbPreda; k++){
	  

	    int * paramworld = getLoupWorld(input->sc, k, input->nbParam);
	    setIAInput(input->sc, k, paramworld, input->loi, input->nbAcRegle, input->nbParam,input->uti);

		free(paramworld);
	  
	  }
	  for(int i=0; i<input->sc->nbProie; i++){
		int * paramworld = getMoutonWorld(input->sc, input->sc->nbPreda + i, 2);//CreateTab1(Nbparam);
		setIAInput(input->sc, input->sc->nbPreda + i, paramworld, MoutonLoi, 32, 2, NULL);
	  
		free(paramworld);
	  }
	
	  mainTickGest(input->sc);
	  
	  int nbd = 0;
	  for(int i = input->sc->nbPreda; i < input->sc->nbProie+input->sc->nbPreda; i++){
		if(input->sc->pla[i].vie == 0){
		  nbd++;
		}
	  }

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
	
	if(lastTue == -1 && lastTue == 0){
	  score += 0;
	}else{
	  score += nbMorts + 1.0/(lastTue+2);
	}
  }
  input->res = score;
  return NULL;
}





int * genreglealea(int Nbparam, int * possible, float probamu){
  //printf("p : %d\n", (Nbparam + 2));
  int * result = (int *)malloc(sizeof(int) * (Nbparam + 2));
  if(result == NULL){
	printf("O connais le pb\n");
  }
  for(int i = 0; i < Nbparam ; i++){
	float proba = (rand()%100)/100.0;
	if(proba < probamu){
	  result[i] = rand()%possible[i];
	}else{
	  result[i] = -1;
	}
  }

  result[Nbparam]=rand()%possible[Nbparam];
  result[Nbparam+1]=rand()%possible[Nbparam+1] + 1;
  return(result);
}



void printIA(int **Mainloi, int nbregles, int nbParam ,int nbEcriture, int type){
  char name[28];
  if(type == 0){
    sprintf(name, "Ressources/IALoup%d.txt", nbEcriture);
  }else if(type == 1){
    sprintf(name, "Ressources/IABobble%d.txt", nbEcriture);
  }else if(type == 2){
    sprintf(name, "Ressources/IA2V2Bobble%d.txt", nbEcriture);
  }else if(type == 3){
    sprintf(name, "Ressources/IA4VBobble%d.txt", nbEcriture);
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
  
  input->uti = (int **)malloc(sizeof(int *) * 4);
  for(int i = 0; i < 4; i++){
    input->uti[i] = (int*)malloc(sizeof(int)*input->nbregle);
  }

  float *score =(float *)malloc(sizeof(float) * nbIA);
  for(int i = 0; i < nbIA; i++){
    score[i] = 0;
  }


  if(input->mode != 2){
	for(int i = 0; i < nbIA-1; i++){
	  for(int j = i+1; j < nbIA; j++){

		for(int ite = 0; ite < NBMATCH; ite++){
		  if(input->mode == 0){
			input->sc->nbPlayer = 2;  
		  }else{
			input->sc->nbPlayer = 4;  
		  }
		  input->sc->maxVie = 1;
		  input->sc->etapeDuJeu = 3;
		  input->sc->modePlay = 0;
		  mainTickGest(input->sc);
		  if(input->mode == 1){
			input->sc->pla[0].equipe = 0;
			input->sc->pla[1].equipe = 0;
			input->sc->pla[2].equipe = 1;
			input->sc->pla[3].equipe = 1;
		  }
		  
		  for(int k = 0; k < input->sc->nbPlayer; k++){
			input->sc->pla[k].IAType = 0;
		  }
		
		  for(int tick=0; tick<60000; tick++){
			//Acquisition de données
			//printf("%d debut\n", tick);

			if(input->mode == 0){
			  int * paramworld = getBooble1v1World(input->sc, 0, input->nbparam);
			  setIAInput(input->sc, 0, paramworld, input->lois[i], input->nbregle, input->nbparam, input->uti[i]);
			  free(paramworld);

			  //printf("milieu\n");
			  // dist adv, dir adv, dist bon, dir bon, dist bon:adv ,dist tn, dir tn + 16 densités
	  
			  paramworld = getBooble1v1World(input->sc, 1, input->nbparam);
			  setIAInput(input->sc, 1, paramworld, input->lois[j], input->nbregle, input->nbparam, input->uti[j]);
			  free(paramworld);
			}else{
			  int * paramworld = getBooble2vWorld(input->sc, 0, input->nbparam, 1);
			  setIAInput(input->sc, 0, paramworld, input->lois[i], input->nbregle, input->nbparam, input->uti[i]);
			  free(paramworld);
			  paramworld = getBooble2vWorld(input->sc, 1, input->nbparam, 1);
			  setIAInput(input->sc, 1, paramworld, input->lois[i], input->nbregle, input->nbparam, input->uti[i]);
			  free(paramworld);

			  //printf("milieu\n");
			  // dist adv, dir adv, dist bon, dir bon, dist bon:adv ,dist tn, dir tn + 16 densités
	  
			  paramworld = getBooble2vWorld(input->sc, 2, input->nbparam, 1);
			  setIAInput(input->sc, 2, paramworld, input->lois[j], input->nbregle, input->nbparam, input->uti[j]);
			  free(paramworld);
			  paramworld = getBooble2vWorld(input->sc, 3, input->nbparam, 1);
			  setIAInput(input->sc, 3, paramworld, input->lois[j], input->nbregle, input->nbparam, input->uti[j]);
			  free(paramworld);
			}

			//printf("fin\n");
	  
			mainTickGest(input->sc);
			if(input->sc->etapeDuJeu == 5){
			  tick = 100000000;
			}
		  }

		  if(input->mode == 0){
			if(input->sc->pla[0].vie == 0){
			  score[i] -= 1;
			  score[j] += 3;
			}else if(input->sc->pla[1].vie == 0){
			  score[i] += 3;
			  score[j] -= 1;
			}
		  }else if(input->mode == 1){
			//tuer +1 mort -1 win +1
			score[i] += input->sc->pla[0].kill + input->sc->pla[1].kill + ((input->sc->pla[2].vie == 0 && input->sc->pla[3].vie == 0)?3:0) -1+input->sc->pla[0].vie -1 +input->sc->pla[1].vie;
			score[j] += input->sc->pla[2].kill + input->sc->pla[3].kill + ((input->sc->pla[0].vie == 0 && input->sc->pla[1].vie == 0)?3:0) -1+input->sc->pla[2].vie -1 +input->sc->pla[3].vie;
		  }
		
		  input->sc->etapeDuJeu = 12;
		  mainTickGest(input->sc);
	
		}
	  }
	}
  }else{
	int mort[4];
	for(int ite = 0; ite < NBMATCH*4; ite++){
	  mort[0] = -1;
	  mort[1] = -1;
	  mort[2] = -1;
	  mort[3] = -1;
	  int nbMort = 0;
	  input->sc->nbPlayer = 4;  	  
	  input->sc->maxVie = 1;
	  input->sc->etapeDuJeu = 3;
	  input->sc->modePlay = 0;
	  mainTickGest(input->sc);
	  for(int k = 0; k < input->sc->nbPlayer; k++){
		input->sc->pla[k].IAType = 0;
	  }
	  for(int tick=0; tick<60000; tick++){
		//Acquisition de données
		//printf("%d debut\n", tick);
		int * paramworld = getBooble2vWorld(input->sc, 0, input->nbparam, 2);
		setIAInput(input->sc, 0, paramworld, input->lois[0], input->nbregle, input->nbparam, input->uti[0]);
		free(paramworld);
		paramworld = getBooble2vWorld(input->sc, 1, input->nbparam, 2);
		setIAInput(input->sc, 1, paramworld, input->lois[1], input->nbregle, input->nbparam, input->uti[1]);
		free(paramworld);

		//printf("milieu\n");
		// dist adv, dir adv, dist bon, dir bon, dist bon:adv ,dist tn, dir tn + 16 densités
	  
		paramworld = getBooble2vWorld(input->sc, 2, input->nbparam, 2);
		setIAInput(input->sc, 2, paramworld, input->lois[2], input->nbregle, input->nbparam, input->uti[2]);
		free(paramworld);
		paramworld = getBooble2vWorld(input->sc, 3, input->nbparam, 2);
		setIAInput(input->sc, 3, paramworld, input->lois[3], input->nbregle, input->nbparam, input->uti[3]);
		free(paramworld);
		//printf("fin\n");

		for(int i = 0; i < 4; i++){
		  if(mort[i] == -1 && input->sc->pla[i].vie == 0){
			mort[i] =nbMort++;
		  }
		}
		
		mainTickGest(input->sc);
		if(input->sc->etapeDuJeu == 5){
		  tick = 100000000;
		}
	  }


	  for(int i = 0; i < 4; i++){
		if(mort[i] == 0){
		  score[i] -= 3;	
		}else if(score[i] == 1){
		  score[i] -= 2;
		}else if(score[i] == 2){
		  score[i] -= 1;
		}else if(score[i] == -1){
		  score[i] += 1;
		}
		score[i] += input->sc->pla[i].kill;
	  }
		
	  input->sc->etapeDuJeu = 12;
	  mainTickGest(input->sc);
		  
	}
  }
  int i, j;
  for (i = 0; i < nbIA-1; i++) {
    for (j = 0; j < nbIA-i-1; j++) {
      if (score[j] < score[j+1]) {
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
    int ia, ia1, ia2, ia3, index;
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




int *** creationFils2(int *** peres, int ligne, int colonne, int nbrParametre, int nbrFils)
{
    int *** fils = createMatrice(nbrFils, colonne, nbrParametre);
    int regle1, nbre;
    int tabPere[3];
    int nbreRegle;

    for (int i = 0; i < nbrFils; i++)
    {
        nbreRegle = 0;
        nbre = 0;
        for (int j = 0; j < 3; j++)
            tabPere[j] = alea(0, ligne-1);
        
        while (nbreRegle < colonne)
        {
            regle1 = alea(0, colonne-1);
            for (int k = 0; k < nbrParametre; k++)
               fils[i][nbreRegle][k] = peres[tabPere[nbreRegle%3]][regle1][k];
            if (nbreRegle%3 == 0)
                nbre++;
            
	    nbreRegle++;
        }     
    }
    return fils;
}
