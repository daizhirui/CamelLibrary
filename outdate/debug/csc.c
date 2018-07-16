/**
 * @brief Camel Studio Connector
 * 
 * @file csc.c
 * @author Zhirui Dai
 * @date 2018-05-26
 */

#include "csc.h"
#include "mcu.h"

void CommSend(char rport, unsigned char * msg)
{
    int i;
    #if 0 //when sync protocol is used for each command
        for (i = 0; i <= SYNC_LEN; i++)
            putc_uart(PAC_HEAD);
    #else
        putc_uart(PAC_HEAD);
    #endif
    putc_uart(rport);
    putc_uart(getMAC());
    for (i = 0; i < DATA_SIZE; i++) {
        if (msg[i] == '\0')
            break;
        putc_uart(msg[i]);
    }
    putc_uart(PAC_TAIL);
}

void CommSendHead(char rport)
{
    #if 0 //when sync protocol is used for each command
        int i;
        for (i = 0; i <= SYNC_LEN; i++)
            putc_uart(PAC_HEAD);
    #else
        putc_uart(PAC_HEAD);
    #endif
    putc_uart(rport);
    putc_uart(getMAC());
}

void CommSendHead2(char rport, char sport)
{
    #if 0 //when sync protocol is used for each command
        int i;
        for (i = 0; i <= SYNC_LEN; i++)
            putc_uart(PAC_HEAD);
    #else
        putc_uart(PAC_HEAD);
    #endif
    putc_uart(rport);
    putc_uart(sport);
}

void CommSendTail()
{
    putc_uart(PAC_TAIL);
}


unsigned int CommRecv(char * port, char data[])
{    
    int i;
    char tmp;
    /*char msg[DATA_SIZE];
    int index;
    msg[0] = '\0';
    index = 0;*/
    data[0] = '\0';
    i = 0;
    
    //if (CommRecvHead(port, msg, &index)) {
    if (CommRecvHead(port)) {
        tmp = getch();
        while (tmp != PAC_TAIL && i < DATA_SIZE) {
            data[i++] = tmp;
            tmp = getch();
        }
        if (i < DATA_SIZE)
            data[i] = '\0';
        else    {
            data[0] = '\0';
            return 0;
        }
        //check to see if this buf is for setting the port id
        if (data[0] == 'S') {
                  if (data[1] == 'S') {    
                setMAC(data[2]);
                return 0; //finish setting, this command is processed, so return 0 to avoid process it again.
            }
        }
        return 1;
    }
    return 0;
}

unsigned int _pac_head_detect()
{
    int i, start, pre, len;
    char tmp[SYNC_LEN];
    char ch;
    int val[SYNC_LEN];
    int state1;
    int state = MemoryRead32(SYS_CTL2_REG);
    state &= ~(7<<4); //clear the uart freq adjust reg
    val[0] = 6;
    val[1] = 5;
    val[2] = 4;
    val[3] = 2;
    val[4] = 7;
    val[5] = 1;
    val[6] = 0;
    val[7] = 3;
    for (i = 0; i < SYNC_LEN; i++) {
        state1 = (state | (val[i]<<4));
        MemoryWrite32(SYS_CTL2_REG, state1);
        tmp[i] = getch();
    }
    pre = -1;
    len = 0;
    start = 0;
    for (i = 0; i < SYNC_LEN; i++) {
        if (pre < 0 && tmp[i] == PAC_HEAD)
            pre = i;
        else if (pre >= 0 && tmp[i] != PAC_HEAD) {
            if (len < (i - pre)) {
                len = i - pre;
                start = pre;
            }
            pre = -1;
        }
    }
    start = start + len/2;
    state1 = (state | (val[start]<<4));
    MemoryWrite32(SYS_CTL2_REG, state1); 
    getch(); //this one is to make sure the next read will be correct since SYS_CTL2_REG is just set
    return 1;
}

#if 1
unsigned int CommRecvHead(char * port)
{
    char recvport;    
    if (!MemoryRead32(UART0_DATA_RDY_REG))
        return 0;
    #if 0  //when sync protocol is used for each command
        if (!_pac_head_detect())
            return 0;
        recvport = getch();
        *port = getch();
    #else
        char head = getch();
        recvport = getch();
        *port = getch();
        if (head != PAC_HEAD) 
            return 0;
    #endif
    if (recvport != getMAC() && recvport != (char)0)                 return 0;
    return 1;
}
#else
unsigned int CommRecvHead(char * port, char msg[], int * index)
{
    char head, recvport;    
    if (!MemoryRead32(UART0_DATA_RDY_REG)()) {
        return 0;
    }
    head = getch();
    recvport = getch();
    *port = getch();
    if (head != PAC_HEAD) {
        cm_strcat(msg, "no h ");
        charcat(msg, head);
        charcat(msg, '\r');
        charcat(msg, getch());
        charcat(msg, '\r');
        CommSendHead2(STUDIO_ID, BROADCAST_ID);
        puts(msg);
        CommSendTail();
        return 0;
    } else { //debug msg
        cm_strcat(msg, "h ");
        charcat(msg, head);
        charcat(msg, '\r');
    }
    if (recvport != __mac_id && recvport != (char)0) {
        cm_strcat(msg, "no rport ");
        charcat(msg, recvport);
        charcat(msg, '\r');
        charcat(msg, getch());
        charcat(msg, '\r');
        CommSendHead2(STUDIO_ID, BROADCAST_ID);
        puts(msg);
        CommSendTail();
        return 0;
    } else { //debug msg
        cm_strcat(msg, "rport ");
        charcat(msg, recvport);
        charcat(msg, '\r');
    }
    cm_strcat(msg, "sport ");
    charcat(msg, *port);
    charcat(msg, '\r');
    return 1;
}
#endif

unsigned int CommRecvTail()
{
    if (getch() == PAC_TAIL)
        return 1;
    else
        return 0;
}

void sendData2Studio(char * msg, unsigned long state)
{
    CommSendHead(STUDIO_ID);
    puts(msg);
         puts(xtoa(state));
    puts("\r");
         CommSendTail();
}
