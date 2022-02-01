#include <lib/cpu.h>
#include <lib/int/apic.h>
#include <lib/int/int.h>

INTFUNC int_timer(frame* stack)
{
    EOI();
}