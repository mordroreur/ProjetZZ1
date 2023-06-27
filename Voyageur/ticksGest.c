#include "ticksGest.h"
#define PI 3.1415

void mainTickGest(ecran *screen){
  if(screen->etapeDuJeu == 3){
    screen->niveau.nbSommets = 9;
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
    generateGraphe(&(screen->niveau), 0.5);
    
    screen->niveau.Sommets = (int **) malloc(sizeof(int *) * screen->niveau.nbSommets);
    for(int i = 0; i < screen->niveau.nbSommets; i++){
      screen->niveau.Sommets[i] = (int *) malloc(sizeof(int) * 2);
    }

    for(int i = 0; i < screen->niveau.nbSommets; i++){
      screen->niveau.Sommets[i][0] = 50 + cos(((360/screen->niveau.nbSommets * i) * 2 * PI)/360)*40;
      screen->niveau.Sommets[i][1] = 50 + sin(((360/screen->niveau.nbSommets * i) * 2 * PI)/360)*40;
    }


    
    /*    
    for(int i = 1; i < screen->niveau.nbSommets; i++){
      for(int j = 1 ;j < screen->niveau.nbSommets; j++){
	screen->niveau.arretes[i][j] = 0;
      }
    }
    
    for(int i = 0; i < screen->niveau.nbSommets; i++){
      for(int j = 0 ;j < screen->niveau.nbSommets; j++){
	printf("%f  ", screen->niveau.arretes[i][j]);
      }
      printf("\n");
      }*/
    
    
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
