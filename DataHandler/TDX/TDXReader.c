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
#include <string.h>


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
	int count = 0;

	DayData dd = (DayData)malloc(DUSIZE);
	DayData head = dd;
	fid=fopen(path,"r");

	while(!feof(fid) &&( p>GetToday() || p<STARTDAY)){
		fread(&p, sizeof(unsigned int), 1, fid);
	}

	while(p<= GetToday() && !feof(fid)){
		count++;
		ReadDayTDX(fid,dd,p);
		dd->next = NULL;
		fread(&p, sizeof(unsigned int), 1, fid);
		if(p<=GetToday() && !feof(fid)){
			DayData tmp = (DayData) malloc( DUSIZE);
			dd->next = tmp;
			dd = tmp;
		}
	}
	fclose(fid);
	int shmid = shmget(0,DUSIZE*count,IPC_CREAT|0666);
	DayData h = (DayData)shmat(shmid, NULL,0);
	while(head){
		memcpy(h, head, DUSIZE);
		h++;
		DayData cur = head;
		head = head->next;
		free(cur);
		cur = NULL;
	}
	return shmid;
}


