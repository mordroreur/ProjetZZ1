#include "ticksGest.h"


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
    generateGraphe(&(screen->niveau), 0, screen->niveau.nbSommets-1);



    printf("On est sortit \n");

    for(int i = 0; i < screen->niveau.nbSommets; i++){
      for(int j = 0 ;j < screen->niveau.nbSommets; j++){
	printf("%f  ", screen->niveau.arretes[i][j]);
      }
      printf("\n");
    }



    
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















void generateGraphe(graphe* g, int bas, int haut){
  if(bas < haut){
    int k = rand()%(haut-(bas+1)+1)+(bas+1);
    printf("%d  et %d == %d\n", bas+1, haut, k);
    g->arretes[bas][bas+1] = 1;
    g->arretes[bas+1][bas] = 1;
    if(k+1 <= haut){
      g->arretes[bas][k+1] = 1;
      g->arretes[k+1][bas] = 1;
    }
    generateGraphe(g,bas+1, k);
    generateGraphe(g, k+1, haut);
  }
}
