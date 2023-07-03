#include "renderingUtil.h"
#include "render.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <pthread.h>


static SDL_Surface ** fileImage;
static SDL_Texture **textureMenu;
static SDL_Texture **images;
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

  int nbImage = 14;
  int nbPlanche = 11;


void InitImage(ecran *screen){
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

    
  fileImage[0] = IMG_Load("Ressources/Image/plancheSprite.png");

  PixelXnb[0] = 114; PixelYnb[0] = 72;XImagenb[0] = 1; YImagenb[0] = 20;
  TotalImagenb[0] = 20; ImYoffset[0] = 63; ImXoffset[0] = 0;
  debX[0] = 84; debY[0] = 28; wichFile[0] = 0;

  fileImage[7] = IMG_Load("Ressources/Image/play.png");
  PixelXnb[10] = 475; PixelYnb[10] = 128; XImagenb[10] = 1; YImagenb[10] = 1;
  TotalImagenb[10] = 1; ImYoffset[10] = 7; ImXoffset[10] = 0;
  debX[10] = 0; debY[10] = 0; wichFile[10] = 7;

  fileImage[8] = IMG_Load("Ressources/Image/quit.png");
  PixelXnb[11] = 475; PixelYnb[11] = 128; XImagenb[11] = 1; YImagenb[11] = 1;
  TotalImagenb[11] = 1; ImYoffset[11] = 7; ImXoffset[11] = 0;
  debX[11] = 0; debY[11] = 0; wichFile[11] = 8;

  fileImage[9] = IMG_Load("Ressources/Image/parametre.png");
  PixelXnb[12] = 100; PixelYnb[12] = 50; XImagenb[12] = 1; YImagenb[12] = 1;
  TotalImagenb[12] = 1; ImYoffset[12] = 7; ImXoffset[12] = 0;
  debX[12] = 0; debY[12] = 0; wichFile[12] = 9;

  fileImage[10] = IMG_Load("Ressources/Image/forme.png");
  PixelXnb[13] = 100; PixelYnb[13] = 100; XImagenb[13] = 1; YImagenb[13] = 1;
  TotalImagenb[13] = 1; ImYoffset[13] = 7; ImXoffset[13] = 0;
  debX[13] = 0; debY[13] = 0; wichFile[13] = 10;
  
  // fileImage[4] = IMG_Load("Ressources/Image/vicRed.png");
  // PixelXnb[4] = 1920; PixelYnb[4] = 1080; XImagenb[4] = 1; YImagenb[4] = 1;
  // TotalImagenb[4] = 1; ImYoffset[4] = 7; ImXoffset[4] = 0;
  // debX[4] = 0; debY[4] = 0; wichFile[4] = 4;

  // fileImage[5] = IMG_Load("Ressources/Image/vicBleu.png");
  // PixelXnb[5] = 1920; PixelYnb[5] = 1080; XImagenb[5] = 1; YImagenb[5] = 1;
  // TotalImagenb[5] = 1; ImYoffset[5] = 7; ImXoffset[5] = 0;
  // debX[5] = 0; debY[5] = 0; wichFile[5] = 5;



  PixelXnb[1] = 114; PixelYnb[1] = 72;XImagenb[1] = 1; YImagenb[1] = 20;
  TotalImagenb[1] = 20; ImYoffset[1] = 63; ImXoffset[1] = 0;
  debX[1] = 324; debY[1] = 28; wichFile[1] = 0;

  PixelXnb[2] = 29; PixelYnb[2] = 29;XImagenb[2] = 1; YImagenb[2] = 1;
  TotalImagenb[2] = 1; ImYoffset[2] = 0; ImXoffset[2] = 0;
  debX[2] = 584; debY[2] = 55; wichFile[2] = 0;

  PixelXnb[3] = 29; PixelYnb[3] = 29;XImagenb[3] = 1; YImagenb[3] = 1;
  TotalImagenb[3] = 1; ImYoffset[3] = 0; ImXoffset[3] = 0;
  debX[3] = 584; debY[3] = 190; wichFile[3] = 0;



  for(int i = 1; i < 7; i++){
    char tmp[30];
    sprintf(tmp, "Ressources/Image/pay%d.png", i);
    fileImage[i] = IMG_Load(tmp);
    PixelXnb[3+i] = 1920; PixelYnb[3+i] = 1088;XImagenb[3+i] = 1; YImagenb[3+i] = 1;
    TotalImagenb[3+i] = 1; ImYoffset[3+i] = 0; ImXoffset[3+i] = 0;
    debX[3+i] = 0; debY[3+i] = 0; wichFile[3+i] = i;
  }

  loadingScreenWithBarre(screen, 100, 100);
  SDL_RenderPresent(screen->renderer);
  SDL_RenderClear(screen->renderer);
  
  //PixelXnb[0] = 16; PixelYnb[0] = 16;XImagenb[0] = 1; YImagenb[0] = 1;
  //TotalImagenb[0] = 1; ImYoffset[0] = 7; ImXoffset[0] = 0;
  //debX[0] = 0; debY[0] = 0; wichFile[0] = 0;

  
  images = (SDL_Texture **)malloc(sizeof(SDL_Surface *) * nbPlanche);
  for(int i = 0; i < nbPlanche; i++){
    images[i] = SDL_CreateTextureFromSurface(screen->renderer, fileImage[i]);
  }
  
  
  for(int i = 0; i < nbPlanche; i++){
    if(fileImage[i] == NULL){
      fprintf(stderr, "error: image %d not found\n", i);
      exit(EXIT_FAILURE);
    }
  }
  
  
  
  
  
}

