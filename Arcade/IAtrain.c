#include "IAtrain.h"
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <stdlib.h>


#define COEURNUMBER 8

void startIALoupMoutontraining(ecran * screen){
  trainLoup(screen);

  //playLoup(screen);


}


void playLoup(ecran *screen){/*
  int Nbparam = 10;
  int Nbregle = 20;
  int Nbpreda = screen->nbPreda;
  int Nbproie = screen->nbProie;
  int slow = 1;

  int ** MoutonLoi = (int **)malloc(sizeof(int*)*32);
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
    

  int **loi = CreateTab2(Nbregle, Nbparam+2);
  readIAFile("Ressources/MatIA.txt", loi);

  for(int i = 0; i < Nbregle; i++){
    for(int j = 0; j < Nbparam+2; j++){
      printf("%d ", loi[i][j]);
    }
    printf("\n");
  }

  screen->etapeDuJeu = 3;
  screen->modePlay = 1;
  mainTickGest(screen);

  for(int tick=0; tick<60000; tick++){
    //Acquisition de données
    for(int k=0; k<Nbpreda; k++){
	  
      int * paramworld = getLoupWorld(screen, k, Nbparam);//CreateTab1(Nbparam);
      setIAInput(screen, k, paramworld, loi, Nbregle, Nbparam);
	  
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

    if(screen->etapeDuJeu == 5){
      tick = 100000000;
    }
    mainTickGest(screen);
  }
  screen->etapeDuJeu = 12;*/
}

