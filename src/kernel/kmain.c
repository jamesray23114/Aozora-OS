#include "kernel/print.h"

void kernel_main()
{
    printString("hello \n", WHITE);
       
    Vchar vstring[] = {{'h', BLUE}, {'e', GREEN}, {'l', YELLOW}, {'l',PURPLE}, {'o',RED}, NULLVCHAR};

    printVString(vstring);
    

    while(1);
}

