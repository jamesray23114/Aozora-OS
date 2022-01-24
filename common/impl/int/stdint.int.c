#include <lib/cpu.h>

typedef struct interrupt_frame_s
{
    uintn ip;
    uintn cs;
    uintn flags;
    uintn sp;
    uintn ss;
} frame;

__attribute__((interrupt)) void int_stdint(frame* stack)
{
    printf("stdint ran at %x, halting\n", (uintn)stack->ip);
    
    cpu_halt();
}

__attribute__((interrupt)) void int_divzero(frame* stack)
{
    printf("divide by zero occured at %x, resuming\n", (uintn)stack->ip);
    //stack->ip += 2;
}
