#include "ticksGest.h"
#define PI 3.1415
#include <limits.h>
#include <time.h>
#include <stdlib.h>


void mainTickGest(ecran *screen){
  if(screen->etapeDuJeu == 3){

    screen->niveau.nbSommets = 9; // nilbre sommets


    screen->niveau.arretes = CreateTab(screen->niveau.nbSommets);
    generateTree(&(screen->niveau), 0, screen->niveau.nbSommets-1);
    generateGraphe(&(screen->niveau), 0.3);
    
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

float ** CreateTab(int taille){
  float ** Newtab = (float **) malloc(sizeof(float*) * taille); // alloue le tableau principal
  if(Newtab == NULL) {printf("MALLOC ERROR\n"); exit(0);}
  for(int i = 0; i < taille; i++) {
    Newtab[i] = (float *) malloc(sizeof(float)*taille);// alloue les sous tableaux
    if(Newtab[i] == NULL) {//cas d'erreur on libere tout ce qui est alloue
      for(int j = 0; j < i; j++) {
        free(Newtab[j]); 
        Newtab[j] = NULL;
      }
      free(Newtab);
      printf("MALLOC ERROR\n");
      exit(0);
    }
    else{
      for(int j = 0; j < taille; j++) {
      Newtab[i][j] = 0;
      }
    }
  }
  return(Newtab);
}

float ** TransfGraphCompl(graphe * G){
  int N = G->nbSommets;
  int INFINI = 150;
  float ** MC = CreateTab(G->nbSommets);
  for(int k=0; k<N;k++){
    for(int i=0; i<N; i++){
      for(int j=0; j<N; j++){
        if(k==0){
          if(G->arretes[i][j]==0){ MC[i][j]=INFINI;}
          else {MC[i][j]=G->arretes[i][j];}
        }
        else{
          MC[i][j]=fmin(MC[i][j],MC[i][k-1] + MC[k-1][j]);
        }
      }
    }
  }
  return(MC);
}


float TestSolution(liste solu, graphe * GC){
  float poids = 0;
  int i = 0;
  int j = 0;
  int N = LL_size(&solu);
  for(int l = 0; l<N; l++){
    i = LL_get_n(&solu,l);
    j = LL_get_n(&solu,l+1);
    poids += GC->arretes[i][j];
  }
  int fin = LL_get_n(&solu,N);
  int deb = LL_get_n(&solu,0);
  poids += GC->arretes[fin][deb];

  return(poids);
}

float rechfourmi(graphe * G, int nbfourmi){
  float ** MC = TransfGraphCompl(G);
  int N = G->nbSommets;
  graphe * GC =;
  GC->arretes = MC;
  GC->nbSommets = N;
  GC->reso = LL_create();
  float ** pheromone = CreateTab(N);
  for(int k=0; k<nbfourmi; k++){
    choixchemin(GC, pheromone);
  }
  return(TestSolution(GC->reso, GC));
}

void choixchemin(graphe * GC, float ** pheromone){
  int N = GC->nbSommets;
  int Sommet = -1;
  int pos = 0;
  liste Tabou = LL_create();
  liste solutemp = LL_create();
  for(int k=0; k<N; k++){
    Sommet = choixsommet(GC,pos,pheromone,Tabou);
    LL_add_first(&Tabou,Sommet);
    LL_add_first(&solutemp,Sommet);
    pos = Sommet;
  }
  majpheromone(GC, solutemp, pheromone);
  if(!LL_size(&(GC->reso))){
    GC->reso = solutemp;
  }
  else {
    float poidstemp = TestSolution(solutemp,GC);
    float poidact = TestSolution(GC->reso,GC);
    if(poidstemp<poidact){
      GC->reso = solutemp;
    }
  }
}

void majpheromone(graphe * GC, liste solutemp, float **pheromone){
  int N = GC->nbSommets;
  int disparition = fmin(4,GC->nbSommets);
  float poidstemp = TestSolution(solutemp,GC);
  for(int i=0; i<N; i++){
    for(int k=0; k<disparition-1; k++){
      pheromone[i][k]=pheromone[i][k+1];
    }
    pheromone[i][disparition] = 1/poidstemp;
  }
}

int choixsommet(graphe * GC, int pos, float ** pheromone, liste Tabou){
  srand( time( NULL ) );
  liste cheminposs = listsommet(GC,pos,Tabou);
  liste probasommet = probasommetposs(GC,cheminposs,pheromone);
  float choixalea = (rand()%100)/100;
  int i = 1;
  float Sprobasommet = 0;
  while(Sprobasommet < choixalea){
    Sprobasommet += LL_get_n(&probasommet, i);
    i++;
  }
  return(LL_get_n(&cheminposs,i-1));
  
}

liste listsommet(graphe * GC, int pos, liste Tabou){
  int N = GC->nbSommets;
  liste cheminposs = LL_create();
  for(int k=0; k<N; k++){
    if((k != pos) && (!LL_contains(&Tabou,k))){
      LL_add_first(&cheminposs,k);
    }
  }
  return(cheminposs);
}

float SpheromSommet(float ** pheromone, int taille, int i){
  float Spherom = 0;
  for(int k=0; k<taille; k++){
    Spherom += pheromone[i][k];
  }
  return Spherom;
}

liste probasommetposs(graphe * GC, liste cheminposs, float ** pheromone){
  int nbchemin = LL_size(&cheminposs);
  float neutre = 1/nbchemin;
  float Spheromchemin = 0;
  for(int i=0; i<nbchemin; i++){
    Spheromchemin += SpheromSommet(pheromone, GC->nbSommets, LL_get_n(&cheminposs,i));
  }
  float moypherom = Spheromchemin/nbchemin;
  liste probasommet = LL_create();
  for(int i=0; i<nbchemin; i++){
    LL_add_last(&probasommet, neutre+(SpheromSommet(pheromone, GC->nbSommets, LL_get_n(&cheminposs,i)) - moypherom));
  }
  return(probasommet);
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
