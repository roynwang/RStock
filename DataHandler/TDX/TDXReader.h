/*
 * =====================================================================================
 *
 *       Filename:  TDXReader.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/28/2012 08:43:31 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */



#ifndef  TDXREADER_INC
#define  TDXREADER_INC

int ReadDayTDX(FILE *fid, DayData day, int date);

int ReadAllDayTDX(const char* path);

#endif   /* ----- #ifndef TDXREADER_INC  ----- */
