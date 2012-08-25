/*
 * =====================================================================================
 *
 *       Filename:  StatusMGR.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/23/2012 08:29:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

int CreateFIFO(const char*tar, int mode);

void SendInt(int fifo, int sn );

int GetInt(int fifo);
