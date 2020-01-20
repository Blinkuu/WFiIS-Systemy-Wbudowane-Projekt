#ifndef INIT_H
#define INIT_H

#include "types.h"
#include "LPC17xx.h"
#include "lcd_write.h"
#include "Open1768_LCD.h"

#include <stdio.h>

void init_lcd(void);

void init_adc(void);

void init_timer(void);

void init(void);

bool ready_to_flush(void);

#endif
