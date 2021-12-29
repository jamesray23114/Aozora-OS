#pragma once

#include <lib/memory.h>

#include <bootlib/io.h>

#define PRINTPAIR(string, num) print_string(string); print_num(num, 10, 0, 0); print_string(".\n\r")


void print_num(int64 num, const byte radix, byte pad, char padchar);
void print_string(char* string);
void print_aozora_memory(aozora_memory memory);
void print_map();
