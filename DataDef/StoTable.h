/*
 * =====================================================================================
 *
 *       Filename:  StoTable.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/27/2012 07:21:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

typedef struct tagStoItem{
	int SN;
	int shmid;
	struct tagStoItem *next;
} *StoItem;

typedef struct tagStoTable{
	unsigned int size;
	unsigned int curret;
	StoItem item;
} *StoTable;

StoTable InitStoTable();
void AddItem(StoTable st, StoItem si);
StoItem GetBySN(StoTable st, int SN);
int DelItem(StoTable st, int SN);
void DtyStoTable(StoTable st);

