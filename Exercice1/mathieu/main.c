#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>


int main(){

  SDL_DisplayMode DM;  
  int width;
  int  height;
  int inGame = 1;

  //srand(time(NULL));
  srand(42);
  
  if(SDL_Init(SDL_INIT_VIDEO) != 0){
    exit(0);
  }

  SDL_GetCurrentDisplayMode(0, &DM);
  width = DM.w;
  height = DM.h;

  //printf("%d  %d \n", width, height);
  
  SDL_Window *barreWin = SDL_CreateWindow("player", (width/2) - (width/16), height-(height/8), (width/8), (height/16), SDL_WINDOW_BORDERLESS);
  SDL_Renderer* barreRen = SDL_CreateRenderer(barreWin, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(barreRen, 0, 255, 0, 255);
  SDL_RenderClear(barreRen);
  SDL_RenderPresent(barreRen);

  SDL_Window *balleWin = SDL_CreateWindow("balle", 0, height-(height/8) - (height/32), (height/32), (height/32), SDL_WINDOW_BORDERLESS);
  SDL_Renderer* balleRen = SDL_CreateRenderer(balleWin, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(balleRen, 255, 255, 255, 255);
  SDL_RenderClear(balleRen);
  SDL_RenderPresent(balleRen);

  
  int Barre_x;
  int Barre_y;

  int life = 3;
  int balleState = -1;
  float ballX = 0;
  float ballY = 0;
  
  
  while(inGame){
    SDL_Delay(10);
    SDL_Event event;
    SDL_GetWindowPosition(barreWin, &Barre_x, &Barre_y);


    if(balleState == -1){
      SDL_SetWindowPosition(balleWin, Barre_x + (width/16.0) - (height/64), Barre_y - (height/32));
    }else{
      ballX += cos(balleState);
      ballY += sin(balleState);
      SDL_SetWindowPosition(balleWin, ballX, ballY);
    }

    
    
    while (SDL_PollEvent(&event)) {
      
      switch (event.type) {
      case SDL_KEYDOWN:
	if(event.key.keysym.sym == 27){
	  inGame = 0;
	}else if(event.key.keysym.sym == 1073741904){
	  if(Barre_x > 0){
	    Barre_x -= 10;
	  }
	  SDL_SetWindowPosition(barreWin, Barre_x, Barre_y);
	}else if(event.key.keysym.sym == 1073741903){
	  if(Barre_x < width - (width/8)){
	    Barre_x += 10;
	  }
	  SDL_SetWindowPosition(barreWin, Barre_x, Barre_y);
	  
	}else if(event.key.keysym.sym == 32 && balleState == -1){
	  balleState = (rand()%160)+10;
	  //	  printf("%d\n", balleState);
	  ballX = Barre_x + (width/16.0) - (height/64);
	  ballY = Barre_y - (height/32);
	}else{
	  printf("%d\n", event.key.keysym.sym);
	}
	break;
      default: break;
      }
    }
  }  
}
