#include "ticksGest.h"


void mainTickGest(ecran *screen){
  if(screen->etapeDuJeu == 2){
    
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

float ** createTab() {
  float ** Tab = (float **) malloc(sizeof(float *)*N); // alloue le tableau 1D
  if(Tab == NULL) errorInCreate2D();                // appelle fonction qui envoie message + quit prog si NULL (malloc impossible)
  for(int i = 0; i < N; i++) {
    Tab[i] = (float *) malloc(sizeof(float)*N);       // alloue le tab2D
    if(Tab[i] == NULL) {                            // free proprement + appelle fonction qui envoie message + quit prog si NULL (malloc impossible)
      for(int j = 0; j < i; j++) {
        free(Tab[j]); 
        Tab[j] = NULL;
      }
      free(Tab);
      errorInCreate2D();
    }
    else {
      for(int j = 0;j<N;j++){
        Tab[i][j]=0;
      }
    }
  }
  return Tab;
}


float **TransfGraphCompl(float ** G){
  float ** GCompl = createTab();
  for k in range(N){
    for i in range(N){
      for j in range(N){
        if(k==0){
          if(G[i][j]==0){ GC[i][j]=INFINI;}
          else {GCompl[i][j]=G[i][j]}
        }
        else{
          GCompl[i][j]=min(GC[i][j],GC[i][k-1] + GC[k-1][j]);
        }
      }
    }
  }
  return(GCompl);
}

float TestSolution(liste * Soluce,float ** GC){
  float poids = 0;
  int i = 0;
  int j = 0;
  for l in range(N-1){
    i = Soluce[l];
    j = Soluce[l+1];
    poids += GC[i][j]
  }
  poids += GC[N][0];

  return(poids);
}

liste * Randlist(int N,int nbliste){

}

liste AlgoGene(float ** GC){

}
