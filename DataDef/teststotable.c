/*
 * =====================================================================================
 *
 *       Filename:  teststotable.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/27/2012 08:20:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "StoTable.h"
#include <stdio.h>


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	StoTable table = InitStoTable();
	
	StoItem si1 = (StoItem)malloc(sizeof(struct tagStoItem));

	StoItem si2 = (StoItem)malloc(sizeof(struct tagStoItem));
	
	StoItem si3 = (StoItem)malloc(sizeof(struct tagStoItem));

	si1->SN = 1;
	si1->next = si2;
	si2->SN = 2;
	si2->next = si3;
	si3->SN = 3;
	si3->next = NULL;

	printf("initialize done!!!\n");
	AddItem(table, si1);
	printf("add si1 success\n");
	AddItem(table, si2);
	printf("add si2 success\n");
	AddItem(table, si3);
	printf("add si3 success\n");
	
	if(!GetBySN(table, 1)) printf("cannot find si1\n");
	printf ( "query 1 success\n" );
	printf ( "delete 1 result: %d\n",DelItem(table, 2));
	if(GetBySN(table, 2)) printf("Item 2 has not been deleted\n");
	printf ( "delete 2 success\n" );

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
