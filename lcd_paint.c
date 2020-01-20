#include "lcd_paint.h"

#include "Open1768_LCD.h"
#include "LCD_ILI9325.h"

void lcd_clear(uint16_t color) {
	for(uint32_t y = 0; y < 320; y++) {
		for(uint32_t x = 0; x < 240; x++){
			lcdWriteReg(DATA_RAM, color);
		}			
	}
}
