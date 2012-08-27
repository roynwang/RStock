/*
 * =====================================================================================
 *
 *       Filename:  testserver.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/23/2012 09:27:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include "StatusHandler/STATUS.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "DataDef/DayData.h"
#include "DataHandler/GetData.h"
	

int fifo_svstat, fifo_ctstat, fifo_shstat;
int svrshmid;
int *svstat;

int MemReadDayTDX(int no){
	return ReadAllDayTDX("sh600242.day");
}

void InitializeServer(){
	svrshmid = shmget(0, sizeof(int), IPC_CREAT|0666); 
	svstat = (int*)shmat(svrshmid, NULL, 0);
	*svstat = -1;

	fifo_svstat = CreateFIFO(SVRSTATUS, O_WRONLY);
	fifo_ctstat = CreateFIFO(CLTSTATUS, O_RDONLY);
	fifo_shstat = CreateFIFO(SVRSHMID,  O_WRONLY);
	SendInt(fifo_svstat, svrshmid);

	printf ( "server started!\n" );
}

void SetServerStatus(int status){
	printf("set server status as %d \n", status);
	*svstat = status;
}

int  ReadReq(){
	int clr=-1;
	clr = GetInt(fifo_ctstat);
	printf ( "Got request : %d\n", clr );
	SetServerStatus(SVRBUSY);
	return clr;
}
int ExecuteReq(int no){
	//start to read the data
	printf ( "executing the query: %d\n", no );
	int head = MemReadDayTDX(no);
	//done
	SetServerStatus(SVRREADY);
	SendInt(fifo_shstat, head);
	return head;
}


void FreeShm(int shmid){
	int next, cur;
	cur = shmid;
	
	while(cur!=0){
		DayData d = (DayData)shmat(cur,NULL, 0);
		next= d->next;
		printf ( "Next is %d\n", next );
		printf ( "Now free %d\n", cur );

		shmctl(cur,IPC_RMID, NULL);
		shmdt(d);
		
		cur = next;
	}
	printf ( "Free share memory finished\n" );
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
	InitializeServer();
	SetServerStatus(SVRREADY);
	int num;
	printf ( "waiting fore request\n" );
	while(1){
		int no = ReadReq();
		if(no == PIPECLOSED) break;
		num = ExecuteReq(no);
	}
	printf ( "Pipe CLTSTATUS closed\n" );
	FreeShm(num);
	unlink(SVRSTATUS);
	unlink(SVRSHMID);
	unlink(CLTSTATUS);
}				/* ----------  end of function main  ---------- */
