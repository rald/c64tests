#include <c64.h>

#define SPRITE0_X   (*(unsigned char*)0xD000)
#define SPRITE0_Y   (*(unsigned char*)0xD001)
#define SPRITE_EN   (*(unsigned char*)0xD015)
#define SPRITE_PTR0 (*(unsigned char*)0x07F8)
#define SPRITE_COL0 (*(unsigned char*)0xD027)
#define SPRITE_XMSB (*(unsigned char*)0xD010)

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
    unsigned char x;
    unsigned char y;
    signed char dx;
    signed char dy;
    unsigned char msb;

    x = 40;
    y = 80;
    dx = 1;
    dy = 1;
    msb = 0;

    for (i = 0; i < 63; ++i) {
        ((unsigned char*)0x2000)[i] = sprite_data[i];
    }

    SPRITE_PTR0 = 0x80;
    SPRITE_COL0 = 1;
    SPRITE_EN = 1;

    while (1) {
        int nx;
        int ny;

		wait_vsync();

        nx = (int)x + dx;
        ny = (int)y + dy;

        if (nx <= 24 || nx >= 238) {
            dx = -dx;
            nx = (int)x + dx;
        }

        if (ny <= 50 || ny >= 230) {
            dy = -dy;
            ny = (int)y + dy;
        }

        x = (unsigned char)nx;
        y = (unsigned char)ny;

        if (nx > 255) msb |= 1;
        else msb &= (unsigned char)~1;

        SPRITE0_X = x;
        SPRITE0_Y = y;
        SPRITE_XMSB = msb;
    }
}