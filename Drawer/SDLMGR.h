/*
 * =====================================================================================
 *
 *       Filename:  SDLMGR.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/25/2012 11:20:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <SDL/SDL.h>

void beginSDL();
void endSDL();
SDL_Surface* initSDL(int width, int height, Uint32 flags);

