#include "IAreflexion.h"



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

  /*for(int i = 0; i < Nbparam; i++){
	printf("%d", paramworld[i]);
  }
  printf("\n");*/

  
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

    if(diffx > 50){orient = (orient+4)%8;}
    else if(diffy > 50){orient = (orient+4)%8;}
    
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

    if(diffx > 50){orient = (orient+4)%8;}
    else if(diffy > 50){orient = (orient+4)%8;}
    
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
