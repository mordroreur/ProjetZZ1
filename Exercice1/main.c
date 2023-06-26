#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define sizePion 50
#define vitesse 1

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

void game(SDL_Window * window, SDL_Renderer * renderer, SDL_Texture ** pion)
{
  SDL_Event event;
  int program_on = 1;
  int px; int py;
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
            case SDLK_UP: j2h = 1; j2hh = 1; j2gg = 0; j2dd = 0; j2bb = 0; break;
            case SDLK_LEFT: j2g = 1; j2hh = 0; j2gg = 1; j2dd = 0; j2bb = 0; break;
            case SDLK_DOWN: j2b = 1; j2hh = 0; j2gg = 0; j2dd = 0; j2bb = 1; break;
            case SDLK_RIGHT: j2d = 1; j2hh = 0; j2gg = 0; j2dd = 1; j2bb = 0; break;
            /* Bouger le joueur 1 */
            case SDLK_z: j1h = 1; j1hh = 1; j1gg = 0; j1dd = 0; j1bb = 0; break; 
            case SDLK_q: j1g = 1; j1hh = 0; j1gg = 1; j1dd = 0; j1bb = 0; break;
            case SDLK_s: j1b = 1; j1hh = 0; j1gg = 0; j1dd = 0; j1bb = 1; break;
            case SDLK_d: j1d = 1; j1hh = 0; j1gg = 0; j1dd = 1; j1bb = 0; break;  
            /* Bouger la fenêtre */
            case SDLK_4: SDL_SetWindowPosition(window, px-5, py); break;
            case SDLK_8: SDL_SetWindowPosition(window, px, py-5 ); break;
            case SDLK_2: SDL_SetWindowPosition(window, px, py+5); break;
            case SDLK_6: SDL_SetWindowPosition(window, px+5, py); break;                     
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
    
    SDL_RenderClear(renderer);
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
  }
  return;
}

int main(int argc, char const *argv[])
{
  SDL_Window *window_1 = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Texture ** joueur = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) 
  {

    SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); // l'initialisation de la SDL a échoué 
    exit(EXIT_FAILURE);
  }
  printf("test12\n");
  /* Création de la fenêtre de gauche */
  window_1 = SDL_CreateWindow(
  "Fenêtre à gauche",                    // codage en utf8, donc accents possibles
  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,                                  // coin haut gauche en haut gauche de l'écran
  1920/2, 1080/2,                              // largeur = 400, hauteur = 300
  SDL_WINDOW_RESIZABLE);                 // redimensionnable
  printf("test3\n");
  if (window_1 == NULL) 
  {
    SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError()); // échec de la création de la fenêtre
    SDL_Quit(); // On referme la SDL       
    exit(EXIT_FAILURE);
  }

  renderer = SDL_CreateRenderer(window_1, -1, 0);
  printf("test4\n");
  loadPion(&renderer, &joueur);
  game(window_1, renderer, joueur);
  printf("test\n");

  SDL_DestroyWindow(window_1);    
  SDL_Quit();
  return 0;
}
