#include <lib/io/ps2.h>
#include <lib/int/int.h>
#include <lib/cpu.h>

byte scancode = 0;

#define KC(num, char) case num: gl_putc(char); break; case num + 0x80: break;

INTFUNC int_keyboard(frame* stack)
{
    scancode = inb(PS2_PORT_DATA);

    switch (scancode)
    {
        KC(KEY_0, '0');
        KC(KEY_1, '1');
        KC(KEY_2, '2');
        KC(KEY_3, '3');
        KC(KEY_4, '4');
        KC(KEY_5, '5');
        KC(KEY_6, '6');
        KC(KEY_7, '7');
        KC(KEY_8, '8');
        KC(KEY_9, '9');

        KC(KEY_A, 'a');
        KC(KEY_B, 'b');
        KC(KEY_C, 'c');
        KC(KEY_D, 'd');
        KC(KEY_E, 'e');
        KC(KEY_F, 'f');
        KC(KEY_G, 'g');
        KC(KEY_H, 'h');
        KC(KEY_I, 'i');
        KC(KEY_J, 'j');
        KC(KEY_K, 'k');
        KC(KEY_L, 'l');
        KC(KEY_M, 'm');
        KC(KEY_N, 'n');
        KC(KEY_O, 'o');
        KC(KEY_P, 'p');
        KC(KEY_Q, 'q');
        KC(KEY_R, 'r');
        KC(KEY_S, 's');
        KC(KEY_T, 't');
        KC(KEY_U, 'u');
        KC(KEY_V, 'v');
        KC(KEY_W, 'w');
        KC(KEY_X, 'x');
        KC(KEY_Y, 'y');
        KC(KEY_Z, 'z');

        KC(KEY_BACK, '\b');
        KC(KEY_ENTER, '\n')
        KC(KEY_SPACE, ' ');

    default:
        printf("-%x-", scancode);
        break;
    }

    EOI();
}

INTFUNC int_mouse(frame* stack)
{
    printf("m recived\n");
    EOI();
}