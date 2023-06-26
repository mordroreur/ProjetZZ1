#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

/*void initFrame(SDL_Window ** window, SDL_Renderer ** renderer, SDL_Texture ** texture)
{
    texture = loadImage("pres.PNG", *renderer);
    if(!textureTableauOptionMenu) {
      fprintf(stderr, "Error loadTextureOptionMenu for textureTableauOptionMenu : %s\n", SDL_GetError()); 
      return -1; 
    }
    return;
}*/

void game(SDL_Window * window, SDL_Renderer * renderer)
{
  SDL_Event event;
  SDL_Rect rectangle;
  int program_on = 1;
  int px;
  int py;
  while (program_on) // La boucle des évènements
  {                            
    while(SDL_PollEvent(&event)) // Tant que on n'a pas trouvé d'évènement utile
    {  
      SDL_GetWindowPosition(window, &px, &py);
      switch (event.type)
      {                         // En fonction de la valeur du type de cet évènement
        case SDL_QUIT:                                // Un évènement simple, on a cliqué sur la x de la // fenêtre
          program_on = 0;                     // Il est temps d'arrêter le programme
        break;
        case SDL_KEYDOWN:                             // Le type de event est : une touche appuyée 
          switch (event.key.keysym.sym) 
          {
            case SDLK_SPACE:
              printf("OUI\n");
                    SDL_SetRenderDrawColor(renderer,                                       
                  50, 0, 0,                             // mode Red, Green, Blue (tous dans 0..255)
                  255);                                 // 0 = transparent ; 255 = opaque
              rectangle.x = 0;                                             // x haut gauche du rectangle
              rectangle.y = 0;                                                  // y haut gauche du rectangle
              rectangle.w = 400;                                                // sa largeur (w = width)
              rectangle.h = 400;                                                // sa hauteur (h = height)
              SDL_RenderFillRect(renderer, &rectangle); 
            break;    
            case SDLK_q:
              SDL_SetWindowPosition(window, px-1, py);
            break;
            case SDLK_z:
              SDL_SetWindowPosition(window, px, py-1 );
            break;
            case SDLK_s:
              SDL_SetWindowPosition(window, px, py+1);
            break;
            case SDLK_d:
              SDL_SetWindowPosition(window, px+1, py);
            break;                     
            default:                                    // Une touche appuyée qu'on ne traite pas
            break;
          }
        break;
      }
    }
  }
  return;
}

int main(int argc, char const *argv[])
{
  SDL_version nb;
  SDL_VERSION(&nb);
  printf("Version de la SDL : %d.%d.%d\n", nb.major, nb.minor, nb.patch);

  // création 2 fenêtre
  SDL_Window *window_1 = NULL;
  SDL_Renderer *renderer = NULL;
  printf("test1\n");

  /* Initialisation de la SDL */
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
  960, 540,                              // largeur = 400, hauteur = 300
  SDL_WINDOW_RESIZABLE);                 // redimensionnable
  printf("test3\n");
  if (window_1 == NULL) 
  {
    SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError()); // échec de la création de la fenêtre
    SDL_Quit(); // On referme la SDL       
    exit(EXIT_FAILURE);
  }

  renderer = SDL_CreateRenderer(window_1, -1, 0);
  SDL_Delay(2000);
  printf("test4\n");
  //initFrame(&window_1, &renderer, &texture);
  game(window_1, renderer);
  printf("test\n");

  SDL_DestroyWindow(window_1);    
  SDL_Quit();
  return 0;
}
