/*
 * =====================================================================================
 *
 *       Filename:  YahooReader.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/29/2012 06:56:14 PM
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
#include <string.h>
#include <sys/shm.h>
#include "../../DataDef/DayData.h"

void ReadDayYahoo(char *line, DayData day);

int ReadAllDayYahoo(const char* path);

void delchar(char *s, char c)
{
	char *p,*q;
	int i=strlen(s);
	for(p=s;p<=s+i;p++){
		if(*p==c){
			q=p;
			for(i--;p<=s+i;p++)  //进行覆盖
				*p=*p+1;
			p=q--;
		}	
	}
}
int FormatDate(char* date){
	delchar(date, '-');
	return atoi(date);
}

int ReadAllDayYahoo(const char* path){
	printf("trying to open file\n");
	FILE *fid = fopen(path, "r");
	printf("file opened\n");
	char line[200];
	printf(".");
	//skip the firt line
	int shmid,head,lshmid;
	lshmid = 0;
	printf(".");
	fgets(line,200, fid);

	printf(".");
	while(fgets(line, 200, fid)){
		printf("trying to new memory");
		shmid = shmget(0, DUSIZE, IPC_CREAT|0666);

		printf("memory initialized");
		DayData dd= (DayData)shmat(shmid, NULL, 0);
		dd->next = lshmid;
		ReadDayYahoo(line, dd);
		head = shmid;
		lshmid = shmid;
	}
	fclose(fid);
	return head;
}


void ReadDayYahoo(char* line, DayData day){
	char *word;
	word = strtok(line, ",");
	int i = 0;
	for(i = 0; i< 6; i++){
		if(i!=0)
			word = strtok(NULL,",");
		printf ( "word = %s\n", word );
		switch(i){
			case 0:
				day->date = FormatDate(word);
				break;
			case 1:	
				day->start = atof(word);
				break;
			case 2:	
				day->highest = atof(word);
				break;
			case 3:	
				day->lowest = atof(word);
				break;
			case 4:	
				day->end = atof(word);
				break;
			case 5:	
				//should read volume here;
				break;
			case 6:
				break;
			default:
				break;
		}
	}
}
