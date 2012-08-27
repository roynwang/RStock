/*
 * =====================================================================================
 *
 *       Filename:  ClientDataReader.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/23/2012 07:16:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  CLIENTDATAREADER_INC
#define  CLIENTDATAREADER_INC


#include <stdlib.h>
#include "DayData.h"
#include "StatusHandler/StatusMGR.h"
#include "StatusHandler/STATUS.h"
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>  
#include <time.h>
#include "Drawer/SDLMGR.h"
#include "inc/SDL.h"
#include "Drawer/SubArea.h"
#include "Drawer/AreaMGR.h"


int fifo_svstat, fifo_ctstat, fifo_shstat;
int *svstat;

void InitializeClient(){

	fifo_svstat = CreateFIFO(SVRSTATUS, O_RDONLY);
	fifo_ctstat = CreateFIFO(CLTSTATUS, O_WRONLY);
	fifo_shstat = CreateFIFO(SVRSHMID,  O_RDONLY);

	int shmid = GetInt(fifo_svstat);
	svstat = (int *)shmat(shmid, NULL, 0);
	printf ( "client started!\n" );
}

void WaitSVRReady(){
	while(*svstat != SVRREADY){
		printf ( "now status is %d \n sleep 1s\n", *svstat );
		sleep(1);
	}
}

int QueryByNo(int no){
	SendInt(fifo_ctstat, no);
	int shmid = GetInt(fifo_shstat);
	printf ( "%d memory = %d \n", no, shmid );
	return shmid;
}

void InitShow(){
	SDL_Surface *screen;
	int fwidth ;
	int fheight ;
	beginSDL();
	fwidth = 640;
	fheight = 480;
	screen = initSDL(fwidth,fheight,SDL_SWSURFACE | SDL_ANYFORMAT);
	Uint32 c_red = SDL_MapRGB(screen->format, 255,0,0);
	SubWin sw = InitialSubWin(screen,40,0,640,240,1);
	//query here!!!!!!1
	DayData head = (DayData)shmat(QueryByNo(8888), NULL, 0);

	drawCandlesticks(sw, head, 60);

	SDL_UpdateRect(screen, 0, 0, 0, 0);//刷新屏幕
	//Wait 10 seconds
	SDL_Delay( 10000 );
	endSDL();
	fprintf(stderr, "显示结束。。。。");

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	InitializeClient();
	InitShow();
}				/* ----------  end of function main  ---------- */

#endif   /* ----- #ifndef CLIENTDATAREADER_INC  ----- */

