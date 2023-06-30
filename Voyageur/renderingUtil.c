#include "renderingUtil.h"
#include <SDL2/SDL_render.h>


static SDL_Surface **fileImage;
static int *wichFile;
static int *PixelXnb;
static int *PixelYnb;
static int *XImagenb;
static int *YImagenb;
static int *ImYoffset;
static int *ImXoffset;
static int *TotalImagenb;
static int *debX;
static int *debY;


TTF_Font *RobotoFont;




long int getTime(){
  struct timespec tms;
  if (clock_gettime(CLOCK_REALTIME,&tms)) {
        return -1;
    }
  return ((tms.tv_sec*1000000) + (tms.tv_nsec/1000));
}

void InitImage(){

  RobotoFont = TTF_OpenFont("Ressources/Roboto-Black.ttf", 70);
  if (RobotoFont == NULL) {
    fprintf(stderr, "error: font not found\n");
    exit(EXIT_FAILURE);
  }



  int nbImage = 11;
  int nbPlanche = 11;
  fileImage = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * nbImage);
  wichFile = (int *)malloc(sizeof(int) * nbImage);
  PixelXnb = (int *)malloc(sizeof(int) * nbImage);
  PixelYnb = (int *)malloc(sizeof(int) * nbImage);
  XImagenb = (int *)malloc(sizeof(int) * nbImage);
  YImagenb = (int *)malloc(sizeof(int) * nbImage);
  ImYoffset = (int *)malloc(sizeof(int) * nbImage);
  ImXoffset = (int *)malloc(sizeof(int) * nbImage);
  TotalImagenb = (int *)malloc(sizeof(int) * nbImage);
  debX = (int *)malloc(sizeof(int) * nbImage);
  debY = (int *)malloc(sizeof(int) * nbImage);

  

  
  fileImage[0] = IMG_Load("Ressources/Image/playButton.png");
  PixelXnb[0] = 100; PixelYnb[0] = 50;XImagenb[0] = 1; YImagenb[0] = 1;
  TotalImagenb[0] = 1; ImYoffset[0] = 0; ImXoffset[0] = 0;
  debX[0] = 0; debY[0] = 0; wichFile[0] = 0;

  fileImage[1] = IMG_Load("Ressources/Image/quitButton.png");
  PixelXnb[1] = 100; PixelYnb[1] = 50;XImagenb[1] = 1; YImagenb[1] = 1;
  TotalImagenb[1] = 1; ImYoffset[1] = 0; ImXoffset[1] = 0;
  debX[1] = 0; debY[1] = 0; wichFile[1] = 1;

  fileImage[2] = IMG_Load("Ressources/Image/parametress.png");
  PixelXnb[2] = 768; PixelYnb[2] = 768;XImagenb[2] = 1; YImagenb[2] = 1;
  TotalImagenb[2] = 1; ImYoffset[2] = 0; ImXoffset[2] = 0;
  debX[2] = 0; debY[2] = 0; wichFile[2] = 2;
  
  
  fileImage[3] = IMG_Load("Ressources/Image/back_menu.png");
  PixelXnb[3] = 1024; PixelYnb[3] = 512;XImagenb[3] = 1; YImagenb[3] = 1;
  TotalImagenb[3] = 1; ImYoffset[2] = 0; ImXoffset[2] = 0;
  debX[3] = 0; debY[3] = 0; wichFile[3] = 3;

  fileImage[4] = IMG_Load("Ressources/Image/forme.png");
  PixelXnb[4] = 100; PixelYnb[4] = 100;XImagenb[4] = 1; YImagenb[4] = 1;
  TotalImagenb[4] = 1; ImYoffset[4] = 0; ImXoffset[4] = 0;
  debX[4] = 0; debY[4] = 0; wichFile[4] = 4;

  fileImage[5] = IMG_Load("Ressources/Image/return.png");
  PixelXnb[5] = 100; PixelYnb[5] = 50;XImagenb[5] = 1; YImagenb[5] = 1;
  TotalImagenb[5] = 1; ImYoffset[5] = 0; ImXoffset[5] = 0;
  debX[5] = 0; debY[5] = 0; wichFile[5] = 5;

  fileImage[6] = IMG_Load("Ressources/Image/back_parametre.png");
  PixelXnb[6] = 1024; PixelYnb[6] = 486; XImagenb[6] = 1; YImagenb[6] = 1;
  TotalImagenb[6] = 1; ImYoffset[6] = 0; ImXoffset[6] = 0;
  debX[6] = 0; debY[6] = 0; wichFile[6] = 6;

  fileImage[7] = IMG_Load("Ressources/Image/voiture.png");
  PixelXnb[7] = 603; PixelYnb[7] = 831; XImagenb[7] = 1; YImagenb[7] = 1;
  TotalImagenb[7] = 1; ImYoffset[7] = 0; ImXoffset[7] = 0;
  debX[7] = 0; debY[7] = 0; wichFile[7] = 7;

  fileImage[8] = IMG_Load("Ressources/Image/voitureIA.png");
  PixelXnb[8] = 603; PixelYnb[8] = 831; XImagenb[8] = 1; YImagenb[8] = 1;
  TotalImagenb[8] = 1; ImYoffset[8] = 0; ImXoffset[8] = 0;
  debX[8] = 0; debY[8] = 0; wichFile[8] = 8;

  fileImage[9] = IMG_Load("Ressources/Image/pasVue.png");
  PixelXnb[9] = 46; PixelYnb[9] = 42; XImagenb[9] = 1; YImagenb[9] = 1;
  TotalImagenb[9] = 1; ImYoffset[9] = 0; ImXoffset[9] = 0;
  debX[9] = 0; debY[9] = 0; wichFile[9] = 9;

  fileImage[10] = IMG_Load("Ressources/Image/vue.png");
  PixelXnb[10] = 46; PixelYnb[10] = 42; XImagenb[10] = 1; YImagenb[10] = 1;
  TotalImagenb[10] = 1; ImYoffset[10] = 0; ImXoffset[10] = 0;
  debX[10] = 0; debY[10] = 0; wichFile[10] = 10;


  
  for(int i = 0; i < nbPlanche; i++){
    if(fileImage[i] == NULL){
      fprintf(stderr, "error: image %d not found\n", i);
      exit(EXIT_FAILURE);
    }
  }

}

