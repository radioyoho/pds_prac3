/*
 * FLEX.c
 *
 *  Created on: Mar 17, 2018
 *      Author: kanta
 */

#include "FLEX.h"
#include "MK64F12.h"
#include "NVIC.h"
#include "GPIO.h"

#define ONE_MILI_S 100
#define MOD_4_GRAD 0xa036
#define MOD_4_TIME 0xa3

static uint8 final = 0;
static uint8 current = 0;
static uint8 done = 1;
static float time = 0;
static uint8 time_counter;


void FTM0_IRQHandler()
{
	time_counter++;
	time += 0.001;
	if(time_counter == 1000)
	{
		time = 0;
		time_counter = 0;
	}
	FTM0->SC &= ~FLEX_TIMER_TOF;
}

void FTM1_IRQHandler()
{
	current++;
	time += 0.5f;
	if(current == final)
	{
		done = 1;
		FLEX_off();
	}
	/**Clearing the overflow interrupt flag*/
	FTM1->SC &= ~FLEX_TIMER_TOF;
}


void FLEX_on_0_5()
{
	done = 0;
	current = 0;
	final = 2;
	FTM1->SC |= FLEX_TIMER_CLKS_1;
}

void FLEX_on_1()
{
	done = 0;
	current = 0;
	final = 4;
	FTM1->SC |= FLEX_TIMER_CLKS_1;
}

void FLEX_off()
{
	FTM1->SC &= ~(FTM_SC_CLKS_MASK);
}

void FLEX_init()
{
	SIM->SCGC6 |= SIM_SCGC6_FTM1_MASK|SIM_SCGC6_FTM0_MASK;/**< Clock gating for the FlexTimer 0 and 1*/
	NVIC_setBASEPRI_threshold(PRIORITY_10);
	NVIC_enableInterruptAndPriotity(FTM1_IRQ,PRIORITY_9);/**< Enable interrupt for FTM1*/
	FTM1->MOD = MOD_4_GRAD;/**< Mod value for 10 Hz with PS 128*/
	FTM1->SC = FLEX_TIMER_TOIE|FLEX_TIMER_PS_128;/**< Configures FTM1 with OF interrupts enabled and PS 128 but TURNED OFF*/

	NVIC_enableInterruptAndPriotity(FTM0_IRQ,PRIORITY_8);/**< Enable interrupt for FTM1*/
	FTM0->MOD = MOD_4_TIME;/**< Mod value for 10 Hz with PS 128*/
	FTM0->SC = FLEX_TIMER_CLKS_1|FLEX_TIMER_TOIE|FLEX_TIMER_PS_128;/**< Configures FTM1 with OF interrupts enabled and PS 128 but TURNED OFF*/

	EnableInterrupts;
}

uint8 FLEX_get_done()
{
	return done;
}

float FLEX_get_time()
{
	return time;
}
