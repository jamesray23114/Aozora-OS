#include <cpuid.h>

#include <lib/cpu.h>
#include <typedef.h>
#include <lib/gl/text.h>

bool init_apic();

void set_handler();
void print_apic_info();
