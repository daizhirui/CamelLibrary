/*--------------------------------------------------------------------
 * TITLE: M2 Hardware Definition
 * AUTHOR: John & Jack 
 * DATE CREATED: 2017/11/4
 * FILENAME: probe.c
 * PROJECT: M2Library
 * COPYRIGHT: Camel Microelectronics, Ltd.
 * DESCRIPTION:
 *         This file is copied from V20170715 directly.
 *--------------------------------------------------------------------*/
//---------------------------------------------------------------------------
// This code demonstrates enumeration using the MAXIM MAX3420E USB Peripheral Controller.
// The code handles all host enumeration requests, as well as suspend/resume. The USB device
// implemented with this code reports itself as capable of signaling remote wakeup (RWU),
//
//
#include "MAX3420E.h"       // MAX3420E registers (rREGNAME), bits (bmBITNAME), and some handy macros
#include "probe_def.h"  // HID keyboard enumeration data
#include "probe.h"
#include "mcu.h"
#include "str.h"

// function prototypes
void Reset_MAX(void);           // Reset the MAX3420E
void wreg(BYTE r,BYTE v);       // Write a MAX3420E register byte
void wregAS(BYTE r,BYTE v);     // Same as 'wreg' but also set the ACKSTAT bit in the SPI command byte
BYTE rreg(BYTE r);              // Read a MAX3420E register byte
BYTE rregAS(BYTE r);            // Same as 'rreg' but also set the ACKSTAT bit
void readbytes(BYTE reg, BYTE N, BYTE *p);  // Read N MAX3420E FIFO bytes into the array p
void writebytes(BYTE reg, BYTE N, const BYTE *p); // Write N MAX3420E FIFO bytes into the array p

// USB functions
void std_request(void);
void class_request(void);
void vendor_request(void);
void send_descriptor(void);
void send_keystroke(BYTE);
void feature(BYTE);
void get_status(void);
void set_interface(void);
void get_interface(void);
void set_configuration(void);
void get_configuration(void);

// Application code
void do_SETUP(void);      // Handle a USB SETUP transfer
void probeWrite(char * buf);
void check_for_resume(void);

//Global variables
BYTE SUD[8];        // Local copy of the 8 setup data read from the MAX3420E SUDFIFO
BYTE configval;        // Set/Get_Configuration value
BYTE ep3stall;        // Flag for EP3 Stall, set by Set_Feature, reported back in Get_Status
BYTE interfacenum;      // Set/Get interface value
BYTE RWU_enabled;       // Set by Set/Clear_Feature RWU request, sent back for Get_Status-RWU
BYTE Suspended;         // Tells the main loop to look for host resume and RWU pushbutton
BYTE send3zeros;        // EP3-IN function uses this to send HID (key up) codes between keystrokes

//
#define ENABLE_IRQS wreg(rEPIEN,(bmSUDAVIE+bmIN3BAVIE)); wreg(rUSBIEN,(bmURESIE+bmURESDNIE));
// Note: the SUSPEND IRQ will be enabled later, when the device is configured.
// This prevents repeated SUSPEND IRQ's

BYTE connected = 0;

void initialize_MAX(void)
{
    ep3stall=0;            // EP3 inintially un-halted (no stall) (CH9 testing)
    // software flags
    configval=0;                    // at pwr on OR bus reset we're unconfigured
    Suspended=0;
    RWU_enabled=0;                  // Set by host Set_Feature(enable RWU) request
    send3zeros=1;
    connected = 0;
    //
    MemoryWrite32(SPI_CTL_REG, 0x6); //master, no irq
    //
    // Always set the FDUPSPI bit in the PINCTL register FIRST if you are using the SPI port in 
    // full duplex mode. This configures the port properly for subsequent SPI accesses.
    //
    wreg(rPINCTL,(bmFDUPSPI+bmINTLEVEL+gpxSOF)); // MAX3420: SPI=full-duplex, INT=neg level, GPX=SOF
    Reset_MAX();
    // This is a self-powered design, so the host could turn off Vbus while we are powered.
    // Therefore set the VBGATE bit to have the MAX3420E automatically disconnect the D+
    // pullup resistor in the absense of Vbus. Note: the VBCOMP pin must be connected to Vbus
    // or pulled high for this code to work--a low on VBCOMP will prevent USB connection.
    wreg(rUSBCTL,(bmCONNECT+bmVBGATE)); // VBGATE=1 disconnects D+ pullup if host turns off VBUS
    ENABLE_IRQS
wreg(rCPUCTL,bmIE);                 // Enable the INT pin
}

