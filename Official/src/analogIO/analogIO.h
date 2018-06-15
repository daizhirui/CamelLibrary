/*--------------------------------------------------------------------
 * TITLE: M2 Hardware Definition
 * AUTHOR: Astro
 * DATE CREATED: 2017/11/2
 * FILENAME: AFE.h
 * PROJECT: M2Library
 * COPYRIGHT: Camel Microelectronics, Ltd.
 * DESCRIPTION:
 * 		Analog Module Library
 * 		2017/11/3	updated from V2017.07.15
 *--------------------------------------------------------------------*/

#ifndef __M2_ANALOG_h__
#define __M2_ANALOG_h__

#include <stdint.h>
#include "mcu.h"

/*********** Value Definition ************/
// This part aims to make coding easier.

/**
 * @brief P-Side Keyword for OPO Module
 */
#define OPO_PSIDE 0x0
/**
 * @brief N-Side Keyword for OPO Module
 */
#define OPO_NSIDE 0x1
/**
 * @brief Pin resistor 1K of OPO Channel
 */
#define OPO_PIN_RESISTOR_1K  0x1
/**
 * @brief Pin resistor 10K of OPO Channel
 */
#define OPO_PIN_RESISTOR_10K  0x0
/**
 * @brief Bypass enable Keyword of OPO Channel
 */
#define OPO_BYPASS_ON   0x1
/**
 * @brief Bypass disable Keyword of OPO Channel
 */
#define OPO_BYPASS_OFF  0x0
/**
 * @brief VCOM
 */
#define VCOM 0x1
/**
 * @brief Ground Pin Keyword
 */
#define GND 0x0
/**
 * @brief P-Side Of Channel 0 Keyword for OPO Module
 */
#define OPO_A0P 0x1
/**
 * @brief P-Side Of Channel 1 Keyword for OPO Module
 */
#define OPO_A1P 0x2
/**
 * @brief P-Side Of Channel 2 Keyword for OPO Module
 */
#define OPO_A2P 0x4
/**
 * @brief P-Side Of Channel 3 Keyword for OPO Module
 */
#define OPO_A3P 0x8
/**
 * @brief N-Side Of Channel 0 Keyword for OPO Module
 */
#define OPO_A0N 0x1
/**
 * @brief N-Side Of Channel 1 Keyword for OPO Module
 */
#define OPO_A1N 0x2
/**
 * @brief N-Side Of Channel 2 Keyword for OPO Module
 */
#define OPO_A2N 0x4
/**
 * @brief N-Side Of Channel 3 Keyword for OPO Module
 */
#define OPO_A3N 0x8
/**
 * @brief Pin gain level 480K for OPO Module
 */
#define OPO_GAIN_480K   0x1
/**
 * @brief Pin gain level 400K for OPO Module
 */
#define OPO_GAIN_400K   0x0
/**
 * @brief Pin gain level 320K for OPO Module
 */
#define OPO_GAIN_320K   0x2
/**
 * @brief Pin gain level 240K for OPO Module
 */
#define OPO_GAIN_240K   0x4
/**
 * @brief Pin gain level 100K for OPO Module
 */
#define OPO_GAIN_100K   0x6
/**
 * @brief Pin gain level 80K for OPO Module
 */
#define OPO_GAIN_80K    0x3
/**
 * @brief Pin gain level 40K for OPO Module
 */
#define OPO_GAIN_40K    0x5
/**
 * @brief Pin gain level 20K for OPO Module
 */
#define OPO_GAIN_20K    0x7
/**
 * @brief Clock Divider Frequency 3M Hz of Sigma Delta Module
 */
#define SD_CLK_3M 0x0
/**
 * @brief Clock Divider Frequency 1.5M Hz of Sigma Delta Module
 */
#define SD_CLK_1_5M 0x1
/**
 * @brief Clock Divider Frequency 781K Hz of Sigma Delta Module
 */
#define SD_CLK_781K 0x2
/**
 * @brief Clock Divider Frequency 390K Hz of Sigma Delta Module
 */
