/*
 
 * =====================================================================================
 *
 *       Filename:  drawlib.c
 *
 *    Description:  a lib containing all method to draw a sharpe
 *
 *        Version:  1.0
 *        Created:  06/23/2012 10:03:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include <stdlib.h>
#include <SDL/SDL_draw.h>
#include <sys/shm.h>
#include "../DayData.h"
#include "SubArea.h"

DayData ReadByShmid(int shmid){
	return (DayData)shmat(shmid, NULL, 0);
}

void getScaleFromDayDataSet(DayData ds, int size, float *h, float *l){
	int i;
	*h = 0;
	*l = 10000;
	while(size-->0){
		ds = ReadByShmid(ds->next);
		if(ds->lowest < *l) *l = ds->lowest;
		if(ds->highest > *h) *h = ds->highest;
	}
	*l*=0.8;
	*h*=1.2;
	printf("final: low = %f high = %f \n", *l,*h);
}

void getRelativePosition(SubWin sw, int *x, int *y, float lowprice, float highprice){

	printf("from %d %d ", *x, *y);
	int basex, basey;
	basex = sw->startx;
	basey = sw->starty + sw-> height;

	*x+=basex;
	*y=  sw->height * (highprice - *y)/(highprice-lowprice);

	printf("to %d %d\n",*x, *y);
}
void drawLine(SubWin sw, Sint16 x, Sint16 y, Sint16 ex, Sint16 ey, Uint32 color){
	printf("%d  %d %d %d \n", x, y, ex, ey);
	Draw_Line(sw->screen,x,y,ex,ey,color);
}
void drawBrokenLine(SubWin sw, int xUnit, int data[],int datasize, Uint32 color){
	int i;
	for(i = 1; i< datasize; i++){
		drawLine(sw,xUnit*(i-1),data[i-1],xUnit*i,data[i],color);
		printf("draw %d to %d \n", data[i-1], data[i]);
	}
}


void drawCandlestick(SubWin sw,int x, float lowprice, float highprice, DayData data){

	//start postion for rectangle. it will be drawn from start to right down corner 
	int startx = x;
	int starty;

	//length of shadow line; hl mean up shadow line, ll mean down shadow line
	int hl, ll;
	float yunit = (highprice - lowprice)/sw->height;
	int length;
	Uint32 color;
	//get the abs value of the candle
	data->start > data->end ? (starty  = data->start, color = GREEN
	):(starty = data->end,color = RED); 
	length = data->start - data->end;
	if(length<0){
		length*=(-1);
	}
	printf("length = %d \n", length);

	//switch to the relative value
	hl = (int)((data->highest - starty)/yunit);
	ll = (int)((starty -length - data->lowest)/yunit);
	length = (int) (length/yunit);

	printf("length = %d pix\n", length);
	if(length <1){
		length = 1;
	}
	getRelativePosition(sw,&startx,&starty, lowprice, highprice);

	//draw
	Draw_Rect(sw->screen,startx,starty,10,length,color);

	Draw_Line(sw->screen,startx+5,starty,startx+5, starty - hl,color);
	Draw_Line(sw->screen,startx+5,starty+length,startx+5, starty+length+ll,color);
}
void drawCandlesticks(SubWin sw, DayData ds, int size){
	int i;
	float h,l;
	DayData head = ds;
	getScaleFromDayDataSet(ds,size,&h,&l);
	for(i = 0; i<size; i++){
		head = ReadByShmid(head->next);
		printf("date = %d start:%f end:%f\n", head->date, head->start, head->end);
//		printf("drawing %f: %f %f %f %f\n", i, head->start, head->end, head->highest, head->lowest);
		drawCandlestick(sw,10*i+1,l,h, head);
	}
}


