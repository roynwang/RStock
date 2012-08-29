/*
 * =====================================================================================
 *
 *       Filename:  YahooReader.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/29/2012 07:05:46 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  YAHOOREADER_INC
#define  YAHOOREADER_INC
void ReadDayYahoo(FILE *fid, DayData day, int data);

void ReadAllDayYahoo(const char* path);

#endif   /* ----- #ifndef YAHOOREADER_INC  ----- */