SDL_Texture *loadImage(const char *path, SDL_Renderer *renderer) {
  SDL_Surface *tmp = NULL;
  SDL_Texture * texture = NULL;
  tmp = IMG_Load(path); // chargement de l'image 
  if(!tmp){ // probleme chargement image donc affiche message d'erreur + return NULL
    fprintf(stderr, "Erreur SDL_Load : %s\n", SDL_GetError());
    return NULL;
  }
  texture = SDL_CreateTextureFromSurface(renderer, tmp); // si pas d'erreur on créer la texture
  //SDL_Delay(300);
  SDL_FreeSurface(tmp); // on libère la mémoire de l'image
  if(!texture){ // probleme transfo image en texture , message + return NULL
    fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s\n", SDL_GetError());
    return NULL;
  }
  return texture; // tout c'est bien passé !
}

int imagePreface(ecran* screen, int i)
{
  SDL_RenderCopyEx(screen->renderer, textureMenu[i], NULL, NULL, 0, NULL, SDL_FLIP_NONE);
  return 0;
}

void loadMusic(ecran * screen)
{
  screen->musique[0] = Mix_LoadMUS("Ressources/musique/musicMenu.mp3");
  if (!screen->musique[0]) {printf("Error load musique 0\n!"); exit(EXIT_FAILURE);}
  screen->musique[1] = Mix_LoadMUS("Ressources/musique/musicGame.mp3");
  if (!screen->musique[1]) {printf("Error load musique 1\n!"); exit(EXIT_FAILURE);}
}

int loadImageMenu(ecran* screen)
{
  RobotoFont = TTF_OpenFont("Ressources/Roboto-Black.ttf", 70);
  if (RobotoFont == NULL) {
    fprintf(stderr, "error: font not found\n");
    exit(EXIT_FAILURE);
  }
  
  loadingScreenWithBarre(screen, 100, 0);
  SDL_RenderPresent(screen->renderer);
  SDL_RenderClear(screen->renderer);
    textureMenu = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*262); // créer tableau de texture
    if (!textureMenu) {
        fprintf(stderr, "Erreur allocation memory in loadImageMenu\n");
        return -1;
    }
    for (int i = 0; i < 262; i++) 
    {
	  if(i%3 == 0){
	    loadingScreenWithBarre(screen, 262, i);
	    SDL_RenderPresent(screen->renderer);
	    SDL_RenderClear(screen->renderer);
	  }
	  char nom[60];
	  sprintf(nom, "Ressources/Image/img_menu/imgComp/%d.png", i);
	  textureMenu[i] = loadImage(nom, screen->renderer);
	  if(!textureMenu[i]) 
        { 
          fprintf(stderr, "Error loadImage for textureMenu : %s\n", SDL_GetError()); 
          return -1;
        }
    }
    
    InitImage(screen);

    return 0;
}

void freeImageMalloc(){
  if(fileImage != NULL){
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
    for(int i = 0; i < nbImage; i++){
      SDL_FreeSurface(fileImage[i]);
    }
    for(int i = 0; i < nbPlanche; i++){
      SDL_DestroyTexture(images[i]);
    }
    free(fileImage);	
    free(textureMenu);
    free(images);
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


  //SDL_Texture *tempo = SDL_CreateTextureFromSurface(screen->renderer, fileImage[wichFile[imagenb]]);
  
  SDL_RenderCopyEx(screen->renderer, images[wichFile[imagenb]], &keepImage, &Image_rect, angle, NULL, flip);
  //SDL_RenderCopy(screen->renderer, tempo, &keepImage, &Image_rect);
  //SDL_DestroyTexture(tempo);
  
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
