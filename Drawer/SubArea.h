/*
 * =====================================================================================
 *
 *       Filename:  subwindow.h
 *
 *    Description:  describe the sub window information
 *
 *        Version:  1.0
 *        Created:  06/23/2012 09:34:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  SUBWINDOW_INC
#define  SUBWINDOW_INC

#define BLACK                            0
#define WHITE                            16777215
#define RED                              16711680
#define GREEN                            65280
#define BLUE                             255
#define CYAN                             65535
#define MAGENTA                          16711935
#define YELLOW                           16776960

 #include "../inc/SDL.h"
typedef struct tagSubWin{
	SDL_Surface *screen;
	int startx;
	int starty;
	int width;
	int height;
} *SubWin, _SubWin;

#endif
