#pragma once

// RETURNS
#define RET_ACKNOWLEDGED    0xFA
#define RET_RESEND          0xFE
#define RET_TESTPASS        0xAA
#define RET_TESTFAIL1       0xFC
#define RET_TESTFAIL2       0xFD
#define RET_ERROR1          0x00
#define RET_ERROR2          0xFF

// SET LED COMMANDS
#define CMD_SETLED          0xED
#define DATA_SCROLLLOCK     0b0001
#define DATA_NUMBERLOCK     0b0010
#define DATA_CAPSLOCK       0b0100
#define DATA_KANALOCK       0b1000 // might not work, dont have complient keyboard to test

// ECHO
#define CMD_ECHO            0xEE

// SCAN CODE SETS
#define CMD_SCANCODE        0xF0
#define DATA_GETSET         0
#define DATA_SET1           1
#define DATA_SET2           2
#define DATA_SET3           3

// IDENTIFY
#define CMD_IDENT           0xF2

// REPEAT / TYPEMATIC
#define CMD_SETREPEAT       0xf3
#define DATA_250MS          0b00000000
#define DATA_500MS          0b00100000
#define DATA_750MS          0b01000000
#define DATA_1000MS         0b01100000
#define DATA_30HZ           0b00000000
#define DATA_20HZ           0b00000011
#define DATA_16HZ           0b00000111
#define DATA_8HZ            0b00001111
#define DATA_4HZ            0b00010111
#define DATA_2HZ            0b00011111

// IO
#define CMD_ENABLEOUT       0xF4
#define CMD_DISABLEOUT      0xF5
#define CMD_RESEND          0xFE
#define CMD_RESTART         0xFF             


// KEYS

#define PRESSED(scode)  scode
#define RELEASED(scode) scode + 0x80

#define KEY_1               0x02
#define KEY_2               0x03
#define KEY_3               0x04
#define KEY_4               0x05
#define KEY_5               0x06
#define KEY_6               0x07
#define KEY_7               0x08
#define KEY_8               0x09
#define KEY_9               0x0A
#define KEY_0               0x0B

#define KEY_Q               0x10
#define KEY_W               0x11
#define KEY_E               0x12
#define KEY_R               0x13
#define KEY_T               0x14
#define KEY_Y               0x15
#define KEY_U               0x16
#define KEY_I               0x17
#define KEY_O               0x18
#define KEY_P               0x19
#define KEY_A               0X1E
#define KEY_S               0X1F
#define KEY_D               0X20
#define KEY_F               0X21
#define KEY_G               0X22
#define KEY_H               0X23
#define KEY_J               0X24
#define KEY_K               0X25
#define KEY_L               0X26
#define KEY_Z               0x2C
#define KEY_X               0x2D
#define KEY_C               0x2E
#define KEY_V               0x2F
#define KEY_B               0x30
#define KEY_N               0x31
#define KEY_M               0x32

#define KEY_MIN             0x0C
#define KEY_EQU             0x0D
#define KEY_OPEN            0x1A
#define KEY_CLOSE           0x1B
#define KEY_SEMI            0x27
#define KEY_QUOTE           0x28
#define KEY_TICK            0x29
#define KEY_COMMA           0x33
#define KEY_PERIOD          0x34
#define KEY_BSLASH          0x2B
#define KEY_FSLASH          0x35

#define KEY_ESC             0x01

#define KEY_LSHIFT          0x2A
#define KEY_RSHIFT          0x36
#define KEY_LCTRL           0x1D
#define KEY_LALT            0x38
#define KEY_CAPSLOCK        0x3A
#define KEY_NUMLOCK         0x45
#define KEY_SCROLLLOCK      0x46

#define KEY_TAB             0x0F
#define KEY_SPACE           0x39
#define KEY_ENTER           0x1C
#define KEY_BACK            0x0E

#define KEY_F1              0x3B
#define KEY_F2              0x3C
#define KEY_F3              0x3D
#define KEY_F4              0x3E
#define KEY_F5              0x3F
#define KEY_F6              0x40
#define KEY_F7              0x41
#define KEY_F8              0x42
#define KEY_F9              0x43
#define KEY_F10             0x44
#define KEY_F11             0x57
#define KEY_F12             0x58

#define KEY_NUM0            0x52
#define KEY_NUM1            0x4F
#define KEY_NUM2            0x50
#define KEY_NUM3            0x51
#define KEY_NUM4            0x4B
#define KEY_NUM5            0x4C
#define KEY_NUM6            0x4D
#define KEY_NUM7            0x47
#define KEY_NUM8            0x48
#define KEY_NUM9            0x49
#define KEY_NUMSUB          0x4A
#define KEY_NUMPLUS         0x4E
#define KEY_NUMSTAR         0x37
#define KEY_NUMDOT          0x53

// OTHER KEYS
#define KEY_OTHER           0xE0

#define KEYEXT_PREVTRACK    0x10
#define KEYEXT_NEXTTRACK    0x19
#define KEYEXT_MUTE         0x20
#define KEYEXT_PLAY         0x22
#define KEYEXT_VOLDOWN      0x2E
#define KEYEXT_VOLUP        0x30

#define KEYEXT_CALC         0x21
#define KEYEXT_APPS         0x5D
#define KEYEXT_EMAIL        0x6C
#define KEYEXT_COMPUTER     0x6B
#define KEYEXT_MEDIASEL     0x6D
#define KEYEXT_BROWSER      0x32
#define KEYEXT_WWWSEARCH    0x65
#define KEYEXT_WWWFAVORITE  0x6A
#define KEYEXT_WWWREFRESH   0x67
#define KEYEXT_WWWSTOP      0x68
#define KEYEXT_WWWFOWARD    0x69
#define KEYEXT_WWWBACK      0x6A

#define KEYEXT_NUMENTER     0x1C
#define KEYEXT_NUMSLASH     0x35

#define KEYEXT_RCTRL        0x1D
#define KEYEXT_RALT         0x38
#define KEYEXT_LWIN         0x5B
#define KEYEXT_RWIN         0x50

#define KEYEXT_HOME         0x47
#define KEYEXT_PGUP         0x49
#define KEYEXT_END          0x4F
#define KEYEXT_PGDOWN       0x51
#define KEYEXT_INSERT       0x52
#define KEYEXT_DELETE       0x53

#define KEYEXT_UP           0x48
#define KEYEXT_DOWN         0x50
#define KEYEXT_LEFT         0x4B
#define KEYEXT_RIGHT        0x4D

#define KEYEXT_POWER        0x5E
#define KEYEXT_SLEEP        0x5F
#define KEYEXT_WAKE         0x63

#define KEYEXT_PRINT1       0x2A     
#define KEYEXT_PRINT2       0x37     
#define KEYEXT_PRINTREL1    0xB7
#define KEYEXT_PRINTREL2    0xAA
#define KEYEXT_PAUSE1       0xE1               
#define KEYEXT_PAUSE2       0x1D  
#define KEYEXT_PAUSE3       0x45
#define KEYEXT_PAUSE4       0xE1
#define KEYEXT_PAUSE5       0x9D
#define KEYEXT_PAUSE6       0xC5    