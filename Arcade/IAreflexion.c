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

	  for(int i = 0; i < screen->nbPreda; i++)
    {
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
	  if(dis0 < dis1){
	    int tmp = dis0;
	    dis0 = dis1;
	    dis1 = tmp;
	  }
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
            
	  dis0 = distobj(screen,k,0);
	  dis1 = distobj(screen,k,1);
	  min = (dis0 < dis1)?0:1;
	  if(dis0 < dis1){
	    int tmp = dis0;
	    dis0 = dis1;
	    dis1 = tmp;
	  }
	  min2 = 1-min;

	  for(int i = 2; i < screen->nbObjetsMax-screen->nbBananes; i++){
	    int disi = distobj(screen,k,i);
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
	  
	  paramworld[p++] = dis0;
	  paramworld[p++] = orientobj(screen,k,min);
	  paramworld[p++] = dis1;
	  paramworld[p] = orientobj(screen, k, min2);
	  
	  

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
	    screen->pla[k].input[4]  = 0;
	    break;
	  case 1:
	    screen->pla[k].input[0]  = 0;
	    screen->pla[k].input[1]  = 1;
	    screen->pla[k].input[2]  = 1;
	    screen->pla[k].input[3]  = 0;
	    screen->pla[k].input[4]  = 0;
	    break;
	  case 2:
	    screen->pla[k].input[0]  = 0;
	    screen->pla[k].input[1]  = 0;
	    screen->pla[k].input[2]  = 1;
	    screen->pla[k].input[3]  = 0;
	    screen->pla[k].input[4]  = 0;
	    break;
	  case 3:
	    screen->pla[k].input[0]  = 0;
	    screen->pla[k].input[1]  = 0;
	    screen->pla[k].input[2]  = 1;
	    screen->pla[k].input[3]  = 1;
	    screen->pla[k].input[4]  = 0;
	    break;
	  case 4:
	    screen->pla[k].input[0]  = 0;
	    screen->pla[k].input[1]  = 0;
	    screen->pla[k].input[2]  = 0;
	    screen->pla[k].input[3]  = 1;
	    screen->pla[k].input[4]  = 0;
	    break;
	  case 5:
	    screen->pla[k].input[0]  = 1;
	    screen->pla[k].input[1]  = 0;
	    screen->pla[k].input[2]  = 0;
	    screen->pla[k].input[3]  = 1;
	    screen->pla[k].input[4]  = 0;
	    break;
	  case 6:
	    screen->pla[k].input[0]  = 1;
	    screen->pla[k].input[1]  = 0;
	    screen->pla[k].input[2]  = 0;
	    screen->pla[k].input[3]  = 0;
	    screen->pla[k].input[4]  = 0;
	    break;
	  case 7:
	    screen->pla[k].input[0]  = 1;
	    screen->pla[k].input[1]  = 1;
	    screen->pla[k].input[2]  = 0;
	    screen->pla[k].input[3]  = 0;
	    screen->pla[k].input[4]  = 0;
	    break;
	  case 8:
	    screen->pla[k].input[0]  = 0;
	    screen->pla[k].input[1]  = 1;
	    screen->pla[k].input[2]  = 0;
	    screen->pla[k].input[3]  = 0;
	    screen->pla[k].input[4]  = 1;
	    break;
	  case 9:
	    screen->pla[k].input[0]  = 0;
	    screen->pla[k].input[1]  = 1;
	    screen->pla[k].input[2]  = 1;
	    screen->pla[k].input[3]  = 0;
	    screen->pla[k].input[4]  = 1;
	    break;
	  case 10:
	    screen->pla[k].input[0]  = 0;
	    screen->pla[k].input[1]  = 0;
	    screen->pla[k].input[2]  = 1;
	    screen->pla[k].input[3]  = 0;
	    screen->pla[k].input[4]  = 1;
	    break;
	  case 11:
	    screen->pla[k].input[0]  = 0;
	    screen->pla[k].input[1]  = 0;
	    screen->pla[k].input[2]  = 1;
	    screen->pla[k].input[3]  = 1;
	    screen->pla[k].input[4]  = 1;
	    break;
	  case 12:
	    screen->pla[k].input[0]  = 0;
	    screen->pla[k].input[1]  = 0;
	    screen->pla[k].input[2]  = 0;
	    screen->pla[k].input[3]  = 1;
	    screen->pla[k].input[4]  = 1;
	    break;
	  case 13:
	    screen->pla[k].input[0]  = 1;
	    screen->pla[k].input[1]  = 0;
	    screen->pla[k].input[2]  = 0;
	    screen->pla[k].input[3]  = 1;
	    screen->pla[k].input[4]  = 1;
	    break;
	  case 14:
	    screen->pla[k].input[0]  = 1;
	    screen->pla[k].input[1]  = 0;
	    screen->pla[k].input[2]  = 0;
	    screen->pla[k].input[3]  = 0;
	    screen->pla[k].input[4]  = 1;
	    break;
	  case 15:
	    screen->pla[k].input[0]  = 1;
	    screen->pla[k].input[1]  = 1;
	    screen->pla[k].input[2]  = 0;
	    screen->pla[k].input[3]  = 0;
	    screen->pla[k].input[4]  = 1;
	    break;
	  default:
	    screen->pla[k].input[0]  = 0;
	    screen->pla[k].input[1]  = 0;
	    screen->pla[k].input[2]  = 0;
	    screen->pla[k].input[3]  = 0;
	    screen->pla[k].input[4]  = 0;
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

int dist(ecran * screen, int self, int other){
    int dist = -1;
    float diffx = (screen->pla[other].pos.x - screen->pla[self].pos.x);
    if(fabs(diffx) > 50){diffx = 100-fabs(diffx);}
    float diffy = (screen->pla[other].pos.y - screen->pla[self].pos.y);
    if(fabs(diffy) > 50){diffy = 100-fabs(diffy);}
    float valdist2 = (carre(diffx)+carre(diffy));
    if(valdist2<carre(20)) {dist = 0;}
    else if(valdist2<carre(40)) {dist = 1;}
    else {dist = 2;}
    return dist;
}



int distBoule(ecran * screen, int self, int other, int boulenb){
    int dist = -1;
    float diffx = (screen->pla[other].boubou[boulenb].pos.x - screen->pla[self].pos.x);
    if(fabs(diffx) > 50){diffx = 100-fabs(diffx);}
    float diffy = (screen->pla[other].boubou[boulenb].pos.y - screen->pla[self].pos.y);
    if(fabs(diffy) > 50){diffy = 100-fabs(diffy);}
    float valdist = (carre(diffx)+carre(diffy));
    if(valdist<carre(15)) {dist = 0;}
    else if(valdist<carre(40)) {dist = 1;}
    else {dist = 2;}
    return dist;
}



int distobj(ecran * screen, int self, int other){
    int dist = -1;
    float diffx = (screen->tbObjet[other].pos.x - screen->pla[self].pos.x);
    if(fabs(diffx) > 50){diffx = 100-fabs(diffx);}
    float diffy = (screen->tbObjet[other].pos.y - screen->pla[self].pos.y);
    if(fabs(diffy) > 50){diffy = 100-fabs(diffy);}
    float valdist = (carre(diffx)+carre(diffy));
    if(valdist<carre(15)) {dist = 0;}
    else if(valdist<carre(40)) {dist = 1;}
    else {dist = 2;}
    return dist;
}

float carre(float x){
    return x*x;
}

int orient(ecran * screen, int self, int other){
    float diffx = (screen->pla[other].pos.x - screen->pla[self].pos.x);
    float diffy = (screen->pla[other].pos.y - screen->pla[self].pos.y);
    int orient = -1;
    float theta = 0.0;
    float pi = 3.14159;
    if(diffx==0){
        if(diffy>0){orient=4;}
        else if(diffy<0){orient=0;}
    }
    else if(diffx>0){
        theta = atanf(diffy/diffx);
        if((theta>(2*pi)/6)){
            orient = 4;
        }
        if((theta>(pi)/6) && (theta<=(2*pi/6))){
            orient = 3;
        }
        if((theta>(-pi)/6) && (theta<=(pi/6))){
            orient = 2;
        }
        if((theta>(-2*pi)/6) && (theta<=(-pi/6))){
            orient = 1;
        }
        if(theta<=(-2*pi)/6){
            orient = 0;
        }
    }
    else if(diffx<0){
        theta = atanf(diffy/diffx);
        if((theta>(2*pi)/6)){
            orient = 0;
        }
        if((theta>(pi)/6) && (theta<=(2*pi/6))){
            orient = 7;
        }
        if((theta>(-pi)/6) && (theta<=(pi/6))){
            orient = 6;
        }
        if((theta>(-2*pi)/6) && (theta<=(-pi/6))){
            orient = 5;
        }
        if(theta<=(-2*pi)/6){
            orient = 4;
        }
    }

    if(fabs(diffx) > 50){orient = 8-orient;}
    else if(fabs(diffy) > 50){orient = (4-orient)%8;}
    
    return orient;
}



int orientBoule(ecran * screen, int self, int other, int nbBoule){
    float diffx = (screen->pla[other].boubou[nbBoule].pos.x - screen->pla[self].pos.x);
    float diffy = (screen->pla[other].boubou[nbBoule].pos.y - screen->pla[self].pos.y);
    int orient = -1;
    float theta = 0.0;
    float pi = 3.14159;
    if(diffx==0){
        if(diffy>0){orient=4;}
        else if(diffy<0){orient=0;}
    }
    else if(diffx>0){
        theta = atanf(diffy/diffx);
        if((theta>(2*pi)/6)){
            orient = 4;
        }
        if((theta>(pi)/6) && (theta<=(2*pi/6))){
            orient = 3;
        }
        if((theta>(-pi)/6) && (theta<=(pi/6))){
            orient = 2;
        }
        if((theta>(-2*pi)/6) && (theta<=(-pi/6))){
            orient = 1;
        }
        if(theta<=(-2*pi)/6){
            orient = 0;
        }
    }
    else if(diffx<0){
        theta = atanf(diffy/diffx);
        if((theta>(2*pi)/6)){
            orient = 0;
        }
        if((theta>(pi)/6) && (theta<=(2*pi/6))){
            orient = 7;
        }
        if((theta>(-pi)/6) && (theta<=(pi/6))){
            orient = 6;
        }
        if((theta>(-2*pi)/6) && (theta<=(-pi/6))){
            orient = 5;
        }
        if(theta<=(-2*pi)/6){
            orient = 4;
        }
    }

    if(fabs(diffx) > 50){orient = 8-orient;}
    else if(fabs(diffy) > 50){orient = (4-orient)%8;}
    
    return orient;
}





int orientobj(ecran * screen, int self, int other){
    float diffx = (screen->tbObjet[other].pos.x - screen->pla[self].pos.x);
    float diffy = (screen->tbObjet[other].pos.y - screen->pla[self].pos.y);
    int orient = -1;
    float theta = 0.0;
    float pi = 3.14159;
    if(diffx==0){
        if(diffy>0){orient=4;}
        else if(diffy<0){orient=0;}
    }
    else if(diffx>0){
        theta = atanf(diffy/diffx);
        if((theta>(2*pi)/6)){
            orient = 4;
        }
        if((theta>(pi)/6) && (theta<=(2*pi/6))){
            orient = 3;
        }
        if((theta>(-pi)/6) && (theta<=(pi/6))){
            orient = 2;
        }
        if((theta>(-2*pi)/6) && (theta<=(-pi/6))){
            orient = 1;
        }
        if(theta<=(-2*pi)/6){
            orient = 0;
        }
    }
    else if(diffx<0){
        theta = atanf(diffy/diffx);
        if((theta>(2*pi)/6)){
            orient = 0;
        }
        if((theta>(pi)/6) && (theta<=(2*pi/6))){
            orient = 7;
        }
        if((theta>(-pi)/6) && (theta<=(pi/6))){
            orient = 6;
        }
        if((theta>(-2*pi)/6) && (theta<=(-pi/6))){
            orient = 5;
        }
        if(theta<=(-2*pi)/6){
            orient = 4;
        }
    }

    if(fabs(diffx) > 50){orient = 8-orient;}
    else if(fabs(diffy) > 50){orient = (4-orient)%8;}
    
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



int * getNBBouleBydirOr(ecran *sc, int self, int Nbdist, int Nborient){
  int * nbBoule = (int *) malloc(sizeof(int) * Nbdist * Nborient);
  for(int i = 0; i < Nbdist * Nborient; i++){
	nbBoule[i] = 0;
  }
  for(int i = 0; i < sc->nbPlayer; i++){
	if(sc->pla[i].equipe != sc->pla[self].equipe){
	  for(int j = sc->pla[i].debBoule; j < sc->pla[i].debBoule+sc->pla[i].nbBouleActive; j++){
		if(sc->pla[i].boubou[j%100].vie >= 0){
		  nbBoule[distBoule(sc, self, i, j%100) * Nbdist + orientBoule(sc, self, i, j%100)]++;
		}
	  }
	}
  }
  return nbBoule;
}
  



float * listdensite(ecran *sc, int self, int Nbdist, int Nborient){

  float * listesurface = (float *) malloc(sizeof(float) * Nbdist);
  for(int i=0; i<Nbdist; i++){
    if(i==0){
      listesurface[i]=3.14159*carre(20.0*(i+1))/8.0;
      }
    else{
      listesurface[i]=(3.14159*carre(20.0*(i+1))/8.0) - listesurface[i-1];
    }
  }
  int * bobo = getNBBouleBydirOr(sc, self, Nbdist, Nborient);
  float * listdensite = (float *) malloc(sizeof(float) * Nbdist*Nborient);
  for(int i=0; i<Nbdist; i++){
    for(int j=0; j<Nborient; j++){
      listdensite[i*Nbdist+j]= bobo[i*Nbdist+j]/listesurface[i];
    }
  }
  free(listesurface);
  free(bobo);
  return listdensite;
}


// dist adv, dir adv, dist bon, dir bon, dist bon:adv ,dist tn, dir tn + 16 densités
int *getBooble1v1World(ecran *screen, int k, int paramNb){
  
  int * paramworld = (int*)malloc(sizeof(int)*(paramNb));
  
  int p = 0;

  paramworld[p++] = dist(screen, k, 1-k);
  paramworld[p++] = orient(screen, k, 1-k);
  
  if(screen->tbObjet[1].vie != 0){
	paramworld[p++] = distobj(screen, k, 1);
	paramworld[p++] = orientobj(screen, k, 1);
	paramworld[p++] = distobj(screen, 1-k, 1);
  }else{
	paramworld[p++] = -1;
	paramworld[p++] = -1;
	paramworld[p++] = -1;
  }

  if(screen->tbObjet[1].vie >= 0){
	paramworld[p++] = distobj(screen, k, 0);
	paramworld[p++] = orientobj(screen, k, 0);
  }else{
	paramworld[p++] = -1;
	paramworld[p++] = -1;
  }
  
  float *densi = listdensite(screen, k, 2,  8);

  for(int i = 0; i < 16; i++){
	paramworld[p++] = (densi[i]<0.1)?0:(densi[i]<0.6)?1:2;
  }

  free(densi);

  return paramworld;


  
}
