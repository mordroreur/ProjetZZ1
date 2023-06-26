#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>


int main(){

  SDL_DisplayMode DM;  
  int width;
  int  height;

  int inGame = 1;
  
  if(SDL_Init(SDL_INIT_VIDEO) != 0){
    exit(0);
  }

  SDL_GetCurrentDisplayMode(0, &DM);
  width = DM.w;
  height = DM.h;

  
  SDL_Window *barreWin = SDL_CreateWindow("test", (width/2) - (width/16), height-(height/8), (width/8), (height/16), SDL_WINDOW_BORDERLESS);
  SDL_Renderer* barreRen = SDL_CreateRenderer(barreWin, -1, 0);
  SDL_SetRenderDrawColor(barreRen, 0, 255, 0, 255);
  SDL_RenderClear(barreRen);
  SDL_RenderPresent(barreRen);

  while(inGame){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_KEYDOWN:
	if(event.key.keysym.sym == 27){
	  inGame = 0;
	}
	printf("%d\n", event.key.keysym.sym);break;
      default: break;
      }
    }
  }  
}
