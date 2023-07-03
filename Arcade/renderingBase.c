#include "renderingBase.h"
#include "renderingUtil.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>


extern int debugging;


long int repaint = 0;

ecran createScreen(int sizex, int sizey, int fullscreen){

  ecran screen;

  SDL_DisplayMode screen_dimension;

  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) != 0)
    end_sdl(0, "ERROR SDL INIT", screen);

  //récupère la taille de l'écran
  SDL_GetCurrentDisplayMode(0, &screen_dimension);
  //      printf("Taille de l'écran\n\tw : %d\n\th : %d\n", screen_dimension.w,
  //      screen_dimension.h);

  screen.isFullScreen = fullscreen;
  /* Création de la fenêtre, cas avec erreur */
  if(fullscreen == 0){
    screen.window = SDL_CreateWindow("This F****** window", SDL_WINDOWPOS_CENTERED,
				     SDL_WINDOWPOS_CENTERED, sizex,
				     sizey, SDL_WINDOW_RESIZABLE);
    screen.otherX = screen_dimension.w;
    screen.otherY = screen_dimension.h;
  }else{
    screen.window = SDL_CreateWindow("This F****** window", SDL_WINDOWPOS_CENTERED,
				     SDL_WINDOWPOS_CENTERED, screen_dimension.w,
				     screen_dimension.h, SDL_WINDOW_FULLSCREEN);
    screen.otherX = sizex;
    screen.otherY = sizey;
  }

  
  
  /*
  SDL_Surface *thumbnail;
  thumbnail = IMG_Load("Res/thumbnail.png");
  SDL_SetWindowIcon(window, thumbnail);
  SDL_FreeSurface(thumbnail);*/

  if (screen.window == NULL)
    end_sdl(0, "ERROR WINDOW CREATION", screen);

  /* Création du renderer (le truc dans la windows) */
  screen.renderer = SDL_CreateRenderer(
      screen.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
  
  if (screen.renderer == NULL)
    end_sdl(0, "ERROR RENDERER CREATION", screen);


  // écrire (lettre chiffre) dans le render, grace à la bibliothèque TTF
  if (TTF_Init() == -1)
  {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
  }
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
  {
    printf("%s", Mix_GetError());
  }

  
  /* Taille de écran fournit par SDL */
  SDL_GetWindowSize(screen.window, &screen.sizeX, &screen.sizeY);

  screen.etapeDuJeu = 0;


  return screen;
}


void end_sdl(int ok, char const * msg, ecran screen) {
  char msg_formated[255];
  int l;
  
  if (!ok){
    strncpy(msg_formated, msg, 250);
    l = strlen(msg_formated);
    strcpy(msg_formated+l, " : %s\n");

    SDL_Log(msg_formated, SDL_GetError());
  }

  if(screen.renderer != NULL){
    SDL_DestroyRenderer(screen.renderer);
  }
  if(screen.window != NULL){
    SDL_DestroyWindow(screen.window);
  }
  Mix_CloseAudio();
  SDL_Quit();

  if (!ok) {exit(EXIT_FAILURE);}
}

int tickCount;



void startMainBoucle(ecran *screen){

  long int LastFrame;
  long int TimeCount;
  long int NowTime;
  long int timeForNewFrame = 1000000 / FPS_TO_GET;

  //Debogage
  int fpsCount = 0;
  int LastFpsCount = 0;
  int LastTickCount = 0;

  //ManetteInit();
  /*
  wavSpec = (SDL_AudioSpec*)malloc(sizeof(SDL_AudioSpec)*1);
   wavLength = (Uint32 *)malloc(sizeof(Uint32)*1);
   wavBuffer = (Uint8 **)malloc(sizeof(Uint8*)*1);
 
  SDL_LoadWAV("Res/Sound/AMOGUS.wav", &wavSpec[0], &wavBuffer[0], &wavLength[0]);
  SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec[0], NULL, 0);
  SDL_QueueAudio(deviceId, wavBuffer[0], wavLength[0]);
  SDL_PauseAudioDevice(deviceId, 0);
  SDL_Delay(500);
  deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec[0], NULL, 0);
  SDL_QueueAudio(deviceId, wavBuffer[0], wavLength[0]);
  SDL_PauseAudioDevice(deviceId, 0);
  */
  
  //SDL_CloseAudioDevice(deviceId);
  //SDL_FreeWAV(wavBuffer);
  
  /************Début de la boucle des ticks***********************/  
  if (loadImageMenu(screen) == -1)
	{
	  printf("Error in loadImageMenu\n");
	  exit( EXIT_FAILURE );
	}

  /************Initialisation des variables de temps**************/
  LastFrame = getTime();
  TimeCount = getTime();
  NowTime = getTime();
  
  pthread_t threadBoucleDesTicks;
  int RetourDuThreadDesTicks = pthread_create(&threadBoucleDesTicks, NULL, BouclePrincipaleDesTicks,  screen);
  if(RetourDuThreadDesTicks){
	end_sdl(1, "", *screen);
  }
  


  /************Début de la boucle frames**************************/
  while (screen->etapeDuJeu) {
    NowTime = getTime();
    
    
    /* Gestion de l'affichage écran */
    if (NowTime - LastFrame > timeForNewFrame) {
      if(repaint == 0){


		mainRendering(screen);

		
      
		if(debugging){
		  char affichageFrameDebug[5];
		  sprintf(affichageFrameDebug, "%d", LastFpsCount);
		  DrawString(affichageFrameDebug, 0, 0, 6, 'n', 0, 255, 0, screen);
		  sprintf(affichageFrameDebug, "%d", LastTickCount);
		  DrawString(affichageFrameDebug, 100, 0, 6, 'e', 0, 255, 0, screen);
		}
      
		SDL_RenderPresent(screen->renderer);
		SDL_RenderClear(screen->renderer);
	
      }		      
      LastFrame += timeForNewFrame;
      fpsCount++;
      }else{
				      
      // Endors le cpu pour garder de la ressource 
      NowTime = getTime();
      
      long SleepForCPU = 0;
      SleepForCPU = (long)(timeForNewFrame - (NowTime - LastFrame)) / 300;
      SDL_Delay(SleepForCPU);
      }
    

    /* Gestion du debugage */
    if (NowTime > TimeCount)
    {
      TimeCount += 1000000;
      LastFpsCount = fpsCount;
      LastTickCount = tickCount;
      //printf("%d images cette seconde et %d ticks\n", fpsCount, tickCount);
      fpsCount = 0;
      tickCount = 0;
    }
  }
  
  /* on referme proprement */
  end_sdl(1, "Normal ending", *screen);
  
}




