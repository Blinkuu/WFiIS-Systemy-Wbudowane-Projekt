#ifndef HANDLERS_H
#define HANDLERS_H

#include <stdio.h>

#include "types.h"
#include "lcd_write.h"
#include "lcd_paint.h"

#include "LPC17xx.h"

static complex* buf;
static complex* scratch;
static volatile uint32_t curr_nr_samples = 0;

void ADC_IRQnHandler(void) {
		uint16_t adc_result = (LPC_ADC->ADGDR >> SBIT_RESULT) & 0xfff;
		char lcd_result_string[15];
		sprintf(lcd_result_string, "%d", adc_result);
		lcd_write_string(lcd_result_string, (Vec2){10, 10}, LCDBlack, true);
}

void TIMER0_IRQHandler(void) {
		LPC_ADC->ADCR  |= SBIT_AD1;
    LPC_ADC->ADCR |= (1 << SBIT_START);
       
		while((LPC_ADC->ADGDR & (1 << 31)) != 0);
		
    uint16_t adc_result = (LPC_ADC->ADGDR >> SBIT_RESULT) & 0xfff;

		buf[curr_nr_samples].Re = adc_result;
		buf[curr_nr_samples].Im = 0.0;

		curr_nr_samples++;
		
		LPC_TIM0->IR = 1;
}

void disable_timer(void)
{
	LPC_TIM0->TCR = 0;
}

void enable_timer(void)
{
	LPC_TIM0->TCR = 1;
}

#endif
