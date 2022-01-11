#include <aoslib.h>

uintn last = 1;
uintn  loc = 0;

uintn rand() { last = (6364136223846793005 * last + 1442695040888963407); return last >> 34; } // returns numbers in range 0 -> 1073741824
void  srand(uintn seed) { last = seed == 0 ? 1 : seed; }


void printf(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    for(int i = 0; format[i]; i++)
    {
        byte minsize = 0;   //TODO: impliment more formatting options
        char padchar = ' ';

        if(format[i] == '%')
        {
start:
            i++;
            switch (format[i])
            {
            case '%':
                gl_putc('%');
                break;

            case 'f':
            case 'F':
                gl_puts("print floats not implimented");
                break;

            case 'e':
            case 'E':
                gl_puts("print floats not implimented");
                break;

            case 'd':
            case 'i': //TODO: check for signed numbers
            case 'u': 
            {
                uintn value = va_arg(args, uintn);
                gl_putnum(value, 10, minsize, padchar);        
            }   break;

            case 'x':
            case 'X':
            {
                uintn value = va_arg(args, uintn);
                gl_putnum(value, 16, minsize, padchar);        
            }   break;

            case 'b':
            {
                uintn value = va_arg(args, uintn);
                gl_putnum(value, 2, minsize, padchar); 
            }   break;

            case 'o':
            case 'O':
            {
                uintn value = va_arg(args, uintn);
                gl_putnum(value, 8, minsize, padchar); 
            }   break;

            case 's':
            {
                char* value = va_arg(args, char*);
                gl_puts(value);
            }   break;

            case 'c':
            {
                char value = va_arg(args, int);
                gl_putc(value);
            } break;

            default:
                goto end;
            }
        }
        else
            gl_putc(format[i]);
    }

end:
    va_end(args);
}
