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


typedef enum{
	COMMAND,
	INPUT
} KEYBOARDMODE;

//pipe for status 
int fifo_svstat, fifo_ctstat, fifo_shstat;
int *svstat;
//string to record user input
char userinput[100] = "";

SDL_Surface *screen;
SubWin subwin;
KEYBOARDMODE TrackKeyDown(SubWin sw, int key, KEYBOARDMODE kmode);
void Event_pagedown(SubWin sw);
KEYBOARDMODE TrackInputMode(int key);
KEYBOARDMODE TrackCommandMode(int key, SubWin sw);
void InitializeClient();
void WaitSVRReady();
int QueryByNo(int no);
void WaitKeyboard(SubWin sw);
void InitShow();
void DrawCan(SubWin sw, DayData head);
void ShowInput(const char* input){
	printf ( "tring to show %s \n", input );
	TTF_Font* font = TTF_OpenFont("DejaVuSans.ttf",15);
	if(font == NULL) printf ( "Load font failed %s \n", TTF_GetError() );
	SDL_Color color = {255,255,255,70};
	SDL_Surface * text = TTF_RenderText_Blended(font, input, color);
	SDL_BlitSurface(text, NULL, screen, NULL);
	SDL_Flip(screen);
	SDL_FreeSurface(text);
}
void ClearInput(){
	SDL_Rect sr = {x:0,y:0, w:80,h:20};
	SDL_FillRect(screen, &sr, BLACK);
	SDL_Flip(screen);
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
KEYBOARDMODE TrackKeyDown(SubWin sw, int key, KEYBOARDMODE kmode){
	if(kmode == INPUT){
		return TrackInputMode(key);
	}
	if(kmode == COMMAND){
		return TrackCommandMode(key, sw);
	}
}

void WaitKeyboard(SubWin sw){
	int quit = 0;
	SDL_Event event;
	KEYBOARDMODE kmode = COMMAND;
	while(quit!=1)
	{
		//		printf ( "waiting for keyboard action\n" );
		while( SDL_PollEvent(&event)){
			printf ( "WaitKeyboard: caught keyboard %x\n", event.key.keysym.sym );
			switch (event.type){
				case SDL_KEYDOWN:
					printf ( "tracking keydown\n" );
					kmode = TrackKeyDown(sw, event.key.keysym.sym, kmode);
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
	subwin = sw;
	ClearInput();
	WaitKeyboard( sw);
}
void DrawCan(SubWin sw, DayData head){
	//now only draw the first 60 days
	drawCandlesticks(sw, head, 60);
}

void Event_pagedown(SubWin sw){
	DayData head = (DayData)shmat(QueryByNo(600000), NULL, 0);
	DrawCan(sw, head);
	SDL_Flip(screen);
}

KEYBOARDMODE TrackCommandMode(int key, SubWin sw){
	switch(key){
		case SDLK_ESCAPE:
			return COMMAND;
		case SDLK_PAGEDOWN:
			Event_pagedown(sw);
			return COMMAND;
		case SDLK_BACKSLASH:
			printf ( "You pressed back slash\n" );
			return INPUT;
	}
}
KEYBOARDMODE TrackInputMode(int key){
	printf ( "TrackInput: caught keyboard %x\n", key );
	char* clean = "             ";
	switch (key){
		case SDLK_0:
			strcat(userinput,"0");
			break;
		case SDLK_1:
			strcat(userinput,"1");
			break;
		case SDLK_2:
			strcat(userinput,"2");
			break;
		case SDLK_3:
			strcat(userinput,"3");
			break;
		case SDLK_4:
			strcat(userinput,"4");
			break;
		case SDLK_5:
			strcat(userinput,"5");
			break;
		case SDLK_6:
			strcat(userinput,"6");
			break;
		case SDLK_7:
			strcat(userinput,"7");
			break;
		case SDLK_8:
			strcat(userinput,"8");
			break;
		case SDLK_9:
			strcat(userinput,"9");
			break;
		case SDLK_RETURN:
		    
//			DayData head = (DayData)shmat(QueryByNo(atoi(userinput)), NULL, 0);
			DrawCan(subwin, (DayData)shmat(QueryByNo(atoi(userinput)), NULL, 0));
//			SDL_Flip(screen);
			ClearInput();
			return COMMAND;
		default:
			break;
	}
	printf ( "strcat done: %s \n", userinput );
	ShowInput(userinput);

	return INPUT;
}


