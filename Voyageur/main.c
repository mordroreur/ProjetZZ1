#include "main.h"

int debugging = 0;

int main(){

  int sizex;
  int sizey;
  int isFullscreen;
  
  FILE *param = fopen(PARAM_NAME, "r");
  if(param == NULL){
    
    sizex = 750;
    sizey = 500;
    isFullscreen = 0;
        
    writeParamFile(sizex, sizey, isFullscreen);
    
  }else{
    fscanf(param, "%d\n%d\n%d\n", &sizex, &sizey, &isFullscreen);
    fclose(param);
  }

  ecran mainScreen = createScreen(sizex, sizey, isFullscreen);

  mainScreen.etapeDuJeu = 1;

  if(debugging){
    srand(42);
  }else{
    srand(time(NULL));
  }
  
  startMainBoucle(&mainScreen);


  return 0;
}
