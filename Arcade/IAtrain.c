#include "IAtrain.h"
#include <SDL2/SDL_keycode.h>
#include <stdio.h>



void startIAtraining(ecran * screen){
  trainLoup(screen);
  //playLoup(screen);
    // printf("IA entrainée\n");
    // generationAlea
    // for i in key
    //     ecran *tournoi1;
    //     tournoi1->etapeDuJeu = 3
    //     tournoi1->modePlay = 1
    //     ticksGest(tournois1);
    //     for(j in nbIter):
    //         IA.inserInput;
    //         tournoi1->pla[0-2 = preda, 3-13 : proi].input[0 = G, 1 = h, 2...] = 0
    //         tournoi1->pla[0].input[0] = 1;
    //         tournoi1->pla[0].input[3] = 1;
    //         tournoi1->pla[0].input[1] = 0;
    //         tournoi1->pla[0].input[2] = 0;
    //         ticksGest(tournois1);
    //         if(tournoi1->etapeDuJeu != 4 ){
    //             on fini
    //         }
}


void playLoup(ecran *screen){
  int Nbparam = 10;
  int Nbregle = 20;
  int Nbpreda = 3;
  int Nbproie = 10;
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
      case SDL_KEYDOWN:
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
  screen->etapeDuJeu = 12;
}

int trainLoup(ecran * screen){
  int Nbparam = 10;
    int Nbregle = 20;
    int Nbloi = 2;
    int Nbpreda = 3;
    int Nbproie = 10;
    //Structure de donnée
    float score[2] = {0, 0};
    int rdparam = 0;
    int rdregle = 0;
    int actualPoss = 200;
    int maxIter = 100000;
    int slow = 0;

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
    

    
    int *** BDDregle = CreateTab3(Nbloi,Nbregle,Nbparam);
    for(int k=0; k<Nbloi; k++){
      int ** loi = CreateTab2(Nbregle,Nbparam);
      for(int i=0; i<Nbregle; i++){
	int * listalea = genreglealea(Nbparam);
	loi[i] = listalea;
      }
      BDDregle[k] = loi;
    }

    

    
    for(int i = 0; i < Nbregle; i++){
      for(int j = 0; j < Nbparam+2; j++){
	BDDregle[1][i][j] = BDDregle[0][i][j];
      }
    }

    
    for(int i = 0; i < Nbregle; i++){
      for(int j = 0; j < Nbparam+2; j++){
	printf("%d ", BDDregle[0][i][j]);
      }
      printf("\n");
    }
    printf("Fin de la matrice\n");

    
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
	  case SDL_KEYDOWN:
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
    
    return 0;    
}

    



int * CreateTab1(int Nbparam){
    int * Newtab = (int *) malloc(sizeof(int) * Nbparam);
    if(Newtab == NULL) {printf("MALLOC ERROR\n"); exit(0);}
    else{
        for(int j = 0; j < Nbparam; j++) {
        Newtab[j] = 0;
        }
    }
    return(Newtab);
}


int ** CreateTab2(int Nbregle, int Nbparam){
  int ** Newtab = (int **) malloc(sizeof(int*) * Nbregle); 
  if(Newtab == NULL) {printf("MALLOC ERROR\n"); exit(0);}
  for(int i = 0; i < Nbregle; i++) {
    Newtab[i] = (int *) malloc(sizeof(int)*Nbparam);
    if(Newtab[i] == NULL) {
      for(int j = 0; j < i; j++) {
        free(Newtab[j]); 
        Newtab[j] = NULL;
      }
      free(Newtab);
      printf("MALLOC ERROR\n");
      exit(0);
    }
    else{
      for(int j = 0; j < Nbparam; j++) {
      Newtab[i][j] = 0;
      }
    }
  }
  return(Newtab);
}

