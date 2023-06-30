#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>

#define PI 3.1415


int main(){

  printf("test\n");
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
  printf("test2\n");

  
  int Barre_x;
  int Barre_y;

  int life = 3;
  int balleState = -1;
  float ballX = 0;
  float ballY = 0;

  float speed = (height/128.0) * 1;
  
  while(inGame)
  {
    printf("test3\n");
    SDL_Delay(10);
    SDL_Event event;
    SDL_GetWindowPosition(barreWin, &Barre_x, &Barre_y);
    //printf("Le balle : %d\n", balleState);

    if(balleState == -1)
    {
      SDL_SetWindowPosition(balleWin, Barre_x + (width/16.0) - (height/64), Barre_y - (height/32));
    } 
    else 
    {
      ballX += cos((balleState * 2 * PI)/360)*speed;
      ballY -= sin((balleState * 2 * PI)/360)*speed;
      if(ballX < cos(balleState)*speed)
      {
	      if(balleState < 180)
        {
	        balleState = 180 - balleState;
        } 
        else 
        {
          balleState = 360 - balleState +180;
        }
      } 
      else if(ballX > width-cos((balleState * 2 * PI)/360)*speed - (height/32))
      {
        if(balleState < 180)
        {
          balleState = 180-balleState;
        }
        else
        {
          balleState = 360-balleState +180 % 360;
        }
      }
      
      
      if(ballY < sin(balleState)*speed  + (height/32))
      {
        printf("De : %d\n", balleState);
        balleState = 360-balleState;
        printf("%d\n", balleState);
        ballY = (height/32.0)*1.2;
      }
      else if(ballY > Barre_y+sin((balleState * 2 * PI)/360)*speed - (height/32.0) && ballX > Barre_x && ballX < Barre_x+(width/8))
      {
        balleState = 360 - balleState;
        ballY = Barre_y - (height/32) -1;
      }
      else if(ballY > height-sin((balleState * 2 * PI)/360)*speed - (height/16))
      {
        balleState = -1;
        life--;
        if(life == 0)
        {
          printf("testICH\n");
          inGame = 0;
        }
      }     
      SDL_SetWindowPosition(balleWin, ballX, ballY);
    }
    printf("test4\n"); 
    while (SDL_PollEvent(&event)) 
    {
      
      switch (event.type) 
      {
        case SDL_KEYDOWN:
          if(event.key.keysym.sym == 27)
          {
            printf("test5ICH\n");
            inGame = 0;
          }
          else if(event.key.keysym.sym == 1073741904)
          {
            printf("test11\n");
            if(Barre_x > 0)
            {
              Barre_x -= (height/40);
              if(Barre_x < 0)
              {
                Barre_x = 0;
              }
            printf("test14\n");
          }
            SDL_SetWindowPosition(barreWin, Barre_x, Barre_y);
          } 
          else if(event.key.keysym.sym == 1073741903)
          {
            printf("test7\n");
            if(Barre_x < width - (width/8))
            {
              Barre_x += (height/40);
              if(Barre_x > width - (width/8))
              {
                Barre_x = width - (width/8);
              }
              printf("test10\n");
            }
            SDL_SetWindowPosition(barreWin, Barre_x, Barre_y);
          }
          else if(event.key.keysym.sym == 32 && balleState == -1)
          {
            printf("test9\n");
            balleState = (rand()%160)+10;
            //	  printf("%d\n", balleState);
            ballX = Barre_x + (width/16.0) - (height/64);
            ballY = Barre_y - (height/32);
            printf("test8\n");
          }
          else
          {
            printf("%d\n", event.key.keysym.sym);
          }
        break;
        default: break;
      }
    }
    printf("test5 %d\n", inGame);
  }
  printf("test6\n"); 
}
