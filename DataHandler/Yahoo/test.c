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


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	char* url = "http://ichart.finance.yahoo.com/table.csv?s=DAI.DE&a=NaN&b=02&c=pr-2&g=d&ignore=.csv";
	DownloadURL(url, "yahooresult.csv");
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
