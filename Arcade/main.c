#include "main.h"

int debugging = 0;


int main(){

  int sizex;
  int sizey;
  int isFullscreen;
  int sound;
  int bonus;
  int trou;
  
  FILE *param = fopen(PARAM_NAME, "r");
  if(param == NULL){
    
    sizex = 750;
    sizey = 500;
    isFullscreen = 0;
    sound = 100;
    bonus = 1;
    trou = 1;
        
    writeParamFile(sizex, sizey, isFullscreen, sound, bonus, trou);
    
  }else{
    fscanf(param, "%d\n%d\n%d\n%d\n%d\n%d\n", &sizex, &sizey, &isFullscreen, &sound, &bonus, &trou);
    fclose(param);
  }

  ecran mainScreen = createScreen(sizex, sizey, isFullscreen, sound, bonus, trou);

  mainScreen.etapeDuJeu = 1;
  
  startMainBoucle(&mainScreen);


  return 0;
}
