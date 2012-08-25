/*
 * =====================================================================================
 *
 *       Filename:  STATUS.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/23/2012 08:21:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * ===================================================================================== */

#ifndef  STATUS_INC
#define  STATUS_INC

#define  SVRSTATUS  "RSTOCKSERVER"  
#define  SVRSHMID   "RSTOCKSHMID"
#define  CLTSTATUS  "RSTOCKCLIENT"

#define SVRBUSY		0x0002
#define SVRREADY    0x0001


#define  RDTDXERROR 0xffff
#define  TESTSTATUS 0x0
#define  READFAIL   0xffff-1
#define	 PIPECLOSED	0xffff-2		/*  */
#endif   /* ----- #ifndef STATUS_INC  ----- */


