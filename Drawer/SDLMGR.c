/*
 * =====================================================================================
 *
 *       Filename:  SDLMGR.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/25/2012 05:44:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>
#include "DrawLib.h"
#include "AreaMGR.h"
#include <time.h>


void beginSDL(){
	if(SDL_WasInit(SDL_INIT_EVERYTHING)!=0){
		fprintf(stderr, "SDL is already running\n");
		return;
	}

	if ( SDL_Init(SDL_INIT_EVERYTHING) == -1) {
	}
	return;
}

void endSDL(){
	if( SDL_WasInit(SDL_INIT_EVERYTHING)==0 )
	{
		fprintf(stderr, "SDL is no running \n");
		return;
	}
	SDL_Quit();
	return;
}
SDL_Surface* initSDL(int width, int height, Uint32 flags){
	if( SDL_Init(SDL_INIT_VIDEO)<0 )
	{
		fprintf(stderr, "SDL init failed %s", SDL_GetError());
		exit(1);
	}
	atexit(endSDL);
	Uint8  video_bpp = 0;
	SDL_Surface *screen = SDL_SetVideoMode(width,height,video_bpp,flags	);
	if( !screen )
	{
		fprintf(stderr, "init as vide failed %s\n",SDL_GetError());
		exit(2);
	}
	return screen;
}

