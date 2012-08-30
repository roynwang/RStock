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
			for(i--;p<=s+i;p++)
				*p=*(p+1);
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
	fgets(line,200, fid);
	DayData head, prev;
	prev = NULL;
	int count = 0;
	while(fgets(line, 200, fid) ){
		DayData tmp = (DayData)malloc(DUSIZE);
		ReadDayYahoo(line, tmp);
		tmp->next = prev;
		prev = tmp;
		head = tmp;
		count ++;
	}
	fclose(fid);
	int shmid = shmget(0, DUSIZE*count,IPC_CREAT|0666); 
	DayData h = (DayData)shmat(shmid, NULL, 0);
	while(head){
		memcpy(h,head, DUSIZE);
		h++;
		DayData cur = head;
		head = head->next;
		//free current node
		free(cur);
		cur = NULL;
		
	}
	printf ( "count = %d shmid = %d\n", count, shmid );
	return shmid;
}


void ReadDayYahoo(char* line, DayData day){
	char *word;
	word = strtok(line, ",");
	int i = 0;
	for(i = 0; i< 6; i++){
		if(i!=0)
			word = strtok(NULL,",");
		switch(i){
			case 0:
				day->date = FormatDate(word);
				break;
			case 1:	
				day->start = atof(word)*100;
				break;
			case 2:	
				day->highest = atof(word)*100;
				break;
			case 3:	
				day->lowest = atof(word)*100;
				break;
			case 4:	
				day->end = atof(word)*100;
				break;
			case 5:	
				day->volume = atof(word);
				//should read volume here;
				break;
			default:
				break;
		}
	}
}

int LoadHistFromYahoo(char* Sn){
	char url[100] = "http://ichart.yahoo.com/table.csv?s=";
	strcat(url,Sn);
	strcat(url,".SS&a=08&b=25&c=2010&g=d");
	printf ( "Now downloading data from url: %s\n", url );
	DownloadURL(url, Sn);
	int shmid = ReadAllDayYahoo(Sn);
	return shmid;

}


