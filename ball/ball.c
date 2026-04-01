#include <c64.h>
#include <stdio.h>
#include <conio.h>

#define SPRITE0_DATA ((unsigned char*)0x2000)
#define SPRITE0_X    (*(unsigned char*)0xD000)
#define SPRITE0_Y    (*(unsigned char*)0xD001)
#define SPRITE_EN    (*(unsigned char*)0xD015)
#define SPRITE_PTR0  (*(unsigned char*)0x07F8)
#define SPRITE_COL0  (*(unsigned char*)0xD027)
#define SPRITE_XMSB  (*(unsigned char*)0xD010)

static unsigned char sprite_data[63] = {
    0x00,0x00,0x00,
    0x00,0x3C,0x00,
    0x00,0xFF,0x00,
    0x01,0xFF,0x80,
    0x03,0xFF,0xC0,
    0x07,0xFF,0xE0,
    0x0F,0xFF,0xF0,
    0x1F,0xFF,0xF8,
    0x1F,0xFF,0xF8,
    0x3F,0xFF,0xFC,
    0x3F,0xFF,0xFC,
    0x3F,0xFF,0xFC,
    0x1F,0xFF,0xF8,
    0x1F,0xFF,0xF8,
    0x0F,0xFF,0xF0,
    0x07,0xFF,0xE0,
    0x03,0xFF,0xC0,
    0x01,0xFF,0x80,
    0x00,0xFF,0x00,
    0x00,0x3C,0x00,
    0x00,0x00,0x00
};

static void wait_vsync(void) {
    while (VIC.rasterline == 0xFF) { }
    while (VIC.rasterline != 0xFF) { }
}

void main(void)
{
    unsigned char i;
    int x, y;
    signed char dx, dy;
    unsigned char msb;

    x = 40;
    y = 80;
    dx = 1;
    dy = 1;

    for (i = 0; i < 63; ++i) {
        SPRITE0_DATA[i] = sprite_data[i];
    }

    SPRITE_PTR0 = 0x80;
    SPRITE_COL0 = 1;
    SPRITE_EN = 1;

    while (!kbhit()) {
        wait_vsync();

		if (x <= 24 || x >= 320) dx = -dx;
		if (y <= 50 || y >= 230) dy = -dy;

        x += dx;
        y += dy;

        msb = 0;
        if (x > 255) {
            msb |= 1;
        }

        SPRITE0_X = (unsigned char)x;
        SPRITE0_Y = (unsigned char)y;
        SPRITE_XMSB = msb;
    }

    SPRITE_EN = 0;
}
