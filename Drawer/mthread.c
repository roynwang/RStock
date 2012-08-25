/*
 * =====================================================================================
 *
 *       Filename:  mthread.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/20/2012 10:51:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  royn.wang.renyuan@gmail.com 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_draw.h"
#include "DayData.h"
#include "DrawLib.h"
#include "AreaMGR.h"
#include "ReadData.h"


int main(int argc, char *argv[])
{
	SDL_Surface *screen;
	int fwidth ;
	int fheight ;
	beginSDL();
	fwidth = 640;
	fheight = 480;
	screen = initSDL(fwidth,fheight,SDL_SWSURFACE | SDL_ANYFORMAT);
	{
//		Uint32 c_red = SDL_MapRGB(screen->format, 255,0,0);
        SubWin sw = InitialSubWin(screen,40,0,640,240,true);
		DayData head;
		head = ReadData("sh600242.day");

		drawCandlesticks(sw, head, 60);

		SDL_UpdateRect(screen, 0, 0, 0, 0);//刷新屏幕
		//Wait 10 seconds
		SDL_Delay( 10000 );
		endSDL();
		
		fprintf(stderr, "显示结束。。。。");
		return 0;

	}
	return 0;
}
