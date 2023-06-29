#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <time.h>

#define WIDTH 200
#define HEIGHT 200
#define nbrWin 11
#define attente 15

TTF_Font * RobotoFont;

typedef struct ecran
{
    SDL_Window * window;
    SDL_Renderer * renderer;
    int x;
    int y;
    int orX;
    int orY;
    int go;
    int etat;
    int vitesse;
    int tour;
} ecran;

int nbrA(int min, int max) 
{ 
    int nombreAleatoire = (rand() % (max - min + 1)) + min;
    return nombreAleatoire;
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    ecran * screen = (ecran*) malloc(nbrWin*sizeof(ecran));
    SDL_Event event;
    int on = 1;
    int timer = 0;
    int index = -1;
    int course = 0;
    SDL_Rect textRect;
    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
    SDL_Color color = {0, 0, 0, 255};
    char Val[10];
    if (argc > 0)
        course = atoi(argv[1]);
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() == -1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    RobotoFont = TTF_OpenFont("Roboto-Black.ttf",100);
    if (RobotoFont == NULL) {
        fprintf(stderr, "error: font not found %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nbrWin; i++)
    {
        screen[i].window = SDL_CreateWindow("tourne", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_BORDERLESS);
        if (screen[i].window == NULL) 
        {
            SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError()); 
            SDL_Quit();      
            exit(EXIT_FAILURE);
        }
        screen[i].renderer = SDL_CreateRenderer(screen[i].window, -1, 0);
    }

    for (int i = 0; i < nbrWin; i++)
    {
        screen[i].vitesse = 30;
        screen[i].x = 0;
        screen[i].y = 0;
        screen[i].orX = 0;
        screen[i].orY = screen[i].vitesse;;
        screen[i].go = 0;
        screen[i].etat = 0;
        screen[i].tour = 0;
        SDL_SetRenderDrawColor(screen[i].renderer, nbrA(0,255), nbrA(0,255), nbrA(0,255), 255);
        SDL_SetWindowPosition(screen[i].window, screen[i].x, screen[i].y);
    }
    
    while (on) {
        while(SDL_PollEvent(&event)) {
            switch (event.type) { 
                case SDL_QUIT: on = 0; break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_q:on = 0; break;
                    }
                break;
            }
        }
        timer++;
        if(timer > attente)
        {
            timer = 0;
            index = (index+1)%nbrWin;
            screen[index].go = 1;
        }
        for (int i = 0; i < nbrWin; i++)
        {
            if (screen[i].go == 1)
            {
                SDL_RenderClear(screen[i].renderer);
                sprintf(Val, "%d", screen[i].tour);
                textSurface = TTF_RenderText_Solid(RobotoFont, Val, color);
                textTexture = SDL_CreateTextureFromSurface(screen[i].renderer, textSurface);
                SDL_FreeSurface(textSurface);
                SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
                textRect.x = WIDTH/2 - textRect.w/2;
                textRect.y = HEIGHT/2 - textRect.h/2;
                SDL_RenderCopy(screen[i].renderer, textTexture, NULL, &textRect);
                SDL_DestroyTexture(textTexture);
                //printf("x: %d, y: %d, orX: %d, orY: %d\n", screen[i].x, screen[i].y, screen[i].orX, screen[i].orY);
                screen[i].x = screen[i].x + screen[i].orX;
                screen[i].y = screen[i].y + screen[i].orY;
                SDL_SetWindowPosition(screen[i].window, screen[i].x, screen[i].y);
                if (screen[i].y >= 1080 - HEIGHT && screen[i].etat == 0)
                {
                    screen[i].orY = 0;
                    screen[i].orX = screen[i].vitesse;
                    screen[i].etat = 1;
                }
                if (screen[i].x >= 1920 - WIDTH && screen[i].etat == 1)
                {
                    if (course)
                        screen[i].vitesse = nbrA(1,50);
                    screen[i].orY = screen[i].vitesse * -1;
                    screen[i].orX = 0;
                    screen[i].etat = 2;
                }
                if (screen[i].y <= 0 && screen[i].etat == 2)
                {
                    screen[i].orY = 0;
                    screen[i].orX = screen[i].vitesse * -1;
                    screen[i].etat = 3;
                }
                if (screen[i].x <= 0 && screen[i].etat == 3)
                {
                    screen[i].orY = screen[i].vitesse;
                    screen[i].orX = 0;
                    screen[i].etat = 0;
                    screen[i].tour += 1;
                }
            }
        SDL_RenderPresent(screen[i].renderer);          
        }
    }
    return 0;
}
