/*
 * FLEX.h
 *
 *  Created on: Mar 17, 2018
 *      Author: kanta
 */

#ifndef FLEX_H_
#define FLEX_H_

#include "MK64F12.h"
#include "DataTypeDefinitions.h"


#define FLEX_TIMER_0_CLOCK_GATING 0x01000000

#define FLEX_TIMER_FAULTIE  0x80
#define FLEX_TIMER_FAULTM_0   0x00
#define FLEX_TIMER_FAULTM_1   0x20
#define FLEX_TIMER_FAULTM_2   0x40
#define FLEX_TIMER_FAULTM_3   0x60
#define FLEX_TIMER_CAPTEST  0x10
#define FLEX_TIMER_PWMSYNC  0x08
#define FLEX_TIMER_WPDIS    0x04
#define FLEX_TIMER_INIT     0x02
#define FLEX_TIMER_FTMEN    0x01

#define FLEX_TIMER_TOF     0x80
#define FLEX_TIMER_TOIE    0x40
#define FLEX_TIMER_CPWMS   0x20
#define FLEX_TIMER_CLKS_0  0x00
#define FLEX_TIMER_CLKS_1  0x08
#define FLEX_TIMER_CLKS_2  0x10
#define FLEX_TIMER_CLKS_3  0x18
#define FLEX_TIMER_PS_1    0x00
#define FLEX_TIMER_PS_2    0x01
#define FLEX_TIMER_PS_4    0x02
#define FLEX_TIMER_PS_8    0x03
#define FLEX_TIMER_PS_16    0x04
#define FLEX_TIMER_PS_32    0x05
#define FLEX_TIMER_PS_64    0x06
#define FLEX_TIMER_PS_128    0x07

#define FLEX_TIMER_PWMLOAD_CH0 0x01
#define FLEX_TIMER_PWMLOAD_CH1 0x02
#define FLEX_TIMER_PWMLOAD_CH2 0x04
#define FLEX_TIMER_PWMLOAD_CH3 0x08
#define FLEX_TIMER_PWMLOAD_CH4 0x10
#define FLEX_TIMER_PWMLOAD_CH5 0x20
#define FLEX_TIMER_PWMLOAD_CH6 0x40
#define FLEX_TIMER_PWMLOAD_CH7 0x80
#define FLEX_TIMER_LDOK        0x200


#define  FLEX_TIMER_DMA   0x01
#define  FLEX_TIMER_ELSA  0x04
#define  FLEX_TIMER_ELSB  0x08
#define  FLEX_TIMER_MSA   0x10
#define  FLEX_TIMER_MSB   0x20
#define  FLEX_TIMER_CHIE  0x40
#define  FLEX_TIMER_CHF   0x80

/**
 * 	\brief Changes a the value of the final value that the motor will take and starts
 * 	a flex timer to gradually change the speed 5% every 0.1 seconds.
 *
 * 	\param[in] final_value The final speed value of the motor.
 */

void FLEX_changeCH(uint8 final_value);

/**
 * 	\brief Updates the speed of the motor to a value from 5 to 100.
 *
 * 	\param[in] decre a value from 5 to 100 that represents the speed percentage of the motor.
 */

void FLEX_updateCHValue(uint8 decre);

/**
 * 	\brief Necessary configurations for PWM timer.
 *
 * 	Initializes FTM0 for PWM and FTM1 for output compare to gradually change motor every 0.1 seconds.
 */

void FLEX_init();

void init_pwm();

void init_grad();

void init_cap();

void init_MCG();

uint32 FLEX_get_cap_frec();

#endif /* FLEX_H_ */
