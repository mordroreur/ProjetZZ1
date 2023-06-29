#include "ticksGest.h"
#include "liste.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#define PI 3.1415
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include "listeFloat.h"


void mainTickGest(ecran *screen){
  if(screen->etapeDuJeu == 3){




    screen->niveau.arretes = CreateTab(screen->niveau.nbSommets,screen->niveau.nbSommets);
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
    

    screen->niveau.playerCase = rand()%screen->niveau.nbSommets;
    screen->niveau.startCase = screen->niveau.playerCase; 
    screen->niveau.PlayerReso = LL_create();
    LL_add_first(screen->niveau.PlayerReso, screen->niveau.playerCase);
    
    SDL_Delay(10);
    screen->etapeDuJeu = 4;
    
  }else if(screen->etapeDuJeu == 4){
    
    pthread_t chercheMinGraphe;
    int RetourDuThreadDuMin = pthread_create(&chercheMinGraphe, NULL, ChercheMinGraphe,  screen);
    if(!RetourDuThreadDuMin){
      screen->etapeDuJeu = 5;
    }
  }else if(screen->etapeDuJeu == 7){
    SDL_Delay(15);
    libererGraphe(&(screen->niveau));
    screen->etapeDuJeu = 2;
  }
}










void *ChercheMinGraphe(void *param){
    ecran *screen = param;
    graphe GC;
    GC.nbSommets=screen->niveau.nbSommets;
    GC.reso=LL_create();
    printf("ICI\n");
    rechfourmi(&(screen->niveau),&GC, 100,100,screen->niveau.startCase, 4);
    printf("LA\n");
    LL_afficheListe(GC.reso);
    
    // resosimple(&screen->niveau, &GC);
    // LL_afficheListe(screen->niveau.reso);
    printf("FINIIIII\n");
    


    //recuitsimul(&screen->niveau, &GC, 100, 0.001, 100, 20);
    //printf("FINIIIII\n");
    //LL_afficheListe(GC.reso);


    return NULL;
}


float ** CreateTab(int haut, int larg){
  float ** Newtab = (float **) malloc(sizeof(float*) * haut); // alloue le tableau principal
  if(Newtab == NULL) {printf("MALLOC ERROR\n"); exit(0);}
  for(int i = 0; i < haut; i++) {
    Newtab[i] = (float *) malloc(sizeof(float)*larg);// alloue les sous tableaux
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
      for(int j = 0; j < larg; j++) {
      Newtab[i][j] = 0;
      }
    }
  }
  return(Newtab);
}

