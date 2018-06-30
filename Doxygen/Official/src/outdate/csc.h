/**
 * @brief Camel Studio Connector
 * 
 * @file csc.c
 * @author Zhirui Dai
 * @date 2018-05-26
 */

#ifndef __CAMEL_STUDIO_CONNECTOR_H__
#define __CAMEL_STUDIO_CONNECTOR_H__

/*********** COMMUNICATION ***************/
//same as in "mcu.h", used as communication between studio/mcu and mcu, PAC_XXX is for RS485 type communication
//format: 
//<PAC_HEAD> <SEND_ID> <RECV_ID> <MSG> <PAC_TAIL>
//<MSG> could be:
// 1. <DATA_START> <DATA> <DATA_END>   //this is used to pass the mcu debbuger sending data back to studio, <DATA> is the data from debugger
// 2. <DBG_ACK>   //mcu entered debugger mode acknowledgement
// 3. <WRITE_ACK>  //mcu acknowledges command from sender is received
// 4. <MSG>  //string send by the program on mcu to receiver
#define SYNC_LEN 8
#define PAC_HEAD 0x1
#define PAC_TAIL 0x17
#define MAC_ID 0x1001f3f0
//#define MAC_ID 0x1001D00
#define DBG_ACK 0x5
#define WRITE_ACK 0x6
#define DATA_START 0x2
#define DATA_END 0x3
//LOAD_START indicate code upload start for uart upload using flash space code
#define LOAD_START 0x4
#define LOAD_END   0x7
#define MASTER_ID 0x20
#define STUDIO_ID 0x20
#define BROADCAST_ID 0x20
/********** END of COMMUNICATION **************/

void CommSend(char rport, unsigned char * msg);
void CommSendHead(char rport);
void CommSendHead2(char rport, char sport);
void CommSendTail();
unsigned int CommRecv(char * port, char data[]);
#if 1
unsigned int CommRecvHead(char * port);
#else
unsigned int CommRecvHead(char * port, char msg[], int * index)
#endif
unsigned int CommRecvTail();
void sendData2Studio(char * msg, unsigned long state);

#endif