#pragma once

#include <bootlib/print.h>

#include <lib/typedef.h>
#include <lib/gl/text.h>

#define CURGLMODE gl_mode

typedef struct  graphics_mode_s graphics_mode;
typedef struct  bitmask_pixel_s bitmask_pixel;
typedef union   rgb_pixel_u     rgb_pixel;
typedef union   bgr_pixel_u     bgr_pixel;
typedef enum    pixel_format_e  pixel_format;
typedef enum    draw_mode_e     draw_mode;

//void init_gl();

void gl_draw_line(uintn x1, uintn y1, uintn x2, uintn y2, uint32 pixel);
void gl_draw_rect(uintn x1, uintn y1, uintn x2, uintn y2, uint32 pixel, const draw_mode mode);

void gl_draw_square(uintn x, uintn y, uintn size, uint32 pixel, const draw_mode mode);

typedef enum pixel_format_e
{
    RGB_8_BIT,
    BGR_8_BIT,
    PIXEL_MASK,
    BUFFERLESS
} pixel_format;

typedef enum draw_mode_e
{
    FILL,
    OUTLINE1
} draw_mode;

typedef struct graphics_mode_s
{
    uint16          vertical_resolution;
    uint16          horizontal_resolution;
    uint16          pitch;
    uint32          resolution;
    pixel_format    format;
    uint32*         location;
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


static inline uint32 gl_pixel(byte red, byte blue, byte green)
{   
    switch (CURGLMODE->format)
    {
    case RGB_8_BIT:
        rgb_pixel rgb = {.red = red, .blue = blue, .green = green};
        return rgb.color;
    case BGR_8_BIT:
        bgr_pixel bgr = {.red = red, .blue = blue, .green = green};
        return bgr.color;
    }

    return 0;
}

static inline void gl_draw_linear(uintn start, uintn count, uint32 pixel) // does not account for pitch
{
    for(int i = 0; i < count; i++)
        CURGLMODE->location[i + start] = pixel;
}

static inline void gl_draw_pixel(uintn x, uintn y, uint32 pixel)
{
    CURGLMODE->location[y * CURGLMODE->pitch + x] = pixel;
}