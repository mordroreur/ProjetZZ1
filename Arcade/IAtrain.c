#include "IAtrain.h"




void startIAtraining(ecran * screen){
    testfct(screen);
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

int testfct(ecran * screen){
    int Nbparam = 10;
    int Nbregle = 100;
    int Nbloi = 30;
    int Nbpreda = 3;
    int Nbproie = 10;
    int Nbmur = screen->nbObjetsMax;
    //Structure de donnée
    int *** BDDregle = CreateTab3(Nbloi,Nbregle,Nbparam);
    for(int k=0; k<Nbloi; k++){
        int ** loi = CreateTab2(Nbregle,Nbparam);
        for(int i=0; i<Nbregle; i++){
            int * listalea = genreglealea(Nbparam);
            loi[i] = listalea;
        }
        BDDregle[k] = loi;
    }
    //Fin structure de donnée

    screen->etapeDuJeu = 3;
    screen->modePlay = 1;
    mainTickGest(screen);
    for(int tick=0; tick<60000; tick++){
        //Acquisition de données
        for(int k=0; k<Nbpreda; k++){
            int * paramworld = CreateTab1(Nbparam);
            
            int p = 0;
            for(int i=0; i<Nbpreda; i+=2){
                if(i!=k){
                    paramworld[p]=dist(screen,k,i);
                    paramworld[p+1]=orient(screen,k,i);
                    p +=2;
                }
            }

            int dis0 = dist(screen,k,Nbpreda);
            int dis1 = dist(screen,k,Nbpreda+1);
            int min = (dis0 < dis1)?0:1;
            int min2 = 1-min;

            for(int i = 2; i < Nbproie; i++){
                int disi = dist(screen,k,Nbpreda+i);
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

            paramworld[p]=dis0;
            paramworld[p+1]=orient(screen,k,Nbpreda+min);
            paramworld[p+2]=dis1;
            paramworld[p+3]=orient(screen,k,Nbpreda+min2);
            
            int dism0 = distobj(screen,k,0);
            min = 0;


            for(int i = 1; i < Nbmur; i++){
                int disi = distobj(screen,k,i);
                if(disi < dism0){
                    dis0 = disi;
                    min = i;
                }
            }
            paramworld[p+4]=-1;
            if(dis0==0){
                paramworld[p+4]=orientobj(screen,k,min);
            }

            //Fin acquisition de données

            //Realisation action
            float * regleposs = (float *)malloc(sizeof(float)*Nbregle*2);
            for(int i=0; i<Nbregle*2; i++){
                regleposs[i]=0;
            }
            float sommproba = 0;
            float s = 1;
            for(int i=0; i<Nbregle; i++){
                if(compareN(paramworld,BDDregle[1][i],Nbparam)){
                    regleposs[i*2]=BDDregle[1][i][Nbparam+1];
                    regleposs[i*2+1]=BDDregle[1][i][Nbparam+2];
                    sommproba += pow(BDDregle[1][i][Nbparam+2],s);
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
        for(int i=0; i<Nbproie; i++){
            for(int j=0; j<4;j++){
                screen->pla[i+Nbpreda].input[j]=(rand()%2);
            }
        }
        mainTickGest(screen);
    }
    screen->etapeDuJeu = 12;
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
        listalea[i]=rand()%3; //a modifier
    }
    for(int j=1; j<Nbparam; j+=2){
        listalea[j]=rand()%9; // 0=rien, 1-9 = Nord + sens horaire
    }
    listalea[Nbparam]=rand()%9;
    listalea[Nbparam+1]=rand()%5;
    return(listalea);
}

int dist(ecran * screen, int self, int other){
    int dist = -1;
    float diffx = screen->pla[other].pos.x - screen->pla[self].pos.x;
    float diffy = screen->pla[other].pos.y - screen->pla[self].pos.y;
    float valdist = sqrtf(carre(diffx)+carre(diffy));
    if(valdist<15) {dist = 0;}
    else if(valdist<40) {dist = 1;}
    else {dist = 2;}
    return dist;
}


int distobj(ecran * screen, int self, int other){
    int dist = -1;
    float diffx = screen->tbObjet[other].pos.x - screen->pla[self].pos.x;
    float diffy = screen->tbObjet[other].pos.y - screen->pla[self].pos.y;
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
            orient = 1;
        }
        if((theta>(pi)/6) && (theta<=(2*pi/6))){
            orient = 2;
        }
        if((theta>(-pi)/6) && (theta<=(pi/6))){
            orient = 3;
        }
        if((theta>(-2*pi)/6) && (theta<=(-pi/6))){
            orient = 4;
        }
        if(theta<=(-2*pi)/6){
            orient = 5;
        }
    }
    else{
        theta = atanf(diffy/-diffx);
        if((theta>(2*pi)/6)){
            orient = 5;
        }
        if((theta>(pi)/6) && (theta<=(2*pi/6))){
            orient = 6;
        }
        if((theta>(-pi)/6) && (theta<=(pi/6))){
            orient = 7;
        }
        if((theta>(-2*pi)/6) && (theta<=(-pi/6))){
            orient = 8;
        }
        if(theta<=(-2*pi)/6){
            orient = 1;
        }
    }
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
            orient = 1;
        }
        if((theta>(pi)/6) && (theta<=(2*pi/6))){
            orient = 2;
        }
        if((theta>(-pi)/6) && (theta<=(pi/6))){
            orient = 3;
        }
        if((theta>(-2*pi)/6) && (theta<=(-pi/6))){
            orient = 4;
        }
        if(theta<=(-2*pi)/6){
            orient = 5;
        }
    }
    else{
        theta = atanf(diffy/-diffx);
        if((theta>(2*pi)/6)){
            orient = 5;
        }
        if((theta>(pi)/6) && (theta<=(2*pi/6))){
            orient = 6;
        }
        if((theta>(-pi)/6) && (theta<=(pi/6))){
            orient = 7;
        }
        if((theta>(-2*pi)/6) && (theta<=(-pi/6))){
            orient = 8;
        }
        if(theta<=(-2*pi)/6){
            orient = 1;
        }
    }
    return orient;
}


int compareN(int * tab1, int* tab2, int N){
    int ret=1;
    for(int i=0; i<N; i++){
        if(tab1[i]!=tab2[i]){
            ret = 0;
        }
    }
    return ret;
}