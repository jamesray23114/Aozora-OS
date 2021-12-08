#pragma once

#include "typedef.h"

#define NULLVCHAR {0, 0}

typedef char Vcolor;

#define BLACK          0
#define BLUE           1
#define GREEN          2
#define CYAN           3
#define RED            4
#define PURPLE         5
#define BROWN          6
#define GREY           7
#define DARK_GREY      8
#define LIGHT_BLUE     9
#define LIGHT_GREEN    10
#define LIGHT_CYAN     11
#define LIGHT_RED      12
#define LIGHT_PURPLE   13
#define YELLOW         14
#define WHITE          15

typedef struct Vchar
{
    char character;
    Vcolor color;
} Vchar;

struct Vchar* VRAM = (struct Vchar*) 0xb8000;
uint8 ROW = 0;
uint8 COL = 0;

void printVString(Vchar* buf)
{
    for(int i = 0; buf[i].character != 0; i++)
    {
        if(buf[i].character == '\n')
        {
            ROW++;
            COL = 0;
        }
            
        VRAM[COL + ROW * 80] = buf[i];

        if(++COL == 80)
        {
            COL = 0;
            ROW++;
        }
    }
}


void printString(char* buf, Vcolor color)
{
    for(int i = 0; ; i++)
    {
        switch (buf[i])
        {
        case '\0': return;
        case '\n':
            ROW++;
            COL = 0;
            break;
        default:
            VRAM[COL + ROW * 80].character = buf[i];
            VRAM[COL + ROW * 80].color = color;

            if(++COL == 80)
            {
                COL = 0;
                ROW++;
            }
        }
    }
}

void printChar(char character, Vcolor color)
{
    if(character == '\n')
    {
        ROW++;
        COL = 0;
        return;
    }

    VRAM[COL + ROW * 80].character = character;
    VRAM[COL + ROW * 80].color = color;

    if(++COL == 80)
    {
        COL = 0;
        ROW++;
    }
}

void printVChar(Vchar character)
{
    if(character.character == '\n')
    {
        ROW++;
        COL = 0;
        return;
    }

    VRAM[COL + ROW * 80] = character;

    if(++COL == 80)
    {
        COL = 0;
        ROW++;
    }
}