#pragma once

#include <aoslib.h>
#include <lib/cpu.h>
#include <lib/io/ps2scancode.h>
#include <lib/io/io.h>

#define PS2_PORT_DATA       0x60
#define PS2_PORT_COMMAND    0x64

#define PS2_CMD_DISABLE1    0xAD
#define PS2_CMD_ENABLE1     0xAE
#define PS2_CMD_DISABLE2    0xA7
#define PS2_CMD_ENABLE2     0xA8
#define PS2_CMD_READCONF    0x20
#define PS2_CMD_WRITECONF   0x60
#define PS2_CMD_READOUT     0xD0
#define PS2_CMD_WRITEOUT    0xD1
#define PS2_CMD_TEST        0xAA

typedef struct interrupt_frame_s frame;

void ps2_init();

void int_keyboard(frame* stack);
void int_mouse(frame* stack);