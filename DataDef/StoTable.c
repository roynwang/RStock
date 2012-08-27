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
#include "DayData.h"
#include "StoTable.h"
#include <sys/shm.h>

void FreeStock(int shmid){
	int next, cur;
	cur = shmid;
	
	while(cur!=0){
		DayData d = (DayData)shmat(cur,NULL, 0);
		next= d->next;
		printf ( "Now free %d\n", cur );

		shmctl(cur,IPC_RMID, NULL);
		shmdt(d);
		
		cur = next;
	}
	printf ( "Free share memory finished\n" );
}
StoTable InitStoTable(){
	StoTable ta = (StoTable)malloc(sizeof(struct tagStoItem));
	ta->size = 0;
	ta->item = NULL;
	return ta;
}

void DtyStoTable(StoTable st){
	if(!st->item) {
		free(st);
		st = NULL;
		return;
	}
	StoItem cur = st->item;
	StoItem next = cur->next;
	while(cur->next!=NULL){
		next = cur->next;
		FreeStock(cur->shmid);
		free(cur);
		cur = NULL;
		cur = next;
	}
	FreeStock(cur->shmid);
	free(cur);
	cur = NULL;
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


