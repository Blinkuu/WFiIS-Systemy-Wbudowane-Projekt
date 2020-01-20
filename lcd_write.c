#include "lcd_write.h"

#include "dft.h"
#include "Open1768_LCD.h"
#include "LCD_ILI9325.h"
#include "asciiLib.h"
#include "tp_lib/TP_Open1768.h"
#include "LPC17xx.h"

void clear(uint16_t color) {
	for(uint32_t i = 0; i < 320; i++)
		for(uint32_t j = 0; j < 240; j++) {
			lcdWriteReg(DATA_RAM, color);
		}
}

void draw_chart(complex* buffer, uint32_t nr_samples) {
	clear(LCDWhite);
	for(uint32_t i = 0; i < nr_samples / 2; i++) {
		double mod =  sqrt(buffer[i].Re * buffer[i].Re + buffer[i].Im * buffer[i].Im);
		lcd_draw_rectangle((Vec2){0,  32 + 2 * i}, mod / 100, 2, LCDBlack);
	}
}

void lcd_draw_rectangle(Vec2 pos, uint32_t height_in_px, uint32_t width_in_px, uint16_t color) {
	for(uint32_t i = 0; i < width_in_px; i++)
		lcd_draw_line((Vec2){pos.x, pos.y + i}, height_in_px, color);
}

void lcd_draw_line(Vec2 pos, uint32_t height_in_px, uint16_t color) {
	if(pos.x + height_in_px > 240) {
		pos.x = 0;
		height_in_px = 240;
	}
	lcdSetCursor(pos.x, pos.y);
	
	for(uint32_t i = 0; i < height_in_px; i++) {
		lcdWriteReg(DATA_RAM, color);
	}
}

void lcd_write_char(unsigned char c, Vec2 pos, uint16_t color,bool override) {
	lcdSetCursor(pos.x, pos.y);
	
	unsigned char buff[16] = {};
	GetASCIICode(0, buff, c);
	
	for(uint32_t i = 0; i < 16; ++i) {
		Vec2 curr_pos = {lcdReadReg(ADRX_RAM), lcdReadReg(ADRY_RAM)};
		for(uint8_t j = 0; j < 8; ++j) {
			uint32_t is_one = buff[i] & (1 << (7 - j));
			if(is_one) {
				lcdWriteReg(DATA_RAM, color);
			} else {
				override ? lcdWriteReg(DATA_RAM, LCDWhite) : lcdSetCursor(curr_pos.x + j + 1,curr_pos.y);
				}
			}
		lcdSetCursor(curr_pos.x, curr_pos.y + 1);
		
		}
	}

void lcd_write_string(const char* string, Vec2 pos, uint16_t color, bool override){
	
	for(int i = 0; string[i]!='\0'; i++){
		Vec2 local_pos = {pos.x+i*8,pos.y};
		lcd_write_char(string[i], local_pos, color,override);
	}
}
