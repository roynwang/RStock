/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/29/2012 07:11:16 PM
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
#include <curl/curl.h>
#include "YahooDownloader.h"
#include "../../DataDef/DayData.h"
#include <sys/shm.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	char* url = "http://ichart.finance.yahoo.com/table.csv?s=600000.ss&a=NaN&b=02&c=pr-2&g=d&ignore=.csv";
	DownloadURL(url, "yahooresult.csv");
    int head;
    head = ReadAllDayYahoo("yahooresult.csv");
	void * d = (void *)shmat(head, NULL, 0);
	shmctl(head, IPC_RMID, NULL);
	shmdt(d);
	printf ( "deleted the shared memory %d\n" , head);
	unlink("yahooresult.csv");
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
