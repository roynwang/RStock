/*
 * =====================================================================================
 *
 *       Filename:  subwinmgr.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/11/2012 11:39:05 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef  SUBWINMGR_INC
#define  SUBWINMGR_INC
#include <stdlib.h>
#include "SubArea.h"
#include "DrawLib.h"

SubWin InitialSubWin(SDL_Surface *screen, int startx, int starty, int width, int height, int withborder){
	SubWin sw = (SubWin)malloc(sizeof(_SubWin));
	sw->screen = screen;
	sw->startx = startx;
	sw->starty = starty;
	sw->width = width;
	sw->height = height;
	if(!withborder) return sw;
	drawLine(sw,startx,starty,startx,starty+height, RED);

	drawLine(sw,startx,starty+height,startx+width,starty+height, RED);
	return sw;
}

#endif   /* ----- #ifndef SUBWINMGR_INC  ----- */