void check_for_resume(void)         
{
      if(rreg(rUSBIRQ) & bmBUSACTIRQ)     // THE HOST RESUMED BUS TRAFFIC
        {
          Suspended=0;                    // no longer suspended
        }
      else if(RWU_enabled)                // Only if the host enabled RWU
        {
          if((rreg(rGPIO)&0x40)==0)       // See if the Remote Wakeup button was pressed
            {
                Suspended=0;                  // no longer suspended
                SETBIT(rUSBCTL,bmSIGRWU)      // signal RWU
                while ((rreg(rUSBIRQ)&bmRWUDNIRQ)==0) ;    // spin until RWU signaling done
                CLRBIT(rUSBCTL,bmSIGRWU)      // remove the RESUME signal 
                wreg(rUSBIRQ,bmRWUDNIRQ);     // clear the IRQ
                while((rreg(rGPIO)&0x40)==0) ;  // hang until RWU button released
                wreg(rUSBIRQ,bmBUSACTIRQ);    // wait for bus traffic -- clear the BUS Active IRQ
                while((rreg(rUSBIRQ) & bmBUSACTIRQ)==0) ; // & hang here until it's set again...
            }
       }
} 

void CMProbe(unsigned char addr, unsigned long val)
{
    static char data[10];
    int i;
    char * buf;
    buf = xtoa(val);
    for (i = 0; i < 8; i++) 
        data[i] = buf[i];
    data[8] = addr;
    data[9] = '\0';
    probeWrite(data);
}

void probeWrite(char * buf/*BYTE c*/)
{
    BYTE itest1,itest2;
    while (1) {
        if(Suspended)
            check_for_resume();
        itest1 = rreg(rEPIRQ);            // Check the EPIRQ bits
        itest2 = rreg(rUSBIRQ);           // Check the USBIRQ bits
        if(itest1 & bmSUDAVIRQ) 
            {
                 wreg(rEPIRQ,bmSUDAVIRQ);     // clear the SUDAV IRQ
                 do_SETUP();
            }
        if(itest1 & bmIN3BAVIRQ)          // Was an EP3-IN packet just dispatched to the host?
            {
                int index = 0;
                while (buf[index] != '\0') {
                wreg(rEP3INFIFO, buf[index]);
                index++;
                }
                wreg(rEP3INBC, index);
                break;
            }                             // NOTE: don't clear the IN3BAVIRQ bit here--loading the EP3-IN byte
                                  // count register in the do_IN3() function does it.
        if((configval != 0) && (itest2&bmSUSPIRQ))   // HOST suspended bus for 3 msec
            {
                wreg(rUSBIRQ,(bmSUSPIRQ+bmBUSACTIRQ));  // clear the IRQ and bus activity IRQ
                Suspended=1;                  // signal the main loop
            }
        if(rreg(rUSBIRQ)& bmURESIRQ)
            {
                wreg(rUSBIRQ,bmURESIRQ);      // clear the IRQ
            }
        if(rreg(rUSBIRQ) & bmURESDNIRQ)
            {
                wreg(rUSBIRQ,bmURESDNIRQ);    // clear the IRQ bit
                Suspended=0;                  // in case we were suspended
                ENABLE_IRQS                   // ...because a bus reset clears the IE bits
            }
    }
}
 
void probe_setup()
{
       BYTE itest1, itest2;
        if (Suspended)
             check_for_resume();
    itest1 = rreg(rEPIRQ);            // Check the EPIRQ bits
        itest2 = rreg(rUSBIRQ);           // Check the USBIRQ bits
    if(itest1 & bmSUDAVIRQ) 
        {
             wreg(rEPIRQ,bmSUDAVIRQ);     // clear the SUDAV IRQ
             do_SETUP();
        }
        if((configval != 0) && (itest2&bmSUSPIRQ))   // HOST suspended bus for 3 msec
            {
            wreg(rUSBIRQ,(bmSUSPIRQ+bmBUSACTIRQ));  // clear the IRQ and bus activity IRQ
            Suspended=1;                  // signal the main loop
            }
    if(rreg(rUSBIRQ)& bmURESIRQ)
            wreg(rUSBIRQ,bmURESIRQ);      // clear the IRQ
    if(rreg(rUSBIRQ) & bmURESDNIRQ)
        {
            wreg(rUSBIRQ,bmURESDNIRQ);    // clear the IRQ bit
            ENABLE_IRQS                   // ...because a bus reset clears the IE bits
        }
}

