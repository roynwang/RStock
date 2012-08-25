/*
 * =====================================================================================
 *
 *       Filename:  DayData.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/21/2012 11:52:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */



#ifndef  DAYDATA_INC
#define  DAYDATA_INC

// head shmid 
#define	DAYHEAD 1000			/*  */
#define	STARTDAY 20100000			/*  */
#define	DUSIZE sizeof(struct tagDayData)			/*  */

typedef struct tagDayData{
	int date;
	float start;
	float end;
	float highest;
	float lowest;
	float volume;
	int next;
} *DayData;
#endif   /* ----- #ifndef DAYDATA_INC  ----- */

