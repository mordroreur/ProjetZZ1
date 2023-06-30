#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL2/SDL_image.h"


// void drawrect(SDL_Renderer * rendy, SDL_Rect *rect, int * vrect, int * moverectx, int * moverecty, int fw, int fh){
//     int bool = 0;
//     SDL_Delay(100);

//     int vrectint = *vrect;
//     int moverectxint = *moverectx;
//     int moverectyint = *moverecty;
//     printf("deb %i\n", moverectxint);
//     if((rect->x)<=0) {
//         moverectxint = vrectint;
//         bool=1;
//     }
//     else if((rect->x)+(rect->w)>=fw) {
//         moverectxint = -vrectint;
//         printf("if %i\n", moverectxint);
//         bool=1;
//     }
//     if((rect->y)<=0) {
//         moverectyint = vrectint;
//         bool=1;
//     }
//     else if((rect->y)+(rect->h) >= fh) {
//         moverectyint = -vrectint;
//         bool=1;
//     }
//     if(bool == 1) {
//         vrectint = 10+(rand()%5);
//         int r = rand()%256;
//         int g = rand()%256;
//         int b = rand()%256;
//         SDL_SetRenderDrawColor(rendy, r, g, b, 255);
//         bool = 0;
//     }
//     rect->x += moverectxint;
//     rect->y += moverectyint;

//   //  SDL_RenderClear(rendy);
//     //printf("%i %i %i\n",rect->x,rect->w,fw);
//     //printf("%i %i %i\n",rect->y,rect->h,fh);
//     SDL_SetRenderDrawColor(rendy, 0, 0, 0, 255);
//     SDL_RenderFillRect(rendy, rect);
//     SDL_RenderPresent(rendy);
//     printf("fin %i\n", moverectxint);
//     *moverectx = moverectxint;
//     *moverecty = moverectyint;
//     *vrect = vrectint;
//     printf("apres fin %i\n", *moverectx);
// }


int main(int argc, char **argv) {

    srand( time( NULL ) );
    (void)argc;
    (void)argv;
    int bool = 0;
    int boolrect = 0;
    int v = 3;
    int fw = 400;
    int fh = 300;
    int r = rand()%256;
    int g = rand()%256;
    int b = rand()%256;
    int movex = v;
    int movey = v;
    SDL_Rect rect;
    rect.x = 190;
    rect.y = 145;
    rect.w = 60;
    rect.h = 60;
    int vrect = 5;
    int moverectx = vrect;
    int moverecty = vrect;
    double angle = 0;
    

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
    SDL_Surface* CD = IMG_Load("SpriteCD.png");
    SDL_Texture* SpriteCD = SDL_CreateTextureFromSurface(rendcolor,CD);
    SDL_FreeSurface(CD);
    int x = 500;
    int y = 500;                                 
    while (program_on) { 
        SDL_Delay(10);  
        SDL_SetWindowPosition(fenet, x, y); 
        SDL_SetRenderDrawColor(rendcolor, r, g, b, 255);

       // SDL_RenderPresent(rendcolor);                          
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

    if((rect.x)<=0) {
    moverectx = vrect;
    boolrect=1;
    }
    else if((rect.x)+(rect.w)>=fw) {
        moverectx = -vrect;
        boolrect=1;
    }
    if((rect.y)<=0) {
        moverecty = vrect;
        boolrect=1;
    }
    else if((rect.y)+(rect.h) >= fh) {
        moverecty = -vrect;
        boolrect=1;
    }
    if(boolrect == 1) {
        vrect = 4+(rand()%3);
        boolrect = 0;
    }

    
    rect.x += moverectx;
    rect.y += moverecty;
        angle = (angle+0.0325);
        if(angle>=6) angle = 0;
        SDL_RenderClear(rendcolor);
        SDL_SetRenderDrawColor(rendcolor, 0, 0, 0, 255);
        //SDL_RenderFillRect(rendcolor, &rect);
        //SDL_RenderCopy(rendcolor,SpriteCD,NULL,&rect);
        SDL_RenderCopyEx(rendcolor, SpriteCD, NULL, &rect, 60*angle, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(rendcolor);
        
    }

    return 0;
    }