#define SD_CLK_390K 0x3
/**
 * @brief Result Length 14-bit of Sigma Delta Module
 */
#define SD_14BIT 0x0
/**
 * @brief Result Length 16-bit of Sigma Delta Module
 */
#define SD_16BIT 0x1
/**
 * @brief Result Length 18-bit of Sigma Delta Module
 */
#define SD_18BIT 0x2
/**
 * @brief Result Length 20-bit of Sigma Delta Module
 */
#define SD_20BIT 0x3
/**
 * @brief Sampling Trigger By TC0 PWM Keyword of Sigma Delta Module
 */
#define SD_TRIG_BY_TC0PWM   0x1
/**
 * @brief Sampling Trigger By wt<2> of SD_READ_REG Keyword of Sigma Delta Module
 */
#define SD_TRIG_BY_WT2READ  0x0
/**
 * @brief Resistor 220K Keyword of Voltage-To-PulseWidth Module
 */
#define V2P_220K 0x0
/**
 * @brief Resistor 256K Keyword of Voltage-To-PulseWidth Module
 */
#define V2P_256K 0x1
/**
 * @brief Resistor 291K Keyword of Voltage-To-PulseWidth Module
 */
#define V2P_291K 0x2
/**
 * @brief Resistor 185K Keyword of Voltage-To-PulseWidth Module
 */
#define V2P_185K 0x3
/**
 * @brief Clear the state of Analog Digit Converter.
 * @return      void
 */
#define RT_ADC_Clear() MemoryWrite32(AD_CLR_REG, 1)
/************* OPO setup **************/
/**
 * @brief Turn the Amplifier on.
 * @return      void
 */
#define RT_OPO_On() MemoryOr32(AD_OPO_REG, 0x1)
/**
 * @brief Turn the Amplifier off.
 * @return      void
 */
#define RT_OPO_Off() MemoryAnd32(AD_OPO_REG, ~1)
/**
 * @brief Set the state of every amplifier channel.
 * @param ch0       channel 0, ON or OFF
 * @param ch1       channel 1, ON or OFF
 * @param ch2       channel 2, ON or OFF
 * @param ch3       channel 3, ON or OFF
 * @return          void
 */
#define RT_OPO_SetChannel(ch0, ch1, ch2, ch3)                                        \
    {                                                                                \
        MemoryAnd32(AD_OPO_REG, ~(0xf << 4));                                        \
        MemoryOr32(AD_OPO_REG, ((ch0 << 4) + (ch1 << 5) + (ch2 << 6) + (ch3 << 7))); \
    }
/**
 * @brief This function sets the amplification of opo.
 * @param Presistor     Pin resistor, OPO_PIN_RESISTOR_1K or OPO_PIN_RESISTOR_10K
 * @param Pgain         Pside amplification
 * @param Nresistor     Nin resistor, OPO_PIN_RESISTOR_1K or OPO_PIN_RESISTOR_10K
 * @param Ngain         Nside amplification
 * @return              void
 */
#define RT_OPO_SetAmplification(Pin, Pgain, Nin, Ngain)                                  \
    {                                                                                    \
        MemoryAnd32(AD_OPO_REG, ~(0xff << 8));                                           \
        MemoryOr32(AD_OPO_REG, (((Pin << 7) + (Pgain << 4) + (Nin << 3) + Ngain) << 8)); \
    }
/**
 * @brief This function sets the feedback mode of OPO
 * select amp feedback to be single side  or both side
 * 0 for both side (normal use), 1 for single side (only n side has feedback)
 * when mode = 1, vcom(1.5V) is connected to the resistor block at inp
 * when mode = 0, vcom is disconnected to the resistor block at inp
 * @param mode      Pside feedback switch, ON or OFF
 * @return          void
 */
#define RT_OPO_SetPsideFeedback(mode)           \
    {                                           \
        if (mode)                               \
            MemoryOr32(AD_OPO_REG, (1 << 3));   \
        else                                    \
            MemoryAnd32(AD_OPO_REG, ~(1 << 3)); \
    }