void do_SETUP(void)
{                            
    readbytes(rSUDFIFO,8,SUD);          // got a SETUP packet. Read 8 SETUP bytes
    switch(SUD[bmRequestType]&0x60)     // Parse the SETUP packet. For request type, look only at b6&b5
        {
            case 0x00:    std_request();        break;
            case 0x20:    class_request();    break;  // just a stub in this program
            case 0x40:    vendor_request();    break;  // just a stub in this program
            default:    STALL_EP0                       // unrecognized request type
        }
}

//*******************
void std_request(void)
{
    switch(SUD[bRequest])            
    {
        case    SR_GET_DESCRIPTOR:    send_descriptor();    break;
        case    SR_SET_FEATURE:        feature(1);           break;
        case    SR_CLEAR_FEATURE:    feature(0);           break;
        case    SR_GET_STATUS:        get_status();         break;
        case    SR_SET_INTERFACE:    set_interface();      break;
        case    SR_GET_INTERFACE:    get_interface();      break;
        case    SR_GET_CONFIGURATION:   get_configuration();  break;
        case    SR_SET_CONFIGURATION:   set_configuration();  break;
        case    SR_SET_ADDRESS:         rregAS(rFNADDR);      break;  // discard return value
        default:  STALL_EP0
    }
}

//**************************
void set_configuration(void)
{
    configval=SUD[wValueL];           // Store the config value
    if(configval != 0)                // If we are configured, 
          SETBIT(rUSBIEN,bmSUSPIE);       // start looking for SUSPEND interrupts
    rregAS(rFNADDR);                  // dummy read to set the ACKSTAT bit
    connected =1;
}

void get_configuration(void)
{
    wreg(rEP0FIFO,configval);         // Send the config value
    wregAS(rEP0BC,1);   
}

//**********************
void set_interface(void)    // All we accept are Interface=0 and AlternateSetting=0, otherwise send STALL
{
    BYTE dumval;
    if((SUD[wValueL]==0)        // wValueL=Alternate Setting index
          &&(SUD[wIndexL]==0))        // wIndexL=Interface index
          dumval=rregAS(rFNADDR);    // dummy read to set the ACKSTAT bit
    else STALL_EP0
}

//**********************
void get_interface(void)    // Check for Interface=0, always report AlternateSetting=0
{
    if(SUD[wIndexL]==0)        // wIndexL=Interface index
      {
          wreg(rEP0FIFO,0);        // AS=0
          wregAS(rEP0BC,1);        // send one byte, ACKSTAT
      }
    else STALL_EP0
}

//*******************
void get_status(void)
{
    BYTE testbyte;
    testbyte=SUD[bmRequestType];
    switch(testbyte)    
    {
        case 0x80:             // directed to DEVICE
            wreg(rEP0FIFO,(RWU_enabled+1));    // first byte is 000000rs where r=enabled for RWU and s=self-powered.
            wreg(rEP0FIFO,0x00);        // second byte is always 0
            wregAS(rEP0BC,2);         // load byte count, arm the IN transfer, ACK the status stage of the CTL transfer
                break;
        case 0x81:             // directed to INTERFACE
            wreg(rEP0FIFO,0x00);        // this one is easy--two zero bytes
            wreg(rEP0FIFO,0x00);        
            wregAS(rEP0BC,2);         // load byte count, arm the IN transfer, ACK the status stage of the CTL transfer
            break;                 
        case 0x82:             // directed to ENDPOINT
            if(SUD[wIndexL]==0x83)        // We only reported ep3, so it's the only one the host can stall IN3=83
               {
                      wreg(rEP0FIFO,ep3stall);    // first byte is 0000000h where h is the halt (stall) bit
                      wreg(rEP0FIFO,0x00);        // second byte is always 0
                      wregAS(rEP0BC,2);         // load byte count, arm the IN transfer, ACK the status stage of the CTL transfer
                      break;
                  }
            else  STALL_EP0        // Host tried to stall an invalid endpoint (not 3)                
        default:      STALL_EP0        // don't recognize the request
    }
}

