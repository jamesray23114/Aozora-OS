#pragma once

#include <typedef.h>


static inline void cpuGetMSR(uint32 msr, uint32 *lo, uint32 *hi)
{
   asm volatile("rdmsr" : "=a"(*lo), "=d"(*hi) : "c"(msr));
}
 
static inline void cpuSetMSR(uint32 msr, uint32 lo, uint32 hi)
{
   asm volatile("wrmsr" : : "a"(lo), "d"(hi), "c"(msr));
}