/**
 * @brief This function sets whether to exchange Pside and Nside
 * 1 for inn and inp switch, 0 for not (normal use)
 * @param mode      exchange switch, ON or OFF
 * @return          void
 */
#define RT_OPO_SetPNExchange(mode)              \
    {                                           \
        if (mode)                               \
            MemoryOr32(AD_OPO_REG, (1 << 2));   \
        else                                    \
            MemoryAnd32(AD_OPO_REG, ~(1 << 2)); \
    }
/**
 * @brief This function sets whether to connecte pin and nin to vcom
 * Channel 0-3 should be closed
 * @param mode      short switch, ON or OFF
 * @return          void
 */
#define RT_OPO_SetShort(mode)                     \
    {                                             \
        if (mode)                                 \
        {                                         \
            MemoryAnd32(AD_OPO_REG, ~(0xf << 4)); \
            MemoryOr32(AD_OPO_REG, (1 << 1));     \
        }                                         \
        else                                      \
            MemoryAnd32(AD_OPO_REG, ~(1 << 1));   \
    }
/**
 * @brief This function sets the bypass of opo.
 * If opo is bypassed, input will be fed into SD directly.
 * (select the filter resistor, 1 for 50k and 0 for 100k)
 * @param mode      bypass switch, ON or OFF
 * @return          void
 */
#define RT_OPO_SetBypass(mode)                    \
    {                                             \
        if (mode)                                 \
            MemoryOr32(AD_CTL0_REG, (1 << 15));   \
        else                                      \
            MemoryAnd32(AD_CTL0_REG, ~(1 << 15)); \
    }
/**
 * @brief This function sets the gnd of Pside
 * op=1, PsideGND = vcom; op=0, PsideGND = 0
 * @param op    the option of gnd, VCOM or GND
 * @return      void
 */
#define RT_OPO_SetPsideGND(op)               \
    {                                        \
        MemoryAnd32(AD_CTL0_REG, ~(1 << 7)); \
        MemoryOr32(AD_CTL0_REG, op << 7);    \
    }
/**
 * @brief This function sets OPO at SingleSide Mode
 *
 * @param PorN      the switch to exchange Pside and Nside, ON or OFF
 * @param channel   the channel to select
 * @return          void
 */
#define RT_OPO_SetSingleSideMode(PorN, channel) \
    {                                           \
        RT_ADC_V2P_SetRes(V2P_185K);            \
        RT_ADC_TemperatureSensorOff();          \
        RT_OPO_SetPNExchange(PorN);             \
        MemoryAnd32(AD_OPO_REG, ~(0xf << 4));   \
        MemoryOr32(AD_OPO_REG, channel);        \
    }
/**
 * @brief This function sets OPO at Differential Mode
 *
 * @param PorN      the switch to exchange Pside and Nside, ON or OFF
 * @param channel   the channel to select
 * @return          void
 */
#define RT_OPO_SetDifferentialMode(PorN, channel) \
    {                                             \
        RT_ADC_V2P_SetRes(0);                     \
        RT_OPO_SetPNExchange(PorN);               \
        MemoryAnd32(AD_OPO_REG, ~(0xf << 4));     \
        MemoryOr32(AD_OPO_REG, channel);          \
    }

/************* SD Setup **************/
// set ADC_SD on
#define RT_ADC_SD_On() MemoryOr32(AD_CTL0_REG, 1)
// set ADC_SD off
#define RT_ADC_SD_Off() MemoryAnd32(AD_CTL0_REG, ~1)
/**
 * @brief This function sets the samplerate of RT_ADC_SD
 *
 * @param mode      SD_CLK_3M, SD_CLK_1_5M, SD_CLK_781K or SD_CLK_390K
 * @return          void
 */
#define RT_ADC_SD_SetSampleRate(mode)          \
    {                                          \
        MemoryAnd32(AD_CTL0_REG, ~(0x3 << 3)); \
        MemoryOr32(AD_CTL0_REG, (mode << 3));  \
    }
