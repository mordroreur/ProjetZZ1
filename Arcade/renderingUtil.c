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

  int nbImage = 27;
  int nbPlanche = 20;


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



  for(int i = 0; i < 6; i++){
    char tmp[30];
    sprintf(tmp, "Ressources/Image/pay%d.png", i+1);
    fileImage[i] = IMG_Load(tmp);
    PixelXnb[i] = 1920; PixelYnb[i] = 1088;XImagenb[i] = 1; YImagenb[i] = 1;
    TotalImagenb[i] = 1; ImYoffset[i] = 0; ImXoffset[i] = 0;
    debX[i] = 0; debY[i] = 0; wichFile[i] = i;
  }


  fileImage[6] = IMG_Load("Ressources/Image/plancheSprite.png"); 

  PixelXnb[IMPLAYER1] = 188; PixelYnb[IMPLAYER1] = 151;XImagenb[IMPLAYER1] = 1; YImagenb[IMPLAYER1] = 20;
  TotalImagenb[IMPLAYER1] = 20; ImYoffset[IMPLAYER1] = 74; ImXoffset[IMPLAYER1] = 0;
  debX[IMPLAYER1] = 142; debY[IMPLAYER1] = 48; wichFile[IMPLAYER1] = 6;

  PixelXnb[IMPLAYER2] = 188; PixelYnb[IMPLAYER2] = 151;XImagenb[IMPLAYER2] = 1; YImagenb[IMPLAYER2] = 20;
  TotalImagenb[IMPLAYER2] = 20; ImYoffset[IMPLAYER2] = 74; ImXoffset[IMPLAYER2] = 0;
  debX[IMPLAYER2] = 545; debY[IMPLAYER2] = 48; wichFile[IMPLAYER2] = 6;

  PixelXnb[IMPLAYER3] = 188; PixelYnb[IMPLAYER3] = 151;XImagenb[IMPLAYER3] = 1; YImagenb[IMPLAYER3] = 20;
  TotalImagenb[IMPLAYER3] = 20; ImYoffset[IMPLAYER3] = 74; ImXoffset[IMPLAYER3] = 0;
  debX[IMPLAYER3] = 942; debY[IMPLAYER3] = 48; wichFile[IMPLAYER3] = 6;

  PixelXnb[IMPLAYER4] = 188; PixelYnb[IMPLAYER4] = 151;XImagenb[IMPLAYER4] = 1; YImagenb[IMPLAYER4] = 20;
  TotalImagenb[IMPLAYER4] = 20; ImYoffset[IMPLAYER4] = 74; ImXoffset[IMPLAYER4] = 0;
  debX[IMPLAYER4] = 1345; debY[IMPLAYER4] = 48; wichFile[IMPLAYER4] = 6;
  
  PixelXnb[IMBOULEP1] = 46; PixelYnb[IMBOULEP1] = 47;XImagenb[IMBOULEP1] = 1; YImagenb[IMBOULEP1] = 1;
  TotalImagenb[IMBOULEP1] = 1; ImYoffset[IMBOULEP1] = 0; ImXoffset[IMBOULEP1] = 0;
  debX[IMBOULEP1] = 1775; debY[IMBOULEP1] = 93; wichFile[IMBOULEP1] = 6;

  PixelXnb[IMBOULEP2] = 46; PixelYnb[IMBOULEP2] = 47;XImagenb[IMBOULEP2] = 1; YImagenb[IMBOULEP2] = 1;
  TotalImagenb[IMBOULEP2] = 1; ImYoffset[IMBOULEP2] = 0; ImXoffset[IMBOULEP2] = 0;
  debX[IMBOULEP2] = 1775; debY[IMBOULEP2] = 318; wichFile[IMBOULEP2] = 6;

  PixelXnb[IMBOULEP3] = 46; PixelYnb[IMBOULEP3] = 47;XImagenb[IMBOULEP3] = 1; YImagenb[IMBOULEP3] = 1;
  TotalImagenb[IMBOULEP3] = 1; ImYoffset[IMBOULEP3] = 0; ImXoffset[IMBOULEP3] = 0;
  debX[IMBOULEP3] = 1775; debY[IMBOULEP3] = 543; wichFile[IMBOULEP3] = 6;

  PixelXnb[IMBOULEP4] = 46; PixelYnb[IMBOULEP4] = 47;XImagenb[IMBOULEP4] = 1; YImagenb[IMBOULEP4] = 1;
  TotalImagenb[IMBOULEP4] = 1; ImYoffset[IMBOULEP4] = 0; ImXoffset[IMBOULEP4] = 0;
  debX[IMBOULEP4] = 1775; debY[IMBOULEP4] = 768; wichFile[IMBOULEP4] = 6;



  fileImage[7] = IMG_Load("Ressources/Image/play.png");
  PixelXnb[IMBUTTONPLAY] = 1232; PixelYnb[IMBUTTONPLAY] = 586; XImagenb[IMBUTTONPLAY] = 1; YImagenb[IMBUTTONPLAY] = 1;
  TotalImagenb[IMBUTTONPLAY] = 1; ImYoffset[IMBUTTONPLAY] = 7; ImXoffset[IMBUTTONPLAY] = 0;
  debX[IMBUTTONPLAY] = 0; debY[IMBUTTONPLAY] = 0; wichFile[IMBUTTONPLAY] = 7;

  fileImage[8] = IMG_Load("Ressources/Image/quit.png");
  PixelXnb[IMBUTTONQUIT] = 1232; PixelYnb[IMBUTTONQUIT] = 586; XImagenb[IMBUTTONQUIT] = 1; YImagenb[IMBUTTONQUIT] = 1;
  TotalImagenb[IMBUTTONQUIT] = 1; ImYoffset[IMBUTTONQUIT] = 7; ImXoffset[IMBUTTONQUIT] = 0;
  debX[IMBUTTONQUIT] = 0; debY[IMBUTTONQUIT] = 0; wichFile[IMBUTTONQUIT] = 8;

  fileImage[9] = IMG_Load("Ressources/Image/parametre.png");
  PixelXnb[IMBUTTONPARAM] = 1232; PixelYnb[IMBUTTONPARAM] = 586; XImagenb[IMBUTTONPARAM] = 1; YImagenb[IMBUTTONPARAM] = 1;
  TotalImagenb[IMBUTTONPARAM] = 1; ImYoffset[IMBUTTONPARAM] = 7; ImXoffset[IMBUTTONPARAM] = 0;
  debX[IMBUTTONPARAM] = 0; debY[IMBUTTONPARAM] = 0; wichFile[IMBUTTONPARAM] = 9;

  fileImage[10] = IMG_Load("Ressources/Image/forme.png");
  PixelXnb[IMBUTTONFORM] = 540; PixelYnb[IMBUTTONFORM] = 1080; XImagenb[IMBUTTONFORM] = 1; YImagenb[IMBUTTONFORM] = 1;
  TotalImagenb[IMBUTTONFORM] = 1; ImYoffset[IMBUTTONFORM] = 7; ImXoffset[IMBUTTONFORM] = 0;
  debX[IMBUTTONFORM] = 0; debY[IMBUTTONFORM] = 0; wichFile[IMBUTTONFORM] = 10;

  fileImage[11] = IMG_Load("Ressources/Image/select.png");
  PixelXnb[IMBUTTONSELECT] = 1232; PixelYnb[IMBUTTONSELECT] = 586; XImagenb[IMBUTTONSELECT] = 1; YImagenb[IMBUTTONSELECT] = 1;
  TotalImagenb[IMBUTTONSELECT] = 1; ImYoffset[IMBUTTONSELECT] = 7; ImXoffset[IMBUTTONSELECT] = 0;
  debX[IMBUTTONSELECT] = 0; debY[IMBUTTONSELECT] = 0; wichFile[IMBUTTONSELECT] = 11;

  fileImage[12] = IMG_Load("Ressources/Image/select2.png");
  PixelXnb[IMBUTTONSELECT2] = 1230; PixelYnb[IMBUTTONSELECT2] = 585; XImagenb[IMBUTTONSELECT2] = 1; YImagenb[IMBUTTONSELECT2] = 1;
  TotalImagenb[IMBUTTONSELECT2] = 1; ImYoffset[IMBUTTONSELECT2] = 7; ImXoffset[IMBUTTONSELECT2] = 0;
  debX[IMBUTTONSELECT2] = 0; debY[IMBUTTONSELECT2] = 0; wichFile[IMBUTTONSELECT2] = 12;

  fileImage[13] = IMG_Load("Ressources/Image/select3.png");
  PixelXnb[IMBUTTONSELECT3] = 1232; PixelYnb[IMBUTTONSELECT3] = 586; XImagenb[IMBUTTONSELECT3] = 1; YImagenb[IMBUTTONSELECT3] = 1;
  TotalImagenb[IMBUTTONSELECT3] = 1; ImYoffset[IMBUTTONSELECT3] = 7; ImXoffset[IMBUTTONSELECT3] = 0;
  debX[IMBUTTONSELECT3] = 0; debY[IMBUTTONSELECT3] = 0; wichFile[IMBUTTONSELECT3] = 13;

  fileImage[14] = IMG_Load("Ressources/Image/select4.png");
  PixelXnb[IMBUTTONSELECT4] = 1261; PixelYnb[IMBUTTONSELECT4] = 601; XImagenb[IMBUTTONSELECT4] = 1; YImagenb[IMBUTTONSELECT4] = 1;
  TotalImagenb[IMBUTTONSELECT4] = 1; ImYoffset[IMBUTTONSELECT4] = 7; ImXoffset[IMBUTTONSELECT4] = 0;
  debX[IMBUTTONSELECT4] = 0; debY[IMBUTTONSELECT4] = 0; wichFile[IMBUTTONSELECT4] = 14;

  fileImage[15] = IMG_Load("Ressources/Image/back.png");
  PixelXnb[IMBUTTONBACK] = 1232; PixelYnb[IMBUTTONBACK] = 587; XImagenb[IMBUTTONBACK] = 1; YImagenb[IMBUTTONBACK] = 1;
  TotalImagenb[IMBUTTONBACK] = 1; ImYoffset[IMBUTTONBACK] = 7; ImXoffset[IMBUTTONBACK] = 0;
  debX[IMBUTTONBACK] = 0; debY[IMBUTTONBACK] = 0; wichFile[IMBUTTONBACK] = 15;

  fileImage[16] = IMG_Load("Ressources/Image/jouer.png");
  PixelXnb[IMBUTTONJOUER] = 1232; PixelYnb[IMBUTTONJOUER] = 586; XImagenb[IMBUTTONJOUER] = 1; YImagenb[IMBUTTONJOUER] = 1;
  TotalImagenb[IMBUTTONJOUER] = 1; ImYoffset[IMBUTTONJOUER] = 7; ImXoffset[IMBUTTONJOUER] = 0;
  debX[IMBUTTONJOUER] = 0; debY[IMBUTTONJOUER] = 0; wichFile[IMBUTTONJOUER] = 16;

  fileImage[17] = IMG_Load("Ressources/Image/iaTrain.png");
  PixelXnb[IMBUTTONIATRAIN] = 1230; PixelYnb[IMBUTTONIATRAIN] = 585; XImagenb[IMBUTTONIATRAIN] = 1; YImagenb[IMBUTTONIATRAIN] = 1;
  TotalImagenb[IMBUTTONIATRAIN] = 1; ImYoffset[IMBUTTONIATRAIN] = 7; ImXoffset[IMBUTTONIATRAIN] = 0;
  debX[IMBUTTONIATRAIN] = 0; debY[IMBUTTONIATRAIN] = 0; wichFile[IMBUTTONIATRAIN] = 17;

  fileImage[18] = IMG_Load("Ressources/Image/blackHole.png");
  PixelXnb[IMBLACKHOLE] = 1230; PixelYnb[IMBLACKHOLE] = 1264; XImagenb[IMBLACKHOLE] = 1; YImagenb[IMBLACKHOLE] = 1;
  TotalImagenb[IMBLACKHOLE] = 1; ImYoffset[IMBLACKHOLE] = 0; ImXoffset[IMBLACKHOLE] = 0;
  debX[IMBLACKHOLE] = 0; debY[IMBLACKHOLE] = 0; wichFile[IMBLACKHOLE] = 18;

  fileImage[19] = IMG_Load("Ressources/Image/Barredevie.png");
  PixelXnb[IMVIE] = 50; PixelYnb[IMVIE] = 25; XImagenb[IMVIE] = 1; YImagenb[IMVIE] = 3;
  TotalImagenb[IMVIE] = 3; ImYoffset[IMVIE] = 0; ImXoffset[IMVIE] = 0;
  debX[IMVIE] = 0; debY[IMVIE] = 0; wichFile[IMVIE] = 18;
  




  

  loadingScreenWithBarre(screen, 100, 100);
  SDL_RenderPresent(screen->renderer);
  SDL_RenderClear(screen->renderer);
  

  
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

void loadRobotoFont()
{
  RobotoFont = TTF_OpenFont("Ressources/Roboto-Black.ttf", 70);
  if (RobotoFont == NULL) {
    fprintf(stderr, "error: font not found\n");
    exit(EXIT_FAILURE);
  }
}

int loadImageMenu(ecran* screen)
{
  loadingScreenWithBarre(screen, 100, 0);
  SDL_RenderPresent(screen->renderer);
  SDL_RenderClear(screen->renderer);
    textureMenu = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*200); // créer tableau de texture
    if (!textureMenu) {
        fprintf(stderr, "Erreur allocation memory in loadImageMenu\n");
        return -1;
    }
    for (int i = 0; i < 200; i++) 
    {
	  if(i%3 == 0){
	    loadingScreenWithBarre(screen, 200, i);
	    SDL_RenderPresent(screen->renderer);
	    SDL_RenderClear(screen->renderer);
	  }
	  char nom[60];
	  sprintf(nom, "Ressources/Image/render_galaxy/%d.png", i);
	  textureMenu[i] = loadImage(nom, screen->renderer);
	  if(!textureMenu[i]) 
        { 
          fprintf(stderr, "Error loadImage for textureMenu : %s\n", SDL_GetError()); 
          return -1;
        }
    }
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
