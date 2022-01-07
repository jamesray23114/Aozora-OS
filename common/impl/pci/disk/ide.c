#include <lib/pci/disk/ide.h>

// TODO: rewrite this file to better fit my usecases

struct IDEChannelRegisters {
   uint16 base;  // I/O Base.
   uint16 ctrl;  // Control Base
   uint16 bmide; // Bus Master IDE
   byte   nIEN;  // nIEN (No Interrupt);
} channels[2];

byte ide_buf[2048] = {0};
volatile byte ide_irq_invoked = 0;
byte atapi_packet[12] = {0xA8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

struct ide_device {
   byte     Reserved;     // 0 (Empty) or 1 (This Drive really exists).
   byte     Channel;      // 0 (Primary Channel) or 1 (Secondary Channel).
   byte     Drive;        // 0 (Master Drive) or 1 (Slave Drive).
   uint16   Type;         // 0: ATA, 1:ATAPI.
   uint16   Signature;    
   uint16   Capabilities; 
   uint32   CommandSets;  
   uint32   Size;         // Size in Sectors.
   char     Model[41];    
} ide_devices[4];

inline void insl(uint64 adr, uint32 unused, uint32 count)
{
    uint32* buf = (uint32*)ide_buf;
    
    for(int i = 0; i < count; i++)
        buf[i] = inl(adr);
}

bool ide_init()
{
    pci_device ide = get_device(1, 1);

    if(ide.header_ver == 100)
    {   
        gl_print_string("could not find ide controller.");
        return false;
    }

    uint32 BAR0 = device_read(ide, 16);
    uint32 BAR1 = device_read(ide, 20);
    uint32 BAR2 = device_read(ide, 24);
    uint32 BAR3 = device_read(ide, 28);
    uint32 BAR4 = device_read(ide, 32);

    int count = 0;

    channels[ATA_PRIMARY  ].base  = (BAR0 & 0xFFFFFFFC) + 0x1F0 * (!BAR0);
    channels[ATA_PRIMARY  ].ctrl  = (BAR1 & 0xFFFFFFFC) + 0x3F6 * (!BAR1);
    channels[ATA_SECONDARY].base  = (BAR2 & 0xFFFFFFFC) + 0x170 * (!BAR2);
    channels[ATA_SECONDARY].ctrl  = (BAR3 & 0xFFFFFFFC) + 0x376 * (!BAR3);
    channels[ATA_PRIMARY  ].bmide = (BAR4 & 0xFFFFFFFC) + 0; // Bus Master IDE
    channels[ATA_SECONDARY].bmide = (BAR4 & 0xFFFFFFFC) + 8; // Bus Master IDE

    ide_write(ATA_PRIMARY  , REG_ATA_CONTROL, 2);
    ide_write(ATA_SECONDARY, REG_ATA_CONTROL, 2);

    for(int i = 0, i2 = 0; i < 2; i++, i2++)
    {
        for(int j = 0; j < 2; j++)
        { 
            byte err, type = ATA, status;
            ide_devices[count].Reserved = 0;


            // select device
            ide_write(i, REG_ATA_HDDEVSEL, 0xA0 | (j << 4));          
            for(int hgl = 0; hgl < 1000; hgl++) asm volatile ("nop\n"); // TODO: replace with sleep(1)


            // send identify command
            ide_write(i, REG_ATA_COMMAND, CMD_ATA_IDENTIFY);
            for(int hgl = 0; hgl < 1000; hgl++) asm volatile ("nop\n"); // TODO: replace with sleep(1)


            // poll
            if (ide_read(i, REG_ATA_STATUS) == 0) continue;         

            while(1) 
            {
                status = ide_read(i, REG_ATA_STATUS);
                if ((status & STA_ATA_ERR)) {err = 1; break;} 
                if (!(status & STA_ATA_BUSY) && (status & STA_ATA_DATA)) break; 
            }

            // read identify data
            ide_read_buffer(i, REG_ATA_DATA, (uintn) ide_buf, 128);


            // read device parameters
            ide_devices[count].Reserved     = 1;
            ide_devices[count].Type         = type;
            ide_devices[count].Channel      = i; 
            i = i2; // TODO: fix, i2 is needed for some reason, im assuming gcc is forgetting what regesters are storing what
            ide_devices[count].Drive        = j;
            ide_devices[count].Signature    = *((uint16*)(ide_buf + IDF_ATA_DEVICETYPE));
            ide_devices[count].Capabilities = *((uint16*)(ide_buf + IDF_ATA_CAPABILITIES));
            ide_devices[count].CommandSets  = *((uint32*)(ide_buf + IDF_ATA_COMMANDSETS));


            // read size
            if (ide_devices[count].CommandSets & (1 << 26)) ide_devices[count].Size = *((uint32*)(ide_buf + IDF_ATA_MAX_LBA_EXT));
            else ide_devices[count].Size   = *((uint32*)(ide_buf + IDF_ATA_MAX_LBA));



            // read device name
            for(int k = 0; k < 40; k += 2) 
            {
                ide_devices[count].Model[k] = ide_buf[IDF_ATA_MODEL + k + 1];
                ide_devices[count].Model[k + 1] = ide_buf[IDF_ATA_MODEL + k];
            }   ide_devices[count].Model[40] = 0; 

            count++;
        }
    }

    for(int i = 0; i < 4; i++)
        if(ide_devices[i].Reserved == 1)
        {
            gl_print_num(i, 10, 0, 0);
            gl_print_string(":");
            gl_print_num(ide_devices[i].Channel, 10, 0, 0);
            gl_print_string(":");
            gl_print_num(ide_devices[i].Drive, 10, 0, 0);
            gl_print_string(": found ");
            gl_print_string((char *[]){"ATA", "ATAPI"}[ide_devices[i].Type]);
            gl_print_string(" drive size: ");
            gl_print_num(ide_devices[i].Size / 1024 / 1024 / 2, 10, 0, 0);
            gl_print_string("GB -> ");
            gl_print_string(ide_devices[i].Model);
            gl_print_char('\n');
        }

    return true;
}

void ide_read_buffer(byte channel, byte reg, uint32 buffer, uint32 quads) 
{
    if (reg > 0x07 && reg < 0x0C)
        ide_write(channel, REG_ATA_CONTROL, 0x80 | channels[channel].nIEN);
    asm volatile ("movw %es, %r15w; movw %ds, %ax; movw %ax, %es;"); // TODO: remove or replace this assembly, i think this is causing a few strange problems
    if (reg < 0x08)
        insl(channels[channel].base  + reg - 0x00, buffer, quads);
    else if (reg < 0x0C)
        insl(channels[channel].base  + reg - 0x06, buffer, quads);
    else if (reg < 0x0E)
        insl(channels[channel].ctrl  + reg - 0x0A, buffer, quads);
    else if (reg < 0x16)
        insl(channels[channel].bmide + reg - 0x0E, buffer, quads);
    if (reg > 0x07 && reg < 0x0C)
       ide_write(channel, REG_ATA_CONTROL, channels[channel].nIEN);
    asm volatile ("movw %r15w, %es;");
}

byte ide_read(byte channel, byte reg)
{
    byte result;
    if (reg > 0x07 && reg < 0x0C)
        ide_write(channel, REG_ATA_CONTROL, 0x80 | channels[channel].nIEN);
    if (reg < 0x08)
        result = inb(channels[channel].base + reg - 0x00);
    else if (reg < 0x0C)
        result = inb(channels[channel].base  + reg - 0x06);
    else if (reg < 0x0E)
        result = inb(channels[channel].ctrl  + reg - 0x0A);
    else if (reg < 0x16)
        result = inb(channels[channel].bmide + reg - 0x0E);
    if (reg > 0x07 && reg < 0x0C)
       ide_write(channel, REG_ATA_CONTROL, channels[channel].nIEN);
    return result;
}

byte ide_write(byte channel, byte reg, byte data)
{
    if (reg > 0x07 && reg < 0x0C)
        ide_write(channel, REG_ATA_CONTROL, 0x80 | channels[channel].nIEN);
    if (reg < 0x08)
        outb(channels[channel].base  + reg - 0x00, data);
    else if (reg < 0x0C)
        outb(channels[channel].base  + reg - 0x06, data);
    else if (reg < 0x0E)
        outb(channels[channel].ctrl  + reg - 0x0C, data);
    else if (reg < 0x16)
        outb(channels[channel].bmide + reg - 0x0E, data);
    if (reg > 0x07 && reg < 0x0C)
        ide_write(channel, REG_ATA_CONTROL, channels[channel].nIEN);
}

byte ide_poll(byte channel, bool advanced_check)
{
   for(int i = 0; i < 4; i++)
      ide_read(channel, REG_ATA_ALTSTATUS);

    while (ide_read(channel, REG_ATA_STATUS) & STA_ATA_BUSY);

    if(advanced_check)
    {
        byte state = ide_read(channel, REG_ATA_STATUS);

        if(state & STA_ATA_ERR)
            return 1;

        if(state & STA_ATA_FAULT)
            return 2;

        if(state & STA_ATA_DATA == 0)
            return 3;
    }

    return 0;
}

void ide_print_error(uint32 drive, byte err)
{

}

void ide_read_sectors(byte drive, uintn location, uintn sectors, byte* buffer)
{
    byte lba_mode, dma = 0, cmd;
    byte lba_io[6];
    byte head, sect, err;
    byte slavebit       = ide_devices[drive].Drive; 
    uint32 channel      = ide_devices[drive].Channel; 
    uint32 bus          = channels[channel].base; 
    uint32 words        = 256; 
    uint16 cyl;

    ide_write(channel, REG_ATA_CONTROL, channels[channel].nIEN = (ide_irq_invoked = 0x0) + 0x02);

    // select drive io mode
    if (location >= 0x10000000) 
    { 
        lba_mode  = 2;
        lba_io[0] = (location & 0x000000FF) >> 0;
        lba_io[1] = (location & 0x0000FF00) >> 8;
        lba_io[2] = (location & 0x00FF0000) >> 16;
        lba_io[3] = (location & 0xFF000000) >> 24;
        lba_io[4] = 0;  
        lba_io[5] = 0;  
        head      = 0; 
    } 
    else if (ide_devices[drive].Capabilities & 0x200)  
    { 
        lba_mode  = 1;
        lba_io[0] = (location & 0x00000FF) >> 0;
        lba_io[1] = (location & 0x000FF00) >> 8;
        lba_io[2] = (location & 0x0FF0000) >> 16;
        lba_io[3] = 0;
        lba_io[4] = 0;
        lba_io[5] = 0;
        head      = (location & 0xF000000) >> 24;
    } 
    else 
    {
        lba_mode  = 0;
        sect      = (location % 63) + 1;
        cyl       = (location + 1  - sect) / (16 * 63);
        lba_io[0] = sect;
        lba_io[1] = (cyl >> 0) & 0xFF;
        lba_io[2] = (cyl >> 8) & 0xFF;
        lba_io[3] = 0;
        lba_io[4] = 0;
        lba_io[5] = 0;
        head      = (location + 1  - sect) % (16 * 63) / (63); 
    }


    // wait untill drive is not busy
    while (ide_read(channel, REG_ATA_STATUS) & STA_ATA_BUSY);


    // select drive
    if (lba_mode == 0)
        ide_write(channel, REG_ATA_HDDEVSEL, 0xA0 | (slavebit << 4) | head); 
    else
        ide_write(channel, REG_ATA_HDDEVSEL, 0xE0 | (slavebit << 4) | head); 


    // write parameters to registers
    if (lba_mode == 2) 
    {
        ide_write(channel, REG_ATA_SECCOUNT1,   0);
        ide_write(channel, REG_ATA_LBA3,        lba_io[3]);
        ide_write(channel, REG_ATA_LBA4,        lba_io[4]);
        ide_write(channel, REG_ATA_LBA5,        lba_io[5]);
    }
    ide_write(channel, REG_ATA_SECCOUNT0,       sectors);
    ide_write(channel, REG_ATA_LBA0,            lba_io[0]);
    ide_write(channel, REG_ATA_LBA1,            lba_io[1]);
    ide_write(channel, REG_ATA_LBA2,            lba_io[2]);


    //select and write command
    if (lba_mode == 0) cmd = CMD_ATA_RD_PIO;
    if (lba_mode == 1) cmd = CMD_ATA_RD_PIO;
    if (lba_mode == 2) cmd = CMD_ATA_RD_PIOEXT;
    ide_write(channel, REG_ATA_COMMAND, cmd);


    // read data
    uint16* wbuffer = (uint16*) buffer;
    for (int i = 0; i < sectors * words; i++) 
    {
       if(err = ide_poll(channel, 1)) { gl_print_string("error\n"); return; } 
        print_num(i, 10, 5, ' ');
        wbuffer[i] = inw(bus);      
    }
}

void ide_write_sectors(byte drive, uintn location, byte sectors, byte* buffer)
{
    byte lba_mode, dma = 0, cmd;
    byte lba_io[6];
    byte head, sect, err;
    uint32 channel      = ide_devices[drive].Channel; 
    uint32 slavebit     = ide_devices[drive].Drive; 
    uint32 bus          = channels[channel].base; 
    uint32 words        = 256; 
    uint16 cyl;


    // select drive io mode
    if (location >= 0x10000000) 
    { 
        lba_mode  = 2;
        lba_io[0] = (location & 0x000000FF) >> 0;
        lba_io[1] = (location & 0x0000FF00) >> 8;
        lba_io[2] = (location & 0x00FF0000) >> 16;
        lba_io[3] = (location & 0xFF000000) >> 24;
        lba_io[4] = 0;  
        lba_io[5] = 0;  
        head      = 0; 
    } 
    else if (ide_devices[drive].Capabilities & 0x200)  
    { 
        lba_mode  = 1;
        lba_io[0] = (location & 0x00000FF) >> 0;
        lba_io[1] = (location & 0x000FF00) >> 8;
        lba_io[2] = (location & 0x0FF0000) >> 16;
        lba_io[3] = 0;
        lba_io[4] = 0;
        lba_io[5] = 0;
        head      = (location & 0xF000000) >> 24;
    } 
    else 
    {
        lba_mode  = 0;
        sect      = (location % 63) + 1;
        cyl       = (location + 1  - sect) / (16 * 63);
        lba_io[0] = sect;
        lba_io[1] = (cyl >> 0) & 0xFF;
        lba_io[2] = (cyl >> 8) & 0xFF;
        lba_io[3] = 0;
        lba_io[4] = 0;
        lba_io[5] = 0;
        head      = (location + 1  - sect) % (16 * 63) / (63); 
    }


    // waiat untill drive is not busy
    while (ide_read(channel, REG_ATA_STATUS) & STA_ATA_BUSY);


    // select drive
    if (lba_mode == 0)
        ide_write(channel, REG_ATA_HDDEVSEL, 0xA0 | (slavebit << 4) | head); 
    else
        ide_write(channel, REG_ATA_HDDEVSEL, 0xE0 | (slavebit << 4) | head); 


    // write parameters to registers
    if (lba_mode == 2) 
    {
        ide_write(channel, REG_ATA_SECCOUNT1,   0);
        ide_write(channel, REG_ATA_LBA3,        lba_io[3]);
        ide_write(channel, REG_ATA_LBA4,        lba_io[4]);
        ide_write(channel, REG_ATA_LBA5,        lba_io[5]);
    }
    ide_write(channel, REG_ATA_SECCOUNT0,       sectors);
    ide_write(channel, REG_ATA_LBA0,            lba_io[0]);
    ide_write(channel, REG_ATA_LBA1,            lba_io[1]);
    ide_write(channel, REG_ATA_LBA2,            lba_io[2]);


    //select and write command
    if (lba_mode == 0) cmd = CMD_ATA_WR_PIO;
    if (lba_mode == 1) cmd = CMD_ATA_WR_PIO;
    if (lba_mode == 2) cmd = CMD_ATA_WR_PIOEXT;
    ide_write(channel, REG_ATA_COMMAND, cmd);
    

    //write data
    uint16* wbuffer = (uint16*) buffer;
    for (int i = 0; i < sectors * words; i++) 
    {
        ide_poll(channel, 0);

        outw(bus, wbuffer[i]);    
    }
    ide_write(channel, REG_ATA_COMMAND, (char []) 
    { 
        CMD_ATA_FLUSH,
        CMD_ATA_FLUSH,
        CMD_ATA_FLUSH_EXT
    }[lba_mode]);
    ide_poll(channel, 0);
}

