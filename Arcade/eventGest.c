#include "eventGest.h"


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
	}
	else if (screen->etapeDuJeu == 13)
	{
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
	else
	    screen->etapeDuJeu = 0;
  }else if(screen->etapeDuJeu == 4){
    switch (key.keysym.sym)
          {
            /* Joueur 2*/
	  case SDLK_UP: if(screen->nbPlayer > 1) screen->pla[1].input[1] = 0; break;
	  case SDLK_LEFT: if(screen->nbPlayer > 1) screen->pla[1].input[0] = 0; break;
	  case SDLK_DOWN: if(screen->nbPlayer > 1) screen->pla[1].input[3] = 0; break;
	  case SDLK_RIGHT: if(screen->nbPlayer > 1) screen->pla[1].input[2] = 0; break;
	  case SDLK_o: if(screen->nbPlayer > 1) screen->pla[1].input[1] = 0; break;
	  case SDLK_k: if(screen->nbPlayer > 1) screen->pla[1].input[0] = 0; break;
	  case SDLK_l: if(screen->nbPlayer > 1) screen->pla[1].input[3] = 0; break;
	  case SDLK_m: if(screen->nbPlayer > 1) screen->pla[1].input[2] = 0; break;
	  case SDLK_RSHIFT: if(screen->nbPlayer > 1) screen->pla[1].input[4] = 0; break;
            /* Joueur 1 */
	  case SDLK_q: if(screen->nbPlayer > 0) screen->pla[0].input[0] = 0; break;
	  case SDLK_z: if(screen->nbPlayer > 0) screen->pla[0].input[1] = 0; break;
	  case SDLK_s: if(screen->nbPlayer > 0) screen->pla[0].input[3] = 0; break;
	  case SDLK_d: if(screen->nbPlayer > 0) screen->pla[0].input[2] = 0; break;
	  case SDLK_SPACE: if(screen->nbPlayer > 0) screen->pla[0].input[4] = 0; break;
	  default:
            break;
          }
  }
}

void keyDown(SDL_KeyboardEvent key, ecran *screen) 
{
	if(screen->etapeDuJeu == 4)
	{
    	switch (key.keysym.sym)
        {
			/* Joueur 2*/
			case SDLK_UP: if(screen->nbPlayer > 1) screen->pla[1].input[1] = 1; break;
			case SDLK_LEFT: if(screen->nbPlayer > 1) screen->pla[1].input[0] = 1; break;
			case SDLK_DOWN: if(screen->nbPlayer > 1) screen->pla[1].input[3] = 1; break;
			case SDLK_RIGHT: if(screen->nbPlayer > 1) screen->pla[1].input[2] = 1; break;
			case SDLK_o: if(screen->nbPlayer > 1) screen->pla[1].input[1] = 1;; break;
			case SDLK_k: if(screen->nbPlayer > 1) screen->pla[1].input[0] = 1; break;
			case SDLK_l: if(screen->nbPlayer > 1) screen->pla[1].input[3] = 1; break;
			case SDLK_m: if(screen->nbPlayer > 1) screen->pla[1].input[2] = 1; break;
			case SDLK_RSHIFT: if(screen->nbPlayer > 1) screen->pla[1].input[4] = 1; break;
					/* Joueur 1 */
			case SDLK_q: if(screen->nbPlayer > 0) screen->pla[0].input[0] = 1; break;
			case SDLK_z: if(screen->nbPlayer > 0) screen->pla[0].input[1] = 1; break;
			case SDLK_s: if(screen->nbPlayer > 0) screen->pla[0].input[3] = 1; break;
			case SDLK_d: if(screen->nbPlayer > 0) screen->pla[0].input[2] = 1; break;
			case SDLK_SPACE: if(screen->nbPlayer > 0) screen->pla[0].input[4] = 1; break;
			default:
					break;
        }
  	}
	if (screen->etapeDuJeu == 10)
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
       	screen->backSelec = 1;
		screen->previousSelGam = screen->etapeSelGam;
		screen->etapeSelGam = 1;
    }
	else if (isInButton(37.875, screen->decalageB5, 23, 20, 'c', posMX, posMY, screen) && screen->etapeSelGam != 2)
	{
		screen->backSelec = 1;
		screen->previousSelGam = screen->etapeSelGam;
		screen->etapeSelGam = 2;
	}
	else if (isInButton(63.125, screen->decalageB5, 23, 20, 'c', posMX, posMY, screen) && screen->etapeSelGam != 3)
	{
		screen->backSelec = 1;
		screen->previousSelGam = screen->etapeSelGam;
		screen->etapeSelGam = 3;
	}
	else if (isInButton(88.375, screen->decalageB5, 23, 20, 'c', posMX, posMY, screen) && screen->etapeSelGam != 4)
	{
		screen->backSelec = 1;
		screen->previousSelGam = screen->etapeSelGam;
		screen->etapeSelGam = 4;
	}
	else if (isInButton(12.625, 105-(screen->decalageB5), 23, 20, 'c', posMX, posMY, screen))
	{
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
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
		default: break;
		}
	}  
	else if (isInButton((screen->decalageB6), 85, 23, 20, 'c', posMX, posMY, screen)) // Button Play
	{
		switch (screen->etapeSelGam)
		{
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
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
