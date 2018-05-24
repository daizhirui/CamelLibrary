/*--------------------------------------------------------------------
 * TITLE: ADC block define
 * AUTHOR: Bill
 * DATE CREATED: 2015-11-4
 * FILENAME: AFE.h
 * PROJECT: m2
 * COPYRIGHT: Camel Microelectronics, Inc.
 * DESCRIPTION:
 *    driver for the OPO and ADC module
 *--------------------------------------------------------------------*/
#ifndef __AFE_H__
#define __AFE_H__

// this is ADC/analog
#define AD_CTL0_REG       0x1f800600  // SD and V2P control (16-bit)
#define AD_CLR_REG        0x1f800603  // SD ADC clear reg
#define AD_OPO_REG        0x1f800601  // OPO and Chan control (16-bit)
#define AD_READ_REG       0x1f800602  // SD df read (16-bit)


/***** OPO and ADC setup******/
void RT_OPO_SetEn(int en); //chose to use OPO or not
void RT_OPO_SetCh(int ch0, int ch1, int ch2, int ch3); //select the channels to be used, 1 for use, 0 for not use
void RT_OPO_SetAmp(int pres, int nres, int pamp, int namp); //select the amplify resistor and amplification factor for both p side and n side
void RT_OPO_SetAmpMode(int mode); //select amp mode to be single side amp or both side amp, 0 for both side (normal use), 1 for single side
void RT_OPO_SetInMode(int mode); //1 for inn and inp switch, 0 for not (normal use)
void RT_OPO_SetShort(int mode); //1 for short inn and inp
void RT_OPO_SetFilter(int res); //select the filter resistor, 1 for 50k and 0 for 100k
void RT_ADC_SetMode(int mode); //choose the ADC, 1 for on, 0 for off
void RT_V2P_SetMode(int mode); //choose v2p, 1 for on, 0 for off
void RT_ADC_SetSampleRate(int mode); //set the measurement sampling rate, mode = 0, 1, 2, 3, --> 3M, 1.5M, 780K, 390K
void RT_ADC_SetFilterCLK(int freq); //set the digital filter clock freq, 0 for 1KHz, 1 for 512Hz
void RT_V2P_SetV2PRes(int res); //set the resistor for v2p, 0 -> 220k, 1 -> 256k, 2 -> 291k, 3 -> 185k
/***** End of OPO and ADC setup *****/
int RT_ADC_Read();
int RT_V2P_Read();

#endif
