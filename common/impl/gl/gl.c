#include <lib/gl/gl.h>


// TODO: fix lines that go from (-, +) <-> (+, -) ie 250, 700, 600, 340
void gl_drawLine(uintn x1, uintn y1, uintn x2, uintn y2, uint32 pixel)
{
    int distx = x1 - x2;
    int disty = y1 - y2;

    int size = isqrt(distx * distx + disty * disty);
    float xrat = abs(distx) / (float)size;
    float yrat = abs(disty) / (float)size;

    int xoff = x1 < x2 ? x1 : x2;
    int yoff = y1 < y2 ? y1 : y2;

    for(int i = 0; i < size; i++)
        gl_drawPixel(i * xrat + xoff, i * yrat + yoff, pixel);
}

void gl_drawRect(uintn x1, uintn y1, uintn x2, uintn y2, uint32 pixel, const draw_mode mode)
{
    switch (mode)
    {
    case FILL:
        for(int i = y1; i < y2; i++)
            gl_drawLinear(x1 + i * GLMODE->pitch, x2 - x1, pixel);
        return;

    case OUTLINE1:
        gl_drawLinear(x1 + y1 * GLMODE->pitch, x2 - x1, pixel);
        gl_drawLinear(x1 + (y2 - 1) * GLMODE->pitch, x2 - x1, pixel);
        for(int i = y1; i < y2; i++)
        {
            gl_drawPixel(x1, i, pixel);
            gl_drawPixel(x2 - 1, i, pixel);
        }
        return;  
    }
}

void gl_drawSquare(uintn x, uintn y, uintn size, uint32 pixel, const draw_mode mode)
{
    switch (mode)
    {
    case FILL:
        for(int i = y; i < y + size; i++)
            gl_drawLinear(x + i * GLMODE->pitch, size, pixel);
        return;

    case OUTLINE1:
        gl_drawLinear(x + y * GLMODE->pitch, size, pixel);
        gl_drawLinear(x + (y + size - 1) * GLMODE->pitch, size, pixel);
        for(int i = y; i < y + size; i++)
        {
            gl_drawPixel(x, i, pixel);
            gl_drawPixel(x + size - 1, i, pixel);
        }
        return;  
    }
}

void gl_drawMap(uintn x, uintn y, uintn sizex, uintn sizey, const uint32* map)
{
    for(int i = 0; i < sizey; i++)
        for(int j = 0; j < sizex; j++)
            gl_drawPixel(x + j, y + i, map[i * sizex + j]);
}

void gl_drawMask(uintn x, uintn y, uintn sizex, uintn sizey, uint32 pixel, const byte* mask)
{
    for(int i = 0; i < sizey; i++)
        for(int j = 0; j < sizex; j++)
            for(int k = 0; k < 8; k++)
                mask[i * sizex + j] & (0b10000000 >> k) ? gl_drawPixel((x + j * 8) + k, y + i, pixel) : gl_drawPixel((x + j * 8) + k, y + i, 0);
}

// B B G G
// B G G B
// G G B B
// G B B G