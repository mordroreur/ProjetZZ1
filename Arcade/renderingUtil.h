#ifndef RENDERING_UTIL_HEADER_
#define RENDERING_UTIL_HEADER_

#include <SDL2/SDL.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>






#define IMBACKGROUNDU 0
#define IMBACKGROUNDD 1
#define IMBACKGROUNDT 2
#define IMBACKGROUNDQ 3
#define IMBACKGROUNDC 4
#define IMBACKGROUNDS 5

#define IMPLAYER1 6
#define IMPLAYER2 7
#define IMPLAYER3 8
#define IMPLAYER4 9

#define IMBOULEP1 10
#define IMBOULEP2 11
#define IMBOULEP3 12
#define IMBOULEP4 13

#define IMBUTTONPLAY 14
#define IMBUTTONQUIT 15
#define IMBUTTONPARAM 16
#define IMBUTTONFORM 17
#define IMBUTTONSELECT 18
#define IMBUTTONSELECT2 19
#define IMBUTTONSELECT3 20
#define IMBUTTONSELECT4 21
#define IMBUTTONBACK 22
#define IMBUTTONJOUER 23
#define IMBUTTONIATRAIN 24
#define IMBLACKHOLE 25
#define IMVIE 26


typedef struct Rect{
  float x;
  float y;
  float w;
  float h;
}frect;

typedef struct boule
{
  int vie;
  frect pos;
  //float speed;
  float vitX;
  float vitY;
} boule;

typedef struct player
{

  int input[5];
  frect pos;
  float vitesse;
  
  int kill;
  int mort;
  int maxBouleVie;
  int vie;

  int nbBoule;
  boule* boubou;
  int dirX;
  int dirY;
  int vitTire;
  
  int equipe;

  int IAType;

  int peuTirer;
  int index;
  int debBoule;
  int nbBouleActive;
  int shoot;
  
} player;


typedef struct objet{

  int id;
  
  SDL_Rect pos;

  int vie;

}objet;

typedef struct Ecran{

  SDL_Window *window;
  SDL_Renderer *renderer;

  int isFullScreen;
  int sizeX;
  int sizeY;
  int otherX;
  int otherY;
  
  int etapeDuJeu;

  int whichBack;
  
  player *pla;

  int nbProie;
  int nbPreda;

  int nbBananes;
  int nbObjetsMax;
  objet* tbObjet;
  

  int etapeMenu;
  int modePlay;
  int maxBoule;
  int maxVie;
  int nbPlayer;

  int TrouNoirTime;
  
  /* rajout par Thomas*/
  Mix_Music * musique[2]; //tableau qui contient toutes les musiques
  int decalageB1; // décallage du bouton Play au menu
  int decalageB2; // décallage du bouton quitter au menu
  int decalageB3; // décallage parametre
  int decalageB4; //decallage parametremenu
  int decalageB5; // decallage selectMenu
  int decalageB6; // decallage du bouton "play" dans selectMenu
  int etapeParam; // dans quelle étape sommes-nous pour les parametres
  int bonus; // boolean pour savoir si les bonus sont activés
  int trousNoir; // boolean pour savoir si les bonus sont activés
     int etapeSelGam; // boolean permettant de savoir dans quel cas nous sommes pour DrawSelectGame
  int etape2SelGam; //  boolean permettant de savoir dans quel cas des cas nous sommes pour DrawSelectGame
  int previousSelGam; // indique l'ancien game sélectionné
  int backSelec; // boolean pour savoir si on "part de la sélection"
  int nbJoueur; // nombre joueur pour le FFA
    int nbHumainP; // nombre joueur predateur
    int nbHumainM; // nombre joueur mouton
    int nbIAP; // nombre IA prédator
    int nbIAM; //nombre IA mouton
    int yve; //tkt
  int showImage; // boolean si on montre les images de début ou pas
}ecran;

/*player * newPlayer(char * name, int xPos, int yPos, int vitesse)
{
    player * p = (player*) malloc(sizeof(player));
    p->x = xPos;
    p->y = yPos;
    p->pioche = 0;
    p->mur = 0;
    p->vitesse = vitesse;
    p->coffre = 0;
    p->nbrLingo = 0;
    p->kill = 0;
    p->mort = 0;
    sprintf(p->nom, name);
    return p;
}*/

long int getTime();
void DrawString(char *s, float x, float y, float size, char center, int R, int G, int B, ecran *screen);
void InitImage(ecran *screen);
void freeImageMalloc();
void DrawImage(int imagenb, float x, float y, float sizeX, float sizeY, char center, int etatPremier, float TimebeforeNext, int flip, int angle, int nbState, int* spriteOrder, ecran *screen);
int isInButton(float x, float y, float sizeX, float sizeY, char center, int posMX, int posMY, ecran *screen);
void loadRobotoFont();
int loadImageMenu(ecran *screen);
int imagePreface(ecran* screen, int i);
SDL_Texture * loadImage(const char * path, SDL_Renderer *renderer);
void loadMusic(ecran* screen);

#endif /* RENDERING_UTIL_HEADER_ */
