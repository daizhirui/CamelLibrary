//################################################################
// TITLE: helper funcution head for boot loader - m2-sejoy
// AUTHOR: John & Matt
// DATE CREATED: 12/10/2013
// FILENAME: helper.h
// PROJECT: m2-sejoy
// COPYRIGHT: Copyright (C) Camel Microelectronics, Inc.
// DESCRIPTION:
// Rev No.: V1.8
//
//   Mini Boot Loader resides @0        (2kx32 rom)
//
//  06/02/2014 - john - V1.8 - print_sysctl, clean up, and put rev, mode infor 
//  04/27/2014 - john - V1.7 - remove print_gdr in interrupt(); make it release version 
//  03/27/2014 - matt - B1.6 - T3 -> T2, max line of loader increased 
//                             to 32k lines (to fit sejoy)
//  02/26/2014 - john - B1.5 - remove explicit uart print functions
//  01/24/2014 - matt - B1.3 - more dbg msg added for loader part
//                             load file size up to 16k lines (flash size)
//  01/22/2014 - matt - B1.2 - file transfer modification 
//                           - added write loop and read loop for testing
//  12/10/2013 - john - B1.1 - based on m1 minib.c, porting to m2 sejoy
//                             use m2.h
//   
//################################################################
#ifndef __HELPER_H__
#define __HELPER_H__

void interrupt(void);
void sys_init();
void _Uart_sync();
void print_menu();
void _w_func();
void _r_func();
void _R_func();
void _s_func();
void _l_func();
void _j_func();

#endif //__HELPER_H__
