/*
 * =====================================================================================
 *
 *       Filename:  ClientLib.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/28/2012 03:58:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include "../StatusHandler/STATUS.h"
#include "../StatusHandler/StatusMGR.h"
#include <fcntl.h>
#include "../inc/SDL.h"
#include "../inc/SDL_ttf.h"
#include "../Drawer/AreaMGR.h"
#include "../Drawer/SDLMGR.h"
#include "../DataDef/DayData.h"

int fifo_svstat, fifo_ctstat, fifo_shstat;
int *svstat;
SDL_Surface *screen;

int FilterKey(SubWin sw, int key);
void Event_pagedown(SubWin sw);

void InitializeClient();
void WaitSVRReady();
int QueryByNo(int no);
void WaitKeyboard(SubWin sw);
void InitShow();
void DrawCan(SubWin sw, DayData head);
void ShowInput(char* input){
	printf ( "tring to show %s \n", input );
	TTF_Font* font = TTF_OpenFont("DejaVuSans.ttf",15);
	if(font == NULL) printf ( "Load font failed %s \n", TTF_GetError() );
	SDL_Color color = {255,255,255,70};
	SDL_Surface * text = TTF_RenderText_Blended(font, input, color);
	SDL_BlitSurface(text, NULL, screen, NULL);
}

void InitializeClient(){

	fifo_svstat = CreateFIFO(SVRSTATUS, O_RDONLY);
	fifo_ctstat = CreateFIFO(CLTSTATUS, O_WRONLY);
	fifo_shstat = CreateFIFO(SVRSHMID,  O_RDONLY);
	TTF_Init();

	int shmid = GetInt(fifo_svstat);
	svstat = (int *)shmat(shmid, NULL, 0);
	printf ( "client started!\n" );
}

void WaitSVRReady(){
	while(*svstat != SVRREADY){
		printf ( "now status is %d \n sleep 1s\n", *svstat );
	}
}

int QueryByNo(int no){
	SendInt(fifo_ctstat, no);
	int shmid = GetInt(fifo_shstat);
	printf ( "%d memory = %d \n", no, shmid );
	return shmid;
}
int FilterKey(SubWin sw, int key){
	switch(key){
		case SDLK_ESCAPE:
			return 1;
		case SDLK_PAGEDOWN:
		    Event_pagedown(sw);
			return 0;
	}
}

void WaitKeyboard(SubWin sw){
	int quit = 0;
	SDL_Event event;
	while(quit!=1)
	{
//		printf ( "waiting for keyboard action\n" );
		while( SDL_PollEvent(&event)){
			switch (event.type){
				case SDL_KEYDOWN:
					quit = FilterKey(sw, event.key.keysym.sym);
					break;
				case SDL_QUIT:
					printf("caugth keyboard esc !\n");
					quit = 1;
			}
		}
	}
	endSDL();
}
void InitShow(){

	int fwidth ;
	int fheight ;
	beginSDL();
	fwidth = 640;
	fheight = 480;
	screen = initSDL(fwidth,fheight,SDL_SWSURFACE | SDL_ANYFORMAT);
	SubWin sw = InitialSubWin(screen,40,0,640,240,1);
	//query here!!!!!!1
//	DayData head = (DayData)shmat(QueryByNo(8888), NULL, 0);
//	drawCandlesticks(sw, head, 60);
//	SDL_UpdateRect(screen, 0, 0, 0, 0);//刷新屏幕
	//Wait 10 seconds
	//	SDL_Delay( 10000 );
	WaitKeyboard( sw);
}
void DrawCan(SubWin sw, DayData head){
//	DayData head = (DayData)shmat(QueryByNo(8888), NULL, 0);
	drawCandlesticks(sw, head, 60);
//	SDL_UpdateRect(screen, 0, 0, 0, 0);//刷新屏幕
//	ShowInput("justfor test");
}

void Event_pagedown(SubWin sw){
	DayData head = (DayData)shmat(QueryByNo(600000), NULL, 0);
	DrawCan(sw, head);
	ShowInput("600000");
//	SDL_Rect f = {0,0,100,100};
//	SDL_FillRect(screen, &f, 0x00000);
	SDL_Flip(screen);

}


