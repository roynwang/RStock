/*
 * =====================================================================================
 *
 *       Filename:  drawlib.h
 *
 *    Description:  header for drawlib
 *
 *        Version:  1.0
 *        Created:  06/23/2012 10:10:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  DRAWLIB_INC
#define  DRAWLIB_INC

#include "SubArea.h"
#include "../DayData.h"
void drawLine(SubWin sw, Sint16 x, Sint16 y, Sint16 ex, Sint16 ey, Uint32 color);

void drawCandlestick(SubWin w, int x, float lowprice, float highprice, DayData data); 

void drawCandlesticks(SubWin w, DayData ds, int size);
void drawBrokenLine(SubWin sw,	int xUnit, int data[], int datasize,Uint32 color);

#endif
