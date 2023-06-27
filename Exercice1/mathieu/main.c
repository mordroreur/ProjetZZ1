#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
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

  //printf("%d  %d \n", width, height);
  
  SDL_Window *barreWin = SDL_CreateWindow("test", (width/2) - (width/16), height-(height/8), (width/8), (height/16), SDL_WINDOW_BORDERLESS);
  SDL_Renderer* barreRen = SDL_CreateRenderer(barreWin, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(barreRen, 0, 255, 0, 255);
  SDL_RenderClear(barreRen);
  SDL_RenderPresent(barreRen);

  
  int Barre_x = (width/2) - (width/16);
  int Barre_y = height-(height/8);
  SDL_SetWindowPosition(barreWin, Barre_x, Barre_y);
  
  while(inGame){
    SDL_Delay(10);
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {

      switch (event.type) {
      case SDL_KEYDOWN:
	if(event.key.keysym.sym == 27){
	  inGame = 0;
	}else if(event.key.keysym.sym == 1073741904){
	  if(Barre_x > (width/16)){
	    Barre_x -= 10;
	  }
	  SDL_SetWindowPosition(barreWin, Barre_x, Barre_y);
	}else if(event.key.keysym.sym == 1073741903){
	  if(Barre_x < width - (width/16)){
	    Barre_x += 10;
	  }
	  SDL_SetWindowPosition(barreWin, Barre_x, Barre_y);
	}else{
	  printf("%d\n", event.key.keysym.sym);
	}
	break;
      default: break;
      }
    }
  }  
}
