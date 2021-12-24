#include <lib/gl/gl.h>


void gl_draw_line(uintn x1, uintn y1, uintn x2, uintn y2, uint32 pixel)
{
    
}

void gl_draw_rect(uintn x1, uintn y1, uintn x2, uintn y2, uint32 pixel, const draw_mode mode)
{
    switch (mode)
    {
    case FILL:
        for(int i = y1; i < y2; i++)
            gl_draw_linear(x1 + i * CURGLMODE->pitch, x2 - x1, pixel);
        return;

    case OUTLINE1:
        gl_draw_linear(x1 + y1 * CURGLMODE->pitch, x2 - x1, pixel);
        gl_draw_linear(x1 + (y2 - 1) * CURGLMODE->pitch, x2 - x1, pixel);
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
            gl_draw_linear(x + i * CURGLMODE->pitch, size, pixel);
        return;

    case OUTLINE1:
        gl_draw_linear(x + y * CURGLMODE->pitch, size, pixel);
        gl_draw_linear(x + (y + size - 1) * CURGLMODE->pitch, size, pixel);
        for(int i = y; i < y + size; i++)
        {
            gl_draw_pixel(x, i, pixel);
            gl_draw_pixel(x + size - 1, i, pixel);
        }
        return;  
    }
}