int *** CreateTab3(int Nbloi, int Nbregle, int Nbparam){
  int *** map;
  map = (int ***) malloc(sizeof(int **)*Nbloi);
  if(!map) {printf("MALLOC ERROR\n"); exit(0);} 
  for(int i = 0 ; i < Nbloi; i++){
    map[i] = (int **) malloc(sizeof(int *)*Nbregle);
    if(!map[i]) {               
      for(int l = 0; l < i; l++) { free(map[l]); map[l] = NULL; }
      free(map); map = NULL;
      printf("MALLOC ERROR\n"); exit(0);
    }
     for(int j = 0; j<Nbregle; j++) {
        map[i][j] = (int *) malloc(sizeof(int) * Nbparam);
        if(!map[i][j]) {  
          for(int m = 0; m < j; m++) { free(map[i][m]); map[i][m] = NULL; }
          for(int n = 0; n < i; n++) { free(map[n]); map[n] = NULL; }
          free(map); map = NULL;
          printf("MALLOC ERROR\n");
          exit(0);
        }
    }
  }
  return map ;
}



int * genreglealea(int Nbparam){
    int * listalea = CreateTab1(Nbparam+2);
    for(int i=0; i<Nbparam; i+=2){
        float proba = (rand()%100)/100.0;
        if(proba<0.25){
            listalea[i]=(rand()%3); //a modifier
        }
        else{
            listalea[i]=-1;
        }
    }
    for(int j=1; j<Nbparam; j+=2){
        float proba = (rand()%100)/100.0;
        if(proba<0.25){
            listalea[j]=(rand()%8); //a modifier
        }
        else{
            listalea[j]=-1;
        }
    }
    listalea[Nbparam]=(rand()%9)-1;
    listalea[Nbparam+1]=rand()%5 + 1;
    return(listalea);
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


int distobj(ecran * screen, int self, int other){
    int dist = -1;
    float diffx = screen->tbObjet[other].pos.x - screen->pla[self].pos.x;
    if(diffx > 50){diffx -= 50;}
    float diffy = screen->tbObjet[other].pos.y - screen->pla[self].pos.y;
    if(diffy > 50){diffy -= 50;}
    float valdist = sqrtf(carre(diffx)+carre(diffy));
    if(valdist<15) {dist = 0;}
    else if(valdist<40) {dist = 1;}
    else {dist = 2;}
    return dist;
}

float carre(float x){
    return x*x;
}

int orient(ecran * screen, int self, int other){
    float diffx = screen->pla[other].pos.x - screen->pla[self].pos.x;
    float diffy = screen->pla[other].pos.y - screen->pla[self].pos.y;
    int orient = -1;
    float theta = 0.0;
    float pi = 3.14159;
    if(diffx==0){
        if(diffy>0){orient=5;}
        else if(diffy<0){orient=-1;}
    }
    else if(diffx>0){
        theta = atanf(diffy/diffx);
        if((theta>(2*pi)/6)){
            orient = 0;
        }
        if((theta>(pi)/6) && (theta<=(2*pi/6))){
            orient = 1;
        }
        if((theta>(-pi)/6) && (theta<=(pi/6))){
            orient = 2;
        }
        if((theta>(-2*pi)/6) && (theta<=(-pi/6))){
            orient = 3;
        }
        if(theta<=(-2*pi)/6){
            orient = 4;
        }
    }
    else{
        theta = atanf(diffy/-diffx);
        if((theta>(2*pi)/6)){
            orient = 4;
        }
        if((theta>(pi)/6) && (theta<=(2*pi/6))){
            orient = 5;
        }
        if((theta>(-pi)/6) && (theta<=(pi/6))){
            orient = 6;
        }
        if((theta>(-2*pi)/6) && (theta<=(-pi/6))){
            orient = 7;
        }
        if(theta<=(-2*pi)/6){
            orient = 0;
        }
    }

    if(diffx > 50){orient += 4;}
    else if(diffy > 50){orient += 50;}
    
    return orient;
}

int orientobj(ecran * screen, int self, int other){
    float diffx = screen->tbObjet[other].pos.x - screen->pla[self].pos.x;
    float diffy = screen->tbObjet[other].pos.y - screen->pla[self].pos.y;
    int orient = -1;
    float theta = 0.0;
    float pi = 3.14159;
    if(diffx==0){
        if(diffy>0){orient=5;}
        else if(diffy<0){orient=-1;}
    }
    else if(diffx>0){
        theta = atanf(diffy/diffx);
        if((theta>(2*pi)/6)){
            orient = 0;
        }
        if((theta>(pi)/6) && (theta<=(2*pi/6))){
            orient = 1;
        }
        if((theta>(-pi)/6) && (theta<=(pi/6))){
            orient = 2;
        }
        if((theta>(-2*pi)/6) && (theta<=(-pi/6))){
            orient = 3;
        }
        if(theta<=(-2*pi)/6){
            orient = 4;
        }
    }
    else{
        theta = atanf(diffy/-diffx);
        if((theta>(2*pi)/6)){
            orient = 4;
        }
        if((theta>(pi)/6) && (theta<=(2*pi/6))){
            orient = 5;
        }
        if((theta>(-pi)/6) && (theta<=(pi/6))){
            orient = 6;
        }
        if((theta>(-2*pi)/6) && (theta<=(-pi/6))){
            orient = 7;
        }
        if(theta<=(-2*pi)/6){
            orient = 0;
        }
    }
    return orient;
}


int compareN(int * tab1, int* tab2, int N){
    int ret=1;
    for(int i=0; i<N; i++){
        if(tab1[i]!=tab2[i] && tab2[i]!=-1){
            ret = 0;
        }
    }
    return ret;
}

void readIAFile(char *name, int **tab){
  FILE* f = fopen(name, "r");
  for(int i = 0; i < 20; i++){
    fscanf(f, "%d %d %d %d %d %d %d %d %d %d %d\n", &(tab[i][0]),  &(tab[i][1]),  &(tab[i][2]),  &(tab[i][3]),  &(tab[i][4]),  &(tab[i][5]), &(tab[i][6]), &(tab[i][7]), &(tab[i][8]), &(tab[i][9]), &(tab[i][10]));
  }
  fclose(f);
}



int * getLoupWorld(ecran *screen, int k, int paramNb){

  int * paramworld = (int*)malloc(sizeof(int)*(paramNb));
  
  	  int p = 0;
	  /*int id = 0;
	    int disti = 100000;
	    for(int i = 0; i < screen->nbPreda; i++){
	    if(i != k){
	    if(dist(screen,k,i) < disti){
	    id = i;
	    disti = dist(screen, k, i);
	    }
	    }
	    }
	    paramworld[p++]=disti;
	    paramworld[p++] = orient(screen, k, id);*/

	  for(int i = 0; i < screen->nbPreda; i++){
	    if(i != k){
	      paramworld[p++] = dist(screen, k, i);
	      paramworld[p++] = orient(screen, k, i);
	    }
	  }
	  
	  
	  /*for(int i=0; i<Nbpreda; i+=2){
	    if(i!=k){
	    paramworld[p]=dist(screen,k,i);
	    paramworld[p+1]=orient(screen,k,i);
	    p +=2;
	    }
            }*/

	  int dis0 = dist(screen,k,screen->nbPreda);
	  int dis1 = dist(screen,k,screen->nbPreda+1);
	  int min = (dis0 < dis1)?0:1;
	  int min2 = 1-min;

	  for(int i = 2; i < screen->nbProie; i++){
	    int disi = dist(screen,k,screen->nbPreda+i);
	    if(disi < dis0){
	      min2 = min;
	      dis1 = dis0;
	      dis0 = disi;
	      min = i;
	    }else if(disi < dis1){
	      min2 = i;
	      dis1 = disi;
	    }
	  }

	  paramworld[p++]=dis0;
	  paramworld[p++]=orient(screen,k,screen->nbPreda+min);
	  paramworld[p++]=dis1;
	  paramworld[p++]=orient(screen,k, screen->nbPreda+min2);
            
	  int dism0 = distobj(screen,k,0);
	  min = 0;


	  for(int i = 1; i < screen->nbObjetsMax-screen->nbBananes; i++){
	    int disi = distobj(screen,k,i);
	    if(disi < dism0){
	      dis0 = disi;
	      min = i;
	    }
	  }
	  
	  paramworld[p++] = distobj(screen, k, min);
	  paramworld[p] = orientobj(screen,k,min);
	  
	  

	  return paramworld;

}



void setIAInput(ecran *screen, int k, int * paramworld, int **loi, int Nbregle, int Nbparam){
	  

	  //Fin acquisition de données

	  //Realisation action
	  float * regleposs = (float *)malloc(sizeof(float)*Nbregle*2);
	  for(int i=0; i<Nbregle*2; i++){
	    regleposs[i]=0;
	  }
	  float sommproba = 0;
	  float s = 1;
	  for(int i=0; i<Nbregle; i++){
	    if(compareN(paramworld,loi[i],Nbparam)){
	      regleposs[i*2]=loi[i][Nbparam];
	      regleposs[i*2+1]=loi[i][Nbparam+1];
	      sommproba += pow(loi[i][Nbparam+1], s);
	    }
	    else{
	      regleposs[i*2]=-1;
	      regleposs[i*2+1]=-1;
	    }
	  }
	  
	  int action = -1;
	  float proba = (rand()%100)/100.0;
	  int trouve = 0;
  
	  for(int i = 0; trouve == 0 && i < Nbregle; i++){
	    if(regleposs[i*2+1] != -1 && proba <= regleposs[i*2+1]/sommproba){
	      trouve = 1;
	      action =regleposs[i*2];
	    }else if(regleposs[i*2+1] != -1){
	      proba -= regleposs[i*2+1]/sommproba;
	    }
	  }
	  free(regleposs);


	  	  //printf("action : %d\n", action);
	  switch(action){
	  case 0:
	    screen->pla[k].input[0]  = 0;
	    screen->pla[k].input[1]  = 1;
	    screen->pla[k].input[2]  = 0;
	    screen->pla[k].input[3]  = 0;
	    break;
	  case 1:
	    screen->pla[k].input[0]  = 0;
	    screen->pla[k].input[1]  = 1;
	    screen->pla[k].input[2]  = 1;
	    screen->pla[k].input[3]  = 0;
	    break;
	  case 2:
	    screen->pla[k].input[0]  = 0;
	    screen->pla[k].input[1]  = 0;
	    screen->pla[k].input[2]  = 1;
	    screen->pla[k].input[3]  = 0;
	    break;
	  case 3:
	    screen->pla[k].input[0]  = 0;
	    screen->pla[k].input[1]  = 0;
	    screen->pla[k].input[2]  = 1;
	    screen->pla[k].input[3]  = 1;
	    break;
	  case 4:
	    screen->pla[k].input[0]  = 0;
	    screen->pla[k].input[1]  = 0;
	    screen->pla[k].input[2]  = 0;
	    screen->pla[k].input[3]  = 1;
	    break;
	  case 5:
	    screen->pla[k].input[0]  = 1;
	    screen->pla[k].input[1]  = 0;
	    screen->pla[k].input[2]  = 0;
	    screen->pla[k].input[3]  = 1;
	    break;
	  case 6:
	    screen->pla[k].input[0]  = 1;
	    screen->pla[k].input[1]  = 0;
	    screen->pla[k].input[2]  = 0;
	    screen->pla[k].input[3]  = 0;
	    break;
	  case 7:
	    screen->pla[k].input[0]  = 1;
	    screen->pla[k].input[1]  = 1;
	    screen->pla[k].input[2]  = 0;
	    screen->pla[k].input[3]  = 0;
	    break;
	  default:
	    screen->pla[k].input[0]  = 0;
	    screen->pla[k].input[1]  = 0;
	    screen->pla[k].input[2]  = 0;
	    screen->pla[k].input[3]  = 0;
	    break;
	  }                

}


int *getMoutonWorld(ecran *screen, int k, int paramNb){

  int * paramworld = (int*)malloc(sizeof(int)*(paramNb));
  
  int p = 0;
  
  int id = 0;
  int disti = 100000;
  for(int i = 0; i < screen->nbPreda; i++){
    if(dist(screen,k,i) < disti){
      id = i;
      disti = dist(screen, k, i);
    }
  }
  paramworld[p++]=disti;
  paramworld[p++] = orient(screen, k, id);
  return paramworld;

}
