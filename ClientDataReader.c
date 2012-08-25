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
#include "StatusMGR.h"
#include "STATUS.h"
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>  
#include <time.h>


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

void QueryByNo(int no){
	SendInt(fifo_ctstat, no);
	int shmid = GetInt(fifo_shstat);
	printf ( "%d memory = %d \n", no, shmid );
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
	printf ( "Start Query\n" );
	QueryByNo(9999);
	printf ( "End Query\n");
}				/* ----------  end of function main  ---------- */

#endif   /* ----- #ifndef CLIENTDATAREADER_INC  ----- */

