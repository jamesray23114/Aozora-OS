#pragma once

#include <typedef.h>

char* pci_class_to_string(byte class, byte subclass)
{
    switch (class)
    {
        default:
        case 0x0:
            switch (subclass)
            {   
                case 0: return "Unclassified VGA-Compatible device";
                default:
                case 1: return "Unclassified device";
            }

        case 0x1:
            switch (subclass) 
            {
                default:
                case 0x80: return "Other Storage Controller";
                case 0x1: return "IDE Storage Controller";
                case 0x2: return "Floppy Disk Controller";
                case 0x3: return "IPI Storage Bus Controller";
                case 0x5:  return "ATA Controller";
                case 0x6:  return "Serial ATA Controller";
                case 0x7:  return "Serial Attached SCSI Storage Controller";
                case 0x8:  return "Non-Volatile Memory Controller";
            }
        
        case 0x2:
            switch (subclass) 
            {
                default:
                case 0x80: return "Other Network Controller";

                    case 0x0:  return "Ethernet Controller";
                    case 0x1:  return "Token Ring Controller";
                    case 0x2:  return "FDDI Controller";
                    case 0x3:  return "ATM Controller";
                    case 0x4:  return "ISDN Controller";
                    case 0x5:  return "WorldFip Controller";
                    case 0x6:  return "PICMG 2.14 Multi Computing Controller";
                    case 0x7:  return "Infiniband Controller";
                    case 0x8:  return "Fabric Controller";
            }
    
        case 0x3:
            switch (subclass)
            {
                default:
                case 0x80: return "Other Display Controller";

                case 0x0:  return "VGA Compatible Controller";
                case 0x1:  return "XGA Controller";
                case 0x2:  return "3D Controller (Not VGA-Compatible)";
            }

        case 0x4:
           switch (subclass)
            {
                default:
                case 0x80: return "Other Multimedia Controller";

                case 0x0:  return "Multimedia Video Controller";
                case 0x1:  return "Multimedia Audio Controller";
                case 0x2:  return "Computer Telephony Device";
                case 0x3:  return "Audio Device";
            }

        case 0x5:
           switch (subclass)
            {
                default:
                case 0x80: return "Other Memory Controller";

                case 0x0: return "RAM Controller";
                case 0x1: return "Flash Controller";
            }

        case 0x6:
           switch (subclass)
            {
                default:
                case 0x80: return "Other Bridge Controller";
 
                case 0x0:   return "Host Bridge";
                case 0x1:   return "ISA Bridge";
                case 0x2:   return "EISA Bridge";
                case 0x3:   return "MCA Bridge";
                case 0x4:   return "PCI-to-PCI Bridge";
                case 0x5:   return "PCMCIA Bridge";
                case 0x6:   return "NuBus Bridge";
                case 0x7:   return "CardBus Bridge";
                case 0x8:   return "RACEway Bridge";
                case 0x9:   return "PCI-to-PCI Bridge";
                case 0x0A:  return "InfiniBand-to-PCI Host Bridge";
            }

        case 0x7:
           switch (subclass)
            {
                default:
                case 0x80: return "Other Communication Controller";

                case 0x0:  return "Serial Controller";
                case 0x1:  return "Parallel Controller";
                case 0x2:  return "Multiport Serial Controller";
                case 0x3:  return "Modem";
                case 0x4:  return "IEEE 488.1/2 (GPIB) Controller";
                case 0x5:  return "Smart Card Controller";
            }

        case 0x8:
           switch (subclass)
            {
                default:
                case 0x80: return "Other System Controller";

                case 0x0:  return "PIC";
                case 0x1:  return "DMA Controller";
                case 0x2:  return "Timer";
                case 0x3:  return "RTC Controller";
                case 0x4:  return "PCI Hot-Plug Controller";
                case 0x5:  return "SD Host controller";
                case 0x6:  return "IOMMU";
            }   

        case 0x9:
           switch (subclass)
            {
                default:
                case 0x80: return "Other Input Controller";

                case 0x0: return "Keyboard Controller";
                case 0x1: return "Digitizer Pen";
                case 0x2: return "Mouse Controller";
                case 0x3: return "Scanner Controller";
                case 0x4: return "Gameport Controller";
            }

        case 0xA:
           switch (subclass)
            {
                default:
                case 0x80: return "Other Docking Station";

                case 0x1:  return "Generic Docking Station";
            }

        case 0xB:
           switch (subclass)
            {
                default:
                case 0x80: return "Other Processor";
                case 0x40: return "Co-Processor";

                case 0x0:  return  "386";
                case 0x1:  return  "486";
                case 0x2:  return  "Pentium";
                case 0x3:  return  "Pentium Pro";
                case 0x10: return  "Alpha";
                case 0x20: return  "PowerPC";
                case 0x30: return  "MIPS";
            }

        case 0xC:
           switch (subclass)
            {
                default:
                case 0x80: return "Other Serial Bus Controller";

                case 0x0: return "FireWire (IEEE 1394) Controller";
                case 0x1: return "ACCESS Bus Controller";
                case 0x2: return "SSA";
                case 0x3: return "USB Controller";
                case 0x4: return "Fibre Channel";
                case 0x5: return "SMBus Controller";
                case 0x6: return "InfiniBand Controller";
                case 0x7: return "IPMI Interface";
                case 0x8: return "SERCOS Interface (IEC 61491)";
                case 0x9: return "CANbus Controller";
            }

        case 0xD:
           switch (subclass)
            {
                default:
                case 0x80: return "Other Wireless Controller";

                case 0x0:   return "iRDA Compatible Controller";
                case 0x1:   return "Consumer IR Controller";
                case 0x10:  return "RF Controller";
                case 0x11:  return "Bluetooth Controller";
                case 0x12:  return "Broadband Controller";
                case 0x20:  return "Ethernet Controller (802.1a)";
                case 0x21:  return "Ethernet Controller (802.1b)";
            }

        case 0xE: return "Intelligent Controller";

        case 0xF: 
           switch (subclass)
            {
                default:
                case 0x80: return "Other Satellite Controller";

                case 0x1: return "Satellite TV Controller";
                case 0x2: return "Satellite Audio Controller";
                case 0x3: return "Satellite Voice Controller";
                case 0x4: return "Satellite Data Controller";
            }
 
        case 0x10: 
           switch (subclass)
            {
                default:
                case 0x80: return "Other Encryption Controller";

                case 0x00: return "Network and Computing Encrpytion/Decryption";
                case 0x10: return "Entertainment Encryption/Decryption";
            }

        case 0x11:
           switch (subclass)
            {
                default:
                case 0x80: return "Other Signal Processing Controller";

                case 0x00: return "DPIO Modules";
                case 0x01: return "Performance Counters";
                case 0x10: return "Communication Synchronizer";
                case 0x20: return "Signal Processing Management";
            }

        case 0x12: return "Processing Accelerator";
        case 0x13: return "Non-Essential Instrumentation";
        case 0x40: return "Co-Processor";
    }       

 return "Unclassified device";
}

/*
           switch (subclass)
            {
                default:
                case 0x80: return "Other Display Controller";
            }
*/