#include <lib/io/ps2.h>


#define PS2WAIT() while(inb(PS2_PORT_COMMAND) & 0b10)

void ps2_init()
{
    byte conf;
    bool port2 = true;

    // disable ps2 devices
    outb(PS2_PORT_COMMAND, PS2_CMD_DISABLE1);
    PS2WAIT();
    outb(PS2_PORT_COMMAND, PS2_CMD_DISABLE2);
    PS2WAIT();

    // flush psu buffer
    inb(PS2_PORT_DATA);
    PS2WAIT();

    // read and set config
    outb(PS2_PORT_COMMAND, PS2_CMD_READCONF);
    PS2WAIT();
    conf = inb(PS2_PORT_DATA);
    if((conf & 0b100000) == 0) port2 = false;
    conf &= 0b11111100;
    PS2WAIT();
    outb(PS2_PORT_COMMAND, PS2_CMD_WRITECONF);
    PS2WAIT();
    outb(PS2_PORT_DATA, conf);
    PS2WAIT();

    // test ps2 device
    outb(PS2_PORT_COMMAND, PS2_CMD_TEST);
    PS2WAIT();
    if(inb(PS2_PORT_DATA) != 0x55) { printf("error intitializing ps2 device"); return; }
    PS2WAIT();

    // test for 2nd channel on ps2 device
    if(port2)
    {
        outb(PS2_PORT_COMMAND, PS2_CMD_ENABLE2);
        PS2WAIT();
        outb(PS2_PORT_COMMAND, PS2_CMD_READCONF);
        PS2WAIT();
        conf = inb(PS2_PORT_DATA);
        if(conf & 0b100000) port2 = false;
        PS2WAIT();
        outb(PS2_PORT_COMMAND, PS2_CMD_DISABLE2);
        PS2WAIT();
    }

    // enable devices and interrupts
    outb(PS2_PORT_COMMAND, PS2_CMD_ENABLE1);
    PS2WAIT();
    outb(PS2_PORT_COMMAND, PS2_CMD_ENABLE2);
    PS2WAIT();
    outb(PS2_PORT_COMMAND, PS2_CMD_READCONF);
    PS2WAIT();
    conf = inb(PS2_PORT_DATA);
    conf |= 0b11;
    outb(PS2_PORT_COMMAND, PS2_CMD_WRITECONF);
    PS2WAIT();
    outb(PS2_PORT_DATA, conf);
    PS2WAIT();

    cpu_addHandler(int_keyboard, 0x21, false);
    cpu_addHandler(int_mouse, 0x22, false);

    //set keyboard stuff

    outb(PS2_PORT_DATA, 0xf0);
    outb(PS2_PORT_DATA, 2);

    PS2WAIT();
}