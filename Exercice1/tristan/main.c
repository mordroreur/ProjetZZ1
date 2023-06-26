#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {

    srand( time( NULL ) );
    (void)argc;
    (void)argv;
    int bool = 0;
    int v = 3;
    int fw = 400;
    int fh = 300;
    int r = 255;
    int g = 255;
    int b = 255;
    int movex = v;
    int movey = v;
    SDL_Window 
    *fenet = NULL;                 

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", 
        SDL_GetError());                
        exit(EXIT_FAILURE);
    }

    fenet = SDL_CreateWindow("DVD", 500, 500, fw, fh, SDL_WINDOW_RESIZABLE|SDL_WINDOW_BORDERLESS);         
    if (fenet == NULL) {
        SDL_Log("Error : SDL window 1 creation - %s\n", 
        SDL_GetError());            
        SDL_Quit();                        
        exit(EXIT_FAILURE);
    }                        

    SDL_Renderer* rendcolor = SDL_CreateRenderer(fenet, -1, SDL_RENDERER_ACCELERATED);
    SDL_bool
    program_on = SDL_TRUE,                                          
    event_utile = SDL_FALSE;                        
    SDL_Event event; 
    int x = 500;
    int y = 500;                                 
    while (program_on) {   
        SDL_SetWindowPosition(fenet, x, y); 
        SDL_SetRenderDrawColor(rendcolor, r, g, b, 255);
        SDL_RenderClear(rendcolor);
        SDL_RenderPresent(rendcolor);                          
        event_utile = SDL_FALSE;
        while(!event_utile && SDL_PollEvent(&event)) {  
            switch (event.type) {                         
                case SDL_QUIT:                                
                    program_on = SDL_FALSE;                     
                    event_utile = SDL_TRUE;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {        
                        case SDLK_ESCAPE:
                            program_on = 0;
                        break;                     
                        case SDLK_q:                          
                            program_on = 0;                                       
                            event_utile = SDL_TRUE;
                            break;
                        default:                                 
                            break;
                    }   
                    break;
            }
        }


        if(x<=30) {
            movex = v;
            bool=1;
        }
        else if(x+fw>=1950) {
            movex = -v;
            bool=1;
        }
        if(y<=65) {
            movey = v;
            bool=1;
        }
        else if(y+fh >= 1080) {
            movey= -v;
            bool=1;
        }
        if(bool == 1) {
            v = 3+(rand()%3);
            r = rand()%256;
            g = rand()%256;
            b = rand()%256;
            bool = 0;
        }
        x += movex;
        y += movey;
    }

    return 0;
    }


