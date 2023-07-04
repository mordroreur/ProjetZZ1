#include "main.h"

int debugging = 1;


int main(int argc, char * argv[]){

  int sizex;
  int sizey;
  int isFullscreen;
  int sound;
  int test = 1;
  if (argc > 1)
    test = atoi(argv[1]);
  else
    test = 1;
  //printf("%d et %d donc %d\n", argc, atoi(argv[1]), test);
  
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
  mainScreen.showImage = test;

  printf("%d\n", mainScreen.showImage);
  mainScreen.etapeDuJeu = 1;
  
  startMainBoucle(&mainScreen);


  return 0;
}
