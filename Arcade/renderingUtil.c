#include "renderingUtil.h"
#include <SDL2/SDL_render.h>


static SDL_Surface **fileImage;
static SDL_Texture ** textureMenu;
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

  
  int nbImage = 1;
  int nbPlanche = 1;
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

  

  
  fileImage[0] = IMG_Load("Ressources/Image/BoiteVide.png");
  PixelXnb[0] = 16; PixelYnb[0] = 16;XImagenb[0] = 1; YImagenb[0] = 1;
  TotalImagenb[0] = 1; ImYoffset[0] = 7; ImXoffset[0] = 0;
  debX[0] = 0; debY[0] = 0; wichFile[0] = 0;

  fileImage[1] = IMG_Load("Ressources/Image/img_menu/0112.png");
  PixelXnb[1] = 1920; PixelYnb[1] = 1080; XImagenb[1] = 1; YImagenb[1] = 1;
  TotalImagenb[1] = 1; ImYoffset[1] = 7; ImXoffset[1] = 0;
  debX[1] = 0; debY[1] = 0; wichFile[1] = 1;

  fileImage[2] = IMG_Load("Ressources/Image/play.png");
  PixelXnb[2] = 475; PixelYnb[2] = 128; XImagenb[2] = 1; YImagenb[2] = 1;
  TotalImagenb[2] = 1; ImYoffset[2] = 7; ImXoffset[2] = 0;
  debX[2] = 0; debY[2] = 0; wichFile[2] = 2;

  fileImage[3] = IMG_Load("Ressources/Image/quit.png");
  PixelXnb[3] = 475; PixelYnb[3] = 128; XImagenb[3] = 1; YImagenb[3] = 1;
  TotalImagenb[3] = 1; ImYoffset[3] = 7; ImXoffset[3] = 0;
  debX[3] = 0; debY[3] = 0; wichFile[3] = 3;
  
  // fileImage[4] = IMG_Load("Ressources/Image/vicRed.png");
  // PixelXnb[4] = 1920; PixelYnb[4] = 1080; XImagenb[4] = 1; YImagenb[4] = 1;
  // TotalImagenb[4] = 1; ImYoffset[4] = 7; ImXoffset[4] = 0;
  // debX[4] = 0; debY[4] = 0; wichFile[4] = 4;

  // fileImage[5] = IMG_Load("Ressources/Image/vicBleu.png");
  // PixelXnb[5] = 1920; PixelYnb[5] = 1080; XImagenb[5] = 1; YImagenb[5] = 1;
  // TotalImagenb[5] = 1; ImYoffset[5] = 7; ImXoffset[5] = 0;
  // debX[5] = 0; debY[5] = 0; wichFile[5] = 5;

  for(int i = 0; i < nbPlanche; i++){
    if(fileImage[0] == NULL){
      fprintf(stderr, "error: image 0 not found\n");
      exit(EXIT_FAILURE);
    }
  }
  
  
  
  
  
}

SDL_Texture * loadImage(const char * path, SDL_Renderer *renderer) 
{
  printf("test1\n");
  SDL_Surface *tmp = NULL; SDL_Texture *texture = NULL;
  printf("test2 %s\n", path);
  tmp = IMG_Load(path); // chargement de l'image 
  printf("test3\n");
  if(!tmp){ // probleme chargement image donc affiche message d'erreur + return NULL
    fprintf(stderr, "Erreur SDL_Load : %s\n", SDL_GetError());
    return NULL;
  }
printf("test4\n");
  texture = SDL_CreateTextureFromSurface(renderer, tmp); // si pas d'erreur on créer la texture
  SDL_FreeSurface(tmp); // on libère la mémoire de l'image
printf("test5\n");
  if(!texture){ // probleme transfo image en texture , message + return NULL
    fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s\n", SDL_GetError());
    return NULL;
  }
  printf("test6\n");
  return texture; // tout c'est bien passé !
}

int imagePreface(ecran* screen, int i)
{
  SDL_RenderCopyEx(screen->renderer, textureMenu[i], NULL, NULL, 0, NULL, SDL_FLIP_NONE);
  return 0;
}

int loadImageMenu(SDL_Renderer * renderer)
{
    textureMenu = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*181); // créer tableau de texture
    if (!textureMenu) {
        fprintf(stderr, "Erreur allocation memory in loadImageMenu\n");
        return -1;
    }
    for (int i = 0; i < 180; i++) 
    { 
        char nom[50];
        sprintf(nom, "Ressources/Image/img_menu/%04d.png", i);
        printf("%s\n", nom);
        if (i != 26 || i != 60 || i != 82 || i != 99 || i != 145)
          textureMenu[i] = IMG_LoadTexture(renderer, nom);//loadImage(nom, renderer);
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
  SDL_Color Color = {R, G, B};
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
