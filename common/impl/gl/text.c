#include <lib/gl/text.h>

void gl_print_char(char c)
{
    uintn res_x = GLMODE->horizontal_resolution / 10;
    uintn res_y = GLMODE->vertical_resolution / 16;
    
    switch(c)
    {
        case '\t':
            gl_print_string("    ");
            return;

        case '\n':
            cur_x = 0;
            cur_y++;
            return;

        case '\b':
            if(cur_x != 0)
            {
                cur_x--;
                gl_print_char(' ');
                cur_x--;
            }
            else if(cur_y != 0)
            {
                cur_x = res_x - 1;
                cur_y--;
                gl_print_char(' ');
                cur_x = res_x - 1;
            }
            return;

        case '\r':
            cur_x = 0;
            return;
        
        default:
            if(cur_x > res_x - 1)
                cur_x = 0, cur_y++;

            gl_draw_mask(cur_x++ * 10, cur_y * 16 + 2, 1, 10, 0xffffffff, letters[c - 32]);
            return;
    }
}

void gl_print_string(char* string)
{
    for(int i = 0; string[i]; i++)
        gl_print_char(string[i]);
}

void gl_print_num(uintn number, const byte radix, byte pad, char topad)
{
    if(number == 0)
	{
		if(pad) pad--;
		while (pad--) gl_print_char(topad);
		gl_print_char('0');
		return;	
	}

	char buf[512];

	int i = 0;
	while(number)
	{
		unsigned char c = number % radix;
		number /= radix;
		buf[i++] = c < 10 ? c + '0' : c + '7';
		if(pad) pad--;
	}

	while (pad--) gl_print_char(topad);
	while (i--) gl_print_char(buf[i]);
}

void gl_set_cursor(uintn x, uintn y)
{
    cur_x = x;
    cur_y = y;
}

void gl_get_dimensions(uintn* x, uintn* y)
{
    *x = GLMODE->horizontal_resolution / 10;
    *y = GLMODE->vertical_resolution / 16;
}