// **********************************************************************************************
// FUNCTION: Set/Get_Feature. Call as feature(1) for Set_Feature or feature(0) for Clear_Feature.
// There are two set/clear feature requests:
//    To a DEVICE:     Remote Wakeup (RWU). 
//      To an ENDPOINT:    Stall (EP3 only for this app)
//
void feature(BYTE sc)
{
    BYTE mask;
      if((SUD[bmRequestType]==0x02)    // dir=h->p, recipient = ENDPOINT
          &&  (SUD[wValueL]==0x00)    // wValueL is feature selector, 00 is EP Halt
          &&  (SUD[wIndexL]==0x83))    // wIndexL is endpoint number IN3=83
      {
          mask=rreg(rEPSTALLS);   // read existing bits
          if(sc==1)               // set_feature
            {
                mask += bmSTLEP3IN;       // Halt EP3IN
                ep3stall=1;
            }
          else                        // clear_feature
            {
                mask &= ~bmSTLEP3IN;      // UnHalt EP3IN
                ep3stall=0;
                wreg(rCLRTOGS,bmCTGEP3IN);  // clear the EP3 data toggle
            }
          wreg(rEPSTALLS,(mask|bmACKSTAT)); // Don't use wregAS for this--directly writing the ACKSTAT bit
       }
      else if ((SUD[bmRequestType]==0x00)    // dir=h->p, recipient = DEVICE
           &&  (SUD[wValueL]==0x01))    // wValueL is feature selector, 01 is Device_Remote_Wakeup
      {
             RWU_enabled = sc<<1;    // =2 for set, =0 for clear feature. The shift puts it in the get_status bit position.            
            rregAS(rFNADDR);        // dummy read to set ACKSTAT
      }
      else STALL_EP0
}

//************************
void send_descriptor(void)
{
    WORD reqlen,sendlen,desclen;
    const BYTE *pDdata;                    // pointer to ROM Descriptor data to send
    //
    // NOTE This function assumes all descriptors are 64 or fewer bytes and can be sent in a single packet
    //
    desclen = 0;                    // check for zero as error condition (no case statements satisfied)
    reqlen = SUD[wLengthL] + 256*SUD[wLengthH];    // 16-bit
    switch (SUD[wValueH])            // wValueH is descriptor type
    {
        case  GD_DEVICE:
                  desclen = DD[0];    // descriptor length
                  pDdata = DD;
                  break;    
        case  GD_CONFIGURATION:
                  desclen = CD[2];    // Config descriptor includes interface, HID, report and ep descriptors
                  pDdata = CD;
                  break;
        case  GD_STRING:
                  desclen = strDesc[SUD[wValueL]][0];   // wValueL=string index, array[0] is the length
                  pDdata = strDesc[SUD[wValueL]];       // point to first array element
                  break;
        case  GD_HID:
                  desclen = CD[18];
                  pDdata = &CD[18];
                  break;
        case  GD_REPORT:
                  desclen = CD[25];
                  pDdata = RepD;
            break;
    }    // end switch on descriptor type
    //
    if (desclen!=0)                   // one of the case statements above filled in a value
    {
        sendlen = (reqlen <= desclen) ? reqlen : desclen; // send the smaller of requested and avaiable
            writebytes(rEP0FIFO,sendlen,pDdata);
        wregAS(rEP0BC,sendlen);   // load EP0BC to arm the EP0-IN transfer & ACKSTAT
    }
    else STALL_EP0  // none of the descriptor types match
}

void class_request(void) 
{
    STALL_EP0
}                         

void vendor_request(void)
{
    STALL_EP0
}

// ******************** END of ENUMERATION CODE ********************
//
void Reset_MAX(void)    
{
    BYTE dum;
    wreg(rUSBCTL,0x20);    // chip reset
    wreg(rUSBCTL,0x00);    // remove the reset
        do                  // Chip reset stops the oscillator. Wait for it to stabilize.
        {
            dum=rreg(rUSBIRQ);

            dum &= bmOSCOKIRQ;
        }
        while (dum==0);
}
//
// ------------------------------------------------------------
// The code below customizes this app for the M3
// microprocessor and the MIPS compiler. Only this
// section changes if you use a different uP and/or compiler.
// ------------------------------------------------------------
//

void wreg(BYTE reg, BYTE dat)
{
      MemoryWrite32(SPI_CTL_REG, 0x6); //cs on
      MemoryWrite32(SPI_IRQACK_REG, 0);
      MemoryWrite32(SPI_WRITE_REG, reg+2); //send the register number with DIR bit (b1) set to WRITE
      while (MemoryRead32(SPI_BUSY_REG));  //loop if data still being sent
      MemoryWrite32(SPI_WRITE_REG, dat);  //send the data
      while (MemoryRead32(SPI_BUSY_REG));  //loop if data still being sent
      MemoryWrite32(SPI_CTL_REG, 0x4); //cs off
      MemoryWrite32(SPI_IRQACK_REG, 0);
}


