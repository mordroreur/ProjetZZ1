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
    rechfourmi(&(screen->niveau),10,10,&GC, screen->niveau.startCase-1,4);
    resosimple(&screen->niveau, &GC);
    printf("FINIIIII\n");
    LL_afficheListe(screen->niveau.reso);


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

void resosimple(graphe *G, graphe * GC){
  liste * resosimple = LL_create();
  GC->arretes = TransfGraphCompl(G);
  int N = G->nbSommets;
  int t = LL_size(GC->reso);
  liste * cheminit = LL_create();
  cheminit = rechemin(G,GC,N-1,0);
  int tint = LL_size(cheminit);
  for(int k=0; k<tint; k++){
    LL_add_last(resosimple,LL_get_n(cheminit,k));
  }
  for(int i=0; i<t; i++){
    liste * cheminit2 = LL_create();
    cheminit2 = rechemin(G,GC,i,i+1);
    int tint2 = LL_size(cheminit);
    for(int j=0; j<tint2; j++){
      LL_add_last(resosimple,LL_get_n(cheminit2,j));
    }
    LL_free(cheminit2);
  }
  G->reso = resosimple;
}


liste * rechemin(graphe * G,graphe * GC, int deb, int fin){
  liste * chemint = LL_create();
  if(G->arretes[deb][fin]){
    LL_add_first(chemint,fin);
    return(chemint);
  }
  else{
    int pos = -1;
    liste * Tabou = LL_create();
    int N = G->nbSommets;
    for(int i=0; i<N; i++){
      if(G->arretes[deb][i] == 0){
        LL_add_first(Tabou,i);
      }
    }
    liste * sommetvois = listsommet(GC, deb, Tabou);
    int V = LL_size(sommetvois);
    for(int k=0; k<V; k++){
      pos = LL_get_n(sommetvois,k);
      liste * chemintbis = LL_create();
      chemintbis = (rechemin(G,GC,pos,fin));
      for(int j=0; j<V; j++){
        LL_add_last(chemint, LL_get_n(chemintbis,j));
        LL_add_first(chemint,deb);
        return(chemint);
      }
      LL_free(chemintbis);
    }
  }
  return(chemint);
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
  for(int l = 0; l<N-1; l++){
    i = LL_get_n(solu,l);
    j = LL_get_n(solu,l+1);
    poids += GC->arretes[i][j];
  }
  int fin = LL_get_n(solu,N-1);
  int deb = LL_get_n(solu,0);
  poids += GC->arretes[fin][deb];
  return(poids);
}

float rechfourmi(graphe * G, int nbfourmi, int nbjour, graphe * GC, int pos, int dureepherom){
  int N = G->nbSommets;  
  float ** pheromtmp = CreateTab(N,1);
  GC->arretes = TransfGraphCompl(G);
  GC->nbSommets = N;
  float ** pheromone = CreateTab(N,dureepherom);
   
  for(int i=0; i<nbjour; i++){
    for(int k=0; k<nbfourmi; k++){
      choixchemin(GC, pheromone, pos, pheromtmp);
    }
    majpheromone(GC, pheromone, dureepherom, pheromtmp);
    
  }
  return(TestSolution(GC->reso, GC));
}

void choixchemin(graphe * GC, float ** pheromone, int pos, float ** pheromtmp){
  
  int N = GC->nbSommets;
  
  int Sommet = -1;
  liste *Tabou = LL_create();
  liste *solutemp = LL_create();
  for(int k=0; k<N; k++){
    Sommet = choixsommet(GC,pos,pheromone,Tabou);
    LL_add_first(Tabou,Sommet);
    LL_add_first(solutemp,Sommet);
    pos = Sommet;
  }

  addpheromone(GC, solutemp, pheromtmp);
  if(!LL_size(GC->reso)){
    LL_free(GC->reso);
    GC->reso = solutemp;
    solutemp = NULL;
  }
  else {
    float poidstemp = TestSolution(solutemp,GC);
    float poidact = TestSolution(GC->reso,GC);
    if(poidstemp<poidact){
      LL_free(GC->reso);
      GC->reso = solutemp;
      solutemp = NULL;
    }
  }
  if(solutemp != NULL){
    free(solutemp);
  }
  if(Tabou != NULL){
    free(Tabou);
  }
}

void majpheromone(graphe * GC, float **pheromone, int dureepherom, float ** pheromtmp){
  int N = GC->nbSommets;
  for(int i=0; i<N; i++){
    for(int k=0; k<dureepherom-1; k++){
      pheromone[i][k]=pheromone[i][k+1];
    }
    pheromone[i][dureepherom] = pheromtmp[i][0];
  }
}

void addpheromone(graphe * GC, liste *solutemp, float ** pheromtmp){
  
  int N = GC->nbSommets;
  float poidstemp = TestSolution(solutemp,GC);
  for(int i=0; i<N; i++){
    pheromtmp[i][0] += 1/poidstemp;
  }
}

int choixsommet(graphe * GC, int pos, float ** pheromone, liste *Tabou){
  liste *cheminposs = listsommet(GC,pos,Tabou);
  listef probasommet = probasommetposs(GC,cheminposs,pheromone);
  float choixalea = ((rand()%100 + 0.01))/100.0;
  int i = 0;
  float Sprobasommet = 0;
  while(Sprobasommet < choixalea){
    Sprobasommet += LLf_get_n(&probasommet, i);
    i++;
  }
  int tmp = LL_get_n(cheminposs,i-1);
  LL_free(cheminposs);
  LLf_free(&probasommet);
  return(tmp);
}

liste *listsommet(graphe * GC, int pos, liste* Tabou){
  int N = GC->nbSommets;
  liste *cheminposs = LL_create();
  for(int k=0; k<N; k++){
    if((k != pos) && (!LL_contains(Tabou,k))){
      LL_add_first(cheminposs,k);
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


listef probasommetposs(graphe * GC, liste *cheminposs, float ** pheromone){
  int nbchemin = LL_size(cheminposs);
  float neutre = 1.0/nbchemin;
  float Spheromchemin = 0;
  for(int i=0; i<nbchemin; i++){
    Spheromchemin += SpheromSommet(pheromone, GC->nbSommets, LL_get_n(cheminposs,i));
  }
  float moypherom = Spheromchemin/nbchemin;
  listef probasommet = LLf_create();
  for(int i=0; i<nbchemin; i++){
    LLf_add_last(&probasommet, neutre+(SpheromSommet(pheromone, GC->nbSommets, LL_get_n(cheminposs,i)) - moypherom));
  }
  return(probasommet);
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
