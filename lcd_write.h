#ifndef LCDWRITE_H
#define LCDWRITE_H

#include <stdbool.h>
#include <stdint.h>

#include "types.h"

#include "LCD_ILI9325.h"

typedef struct Vec2 {
	uint32_t x;
	uint32_t y;
} Vec2;

void clear(uint16_t color);

void draw_chart(complex* buffer, uint32_t nr_samples);

void lcd_draw_rectangle(Vec2 pos, uint32_t height_in_px, uint32_t width_in_px, uint16_t color);

void lcd_draw_line(Vec2 pos, uint32_t height_in_px, uint16_t color);

void lcd_write_char(unsigned char c, Vec2 pos, uint16_t color,bool override);

void lcd_write_string(const char* string, Vec2 pos, uint16_t color, bool override);

#endif