int trainLoup(ecran * screen){
  
  int Nbparam = 10;
  int NbActuRegle = 15;
  int NbMaxRegle = 30;
  int Nbpreda = screen->nbPreda;
  int Nbproie = screen->nbProie;
  
  //Structure de donnée
  float score = 0;
  int changing = 0;
  int changeValue = -1;

  int ContinueTrain = 1;
  int slow = 0;

  int possibilites[12] = {3, 8, 3, 8, 3, 8, 3, 8, 3, 8, 8, 5};
  
  //setup basic sheep IA
  int ** MoutonLoi = (int **)malloc(sizeof(int*)*32);
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
    
  int ** Mainloi = (int **)malloc(sizeof(int)*NbActuRegle);
  for(int i=0; i<NbActuRegle; i++){
	int * listalea = genreglealea(Nbparam, possibilites);
	Mainloi[i] = listalea;
  }
  

  int ***SousLoi = (int ***)malloc(sizeof(int **)*(COEURNUMBER-3));
  for(int k = 0; k < (COEURNUMBER - 3); k++){
	SousLoi[k] = (int **)malloc(sizeof(int)*NbActuRegle);
	for(int i=0; i<NbActuRegle; i++){
	  int * listalea = genreglealea(Nbparam, possibilites);
	  Mainloi[i] = listalea;
	}
  }

  ecran** allScreen = (ecran **)malloc(sizeof(ecran*) * (COEURNUMBER-3));
  for(int i = 1; i < (COEURNUMBER-3); i++){
	allScreen[i] = (ecran *)malloc(sizeof(ecran));
  }
  allScreen[0] = screen;

  pthread_t *allThread = (pthread_t*)malloc(sizeof(pthread_t)*(COEURNUMBER-3));
  int *threadRetour = (int*)malloc(sizeof(int)*(COEURNUMBER-3));


  while(ContinueTrain){
	int *allCase = (int*)malloc(sizeof(int) * NbActuRegle*(Nbparam+2));
	for(int i = 0; i < NbActuRegle*(Nbparam+2); i++){
	  allCase[i] = i;
	}
	for(int i = 0; i < 3*NbActuRegle*(Nbparam+2); i++){
	  int c1 = rand()%(NbActuRegle*(Nbparam+2));
	  int c2 = rand()%(NbActuRegle*(Nbparam+2));
	  int tmp = allCase[c1];
	  allCase[c1] = allCase[c2];
	  allCase[c2] = tmp;
	}

	for(int i = 0; i < NbActuRegle*(Nbparam+2); i++){

	  
	  break;
	  /*	  
			  pthread_t threadBoucleDesTicks;
			  int RetourDuThreadDesTicks = pthread_create(&threadBoucleDesTicks, NULL, BouclePrincipaleDesTicks,  screen);
			  if(RetourDuThreadDesTicks){
			  end_sdl(1, "", *screen);
			  }*/


	  
	}
	


	
	free(allCase);
	break;
  }
  
  

  
  /*for(int i = 0; i < NbActuRegle; i++){
	for(int j = 0; j < Nbparam+2; j++){
	  printf("%d ", loi[i][j]);
	}
	printf("\n");
  }
  printf("Fin de la matrice\n");*/
  
  
  
  

	/*
	
	  
	  for(int nbiter = 0; nbiter <= maxIter; nbiter++){
      int lastTue = -1;
      int nbMorts = 0;
      screen->etapeDuJeu = 3;
      screen->modePlay = 1;
      mainTickGest(screen);
      for(int tick=0; tick<60000; tick++){
	  //Acquisition de données
	  for(int k=0; k<Nbpreda; k++){
	  
	  int * paramworld = getLoupWorld(screen, k, Nbparam);//CreateTab1(Nbparam);
	  setIAInput(screen, k, paramworld, BDDregle[0], Nbregle, Nbparam);
	  
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
	      tick = 1000000;
	      maxIter = nbiter-1;
	      //	      SDL_FlushEvent(SDL_KEYDOWN);
	    }else if(event.key.keysym.sym == SDLK_SPACE){
	      slow = !slow;
	    }break;
	  default:break;
	  }  
	}
	if(slow){
	  SDL_Delay(1);
	}
	
	int nbd = 0;
	for(int i = Nbpreda; i < Nbproie+Nbpreda; i++){
	  if(screen->pla[i].vie == 0){
	    nbd++;
	  }
	}
	if(nbd != nbMorts){
	  nbMorts = nbd;
	  lastTue = nbiter;
	}
        if(screen->etapeDuJeu == 5){
	  tick = 100000000;
	}
        mainTickGest(screen);
      }

      if(lastTue == -1){
	score[0] += 0;
      }else{
	score[0] += nbMorts + 1.0/lastTue;
      }

      if(nbiter %3 == 0){
	if(score[0] >= score[1]){
	  BDDregle[1][rdregle][rdparam] = BDDregle[0][rdregle][rdparam];
	  score[1] = score[0];
	  score[0] = 0;
	}else{
	  BDDregle[0][rdregle][rdparam] = BDDregle[1][rdregle][rdparam];
	  score[0] = 0;
	}

	if((actualPoss > 2 && (rdparam == 0 || rdparam == 2 || rdparam == 4 || rdparam == 6 || rdparam == 8)) || (actualPoss > 7 && (rdparam == 1 || rdparam == 3 || rdparam == 5 || rdparam == 7 || rdparam == 9 || rdparam == 10)) || (actualPoss > 6 && (rdparam == 11))){
	  rdparam = rand()%(Nbparam+2);
	  rdregle = rand()%(Nbregle);
	  actualPoss = -1;
	  if(rdparam == 11){
	    actualPoss = 1;
	  }
	}
	BDDregle[0][rdregle][rdparam] = actualPoss++;
      
      }
      screen->etapeDuJeu = 12;
    }

    
    for(int i = 0; i < Nbregle; i++){
      for(int j = 0; j < Nbparam+2; j++){
	printf("%d ", BDDregle[0][i][j]);
      }
      printf("\n");
    }
  */


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


  
    return 0;    
}


int * genreglealea(int Nbparam, int * possible){
  int * result = (int *)malloc(sizeof(int) * Nbparam +2);

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

// int dist(ecran * screen, int self, int other){
//     int dist = -1;
//     float diffx = (screen->pla[other].pos.x - screen->pla[self].pos.x);
//     if(diffx > 50){diffx -= 50;}
//     float diffy = screen->pla[other].pos.y - screen->pla[self].pos.y;
//     if(diffy > 50){diffy -= 50;}
//     float valdist = sqrtf(carre(diffx)+carre(diffy));
//     if(valdist<15) {dist = 0;}
//     else if(valdist<40) {dist = 1;}
//     else {dist = 2;}
//     return dist;
// }


void readIAFile(char *name, int **tab){
  FILE* f = fopen(name, "r");
  for(int i = 0; i < 20; i++){
    fscanf(f, "%d %d %d %d %d %d %d %d %d %d %d\n", &(tab[i][0]),  &(tab[i][1]),  &(tab[i][2]),  &(tab[i][3]),  &(tab[i][4]),  &(tab[i][5]), &(tab[i][6]), &(tab[i][7]), &(tab[i][8]), &(tab[i][9]), &(tab[i][10]));
  }
  fclose(f);
}

