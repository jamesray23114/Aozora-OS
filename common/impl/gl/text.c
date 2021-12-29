#include <lib/gl/text.h>

void gl_print_char(char c)
{
    uintn res_x = CURGLMODE->horizontal_resolution / 10;
    uintn res_y = CURGLMODE->vertical_resolution / 12;
    
    if(c >= 0x20 && c < 0x7f)
    {
        if(cur_x > res_x - 1)
            cur_x = 0, cur_y++;

        gl_draw_mask(cur_x++ * 10 + 1, cur_y * 14, 1, 10, 0xffffffff, letters[c - 32]);
    }
}

void gl_print_string(char* string)
{
    for(int i = 0; string[i]; i++)
        gl_print_char(string[i]);
}

void gl_print_num(uintn number, const byte radix, byte pad, char topad)
{

}

void gl_set_cursor(uintn x, uintn y)
{
    cur_x = x;
    cur_y = y;
}

void gl_get_dimensions(uintn* x, uintn* y)
{
    *x = CURGLMODE->horizontal_resolution / 10;
    *y = CURGLMODE->vertical_resolution / 12;
}