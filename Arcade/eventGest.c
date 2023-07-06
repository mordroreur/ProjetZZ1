#include "eventGest.h"
#include "IAtrain.h"
#include "renderingBase.h"
#include "ticksGest.h"
#include <SDL2/SDL_mixer.h>


void keyUp(SDL_KeyboardEvent key, ecran *screen) {
  if(key.keysym.sym == SDLK_ESCAPE){

	if (screen->etapeDuJeu == 5 || screen->etapeDuJeu == 4)
	  {
		Mix_PlayMusic(screen->musique[0], -1);
		screen->etapeDuJeu = 12;
		SDL_Delay(50);
		screen->decalageB1 = 116;
		screen->decalageB2 = 130;
	  }
	else if (screen->etapeDuJeu == 10)
	  {
		screen->etapeParam = 0;
		screen->etapeDuJeu = 11;
		writeParamFile(screen->isFullScreen?screen->otherX:screen->sizeX, screen->isFullScreen?screen->otherY:screen->sizeY, screen->isFullScreen, Mix_VolumeMusic(-1), screen->bonus, screen->trousNoir);
	  }
	else if (screen->etapeDuJeu == 13)
	  {
		screen->backSelec = 1;
		if (screen->etapeSelGam)
		  {
			screen->etape2SelGam = 0;
			screen->previousSelGam = screen->etapeSelGam;
			screen->etapeSelGam = 0;
		  }
		else
		  {
			screen->etapeDuJeu = 14;
		  }
	  }
	else
	  screen->etapeDuJeu = 0;
  }else if(screen->etapeDuJeu == 4){
    int index = 0;
	int input[4];
	if(screen->etapeSelGam == 4){
	  for(int i = 0; i < screen->nbHumainP; i++){
		input[index++] = i;
	  }
	  for(int i = screen->nbPreda; i < screen->nbHumainM + screen->nbPreda; i++){
		input[index++] = i;
	  }
	  for(; index < 4;index++){
		input[index] = -1;
	  }
	}else{
	  for(int i = 0; i < screen->nbPlayer; i++){
		input[i] = i;
	  }
	}
		

	switch (key.keysym.sym)
	  {
		/* Joueur 2*/
	  case SDLK_UP: if(screen->nbPlayer > 1 && input[1] != -1) screen->pla[input[1]].input[1] = 0; break;
	  case SDLK_LEFT: if(screen->nbPlayer > 1 && input[1] != -1) screen->pla[input[1]].input[0] = 0; break;
	  case SDLK_DOWN: if(screen->nbPlayer > 1 && input[1] != -1) screen->pla[input[1]].input[3] = 0; break;
	  case SDLK_RIGHT: if(screen->nbPlayer > 1 && input[1] != -1) screen->pla[input[1]].input[2] = 0; break;
	  case SDLK_t: if(screen->nbPlayer > 1 && input[1] != -1) screen->pla[input[1]].input[1] = 0; break;
	  case SDLK_f: if(screen->nbPlayer > 1 && input[1] != -1) screen->pla[input[1]].input[0] = 0; break;
	  case SDLK_g: if(screen->nbPlayer > 1 && input[1] != -1) screen->pla[input[1]].input[3] = 0; break;
	  case SDLK_h: if(screen->nbPlayer > 1 && input[1] != -1) screen->pla[input[1]].input[2] = 0; break;
	  case SDLK_y: if(screen->nbPlayer > 1 && input[1] != -1) screen->pla[input[1]].input[4] = 0; break;
	  case SDLK_RSHIFT: if(screen->nbPlayer > 1 && input[1] != -1) screen->pla[input[1]].input[4] = 0; break;
		/* Joueur 1 */
	  case SDLK_q: if(screen->nbPlayer > 0 && input[0] != -1) screen->pla[input[0]].input[0] = 0; break;
	  case SDLK_z: if(screen->nbPlayer > 0 && input[0] != -1) screen->pla[input[0]].input[1] = 0; break;
	  case SDLK_s: if(screen->nbPlayer > 0 && input[0] != -1) screen->pla[input[0]].input[3] = 0; break;
	  case SDLK_d: if(screen->nbPlayer > 0 && input[0] != -1) screen->pla[input[0]].input[2] = 0; break;
	  case SDLK_SPACE: if(screen->nbPlayer > 0 && input[0] != -1) screen->pla[input[0]].input[4] = 0; break;
	  case SDLK_e: if(screen->nbPlayer > 0 && input[0] != -1) screen->pla[input[0]].input[4] = 0; break;
		/*Joueur 3*/
	  case SDLK_i: if(screen->nbPlayer > 2 && input[2] != -1) screen->pla[input[2]].input[1] = 0; break;
	  case SDLK_j: if(screen->nbPlayer > 2 && input[2] != -1) screen->pla[input[2]].input[0] = 0; break;
	  case SDLK_k: if(screen->nbPlayer > 2 && input[2] != -1) screen->pla[input[2]].input[3] = 0; break;
	  case SDLK_l: if(screen->nbPlayer > 2 && input[2] != -1) screen->pla[input[2]].input[2] = 0; break;
	  case SDLK_o: if(screen->nbPlayer > 2 && input[2] != -1) screen->pla[input[2]].input[4] = 0; break;
		/*Joueur 4*/
	  case 1073741824: if(screen->nbPlayer > 3 && input[3] != -1) screen->pla[input[3]].input[1] = 0; break;
	  case SDLK_m: if(screen->nbPlayer > 3 && input[3] != -1) screen->pla[input[3]].input[0] = 0; break;
	  case 249: if(screen->nbPlayer > 3 && input[3] != -1) screen->pla[input[3]].input[3] = 0; break;
	  case SDLK_ASTERISK: if(screen->nbPlayer > 3 && input[3] != -1) screen->pla[input[3]].input[2] = 0; break;
	  case SDLK_DOLLAR: if(screen->nbPlayer > 3 && input[3] != -1) screen->pla[input[3]].input[4] = 0; break;
			
	  default:
		break;
	  }
  }
}

