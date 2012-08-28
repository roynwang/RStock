/*
 * =====================================================================================
 *
 *       Filename:  TDXReader.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/22/2012 09:45:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */



#include "../../DataDef/DayData.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>


long GetToday(){
	time_t rawtime;
	struct tm *	hrtime;
	time(&rawtime);
	hrtime = localtime( &rawtime);
	long maxtime;
	maxtime = (hrtime->tm_year+1900)*(long)10000 + (hrtime->tm_mon+1)*100 + hrtime->tm_mday;
	return maxtime;
}

int ReadDayTDX(FILE *fid, DayData day, int date){

	int p = 0;

//	fread(&p, sizeof(unsigned int), 1, fid);
	if(date<STARTDAY || date>GetToday()) return 0;
	day->date  = date;

	fread(&p, sizeof(unsigned int), 1, fid);
	day->start = (float)p;

	fread(&p, sizeof(unsigned int), 1, fid);
	day->highest =(float) p;

	fread(&p, sizeof(unsigned int), 1, fid);
	day->lowest = (float)p;

	fread(&p, sizeof(unsigned int), 1, fid);
	day->end = (float)p;

	//move to next node
	fseek(fid, 3*sizeof(unsigned int), 1);

	return 1;
}

int ReadAllDayTDX(const char* path){
	int p = 0;
	FILE * fid;

	//initialzie the head node 
	int shmid, head;
	shmid=shmget(0,DUSIZE,IPC_CREAT|0666);
	head = shmid;
	DayData dd = (DayData)shmat(shmid, NULL, 0);

	fid=fopen(path,"r");

	while(!feof(fid) &&( p>GetToday() || p<STARTDAY)){
		fread(&p, sizeof(unsigned int), 1, fid);
	}

	while(p<= GetToday() && !feof(fid)){
		ReadDayTDX(fid,dd,p);
		printf ( "write shmid %d with date %d\n", shmid, p );
		shmid=shmget(0,DUSIZE,IPC_CREAT|0666);
		dd->next = shmid;
		dd = (DayData)shmat(shmid, NULL, 0);
		fread(&p, sizeof(unsigned int), 1, fid);
	}

	fclose(fid);
	return head;

}