void freeImageMalloc(){
  if(fileImage != NULL){
    free(fileImage);
    free(wichFile);
    free(PixelXnb);
    free(PixelYnb);
    free(XImagenb);
    free(YImagenb);
    free(ImXoffset);
    free(ImYoffset);
    free(TotalImagenb);
    free(debX);
    free(debY);
  }
  if(RobotoFont != NULL){
    TTF_CloseFont(RobotoFont);
  }
}



void DrawString(char *s, float x, float y, float size, char center, int R, int G, int B, ecran *screen){
  SDL_Color Color = {R, G, B, 255};
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(RobotoFont, s, Color);
  SDL_Texture* Message = SDL_CreateTextureFromSurface(screen->renderer, surfaceMessage);
  SDL_Rect Message_rect;
  int tmph = surfaceMessage->h;
  int tmpw = surfaceMessage->w;
  float ratio = (float)(tmph)/screen->sizeY;

  
  Message_rect.w = tmpw/(ratio*100) * size;
  Message_rect.h = tmph/(ratio*100) * size;
  
  switch (center) {
  case 'n':
    Message_rect.x = (int)((float)(screen->sizeX)/100 * x); 
    Message_rect.y = (int)((float)(screen->sizeY)/100 * y);
    break;
  case 'e':
    Message_rect.x = (int)((float)(screen->sizeX)/100 * x) - Message_rect.w; 
    Message_rect.y = (int)((float)(screen->sizeY)/100 * y);
    break;
    case 'c':
    Message_rect.x = (int)((float)(screen->sizeX)/100 * x) - Message_rect.w/2; 
    Message_rect.y = (int)((float)(screen->sizeY)/100 * y) - Message_rect.h/2;
    
    break;
  default:
    Message_rect.x = (int)((float)(screen->sizeX)/100 * x); 
    Message_rect.y = (int)((float)(screen->sizeY)/100 * y);
    break;
    }
  
  SDL_SetRenderDrawColor(screen->renderer, 0, 0, 0, 0);
  SDL_RenderCopy(screen->renderer, Message, NULL, &Message_rect);
  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(Message);
}