void keyDown(SDL_KeyboardEvent key, ecran *screen) 
{
  if(screen->etapeDuJeu == 4)
	{
	  int index = 0;
	  int input[4];
	  if(screen->etapeSelGam == 4){
		for(int i = 0; i < screen->nbHumainP; i++){
		  input[index++] = i;
		}
		for(int i = screen->nbPreda; i < screen->nbHumainM + screen->nbPreda; i++){
		  input[index++] = i;
		}
		for(; index < 4;index++){
		  input[index] = -1;
		}
	  }else{
		for(int i = 0; i < screen->nbPlayer; i++){
		  input[i] = i;
		}
	  }
		

	  switch (key.keysym.sym)
		{
		  /* Joueur 2*/
		case SDLK_UP: if(screen->nbPlayer > 1 && input[1] != -1) screen->pla[input[1]].input[1] = 1; break;
		case SDLK_LEFT: if(screen->nbPlayer > 1 && input[1] != -1) screen->pla[input[1]].input[0] = 1; break;
		case SDLK_DOWN: if(screen->nbPlayer > 1 && input[1] != -1) screen->pla[input[1]].input[3] = 1; break;
		case SDLK_RIGHT: if(screen->nbPlayer > 1 && input[1] != -1) screen->pla[input[1]].input[2] = 1; break;
		case SDLK_t: if(screen->nbPlayer > 1 && input[1] != -1) screen->pla[input[1]].input[1] = 1; break;
		case SDLK_f: if(screen->nbPlayer > 1 && input[1] != -1) screen->pla[input[1]].input[0] = 1; break;
		case SDLK_g: if(screen->nbPlayer > 1 && input[1] != -1) screen->pla[input[1]].input[3] = 1; break;
		case SDLK_h: if(screen->nbPlayer > 1 && input[1] != -1) screen->pla[input[1]].input[2] = 1; break;
		case SDLK_y: if(screen->nbPlayer > 1 && input[1] != -1) screen->pla[input[1]].input[4] = 1; break;
		case SDLK_RSHIFT: if(screen->nbPlayer > 1 && input[1] != -1 && screen->pla[input[1]].input[4] == 0) screen->pla[input[1]].input[4] = 1; break;
		  /* Joueur 1 */
		case SDLK_q: if(screen->nbPlayer > 0 && input[0] != -1) screen->pla[input[0]].input[0] = 1; break;
		case SDLK_z: if(screen->nbPlayer > 0 && input[0] != -1) screen->pla[input[0]].input[1] = 1; break;
		case SDLK_s: if(screen->nbPlayer > 0 && input[0] != -1) screen->pla[input[0]].input[3] = 1; break;
		case SDLK_d: if(screen->nbPlayer > 0 && input[0] != -1) screen->pla[input[0]].input[2] = 1; break;
		case SDLK_SPACE: if(screen->nbPlayer > 0 && input[0] != -1 && screen->pla[input[0]].input[4] == 0) screen->pla[input[0]].input[4] = 1; break;
		case SDLK_e: if(screen->nbPlayer > 0 && input[0] != -1 && screen->pla[input[0]].input[4] == 0) screen->pla[input[0]].input[4] = 1; break;
		  /*Joueur 3*/
		case SDLK_i: if(screen->nbPlayer > 2 && input[2] != -1) screen->pla[input[2]].input[1] = 1; break;
		case SDLK_j: if(screen->nbPlayer > 2 && input[2] != -1) screen->pla[input[2]].input[0] = 1; break;
		case SDLK_k: if(screen->nbPlayer > 2 && input[2] != -1) screen->pla[input[2]].input[3] = 1; break;
		case SDLK_l: if(screen->nbPlayer > 2 && input[2] != -1) screen->pla[input[2]].input[2] = 1; break;
		case SDLK_o: if(screen->nbPlayer > 2 && input[2] != -1 && screen->pla[input[2]].input[4] == 0) screen->pla[input[2]].input[4] = 1; break;
		  /*Joueur 4*/
		case 1073741824: if(screen->nbPlayer > 3 && input[3] != -1) screen->pla[input[3]].input[1] = 1; break;
		case SDLK_m: if(screen->nbPlayer > 3 && input[3] != -1) screen->pla[input[3]].input[0] = 1; break;
		case 249: if(screen->nbPlayer > 3 && input[3] != -1) screen->pla[input[3]].input[3] = 1; break;
		case SDLK_ASTERISK: if(screen->nbPlayer > 3 && input[3] != -1) screen->pla[input[3]].input[2] = 1; break;
		case SDLK_DOLLAR: if(screen->nbPlayer > 3 && input[3] != -1 && screen->pla[input[3]].input[4] == 0) screen->pla[input[3]].input[4] = 1; break;
			
		default:
		  break;
		}
	
  	}
  else if (screen->etapeDuJeu == 10)
	{
	  switch (key.keysym.sym)
        {
		case SDLK_DOWN: 
		  screen->etapeParam = (screen->etapeParam + 1)%3;
		  break;
		case SDLK_UP:
		  if (screen->etapeParam == 0)
			screen->etapeParam = 2;
		  else
			screen->etapeParam -= 1;
		  break;
		case SDLK_RIGHT:
		  if (screen->etapeParam == 0 && Mix_VolumeMusic(-1) < 100) 
			Mix_VolumeMusic(Mix_VolumeMusic(-1)+1); 
		  break;
		case SDLK_LEFT:
		  if (screen->etapeParam == 0)
			Mix_VolumeMusic(Mix_VolumeMusic(-1)-1); 
		  break;
		case SDLK_RETURN:
		  if (screen->etapeParam == 1)
			screen->bonus = (screen->bonus == 0) ? 1 : 0;
			  if (screen->etapeParam == 2)
				screen->trousNoir = (screen->trousNoir == 0) ? 1 : 0;
			  break;
		}
	}
  else if (screen->etapeDuJeu == 8)
	{
	  switch (key.keysym.sym)
        {
		case SDLK_s:
		  screen->etapeDuJeu = 13;
		  screen->previousSelGam = 0;
		  screen->etapeSelGam = 1;
		  break;
		}
	}
  else if (screen->etapeDuJeu == 13 && screen->etapeSelGam)
	{
	  switch (key.keysym.sym)
        {
		case SDLK_UP:
		  if (screen->etape2SelGam -1 < 0)
			screen->etape2SelGam = (screen->etapeSelGam == 4) ? 3 : 2;
		  else
			(screen->etape2SelGam)--;
			  break;
		case SDLK_DOWN:
		  screen->etape2SelGam = (screen->etape2SelGam + 1)%((screen->etapeSelGam == 4) ? 4 : 3);
		  break;
		}
	  if (screen->etapeSelGam == 3)
		{
		  switch (key.keysym.sym)
        	{
			case SDLK_RIGHT:
			  screen->nbJoueur = (screen->nbJoueur + 1)%5;
			  break;
			case SDLK_LEFT:
			  if (screen->nbJoueur -1 < 0)
				screen->nbJoueur = 4;
			  else
				(screen->nbJoueur)--;
			  break;
			}
		}
	  if (screen->etapeSelGam == 4)
		{
		  switch (key.keysym.sym)
        	{
			case SDLK_RIGHT:
			  switch (screen->etape2SelGam)
				{
				case 0:
				  if(screen->nbHumainM + screen->nbHumainP + 1 > 4 && screen->nbHumainP > 0)
					{
					  (screen->nbHumainM)++;
					  (screen->nbHumainP)--;
					}
				  else if (screen->nbHumainM + screen->nbHumainP + 1 <= 4)
					(screen->nbHumainM)++;
				  break;
				case 1:
				  if(screen->nbHumainP + screen->nbHumainM + 1 > 4 && screen->nbHumainM > 0)
					{
					  (screen->nbHumainP)++;
					  (screen->nbHumainM)--;
					}
				  else if (screen->nbHumainP + screen->nbHumainM + 1 <= 4)
					(screen->nbHumainP)++;	
				  break;
				case 2: (screen->nbIAM)++; break;
				case 3: (screen->nbIAP)++; break;
				default:break;
				}
			  break;
			case SDLK_LEFT:
			  switch (screen->etape2SelGam)
				{
				case 0: screen->nbHumainM = (screen->nbHumainM - 1 < 0) ? 0 : (screen->nbHumainM)-1; break;
				case 1: screen->nbHumainP = (screen->nbHumainP - 1 < 0) ? 0 : (screen->nbHumainP)-1; break;
				case 2: screen->nbIAM = (screen->nbIAM - 1 < 0) ? 0 : (screen->nbIAM)-1; break;
				case 3: screen->nbIAP = (screen->nbIAP - 1 < 0) ? 0 : (screen->nbIAP)-1; break;
				default:break;
				}
			  break;
			}
		}
	}
}

