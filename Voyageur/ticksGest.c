#include "ticksGest.h"
#include <math.h>
#include <stdlib.h>
#define PI 3.1415

void mainTickGest(ecran *screen){
  if(screen->etapeDuJeu == 3){
    
    screen->niveau.arretes = (float **) malloc(sizeof(float*) * screen->niveau.nbSommets); // alloue le tableau principal
    if(screen->niveau.arretes == NULL) {screen->etapeDuJeu = 0; printf("MALLOC ERROR\n");}
    for(int i = 0; i < screen->niveau.nbSommets; i++) {
      screen->niveau.arretes[i] = (float *) malloc(sizeof(float)*screen->niveau.nbSommets);// alloue les sous tableaux
      if(screen->niveau.arretes[i] == NULL) {//cas d'erreur on libere tout ce qui est alloue
	for(int j = 0; j < i; j++) {
	  free(screen->niveau.arretes[j]); 
	  screen->niveau.arretes[j] = NULL;
	}
	free(screen->niveau.arretes);
	printf("MALLOC ERROR\n");
	screen->etapeDuJeu = 0;
      }else{
	for(int j = 0; j < screen->niveau.nbSommets; j++) {
	  screen->niveau.arretes[i][j] = 0;
	}
      }
    }
    generateTree(&(screen->niveau), 0, screen->niveau.nbSommets-1);
    generateGraphe(&(screen->niveau), screen->niveau.proba);
    
    positionneGraphe(&(screen->niveau));

    changeArreteSize(&(screen->niveau));


    /*
    for(int i = 1; i < screen->niveau.nbSommets; i++){
      for(int j = 1 ;j < screen->niveau.nbSommets; j++){
        screen->niveau.arretes[i][j] = 0;
      }
    }
    */
    /*    
    for(int i = 0; i < screen->niveau.nbSommets; i++){
      for(int j = 0 ;j < screen->niveau.nbSommets; j++){
	printf("%f  ", screen->niveau.arretes[i][j]);
      }
      printf("\n");
      }
    */
    
    screen->etapeDuJeu = 4;
    
  }else if(screen->etapeDuJeu == 4){
    
    pthread_t chercheMinGraphe;
    int RetourDuThreadDuMin = pthread_create(&chercheMinGraphe, NULL, ChercheMinGraphe,  screen);
    if(!RetourDuThreadDuMin){
      screen->etapeDuJeu = 5;
    }
  }
}


void *ChercheMinGraphe(void *param){
    ecran *screen = param;

    printf("test\n");

    return NULL;
}















void generateTree(graphe* g, int bas, int haut){
  if(bas < haut){
    int k = rand()%(haut-(bas+1)+1)+(bas+1);
    g->arretes[bas][bas+1] = 1;
    g->arretes[bas+1][bas] = 1;
    if(k+1 <= haut){
      g->arretes[bas][k+1] = 1;
      g->arretes[k+1][bas] = 1;
    }
    generateTree(g,bas+1, k);
    generateTree(g, k+1, haut);
  }
}

void generateGraphe(graphe* g, float proba){
  for(int i = 0; i < g->nbSommets; i++){
    for(int j = i+1; j < g->nbSommets; j++){
      if(rand()%1000000 < proba*1000000){
	g->arretes[i][j] = 1;
	g->arretes[j][i] = 1;
      }
    }
  }
}


void changeArreteSize(graphe * g){
  for(int i = 0; i < g->nbSommets; i++){
    for(int j = i; j < g->nbSommets; j++){
      if(g->arretes[i][j] > 0){
	g->arretes[i][j] = sqrt( pow(g->Sommets[i][0] + g->Sommets[j][0], 2) + pow(g->Sommets[i][1] + g->Sommets[j][1], 2));
	g->arretes[j][i] = g->arretes[i][j];
      }
    }
  }
}



void positionneGraphe(graphe * g){

  g->Sommets = (int **) malloc(sizeof(int *) * g->nbSommets);
  for(int i = 0; i < g->nbSommets; i++){
    g->Sommets[i] = (int *) malloc(sizeof(int) * 2);
  }

  if(rand()%100 < 10){
    for(int i = 0; i < g->nbSommets; i++){
      g->Sommets[i][0] = 50 + cos(((360.0/g->nbSommets * i) * 2 * PI)/360)*40;
      g->Sommets[i][1] = 50 + sin(((360.0/g->nbSommets * i) * 2 * PI)/360)*40;
    }
  }else{
    int veux = 9*g->nbSommets;
    int x = ceil(sqrt(veux));
    int y = x;
    while(x*(y-1) >= veux){
      y--;
    }

    int freeCase = x*y;
    int * cases = (int *)malloc(sizeof(int) * freeCase);
    if(cases == NULL){exit(0);}

    for(int i = 0; i < freeCase; i++){cases[i] = 0;}
    
    for(int i = 0; i < g->nbSommets; i++){
      int wich = rand()%freeCase;
      int ou = 0;
      int la = 0;
      while(ou != wich){
	if(cases[la] == 0){
	  ou++;
	}
	la++;
	if(la > x*y){
	  printf("C la full merde\n");
	}
      }
      g->Sommets[i][0] = (floor(la%x) * 100/x) + (rand() % (100000/x))/1000.0;
      g->Sommets[i][1] = (floor((float)(la)/x) * 100/y) + (rand() % (100000/y))/1000.0;



      for(int j = -1; j < 2; j++){
	for(int k = -1; k < 2; k++){
	  if(la+(k*x)+j < x*y && la+(k*x)+j >= 0 && cases[la+(k*x)+j] == 0){
	    cases[la+(k*x)+j] = 1;
	    freeCase--;
	  }
	}
      }
    }

    
    float minx = g->Sommets[0][0];
    float maxx = g->Sommets[0][0];
    float miny = g->Sommets[0][1];
    float maxy = g->Sommets[0][1];
    
    for(int i = 1; i < g->nbSommets; i++){
      if(minx > g->Sommets[i][0]){
	minx = g->Sommets[i][0];
      }else if(maxx < g->Sommets[i][0]){
	maxx = g->Sommets[i][0];
      }

      if(miny > g->Sommets[i][1]){
	miny = g->Sommets[i][1];
      }else if(maxy < g->Sommets[i][1]){
	maxy = g->Sommets[i][1];
      }
    }

    float decalageX = 50-((maxx+minx)/2);
    float decalageY = 50-((maxy+miny)/2);

    for(int i = 0; i < g->nbSommets; i++){
      g->Sommets[i][0] += decalageX;
      g->Sommets[i][1] += decalageY;
    } 
  }
}