void DrawImage(int imagenb, float x, float y, float sizeX, float sizeY, char center, int etatPremier, float TimebeforeNext, int flip, int angle, int nbState, int* spriteOrder, ecran *screen){


  SDL_Rect Image_rect;
  SDL_Rect keepImage;
  int imageVoulu = 0;

  float resx;
  float resy;
  
  if(sizeY == 0 && sizeX != 0){
    resx = ((float)screen->sizeX * sizeX/99.9)/PixelXnb[imagenb];
    resy = resx;
  }else if(sizeX == 0 && sizeY != 0){
    resy = ((float)screen->sizeY * sizeY/100.0)/PixelYnb[imagenb];
    resx = resy;
  }else if(sizeX != 0 && sizeY != 0){
    resx = ((float)screen->sizeX * (float)sizeX/100)/PixelXnb[imagenb];
    resy = ((float)screen->sizeY * (float)sizeY/100)/PixelYnb[imagenb];
  }else{
    resx = 1;
    resy = 1;
  }
  
  Image_rect.h = resy * (PixelYnb[imagenb] + ImYoffset[imagenb]);
  Image_rect.w = resx * (PixelXnb[imagenb] + ImXoffset[imagenb]);

  
  switch (center) {
  case 'n':
    Image_rect.x = (int)((float)(screen->sizeX)/100 * x - ImXoffset[imagenb]*resx); 
    Image_rect.y = (int)((float)(screen->sizeY)/100 * y - ImYoffset[imagenb]*resy);
    break;
  case 'e':
    Image_rect.x = (int)((float)(screen->sizeX)/100 * x - (float)(PixelXnb[imagenb]) * resx - ImXoffset[imagenb]*resx); 
    Image_rect.y = (int)((float)(screen->sizeY)/100 * y - ImYoffset[imagenb]*resy);
    break;
  case 's':
    Image_rect.x = (int)((float)(screen->sizeX)/100 * x - (float)(PixelXnb[imagenb]) * resx - ImXoffset[imagenb]*resx); 
    Image_rect.y = (int)((float)(screen->sizeY)/100 * y - (float)(PixelYnb[imagenb]) * resy - ImYoffset[imagenb]*resy);
    break;
  case 'w':
    Image_rect.x = (int)((float)(screen->sizeX)/100 * x - ImXoffset[imagenb]*resx);
    Image_rect.y = (int)((float)(screen->sizeY)/100 * y - (float)(PixelYnb[imagenb]) * resy - ImYoffset[imagenb]*resy);
    break;
  case 'c':
    Image_rect.x = (int)((float)(screen->sizeX)/100 * x - (float)(PixelXnb[imagenb]) * resx/2 - ImXoffset[imagenb]*resx); 
    Image_rect.y = (int)((float)(screen->sizeY)/100 * y - (float)(PixelYnb[imagenb]) * resy/2 - ImYoffset[imagenb]*resy);
    break;
  default:
    Image_rect.x = (int)((float)(screen->sizeX)/100 * x - ImXoffset[imagenb]*resx); 
    Image_rect.y = (int)((float)(screen->sizeY)/100 * y - ImYoffset[imagenb]*resy);
    break;
  }

  if(TimebeforeNext == 0){
    imageVoulu = etatPremier;
  }else{
    imageVoulu = spriteOrder[(etatPremier + ((int)((SDL_GetTicks()/((float)1000*TimebeforeNext)))%nbState))%nbState];
  }

 

  
  if(TotalImagenb[imagenb] != 1){
    int col = imageVoulu / XImagenb[imagenb];
    int line = imageVoulu % XImagenb[imagenb];
    keepImage.x = debX[imagenb] + line*(PixelXnb[imagenb] + ImXoffset[imagenb]);
    keepImage.y = debY[imagenb] + col*(PixelYnb[imagenb] + ImYoffset[imagenb]);
    keepImage.w = PixelXnb[imagenb];
    keepImage.h = PixelYnb[imagenb];
  }else {
    keepImage.x = debX[imagenb];
    keepImage.y = debY[imagenb];
    keepImage.w = (float)PixelXnb[imagenb] + ImXoffset[imagenb];
    keepImage.h = (float)PixelYnb[imagenb] + ImYoffset[imagenb];
  }


  SDL_Texture *tempo = SDL_CreateTextureFromSurface(screen->renderer, fileImage[wichFile[imagenb]]);

  SDL_RenderCopyEx(screen->renderer, tempo, &keepImage, &Image_rect, angle, NULL, flip);
  //SDL_RenderCopy(screen->renderer, tempo, &keepImage, &Image_rect);
  SDL_DestroyTexture(tempo);
  
}




int isInButton(float x, float y, float sizeX, float sizeY, char center, int posMX, int posMY, ecran *screen)
{

  if(center == 'c'){
    if(posMX < screen->sizeX*((x+sizeX/2)/100) && posMX > screen->sizeX*((x-sizeX/2)/100) && posMY < screen->sizeY*((y+sizeY/2)/100) && posMY > screen->sizeY*((y-sizeY/2)/100)){
      return 1;
    }
    return 0;
  }else if(center == 'n'){
    if(posMX < screen->sizeX*((x+sizeX)/100) && posMX > screen->sizeX*((x)/100) && posMY < screen->sizeY*((y+sizeY)/100) && posMY > screen->sizeY*((y)/100)){
      return 1;
    }else{
      return 0;
    }
  }
  return 0;
}
