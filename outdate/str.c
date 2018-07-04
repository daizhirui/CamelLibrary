/*--------------------------------------------------------------------
 * TITLE: M2 Hardware Defines
 * AUTHOR: John & Jack 
 * DATE CREATED: 2013/10/10
 * FILENAME: str.c
 * PROJECT: M2Library
 * COPYRIGHT: Small World, Inc.
 * DESCRIPTION:
 *    M2 Hardware Defines
 * NOTE:
 *         This str library is almost copied from old version. It hasn't
 * been checked again.    -- Astro, 2017/11/4
 *-------------------------------------------------------------------*/
#include "mcu.h"
#include "str.h"


void putc_uart(unsigned char c)// 
{
    unsigned int uport;
    
    do {
          uport=*(volatile unsigned*) uart_bport;
    } while (uport & WRITE_BUSY);
    
    *(volatile unsigned char*)uart_wport=c;
}    

unsigned char read_uart()//Apr.4.2005 changed 32 bits port
{
    unsigned uport=*(volatile unsigned*) uart_rport;
    return uport;
}    


int putch(unsigned char value)
{
   putc_uart (value);
}

int puts(const char *string)
{
   while(*string)
   {
      if(*string == '\n')
         putch('\r');
      putch(*string++);
   }
   return 0;
}

char *xtoa(unsigned long num)
{
   static char buf[12];
   int i, digit;
   buf[8] = 0;
   for (i = 7; i >= 0; --i)
   {
      digit = num & 0xf;
      buf[i] = digit + (digit < 10 ? '0' : 'A' - 10);
      num >>= 4;
   }
   return buf;
}

char * cm_strcat(char * des, char * source)
{
    int index;
    index = DATA_SIZE -1;
    char * tmp = des;
    while (*tmp) {
        index--;
        tmp++;
        if (index == 0)
            return des;
    }
    while (*source) {
        *tmp++ = *source++;
        index--;
        if (index == 0)
            return des;
    }
    *tmp = '\0';
    return des;
}

char * charcat(char * des, char source)
{
    int index;
    char * tmp = des;
    index = DATA_SIZE - 2;
    while (*tmp) {
        tmp++;
        index--;
        if (index == 0)
            return des;
    }
    *tmp++ = source;
    *tmp = '\0';
    return des;
}

int kbhit(void)
{
   return MemoryRead(UART_DATA_RDY) & READ_RDY;
}

//
// this can only be called in interrupt routine
//
unsigned char getch(void)
{
   while(!kbhit()) ;
   return read_uart();
}

unsigned long getnum(void)
{
   int i;
   unsigned char ch;
   unsigned long value=0;

   for(i = 0; i < 16; )   // why 16 ? not 8?
   {
      ch  = getch();
      if(ch == '\r')
         break;
      if(ch == '\n' || ch == '\r' || ch == ' ')
         break;
      if('0' <= ch && ch <= '9')
         ch -= '0';
      else if('A' <= ch && ch <= 'Z')
         ch = ch - 'A' + 10;
      else if('a' <= ch && ch <= 'z')
         ch = ch - 'a' + 10;
      else if(ch == 8)  // ^H  or \b  backspace  ???
      {
         if(i > 0)
            --i;
         value >>= 4;
         continue;
      }
      value = (value << 4) + ch;
      ++i;
   }
   return value;
}

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
    if (!kbhit())
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
    if (!kbhit()) {
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


