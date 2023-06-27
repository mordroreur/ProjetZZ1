#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>

#define WIDTH 1920
#define HEIGHT 1080
#define sizePion 50
#define sizeBoule 25
#define vitesse 1
#define vieBoule 1000
#define vitesseBoule 2

typedef struct boule
{
  int vie;
  int orientation;
  SDL_Rect pos;
} boule;

TTF_Font * RobotoFont;

void DrawString(char *s, float x, float y, float size, char center, int R, int G, int B, SDL_Renderer *screen){
  SDL_Color Color = {R, G, B};
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(RobotoFont, s, Color);
  SDL_Texture* Message = SDL_CreateTextureFromSurface(screen, surfaceMessage);
  SDL_Rect Message_rect;
  int tmph = surfaceMessage->h;
  int tmpw = surfaceMessage->w;
  float ratio = (float)(tmph)/HEIGHT;

  
  Message_rect.w = tmpw/(ratio*100) * size;
  Message_rect.h = tmph/(ratio*100) * size;
  
  switch (center) {
  case 'n':
    Message_rect.x = (int)((float)(WIDTH)/100 * x); 
    Message_rect.y = (int)((float)(HEIGHT)/100 * y);
    break;
  case 'e':
    Message_rect.x = (int)((float)(WIDTH)/100 * x) - Message_rect.w; 
    Message_rect.y = (int)((float)(HEIGHT)/100 * y);
    break;
    case 'c':
    Message_rect.x = (int)((float)(WIDTH)/100 * x) - Message_rect.w/2; 
    Message_rect.y = (int)((float)(HEIGHT)/100 * y) - Message_rect.h/2;
    
    break;
  default:
    Message_rect.x = (int)((float)(WIDTH)/100 * x); 
    Message_rect.y = (int)((float)(HEIGHT)/100 * y);
    break;
    }
  
  SDL_SetRenderDrawColor(screen, 0, 0, 0, 0);
  SDL_RenderCopy(screen, Message, NULL, &Message_rect);
  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(Message);  
}

SDL_Texture * loadImage(const char * path, SDL_Renderer *renderer) {
  SDL_Surface *tmp = NULL; SDL_Texture *texture = NULL;
  tmp = IMG_Load(path); // chargement de l'image 

  if(!tmp){ // probleme chargement image donc affiche message d'erreur + return NULL
    fprintf(stderr, "Erreur SDL_Load : %s\n", SDL_GetError());
    return NULL;
  }

  texture = SDL_CreateTextureFromSurface(renderer, tmp); // si pas d'erreur on créer la texture
  SDL_FreeSurface(tmp); // on libère la mémoire de l'image

  if(!texture){ // probleme transfo image en texture , message + return NULL
    fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s\n", SDL_GetError());
    return NULL;
  }
  return texture; // tout c'est bien passé !
}

int loadPion(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauPion)
{
    SDL_Texture ** pion = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*2); // créer tableau de texture
    if (!pion) {
        fprintf(stderr, "Erreur allocation memory in loadPion\n");
        return -1;
    }
    for (int i = 0; i < 2; i++) 
    { 
        char nom[30];
        sprintf(nom, "b%d.png", i);
        pion[i] = loadImage(nom, * renderer);
        if(!pion[i]) 
        { 
          fprintf(stderr, "Error loadPion for pion[i] : %s\n", SDL_GetError()); 
        return -1;
        }
    }
    * pTextureTableauPion = pion; // mets le tableau dans le pointeur car aucun retour de tableau
    return 0;
}

int loadBoule(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauBoule)
{
    SDL_Texture ** boules = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*2); // créer tableau de texture
    if (!boules) {
        fprintf(stderr, "Erreur allocation memory in loadBoule\n");
        return -1;
    }
    for (int i = 0; i < 2; i++) 
    { 
        char nom[30];
        sprintf(nom, "boule%d.png", i);
        boules[i] = loadImage(nom, * renderer);
        if(!boules[i]) 
        { 
          fprintf(stderr, "Error loadPion for boule[i] : %s\n", SDL_GetError()); 
        return -1;
        }
    }
    * pTextureTableauBoule = boules; // mets le tableau dans le pointeur car aucun retour de tableau
    return 0;
}

