#include <lib/gl/gl.h>

void gl_draw_line(uintn x1, uintn y1, uintn x2, uintn y2, uint32 pixel)
{
    int distx = x1 - x2;
    int disty = y1 - y2;

    int size = sqrt(p2(distx) + p2(disty));
    float xrat = abs(distx) / (float)size;
    float yrat = abs(disty) / (float)size;

    for(int i = 0; i < size; i++)
        gl_draw_pixel(i * xrat, i * yrat, pixel);
}

void gl_draw_rect(uintn x1, uintn y1, uintn x2, uintn y2, uint32 pixel, const draw_mode mode)
{
    switch (mode)
    {
    case FILL:
        for(int i = y1; i < y2; i++)
            gl_draw_linear(x1 + i * GLMODE->pitch, x2 - x1, pixel);
        return;

    case OUTLINE1:
        gl_draw_linear(x1 + y1 * GLMODE->pitch, x2 - x1, pixel);
        gl_draw_linear(x1 + (y2 - 1) * GLMODE->pitch, x2 - x1, pixel);
        for(int i = y1; i < y2; i++)
        {
            gl_draw_pixel(x1, i, pixel);
            gl_draw_pixel(x2 - 1, i, pixel);
        }
        return;  
    }
}

void gl_draw_square(uintn x, uintn y, uintn size, uint32 pixel, const draw_mode mode)
{
    switch (mode)
    {
    case FILL:
        for(int i = y; i < y + size; i++)
            gl_draw_linear(x + i * GLMODE->pitch, size, pixel);
        return;

    case OUTLINE1:
        gl_draw_linear(x + y * GLMODE->pitch, size, pixel);
        gl_draw_linear(x + (y + size - 1) * GLMODE->pitch, size, pixel);
        for(int i = y; i < y + size; i++)
        {
            gl_draw_pixel(x, i, pixel);
            gl_draw_pixel(x + size - 1, i, pixel);
        }
        return;  
    }
}

void gl_draw_img(uintn x, uintn y, uintn sizex, uintn sizey, const uint32* map)
{
    for(int i = 0; i < sizey; i++)
        for(int j = 0; j < sizex; j++)
            gl_draw_pixel(x + j, y + i, map[i * sizex + j]);
}

void gl_draw_mask(uintn x, uintn y, uintn sizex, uintn sizey, uint32 pixel, const byte* mask)
{
    for(int i = 0; i < sizey; i++)
        for(int j = 0; j < sizex; j++)
            for(int k = 0; k < 8; k++)
                mask[i * sizex + j] & (0b10000000 >> k) ? gl_draw_pixel((x + j * 8) + k, y + i, pixel) : gl_draw_pixel((x + j * 8) + k, y + i, 0);
}