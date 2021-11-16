#pragma once

#define NULLVCHAR {0, 0}

typedef char Vcolor;

const Vcolor BLACK          = 0;
const Vcolor BLUE           = 1;
const Vcolor GREEN          = 2;
const Vcolor CYAN           = 3;
const Vcolor RED            = 4;
const Vcolor PURPLE         = 5;
const Vcolor BROWN          = 6;
const Vcolor GREY           = 7;
const Vcolor DARK_GREY      = 8;
const Vcolor LIGHT_BLUE     = 9;
const Vcolor LIGHT_GREEN    = 10;
const Vcolor LIGHT_CYAN     = 11;
const Vcolor LIGHT_RED      = 12;
const Vcolor LIGHT_PURPLE   = 13;
const Vcolor YELLOW         = 14;
const Vcolor WHITE          = 15;

typedef struct Vchar
{
    char character;
    Vcolor color;
} Vchar;

struct Vchar* VRAM = (struct Vchar*) 0xb8000;
char ROW = 0;
char COL = 0;

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
    for(int i = 0; buf[i] != 0; i++)
    {
        if(buf[i] == '\n')
        {
            ROW++;
            COL = 0;
            return;
        }

        VRAM[COL + ROW * 80].character = buf[i];
        VRAM[COL + ROW * 80].color = color;

        if(++COL == 80)
        {
            COL = 0;
            ROW++;
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