boule * initBoule(SDL_Texture ** bouboule)
{
  boule * tab = (boule *) malloc(100*sizeof(boule));
  for (int i = 0; i < 100; i++)
  {
    tab[i].vie = -1;
    tab[i].orientation = 1;
    SDL_QueryTexture(bouboule[0], NULL, NULL, &(tab[i].pos.w), &(tab[i].pos.h));
  }
  return tab;
}

void freeBoule(boule * tab)
{
  free(tab);
  return;
}

void game(SDL_Window * window, SDL_Renderer * renderer, SDL_Texture ** pion, boule * bouleTab, boule * bouleTab2, SDL_Texture ** textureBoule)
{
  SDL_Event event;
  int program_on = 1;
  int px; int py;
  int index1 = 0;
  int index2 = 0;
  int score1 = 0;
  int score2 = 0;
  char str[12];
  /* direction pion*/
  int j1g = 0; int j1d = 0; int j1b = 0; int j1h = 0;
  int j2g = 0; int j2d = 0; int j2b = 0; int j2h = 0;
  /* orientation pion*/
  int j1gg = 0; int j1dd = 1; int j1bb = 0; int j1hh = 0;
  int j2gg = 1; int j2dd = 0; int j2bb = 0; int j2hh = 0;
  SDL_Rect position, position2;
  position.x = 0; position.y = 0;
  position2.x = 1920/2 - sizePion; position2.y = 1080/2 - sizePion;
  SDL_QueryTexture(pion[0], NULL, NULL, &position.w, &position.h);
  SDL_QueryTexture(pion[1], NULL, NULL, &position2.w, &position2.h);

  while (program_on) // La boucle des évènements
  {                            
    while(SDL_PollEvent(&event)) // Tant que on n'a pas trouvé d'évènement utile
    {  
      SDL_GetWindowPosition(window, &px, &py);
      switch (event.type)
      {                         //
        case SDL_QUIT:                                
          program_on = 0;                    
        break;
        case SDL_KEYUP:
          switch (event.key.keysym.sym)
          {
            /* Joueur 2*/
            case SDLK_UP: j2h = 0; break;
            case SDLK_LEFT: j2g = 0; break;
            case SDLK_DOWN: j2b = 0; break;
            case SDLK_RIGHT: j2d = 0; break;
            case SDLK_o: j2h = 0; break;
            case SDLK_k: j2g = 0; break;
            case SDLK_l: j2b = 0; break;
            case SDLK_m: j2d = 0; break;
            /* Joueur 1 */
            case SDLK_q: j1g = 0; break;
            case SDLK_z: j1h = 0; break;
            case SDLK_s: j1b = 0; break;
            case SDLK_d: j1d = 0; break;
            default:
            break;
          }
        break;
        case SDL_KEYDOWN:                              
          switch (event.key.keysym.sym) 
          {
            /* Bouger le joueur 2 */
            case (SDLK_UP): j2h = 1; j2hh = 1; j2gg = 0; j2dd = 0; j2bb = 0; break;
            case (SDLK_LEFT): j2g = 1; j2hh = 0; j2gg = 1; j2dd = 0; j2bb = 0; break;
            case (SDLK_DOWN): j2b = 1; j2hh = 0; j2gg = 0; j2dd = 0; j2bb = 1; break;
            case (SDLK_RIGHT): j2d = 1; j2hh = 0; j2gg = 0; j2dd = 1; j2bb = 0; break;
            case (SDLK_o): j2h = 1; j2hh = 1; j2gg = 0; j2dd = 0; j2bb = 0; break;
            case (SDLK_k): j2g = 1; j2hh = 0; j2gg = 1; j2dd = 0; j2bb = 0; break;
            case (SDLK_l): j2b = 1; j2hh = 0; j2gg = 0; j2dd = 0; j2bb = 1; break;
            case (SDLK_m): j2d = 1; j2hh = 0; j2gg = 0; j2dd = 1; j2bb = 0; break;
            case SDLK_KP_1:
              bouleTab2[index2].vie = vieBoule;
              bouleTab2[index2].pos.x = position2.x + sizePion/2;
              bouleTab2[index2].pos.y = position2.y + sizePion/2;
              bouleTab2[index2].orientation = (j2hh == 1) ? 1 : (j2bb == 1) ? 2 : (j2gg == 1) ? 3 : 4;
              index2 = (index2 + 1)%100;
            break;
            /* Bouger le joueur 1 */
            case SDLK_z: j1h = 1; j1hh = 1; j1gg = 0; j1dd = 0; j1bb = 0; break; 
            case SDLK_q: j1g = 1; j1hh = 0; j1gg = 1; j1dd = 0; j1bb = 0; break;
            case SDLK_s: j1b = 1; j1hh = 0; j1gg = 0; j1dd = 0; j1bb = 1; break;
            case SDLK_d: j1d = 1; j1hh = 0; j1gg = 0; j1dd = 1; j1bb = 0; break;
            case SDLK_g: 
              bouleTab[index1].vie = vieBoule;
              bouleTab[index1].pos.x = position.x + sizePion/2;
              bouleTab[index1].pos.y = position.y + sizePion/2;
              bouleTab[index1].orientation = (j1hh == 1) ? 1 : (j1bb == 1) ? 2 : (j1gg == 1) ? 3 : 4;
              index1 = (index1 + 1)%100;
            break;
            /* Bouger la fenêtre */
            case SDLK_KP_4: SDL_SetWindowPosition(window, px-5, py); break;
            case SDLK_KP_8: SDL_SetWindowPosition(window, px, py-5 ); break;
            case SDLK_KP_2: SDL_SetWindowPosition(window, px, py+5); break;
            case SDLK_KP_6: SDL_SetWindowPosition(window, px+5, py); break;                     
            default:                                
            break;
          }
        break;
      }
    }
    if (j1h && j1d) {position.y -= vitesse; position.x += vitesse;}
    else if (j1h && j1g) {position.y -= vitesse; position.x -= vitesse;}
    else if (j1b && j1d) {position.y += vitesse; position.x += vitesse;}
    else if (j1b && j1g) {position.y += vitesse; position.x -= vitesse;}
    else if ((j1h && j1b) || (j1d && j1g)) {/*nothing*/}
    else if (j1h) {position.y -= vitesse;}
    else if (j1g) {position.x -= vitesse;}
    else if (j1d) {position.x += vitesse;}
    else if (j1b) {position.y += vitesse;}
    else {}

    if (j2h && j2d) {position2.y -= vitesse; position2.x += vitesse;}
    else if (j2h && j2g) {position2.y -= vitesse; position2.x -= vitesse;}
    else if (j2b && j2d) {position2.y += vitesse; position2.x += vitesse;}
    else if (j2b && j2g) {position2.y += vitesse; position2.x -= vitesse;}
    else if ((j2h && j2b) || (j2d && j2g)) {/*nothing*/}
    else if (j2h) {position2.y -= vitesse;}
    else if (j2g) {position2.x -= vitesse;}
    else if (j2d) {position2.x += vitesse;}
    else if (j2b) {position2.y += vitesse;}
    else {}

    /*position j1*/
    if (position.x + (sizePion/2) < 0) {position.x = WIDTH - (sizePion/2) -1;}
    if (position.x + (sizePion/2) > WIDTH) {position.x = 0 - (sizePion/2) +1;}
    if (position.y + (sizePion/2) < 0) {position.y = HEIGHT - (sizePion/2) -1;}
    if (position.y + (sizePion/2) > HEIGHT) {position.y = 0 - (sizePion/2) +1;}
    /*position j2*/
    if (position2.x + (sizePion/2) < 0) {position2.x = WIDTH - (sizePion/2) -1;}
    if (position2.x + (sizePion/2) > WIDTH) {position2.x = 0 - (sizePion/2) +1;}
    if (position2.y + (sizePion/2) < 0) {position2.y = HEIGHT - (sizePion/2) -1;}
    if (position2.y + (sizePion/2) > HEIGHT) {position2.y = 0 - (sizePion/2) +1;}

    SDL_RenderClear(renderer);

    for (int i = 0; i < 100; i++)
    {
      if (bouleTab[i].vie > 0)
      {
        SDL_RenderCopyEx(renderer, textureBoule[0], NULL, &(bouleTab[i].pos), 0, NULL, SDL_FLIP_NONE);
        switch (bouleTab[i].orientation)
        {
          case 1: bouleTab[i].pos.y -= vitesseBoule; break;
          case 2: bouleTab[i].pos.y += vitesseBoule; break;
          case 3: bouleTab[i].pos.x -= vitesseBoule; break;
          case 4: bouleTab[i].pos.x += vitesseBoule; break; 
        }
        if (bouleTab[i].pos.x + (sizeBoule/2) < 0) {bouleTab[i].pos.x = WIDTH - (sizeBoule/2) -1;}
        if (bouleTab[i].pos.x + (sizeBoule/2) > WIDTH) {bouleTab[i].pos.x = 0 - (sizeBoule/2) +1;}
        if (bouleTab[i].pos.y + (sizeBoule/2) < 0) {bouleTab[i].pos.y = HEIGHT - (sizeBoule/2) -1;}
        if (bouleTab[i].pos.y + (sizeBoule/2) > HEIGHT) {bouleTab[i].pos.y = 0 - (sizeBoule/2) +1;}
        bouleTab[i].vie -= 1;
        if ( sqrt(pow((bouleTab[i].pos.x + sizeBoule/2) - (position2.x + sizePion/2) ,2) + pow((bouleTab[i].pos.y + sizeBoule/2) - (position2.y + sizePion/2) ,2)) < sizeBoule)
        {
          score1++;
          bouleTab[i].vie = -1;
        } 
      }

      if (bouleTab2[i].vie > 0)
      {
        SDL_RenderCopyEx(renderer, textureBoule[1], NULL, &(bouleTab2[i].pos), 0, NULL, SDL_FLIP_NONE);
        switch (bouleTab2[i].orientation)
        {
          case 1: bouleTab2[i].pos.y -= vitesseBoule; break;
          case 2: bouleTab2[i].pos.y += vitesseBoule; break;
          case 3: bouleTab2[i].pos.x -= vitesseBoule; break;
          case 4: bouleTab2[i].pos.x += vitesseBoule; break; 
        }
        if (bouleTab2[i].pos.x + (sizeBoule/2) < 0) {bouleTab2[i].pos.x = WIDTH - (sizeBoule/2) -1;}
        if (bouleTab2[i].pos.x + (sizeBoule/2) > WIDTH) {bouleTab2[i].pos.x = 0 - (sizeBoule/2) +1;}
        if (bouleTab2[i].pos.y + (sizeBoule/2) < 0) {bouleTab2[i].pos.y = HEIGHT - (sizeBoule/2) -1;}
        if (bouleTab2[i].pos.y + (sizeBoule/2) > HEIGHT) {bouleTab2[i].pos.y = 0 - (sizeBoule/2) +1;}
        bouleTab2[i].vie -= 1;
        if ( sqrt(pow((bouleTab2[i].pos.x + sizeBoule/2) - (position.x + sizePion/2) ,2) + pow((bouleTab2[i].pos.y + sizeBoule/2) - (position.y + sizePion/2) ,2)) < sizeBoule)
        {
          score2++;
          bouleTab2[i].vie = -1;
        }  
      }
    }
    
    sprintf(str, "%d", score1);
    DrawString(str, 5, 5, 2, 'c', 250, 0, 0, renderer);
    sprintf(str, "%d", score2);
    DrawString(str, 95, 5, 2, 'c', 0, 0, 250, renderer);
    
    if (j1dd)
      SDL_RenderCopyEx(renderer, pion[0], NULL, &position, 0, NULL, SDL_FLIP_NONE);
    else if (j1gg)
      SDL_RenderCopyEx(renderer, pion[0], NULL, &position, 0, NULL, SDL_FLIP_HORIZONTAL);
    else if (j1hh)
      SDL_RenderCopyEx(renderer, pion[0], NULL, &position, 270, NULL, SDL_FLIP_NONE);
    else if (j1bb)
      SDL_RenderCopyEx(renderer, pion[0], NULL, &position, 90, NULL, SDL_FLIP_NONE);
    else {}

    if (j2gg)
      SDL_RenderCopyEx(renderer, pion[1], NULL, &position2, 0, NULL, SDL_FLIP_HORIZONTAL);
    else if (j2dd)
      SDL_RenderCopyEx(renderer, pion[1], NULL, &position2, 0, NULL, SDL_FLIP_NONE);
    else if (j2hh)
      SDL_RenderCopyEx(renderer, pion[1], NULL, &position2, 270, NULL, SDL_FLIP_NONE);
    else if (j2bb)
      SDL_RenderCopyEx(renderer, pion[1], NULL, &position2, 90, NULL, SDL_FLIP_NONE);
    else {}
    SDL_RenderPresent(renderer);
    if(score1 >= 10)
    {
      printf("Les rouges ont gagné\n");
      SDL_Delay(3000);
      program_on = 0;
    }
    if(score2 >= 10)
    {
      printf("Les bleu ont gagné\n");
      SDL_Delay(3000);
      program_on = 0;
    }
    // printf("1->%d & %d\n", position.x, position.y);
    // printf("2->%d & %d\n", position2.x, position2.y);
  }
  return;
}