float *** CreateTab3(int haut, int larg, int prof)  {
  float *** map;
  map = (float ***) malloc(sizeof(float **)*haut);
  if(!map) {printf("MALLOC ERROR\n"); exit(0);} 
  for(int i = 0 ; i < haut; i++){
    map[i] = (float **) malloc(sizeof(float *)*larg);
    if(!map[i]) {               
      for(int l = 0; l < i; l++) { free(map[l]); map[l] = NULL; }
      free(map); map = NULL;
      printf("MALLOC ERROR\n"); exit(0);
    }
     for(int j = 0; j<larg; j++) {
        map[i][j] = (float *) malloc(sizeof(float) * prof);
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

void resosimple(graphe *G, graphe * GC){
  int N = G->nbSommets;  
  liste * resosimple = LL_create();
  LL_add_last(resosimple,LL_get_n(GC->reso,0));
  int pos = -1;
  int arrive = -1;
  float dist = 10000.0;
  for(int i=0; i<N-1; i++){
    pos = LL_get_n(GC->reso,i);
    arrive = LL_get_n(GC->reso,i+1);
    dist = GC->arretes[pos][arrive];
    liste * voisin = LL_create();
    voisin = voisins(G,pos);
    int t = LL_size(voisin);
    for(int k=0; k<t; k++){
      int postmp = LL_get_n(voisin,k);
      int disttmp = GC->arretes[k][arrive];
      if(disttmp<dist){
        dist = disttmp;
        pos = postmp;
      }
      LL_add_last(resosimple,pos);
    }
  }
  pos = LL_get_n(GC->reso,N);
  arrive = LL_get_n(GC->reso,0);
  dist = GC->arretes[pos][arrive];
  liste * voisinf = LL_create();
  voisinf = voisins(G,pos);
  int t = LL_size(voisinf);
  for(int j=0; j<t; j++){
    int postmp = LL_get_n(voisinf,j);
    int disttmp = GC->arretes[j][arrive];
    if(disttmp<dist){
      dist = disttmp;
      pos = postmp;
    }
    LL_add_last(resosimple,pos);
  }
  G->reso = resosimple;
}

liste * voisins(graphe * G, int pos){
  int N = G->nbSommets;
  liste *voisins = LL_create();
  for(int k=0; k<N; k++){
    if(G->arretes[pos][k]){
      LL_add_first(voisins,k);
    }
  }
  return(voisins);
}



float ** TransfGraphCompl(graphe * G){
  int N = G->nbSommets;
  int INFINI = 10000;
  float ** MC = CreateTab(G->nbSommets, G->nbSommets);
  for(int k=0; k<N;k++){
    for(int i=0; i<N; i++){
      for(int j=0; j<N; j++){
        if(k==0){
          if(G->arretes[i][j]==0){ MC[i][j]=INFINI;}
          else {MC[i][j]=G->arretes[i][j];}
        }
        else if(i != j){
          MC[i][j]=fmin(MC[i][j],MC[i][k-1] + MC[k-1][j]);
        }
      }
    }
  }

  return(MC);
}


float TestSolution(liste *solu, graphe * GC){
  
  float poids = 0;
  int i = 0;
  int j = 0;
  int N = LL_size(solu);

  for(int l = 0; l<N-2; l++){
    
    i = LL_get_n(solu,l);
    j = LL_get_n(solu,l+1);
    
    poids += GC->arretes[i][j];
  }
  int fin = LL_get_n(solu,N-1);
  int deb = LL_get_n(solu,0);
  poids += GC->arretes[fin][deb];
  return(poids);
}

float rechfourmi(graphe * G, graphe * GC,int nbfourmi, int nbjour, int pos, int dureepherom){
  int N = G->nbSommets;  
  
  GC->arretes = TransfGraphCompl(G);
  
  GC->nbSommets = N;
  float *** pheromone = CreateTab3(N,N,dureepherom);
  float ** pheromtmp = CreateTab(N,N);
  
  for(int i=0; i<nbjour; i++){
    for(int k=0; k<nbfourmi; k++){
      
      choixchemin(GC, pheromone, dureepherom, pos, pheromtmp);
      
    }
    majpheromone(GC, pheromone, dureepherom, pheromtmp);
   
  }
  
  return(TestSolution(GC->reso, GC));
}

void choixchemin(graphe * GC, float *** pheromone,int dureepherom, int posdep, float ** pheromtmp){
  
  int N = GC->nbSommets;
  
  int pos = posdep;
  liste *Tabou = LL_create();
  liste *chemintemp = LL_create();
  LL_add_first(chemintemp,pos);
  LL_add_first(Tabou,pos);
  
  for(int k=0; k<N; k++){
    
    int posnext = choixsommet(GC,pos,pheromone,dureepherom,Tabou);
    if(posnext != -1){
      LL_add_first(Tabou,posnext);
      
      LL_add_last(chemintemp,posnext);
      pos = posnext;
    }
    
  }
  
  addpheromone(GC, chemintemp, pheromtmp);
    
  if(!LL_size(GC->reso)){
    LL_free(GC->reso);
    GC->reso = chemintemp;
    
    chemintemp = NULL;
  }
  else {
    float poidstemp = TestSolution(chemintemp,GC);
    float poidact = TestSolution(GC->reso,GC);
    if(poidstemp<poidact){
      LL_free(GC->reso);
      GC->reso = chemintemp;
     
      chemintemp = NULL;
    }
  }
  if(chemintemp != NULL){
    free(chemintemp);
  }
  if(Tabou != NULL){
    free(Tabou);
  }
}

void majpheromone(graphe * GC, float ***pheromone, int dureepherom, float ** pheromtmp){
  int N = GC->nbSommets;
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      for(int k=0; k<dureepherom-1; k++){
        pheromone[i][j][k]=pheromone[i][j][k+1];
      }
      pheromone[i][j][dureepherom] = pheromtmp[i][j];
    }
  }
}

float ** addpheromone(graphe * GC, liste *solutemp, float ** pheromtmp){
  float poidstemp = TestSolution(solutemp,GC);
  
  int t = LL_size(solutemp);
  int pos = -1;
  int posnext = -1;
  for(int i=0; i<t-1; i++){
    pos = LL_get_n(solutemp,i);
    posnext = LL_get_n(solutemp,i+1);
    pheromtmp[pos][posnext] += 1/poidstemp;
    
  }
  return(pheromtmp);
}

int choixsommet(graphe * GC, int pos, float *** pheromone, int dureepherom, liste *Tabou){
  liste *cheminposs = listsommet(GC,pos,Tabou);
  int tmp = -1;
 
  if(LL_size(cheminposs) != 0){
    
    listef probasommet = probasommetposs(GC,pos,cheminposs,pheromone,dureepherom);

    float choixalea = (rand()%100)/100.0;
    int i = 0;
    float Sprobasommet = 0.0;
    
    while(Sprobasommet < choixalea){
      //printf("%f\n",Sprobasommet);
      Sprobasommet += LLf_get_n(&probasommet, i);
      
      i++;
    }
    
    tmp = LL_get_n(cheminposs,i-1);
    
    LL_free(cheminposs);
    LLf_free(&probasommet);
  }
  return(tmp);
}

liste * listsommet(graphe * GC, int pos, liste* Tabou){
  int N = GC->nbSommets;
  liste *cheminposs = LL_create();
  for(int k=0; k<N; k++){
    if((k != pos) && (!LL_contains(Tabou,k))){
      LL_add_last(cheminposs,k);
    }
  }
  return(cheminposs);
}


listef probasommetposs(graphe * GC, int pos, liste *cheminposs, float *** pheromone, int dureepherom){
  
  int nbchemin = LL_size(cheminposs);
  listef probasommet = LLf_create();
  float Spoids = 0;
  int posnext = -1;
  float Sommepherom = 0.0;
  for(int k=0; k<nbchemin; k++){
    posnext = LL_get_n(cheminposs,k);
    Sommepherom = pheromij(pheromone,pos,posnext,dureepherom);
    
    Spoids += Sommepherom*(GC->arretes[pos][posnext]);
    //printf("%f\n",GC->arretes[1][2]);
    //printf("%f\n",GC->arretes[pos][posnext]);
    
  }

  for(int i=0; i<nbchemin; i++){
    posnext = LL_get_n(cheminposs,i);
    Sommepherom = pheromij(pheromone,pos,posnext,dureepherom);
    LLf_add_last(&probasommet, Sommepherom*(GC->arretes[pos][posnext])/Spoids);
  }
  return(probasommet);
}

float pheromij(float *** pheromone, int i, int j, int dureepherom){
  float valpheromij = 1;
  for(int k = 0; k<dureepherom; k++){
    valpheromij += pheromone[i][j][k];
    
  }
  return(valpheromij);
}
  
  










float recuitsimul(graphe * G, graphe * GC, float tinit, float tfin, int nbiter, int nblistinit){
  int N = G->nbSommets;
  GC->arretes = TransfGraphCompl(G);
  GC->nbSommets = N;
  liste * listedep = choixlistdep(nblistinit, GC);
  liste * listvoisin = LL_create();
  float t = tinit;
  float alpha = (tinit-tfin)/nbiter;
  for(int k=0; k<nbiter; k++){
    t = t-alpha;
    listvoisin = genlistvois(listedep, GC);
    float diffsol = TestSolution(listvoisin, GC) - TestSolution(listedep, GC);
    if(diffsol < 0){
      listedep = listvoisin;
    }
    else{
      float p = exp(-(diffsol/t));
      float floatrand = (rand()%100)/100.0;
      if(floatrand<p){
        listedep = listvoisin;
      }
    }

  }

  GC->reso = listedep;
  return(TestSolution(listedep, GC));
}



liste * choixlistdep(int nblistinit,graphe * GC){
  float poidslistdep = 1000000;
  liste * listedep = LL_create();
  for(int k=0; k<nblistinit; k++){
    liste * listtmp = genlistalea(GC);
    float poidstmp = TestSolution(listtmp, GC);
    if(poidstmp < poidslistdep){
      listedep = listtmp;
    }
  }
  return(listedep);
}


liste * genlistalea(graphe * GC){
  int N = GC->nbSommets;
  liste * listalea = LL_create();
  liste * listneutre = LL_create();
  for(int k=0; k<N; k++){
    LL_add_last(listneutre,k);
  }
  int n = LL_size(listneutre);
  while(n>0){
    int indicerand = rand()%n;
    LL_add_last(listalea,LL_get_n(listneutre,indicerand));
    LL_remove_n(listneutre,indicerand);
    n--;
  }
  return(listalea);
}

liste * genlistvois(liste * listeact, graphe * GC){
  int N = GC->nbSommets;
  int *tab = (int *)malloc(sizeof(int)*N);
  if(!tab){exit(0);}
  
  for(int i=0; i<N; i++){
    tab[i] = LL_get_n(listeact,i);
  }
  

  int rand1 = rand()%N;
  int rand2 = rand()%N;

  
  int tmp = tab[rand1];
  tab[rand1] = tab[rand2];
  tab[rand2] = tmp;
  
  liste *listvoisin = LL_create();

  for(int i = 0; i < N; i++){
    LL_add_last(listvoisin, tab[i]);
  }

  return(listvoisin);
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
	g->arretes[i][j] = sqrt( pow(g->Sommets[i][0] - g->Sommets[j][0], 2) + pow(g->Sommets[i][1] - g->Sommets[j][1], 2));
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
    free(cases);
  }
}

void libererGraphe(graphe *g){
  if(g->arretes){
    for(int i = 0; i < g->nbSommets; i++){
      free(g->arretes[i]);
    }
    free(g->arretes);
  }

  
  if(g->Sommets){
    for(int i = 0; i < g->nbSommets; i++){
      free(g->Sommets[i]);
    }
    free(g->Sommets);
    }

  LL_free(g->PlayerReso);
}