// set the digital filter clock freq with ad bits (defined at the beginning)
/**
 * @brief This function sets the number of ad
 * @note  This function sets the filter frequency to adjust the ad width.
 *          1K Hz is for 14bit, 512Hz for 16bit, 256Hz for 18bit, 128Hz for 20bit.
 *          These frequency is relative to the sd clock frequency.
 * @param mode      SD_14BIT, SD_16BIT, SD_18BIT or SD_20BIT
 * @return          void
 */
#define RT_ADC_SD_SetAdWidth(mode)      \
    {                                   \
        MemoryAnd32(AD_CTL0_REG, ~(0x3 << 1)); \
        MemoryOr32(AD_CTL0_REG, (mode << 1));  \
    }
/**
 * @brief This function sets the trigger source of RT_ADC_SD
 * @param source    SD_TRIG_BY_WT2READ or SD_TRIG_BY_TC0PWM
 * @return          void
 */
#define RT_ADC_SD_SetTrigger(source)         \
    {                                        \
        MemoryAnd32(AD_CTL0_REG, ~(1 << 6)); \
        MemoryOr32(AD_CTL0_REG, source << 6);\
    }
/**
 * @brief This function sets RT_ADC_SD briefly.
 *
 * @param sampleRate    the sample rate of SD
 * @param adWidth       the precision of the result
 * @param triggerSource the source to trigger sampling.
 * @return              void
 */
#define RT_ADC_SD_Setup(sampleRate, adWidth, triggerSource)  \
    {                                        \
        RT_ADC_SD_SetSampleRate(sampleRate); \
        RT_ADC_SD_SetAdWidth(adWidth);      \
        RT_ADC_SD_SetTrigger(triggerSource); \
    }
/**
 * @brief Start SD accumulate
 * @note  When writing to AD_READ_REG, it will start df conversion,
 *        if SD is enabled and choose trig pwm. SD flag or irq will
 *        be asserted upon conversion completed.
 * @return void
 */
#define RT_ADC_SD_Start()              \
    {                                  \
        RT_ADC_SD_On();                \
        RT_ADC_Clear();                \
        MemoryWrite32(AD_READ_REG, 1); \
    }
/**
 * @brief Check is the accumulation of SD is completed.
 * @return The result if the accumulation is completed, 1=completed, 0=not completed
 */
#define RT_ADC_SD_DataReady()   ((MemoryRead32(AD_CTL0_REG) & 0x80000000) >> 31)

/************* V2P Setup **************/
// set ADC_V2P on
#define RT_ADC_V2P_On() MemoryOr32(AD_CTL0_REG, (1 << 8))
// set ADC_V2P off
#define RT_ADC_V2P_Off() MemoryAnd32(AD_CTL0_REG, ~(1 << 8))
/**
 * @brief This function sets the resistor of V2P
 * when res = 3, single input mode is enabled, vcom will be fed into the P-side of OPO
 * @param res   V2P_185K, V2P_220K, V2P_256K, or V2P_291K
 * @return #define
 */
#define RT_ADC_V2P_SetRes(res)                 \
    {                                          \
        MemoryAnd32(AD_CTL0_REG, ~(0x3 << 9)); \
        MemoryOr32(AD_CTL0_REG, (res << 9));   \
    }
// set ADC temperature sensor on
#define RT_ADC_TemperatureSensorOn() MemoryOr32(AD_CTL0_REG, 1 << 5)
// set ADC temperature sensor off
#define RT_ADC_TemperatureSensorOff() MemoryAnd32(AD_CTL0_REG, ~(1 << 5))

/**
 * @brief This function returns ADC_SD Value
 * @return uint32_t  ADC_SD Value
 */
uint32_t RT_ADC_SD_Read();
/**
 * @brief This function returns ADC_V2P Value
 *
 * @return int  ADC_V2P Value
 */
uint32_t RT_ADC_V2P_Read();
#endif // End of __AFE_h__
