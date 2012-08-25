/*
 * =====================================================================================
 *
 *       Filename:  subwinmgr.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/11/2012 11:54:00 AM
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
#include "SubArea.h"
SubWin InitialSubWin(SDL_Surface *screen, int startx, int starty, int width, int height, int withborder);

#endif   /* ----- #ifndef SUBWINMGR_INC  ----- */