void *BouclePrincipaleDesTicks(void *unEcran){
  ecran *screen = unEcran;
  long int LastTick;
  long int timeForNewTick = 1000000 / TICK_TO_GET;
  long int NowTime;

  SDL_Event event;

  
  NowTime = getTime();
  LastTick = getTime();

  
  InitImage();
  loadMusic(screen);

  screen->etapeMenu = 0;
  screen->nbObjetsMax = 0;
  screen->maxBoule = 3;
  screen->maxVie = 3;
  screen->nbPlayer = 2;
  screen->modePlay = 0;

  
  screen->decalageB1 = 116;
  screen->decalageB2 = 130;
  
  screen->etapeDuJeu = 8;
  
  while(screen->etapeDuJeu){

    NowTime = getTime();
    
    /* Gestion des verif gameplay */
    if (NowTime - LastTick > timeForNewTick) {

      if(repaint != 0){
		if(repaint < getTime()-350){
		  repaint = 0;
		}
      }

      mainTickGest(screen);

	  
      LastTick += timeForNewTick;
      tickCount++;
    }else{

      /* Endors le cpu pour garder de la ressource */
      NowTime = getTime();
      
      long SleepForCPU = 0;
      SleepForCPU = (long)(timeForNewTick - (NowTime - LastTick)) / 300;
      SDL_Delay(SleepForCPU);
    }

    while (SDL_PollEvent(&event))
	  {
		switch (event.type)
		  {
		  case SDL_KEYDOWN:
			keyDown(event.key, screen);
			break;
		  case SDL_KEYUP:
			if(event.key.keysym.sym == SDLK_F11){

			  repaint = getTime();
			  SDL_Delay(250);
			  /*if(screen->renderer != NULL){
				SDL_DestroyRenderer(screen->renderer);
			  }
			  if(screen->window != NULL){
				SDL_DestroyWindow(screen->window);
				}*/
	  
			  screen->isFullScreen = !screen->isFullScreen;
			  if(screen->isFullScreen == 0){
				SDL_SetWindowFullscreen(screen->window, 0);

				int tmp;
				tmp = screen->sizeX;
				screen->sizeX = screen->otherX;
				screen->otherX = tmp;
	    
				tmp = screen->sizeY;
				screen->sizeY = screen->otherY ;
				screen->otherY = tmp;

				writeParamFile(screen->sizeX, screen->sizeY, screen->isFullScreen);
	    
			  }else{
				SDL_SetWindowFullscreen(screen->window, SDL_WINDOW_FULLSCREEN_DESKTOP);

				int tmp;
				tmp = screen->sizeX;
				screen->sizeX = screen->otherX ;
				screen->otherX = tmp;
	    
				tmp = screen->sizeY;
				screen->sizeY = screen->otherY ;
				screen->otherY = tmp;

				writeParamFile(screen->otherX, screen->otherY, screen->isFullScreen);
			  }
			  if (screen->window == NULL)
				end_sdl(0, "ERROR WINDOW CREATION", *screen);
	  

  
			  if (screen->renderer == NULL)
				end_sdl(0, "ERROR RENDERER CREATION", *screen);

			  
			}else{
			  keyUp(event.key, screen);
			}
			break;
		  case SDL_MOUSEWHEEL:
			// if (event.wheel.y > 0) {
			// } else if (event.wheel.y < 0) {
			// }
			break;
		  case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
			  LeftClick(screen);
			} else if (event.button.button == SDL_BUTTON_RIGHT) {
			  RightClick(screen);
			}
			break;
		  case SDL_QUIT:
			screen->etapeDuJeu = 0;
			break;
		  case SDL_WINDOWEVENT:
			if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
			  if(repaint == 0){
				screen->sizeX = event.window.data1;
				screen->sizeY = event.window.data2;
				writeParamFile(screen->sizeX, screen->sizeY, screen->isFullScreen);
			  }
			}
			break;
			/*case SDL_JOYBUTTONDOWN:
			  if(event.jbutton.button == 0){
			  inputsJoueurs[event.jbutton.which][INPUT_JUMP] = 1;
			  }break;
			  case SDL_JOYBUTTONUP:
			  if(event.jbutton.button == 0){
			  inputsJoueurs[event.jbutton.which][INPUT_JUMP] = 0;
			  }break;*/
		  default:
			break;
		  }
	  }

    
  }
  return NULL;
}





void writeParamFile(int sizex, int sizey, int isFullscreen){

  FILE *param = fopen(PARAM_NAME, "w");
  fprintf(param, "%d\n%d\n%d\n", sizex, sizey, isFullscreen);
  fflush(param);
  fclose(param);

  
}
