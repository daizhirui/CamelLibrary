//########################################################//
//  Title:Sub-function for AFE	      //	 
//  AUTHER:lilb                                           //
//  PROJECT:m2                                            //
//########################################################//


#include "AFE.h"
#include "TC0.h"
#include "mcu.h"
#include "CORE.h"


int RT_ADC_Read()
{ 
	int ready;
	MemoryWrite32(AD_CLR_REG, 0); //clear ADC to prepare reading
	RT_Delay_ms(1); //add delay for acc_en up
	MemoryWrite32(AD_READ_REG, 0); //kick off the ADC read process
	ready = MemoryRead32(AD_CTL0_REG);
	while (!(ready & 0x80000000)) //check if rdy bit is ok
		ready = MemoryRead32(AD_CTL0_REG);
	return MemoryRead32(AD_READ_REG)&0xffff; //read the low 16bit data
}

int RT_V2P_Read()
{
	int count = 0;
	int number = 16; //16 times to average
	int valid = 0;
	int i = 0;
	for ( i = 0; i < number; i++) {
		int tmp;
		RT_T0_Clr();
		while (!RT_T0_Flag());
		tmp = RT_T0_ReadCnt();
		if (tmp > 1000) {
			valid++;
			count += tmp;
		}
	}
	if (valid > 0)
		return count/valid;	
	else
		return 0;
}
