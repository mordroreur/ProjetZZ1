#include "main.h"

int debugging = 1;


int main(){

  int sizex;
  int sizey;
  int isFullscreen;
  int sound;
  
  FILE *param = fopen(PARAM_NAME, "r");
  if(param == NULL){
    
    sizex = 750;
    sizey = 500;
    isFullscreen = 0;
    sound = 100;
        
    writeParamFile(sizex, sizey, isFullscreen, sound);
    
  }else{
    fscanf(param, "%d\n%d\n%d\n%d\n", &sizex, &sizey, &isFullscreen, &sound);
    fclose(param);
  }

  ecran mainScreen = createScreen(sizex, sizey, isFullscreen, sound);

  mainScreen.etapeDuJeu = 1;
  
  startMainBoucle(&mainScreen);


  return 0;
}
