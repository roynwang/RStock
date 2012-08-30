/*
 * =====================================================================================
 *
 *       Filename:  StoTable.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/27/2012 07:22:27 PM
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
#include "DayData.h"
#include "StoTable.h"
#include <sys/shm.h>

void FreeStock(StoItem si){
	DayData d = (DayData)shmat(si->shmid,NULL, 0);
	shmctl(si->shmid,IPC_RMID, NULL);
	shmdt(d);
	printf ( "Free share memory %d finished\n", si->shmid );

	char sf[10];
	sprintf(sf, "%d", si->SN);
	unlink(sf);
	printf ( "deleted the stock data %d\n", si->SN );
	free(si);
	si = NULL;

}
StoTable InitStoTable(){
	StoTable ta = (StoTable)malloc(sizeof(struct tagStoItem));
	ta->size = 0;
	ta->item = NULL;
	return ta;
}


void DtyStoTable(StoTable st){
	if(!st->item) {
		printf ( "table is null\n" );
		free(st);
		st = NULL;
		return;
	}

	StoItem cur = st->item;
	StoItem next = cur->next;
	while(cur->next!=NULL){
		next = cur->next;
		FreeStock(cur);
		cur = next;
	}
	FreeStock(cur);

	printf ( "Free Stock Table finished\n" );
	free(st);
	st = NULL;
}

void AddItem(StoTable st, StoItem si){ 
	si->next = NULL;
	if(!st->item){
		st->item = si;
		st->size++;
		return;
	}
	StoItem head = st->item;
	int i;
	for(i=1; i<st->size; i++){
		head= head->next;
	}
	head->next = si;
	st->size++;
}

StoItem GetBySN(StoTable st, int SN){
	if(st->item == NULL) return NULL;
	StoItem head = st->item;
	while(head->SN != SN && head->next!=NULL) head++;
	if(head->SN == SN) return head;
	return NULL;

}

//return 1 if found
//return 0 if not found
int DelItem(StoTable st, int SN){
	StoItem head = st->item;
	StoItem last = head;

	while(head->SN != SN && head->next!=NULL) {
		last = head;
		head = head->next;
	}

	//delete the node if found
	if(head->SN == SN){
		StoItem next= head->next;
		last->next = next;
		free(head);
		return 1;
	}
	return 0;
}


