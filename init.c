#include "init.h"

void init_lcd() {
	lcdConfiguration();
	LPC_GPIO0->FIODIR0 = 0xFF;
	
	register int state = lcdReadReg(OSCIL_ON);
	
	if(state == 0x8989) {
		LPC_GPIO0->FIOPIN0 = 0x01;
	} else if (state == 0x9325) {
		LPC_GPIO0->FIOPIN0 = 0x02;
	} else {
		LPC_GPIO0->FIOPIN0 = 0x03;
	}
		
	init_ILI9325();
}

void init_adc() {
	LPC_SC->PCONP |= (1 << 12);      /* Enable CLOCK for internal ADC controller */
	LPC_ADC->ADCR = ((1<<SBIT_PDN) | (10<<SBIT_CLCKDIV) | (8 << SBIT_START));  //Set the clock and Power ON ADC module
	LPC_PINCON->PINSEL1 |= (1<<16);      	/* Select the P0_23 AD0[0] for ADC function */
	LPC_ADC->ADINTEN = 1; // Generate interrupt when conversion is done
	NVIC_EnableIRQ(ADC_IRQn);
}

void init_timer() {
	LPC_TIM0->MCR = 3;
	
	LPC_TIM0->MR0 = 25e6/32000;
	LPC_TIM0->TCR = 1;
	NVIC_EnableIRQ(TIMER0_IRQn);
}

void init() {
	init_lcd();
	init_adc();
	init_timer();
}
