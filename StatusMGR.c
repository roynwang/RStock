/*
 * =====================================================================================
 *
 *       Filename:  StatusMGR.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/23/2012 08:20:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "STATUS.h"

int CreateFIFO(const char* tar, int mode){
	int fifo = -1;
	if ( mode == O_WRONLY && access(tar, F_OK) == -1)  
	{  
		int res = mkfifo(tar, 0777);  
		if (res != 0)  
		{  
			printf("Could not create fifo %s/n", tar);  
			return -1;
		}  
		printf("initialize FIFO done \n");
		fifo =  open(tar, mode);
		printf("open FIFO %d for write\n", fifo);
		return fifo;
	}
	if( mode == O_RDONLY){
		while(fifo == -1){
			fifo = open(tar, mode);
			sleep(1);
		}
		printf("open FIFO %d for read\n", fifo);
		return fifo;
	}

}


void SendInt(int fifo, int sn){
	printf ( "write %d into %d\n", sn, fifo );
	write(fifo, &sn, sizeof(int));
}


int GetInt(int fifo){
	int output = PIPECLOSED; 
	read(fifo, &output, sizeof(int));
	printf("read out %d from %d\n", output, fifo);
	return output;
}