void LeftClick(ecran *screen) {
  int posMX, posMY;
  SDL_GetMouseState(&posMX, &posMY);
  if(screen->etapeDuJeu == 2){
    if(isInButton(80, 50, 30, 20, 'c', posMX, posMY, screen)){
      screen->etapeDuJeu = 13;
    }
    else if (isInButton(80, 80, 30, 20, 'c', posMX, posMY, screen))
      {
		screen->etapeDuJeu = 0;
      }
    else if (isInButton(18, 20, 30, 20, 'c', posMX, posMY, screen))
      {
		screen->etapeDuJeu = 10;
      }
  }
  if (screen->etapeDuJeu == 13)
    {
      if(isInButton(12.625, screen->decalageB5, 23, 20, 'c', posMX, posMY, screen) && screen->etapeSelGam != 1){
       	screen->etape2SelGam = 0;
		screen->backSelec = 1;
		screen->previousSelGam = screen->etapeSelGam;
		screen->etapeSelGam = 1;
      }
      else if (isInButton(37.875, screen->decalageB5, 23, 20, 'c', posMX, posMY, screen) && screen->etapeSelGam != 2)
		{
		  screen->etape2SelGam = 0;
		  screen->backSelec = 1;
		  screen->previousSelGam = screen->etapeSelGam;
		  screen->etapeSelGam = 2;
		}
      else if (isInButton(63.125, screen->decalageB5, 23, 20, 'c', posMX, posMY, screen) && screen->etapeSelGam != 3)
		{
		  screen->etape2SelGam = 0;
		  screen->backSelec = 1;
		  screen->previousSelGam = screen->etapeSelGam;
		  screen->etapeSelGam = 3;
		}
      else if (isInButton(88.375, screen->decalageB5, 23, 20, 'c', posMX, posMY, screen) && screen->etapeSelGam != 4)
		{
		  screen->etape2SelGam = 0;
		  screen->backSelec = 1;
		  screen->previousSelGam = screen->etapeSelGam;
		  screen->etapeSelGam = 4;
		}
      else if (isInButton(12.625, 105-(screen->decalageB5), 23, 20, 'c', posMX, posMY, screen))
		{
		  screen->etape2SelGam = 0;
		  screen->backSelec = 1;
		  if (screen->etapeSelGam)
			{
			  screen->previousSelGam = screen->etapeSelGam;
			  screen->etapeSelGam = 0;
			}
		  else
			{
			  screen->etapeDuJeu = 14;
			}
		}
      else if (isInButton(50, (screen->decalageB4)+33, 30, 15, 'c', posMX, posMY, screen)) //Button IA Training
		{
		  switch (screen->etapeSelGam)
			{
			case 1: startBubbleTraining(screen, 0); break;
			case 2: startBubbleTraining(screen, 1);break;
			case 3: startBubbleTraining(screen, 2);break;
			case 4: startIALoupMoutontraining(screen);break;
			default: break;
			}
		}  
      else if (isInButton((screen->decalageB6), 85, 23, 20, 'c', posMX, posMY, screen)) // Button Play
		{
		  switch (screen->etapeSelGam)
			{
			case 1: screen->maxVie = 3; screen->nbPlayer = 2;screen->modePlay = 0;screen->etapeDuJeu = 3;mainTickGest(screen);
			  switch(screen->etape2SelGam){
			  case 0:screen->pla[0].IAType = 0;screen->pla[1].IAType = 0;break;
			  case 1:screen->pla[0].IAType = 0;loadBubbleIA2(screen);break;
			  default:loadBubbleIA2(screen);loadBubbleIA1(screen);break;
			  }
			  break;
			case 2:screen->maxVie = 3; screen->nbPlayer = 4;screen->modePlay = 0;screen->etapeDuJeu = 3;mainTickGest(screen);screen->pla[0].equipe = 0;screen->pla[1].equipe = 0;screen->pla[2].equipe = 1;screen->pla[3].equipe = 1;
			  switch(screen->etape2SelGam){
			  case 0:screen->pla[0].IAType = 0;screen->pla[1].IAType = 0;screen->pla[2].IAType = 0;screen->pla[3].IAType = 0;break;
			  case 1:screen->pla[0].IAType = 0;screen->pla[1].IAType = 0;screen->pla[2].IAType = 1;screen->pla[3].IAType = 1;loadBubble2V2IA1(screen);break;
			  default:screen->pla[0].IAType = 1;screen->pla[1].IAType = 1;screen->pla[2].IAType = 2;screen->pla[3].IAType = 2;loadBubble2V2IA2(screen);loadBubble2V2IA1(screen);break;
			  } break;
			case 3: break;
			case 4: screen->modePlay = 1;screen->etapeDuJeu = 3; screen->nbPreda = screen->nbIAP + screen->nbHumainP; screen->nbProie = screen->nbIAM + screen->nbHumainM; mainTickGest(screen); initMout();loadIALout(screen);
			  for(int i = 0; i < screen->nbHumainP; i++){
				screen->pla[i].IAType = 0;
			  }
			  for(int i = screen->nbPreda; i < screen->nbHumainM + screen->nbPreda; i++){
				screen->pla[i].IAType = 0;
			  }
			  break;
			default: break;
			}
		}
    }
}

void RightClick(ecran *screen) {
  int posMX, posMY;
  SDL_GetMouseState(&posMX, &posMY);
  (void) screen;
 
}