// Write a MAX3410E register with the "ACK STATUS" bit set in the command byte
void wregAS(BYTE reg, BYTE dat)
{
      MemoryWrite32(SPI_CTL_REG, 0x6); //cs on
      MemoryWrite32(SPI_IRQACK_REG, 0);
      MemoryWrite32(SPI_WRITE_REG, reg+3); //send the register number with DIR bit (b1) set to WRITE and ACKSTAT=1
      while (MemoryRead32(SPI_BUSY_REG));  //loop if data still being sent
      MemoryWrite32(SPI_WRITE_REG, dat);  //send the data
      while (MemoryRead32(SPI_BUSY_REG));  //loop if data still being sent
      MemoryWrite32(SPI_CTL_REG, 0x4); //cs off
      MemoryWrite32(SPI_IRQACK_REG, 0);
}

// Read a register, return its value.
BYTE rreg(BYTE reg)
{
      BYTE dum;
      MemoryWrite32(SPI_CTL_REG, 0x6); //cs on
      MemoryWrite32(SPI_IRQACK_REG, 0);
      MemoryWrite32(SPI_WRITE_REG, reg); //reg number w. dir=0 (IN)
      while (MemoryRead32(SPI_BUSY_REG));  //loop if data still being sent
      MemoryWrite32(SPI_WRITE_REG, 0x00);  //send the not care data to read data from slave SPI
      while (MemoryRead32(SPI_BUSY_REG));  //loop if data still being sent
      dum = MemoryRead32(SPI_READ_REG);  //this has to  be done before the next step, otherwise SPI_READ_REG value changed
      MemoryWrite32(SPI_CTL_REG, 0x4); //cs off
      MemoryWrite32(SPI_IRQACK_REG, 0);
      return dum; 
}

// Read a byte (as rreg), but also set the AckStat bit in the command byte.
BYTE rregAS(BYTE reg)
{
      BYTE dum;
      MemoryWrite32(SPI_CTL_REG, 0x6); //cs on
      MemoryWrite32(SPI_IRQACK_REG, 0);
      MemoryWrite32(SPI_WRITE_REG, reg+1); //reg number w. dir=0 (IN) and ACKSTAT=1
      while (MemoryRead32(SPI_BUSY_REG));  //loop if data still being sent
      MemoryWrite32(SPI_WRITE_REG, 0x00);  //send the not care data to read data from slave SPI
      while (MemoryRead32(SPI_BUSY_REG));  //loop if data still being sent
      dum = MemoryRead32(SPI_READ_REG);  //this has to  be done before the next step, otherwise SPI_READ_REG value changed
      MemoryWrite32(SPI_CTL_REG, 0x4); //cs off
      MemoryWrite32(SPI_IRQACK_REG, 0);
      return dum;
}

void readbytes(BYTE reg, BYTE N, BYTE *p)
{
      BYTE j;
      MemoryWrite32(SPI_CTL_REG, 0x6); //cs on
      MemoryWrite32(SPI_IRQACK_REG, 0);
      MemoryWrite32(SPI_WRITE_REG, reg); //write bit b1=0 to command a read operation
      while (MemoryRead32(SPI_BUSY_REG));  //loop if data still being sent
      for (j = 0; j < N; j++) {
            MemoryWrite32(SPI_WRITE_REG, 0x00);  //send the not care data to read data from slave SPI
            while (MemoryRead32(SPI_BUSY_REG));  //loop if data still being sent
            *p = MemoryRead32(SPI_READ_REG);   //stoare it in the data array
            p++;                                //bump the pointer
      }
      MemoryWrite32(SPI_CTL_REG, 0x4); //cs off
      MemoryWrite32(SPI_IRQACK_REG, 0);
}

void writebytes(BYTE reg, BYTE N, const BYTE *p)
{
      BYTE j, wd;
      MemoryWrite32(SPI_CTL_REG, 0x6); //cs on
      MemoryWrite32(SPI_IRQACK_REG, 0);
      MemoryWrite32(SPI_WRITE_REG, reg+2); //write bit b1=1 to command a write operation
      while (MemoryRead32(SPI_BUSY_REG));  //loop if data still being sent
      for (j = 0; j < N; j++) {
            wd = *p;                           //write the array value
            MemoryWrite32(SPI_WRITE_REG, wd);  //send the data 
            while (MemoryRead32(SPI_BUSY_REG));  //loop if data still being sent
            p++;                         //bump the pointer
      }
      MemoryWrite32(SPI_CTL_REG, 0x4); //cs off
      MemoryWrite32(SPI_IRQACK_REG, 0);
}

 