int main(int argc, char const *argv[])
{
  SDL_Window *window_1 = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Texture ** joueur = NULL;
  SDL_Texture ** bouboule = NULL;
  boule * bouleTab;
  boule * bouleTab2;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) 
  {

    SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); // l'initialisation de la SDL a échoué 
    exit(EXIT_FAILURE);
  }

  if (TTF_Init() == -1)
  {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
  }

  RobotoFont = TTF_OpenFont("Roboto-Black.ttf", 70);
  if (RobotoFont == NULL) {
    fprintf(stderr, "error: font not found %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }

  /* Création de la fenêtre de gauche */
  window_1 = SDL_CreateWindow(
  "Fenêtre à gauche",                    // codage en utf8, donc accents possibles
  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,                                  // coin haut gauche en haut gauche de l'écran
  WIDTH, HEIGHT,                              // largeur = 400, hauteur = 300
  SDL_WINDOW_RESIZABLE);                 // redimensionnable
  if (window_1 == NULL) 
  {
    SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError()); // échec de la création de la fenêtre
    SDL_Quit(); // On referme la SDL       
    exit(EXIT_FAILURE);
  }

  renderer = SDL_CreateRenderer(window_1, -1, 0);
  loadPion(&renderer, &joueur);
  loadBoule(&renderer, &bouboule);
  bouleTab = initBoule(bouboule);
  bouleTab2 = initBoule(bouboule);
  game(window_1, renderer, joueur, bouleTab, bouleTab2, bouboule);
  freeBoule(bouleTab);
  freeBoule(bouleTab2);
  SDL_DestroyWindow(window_1);
  SDL_Quit();
  return 0;
}
