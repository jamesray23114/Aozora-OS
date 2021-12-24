#pragma once

#include <lib/typedef.h>

#include <lib/gl/text.h>

#define CURGLMODE *gl_mode

typedef struct  graphics_mode_s graphics_mode;
typedef struct  bitmask_pixel_s bitmask_pixel;
typedef union   rgb_pixel_u     rgb_pixel;
typedef union   bgr_pixel_u     bgr_pixel;
typedef enum    pixel_format_e  pixel_format;

void gl_draw_linear();
void gl_draw_pixel();

typedef enum pixel_format_e
{
    RGB_8_BIT,
    BGR_8_BIT,
    PIXEL_MASK,
    BUFFERLESS
} pixel_format;

typedef struct graphics_mode_s
{
    uint16           vertical_resolution;
    uint16           horizontal_resolution;
    uint16           pitch;
    pixel_format     format;
} graphics_mode;

typedef union rgb_pixel_u
{
    struct 
    {
        byte red;
        byte green;
        byte blue;
        byte none;
    };
    uint32 color;
} rgb_pixel;

typedef union bgr_pixel_u
{
    struct 
    {
        byte blue;
        byte green;
        byte red;
        byte none;
    };
    uint32 color;
} bgr_pixel;

typedef struct bitmask_pixel_s
{
    uint32 red;
    uint32 green;
    uint32 blue;
    uint32 none;
} bitmask_pixel;

static graphics_mode* gl_mode = (graphics_mode*) 0x24000; //THIS CAN CAUSE ISSUES, PLEASE REVIEW IN FUTURE