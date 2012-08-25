/*
 * =====================================================================================
 *
 *       Filename:  TestGetData.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/22/2012 10:36:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include	<stdlib.h>
#include "GetData.h"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	ReadAllDayTDX("sh600242.day");
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
