#pragma once

#include <lib/typedef.h>

#include "efidef.h"
#include "eficon.h"

struct _EFI_SYSTEM_TABLE;

typedef uintn (*EFI_ALLOCATE_PAGES) (
    EFI_ALLOCATE_TYPE            Type,
    EFI_MEMORY_TYPE              MemoryType,
    uintn                        NoPages,
    EFI_PHYSICAL_ADDRESS        *Memory
    );

typedef uintn (*EFI_FREE_PAGES) (
    EFI_PHYSICAL_ADDRESS         Memory,
    uintn                        NoPages
    );

typedef uintn (*EFI_GET_MEMORY_MAP) (
    uintn                       *MemoryMapSize,
    EFI_MEMORY_DESCRIPTOR       *MemoryMap,
    uintn                       *MapKey,
    uintn                       *DescriptorSize,
    uint32                      *DescriptorVersion
    );

#define NextMemoryDescriptor(Ptr,Size)  ((EFI_MEMORY_DESCRIPTOR *) (((uint8 *) Ptr) + Size))


typedef uintn (*EFI_ALLOCATE_POOL) (
    EFI_MEMORY_TYPE              PoolType,
    uintn                        Size,
    void                        **Buffer
    );

typedef uintn (*EFI_FREE_POOL) (
    void                         *Buffer
    );

typedef uintn (*EFI_SET_VIRTUAL_ADDRESS_MAP) (
    uintn                        MemoryMapSize,
    uintn                        DescriptorSize,
    uint32                       DescriptorVersion,
    EFI_MEMORY_DESCRIPTOR        *VirtualMap
    );


#define EFI__PTR            0x00000001
#define EFI_INTERNAL_FNC            0x00000002      // Pointer to internal runtime fnc
#define EFI_INTERNAL_PTR            0x00000004      // Pointer to internal runtime data


typedef uintn (*EFI_CONVERT_POINTER) (
    uintn                        DebugDisposition,
    void                     **Address
    );


//
// EFI Events
//

#define EVT_TIMER                           0x80000000
#define EVT_RUNTIME                         0x40000000
#define EVT_RUNTIME_CONTEXT                 0x20000000

#define EVT_NOTIFY_WAIT                     0x00000100
#define EVT_NOTIFY_SIGNAL                   0x00000200

#define EVT_SIGNAL_EXIT_BOOT_SERVICES       0x00000201
#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE   0x60000202

#define EVT_EFI_SIGNAL_MASK                 0x000000FF
#define EVT_EFI_SIGNAL_MAX                  4

#define EFI_EVENT_TIMER                         EVT_TIMER
#define EFI_EVENT_RUNTIME                       EVT_RUNTIME
#define EFI_EVENT_RUNTIME_CONTEXT               EVT_RUNTIME_CONTEXT
#define EFI_EVENT_NOTIFY_WAIT                   EVT_NOTIFY_WAIT
#define EFI_EVENT_NOTIFY_SIGNAL                 EVT_NOTIFY_SIGNAL
#define EFI_EVENT_SIGNAL_EXIT_BOOT_SERVICES     EVT_SIGNAL_EXIT_BOOT_SERVICES
#define EFI_EVENT_SIGNAL_VIRTUAL_ADDRESS_CHANGE EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE
#define EFI_EVENT_EFI_SIGNAL_MASK               EVT_EFI_SIGNAL_MASK
#define EFI_EVENT_EFI_SIGNAL_MAX                EVT_EFI_SIGNAL_MAX


typedef void (*EFI_EVENT_NOTIFY) (
    EFI_EVENT                Event,
    void                     *Context
    );

typedef uintn (*EFI_CREATE_EVENT) 
(
    uint32                       Type,
    EFI_TPL                      NotifyTpl,
    EFI_EVENT_NOTIFY             NotifyFunction,
    void                         *NotifyContext,
    EFI_EVENT                    *Event
    );

typedef enum {
    TimerCancel,
    TimerPeriodic,
    TimerRelative,
    TimerTypeMax
} EFI_TIMER_DELAY;

typedef uintn (*EFI_SET_TIMER) (
    EFI_EVENT                Event,
    EFI_TIMER_DELAY          Type,
    uint64                   TriggerTime
    );

typedef uintn (*EFI_SIGNAL_EVENT) (
    EFI_EVENT                Event
    );

typedef uintn (*EFI_WAIT_FOR_EVENT) (
    uintn                    NumberOfEvents,
    EFI_EVENT                *Event,
    uintn                   *Index
    );

typedef uintn (*EFI_CLOSE_EVENT) (
    EFI_EVENT                Event
    );

typedef uintn (*EFI_CHECK_EVENT) (
    EFI_EVENT                Event
    );

//
// Task priority level
//

#define TPL_APPLICATION       4
#define TPL_CALLBACK          8
#define TPL_NOTIFY           16
#define TPL_HIGH_LEVEL       31
#define EFI_TPL_APPLICATION  TPL_APPLICATION
#define EFI_TPL_CALLBACK     TPL_CALLBACK
#define EFI_TPL_NOTIFY       TPL_NOTIFY
#define EFI_TPL_HIGH_LEVEL   TPL_HIGH_LEVEL

typedef EFI_TPL (*EFI_RAISE_TPL) (
    EFI_TPL      NewTpl
    );

typedef void (*EFI_RESTORE_TPL) (
    EFI_TPL      OldTpl
    );


//
// EFI platform varibles
//

#define EFI_GLOBAL_VARIABLE     \
    { 0x8BE4DF61, 0x93CA, 0x11d2, {0xAA, 0x0D, 0x00, 0xE0, 0x98, 0x03, 0x2B, 0x8C} }

// Variable attributes
#define EFI_VARIABLE_NON_VOLATILE                          0x00000001
#define EFI_VARIABLE_BOOTSERVICE_ACCESS                    0x00000002
#define EFI_VARIABLE_RUNTIME_ACCESS                        0x00000004
#define EFI_VARIABLE_HARDWARE_ERROR_RECORD                 0x00000008
#define EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS            0x00000010
#define EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS 0x00000020
#define EFI_VARIABLE_APPEND_WRITE                          0x00000040

// Variable size limitation
#define EFI_MAXIMUM_VARIABLE_SIZE           1024

typedef uintn (*EFI_GET_VARIABLE) (
    uint16                       *VariableName,
    EFI_GUID                     *VendorGuid,
    uint32                      *Attributes ,
    uintn                    *DataSize,
    void                        *Data
    );

typedef uintn (*EFI_GET_NEXT_VARIABLE_NAME) (
    uintn                    *VariableNameSize,
    uint16                   *VariableName,
    EFI_GUID                 *VendorGuid
    );


typedef uintn (*EFI_SET_VARIABLE) (
    uint16                       *VariableName,
    EFI_GUID                     *VendorGuid,
    uint32                       Attributes,
    uintn                        DataSize,
    void                         *Data
    );


//
// EFI Time
//

typedef struct {
        uint32                      Resolution;     // 1e-6 parts per million
        uint32                      Accuracy;       // hertz
        uint8                       SetsToZero;     // Set clears sub-second time
} EFI_TIME_CAPABILITIES;


typedef uintn (*EFI_GET_TIME) (
    EFI_TIME                    *Time,
    EFI_TIME_CAPABILITIES       *Capabilities 
    );

typedef uintn (*EFI_SET_TIME) (
    EFI_TIME                     *Time
    );

typedef uintn (*EFI_GET_WAKEUP_TIME) (
    uint8                       *Enabled,
    uint8                       *Pending,
    EFI_TIME                    *Time
    );

typedef uintn (*EFI_SET_WAKEUP_TIME) (
    uint8                        Enable,
    EFI_TIME                     *Time 
    );


//
// Image functions
//


// PE32+ Subsystem type for EFI images

#if !defined(IMAGE_SUBSYSTEM_EFI_APPLICATION)
#define IMAGE_SUBSYSTEM_EFI_APPLICATION             10
#define IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER     11
#define IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER          12
#endif

// PE32+ Machine type for EFI images

#if !defined(EFI_IMAGE_MACHINE_IA32)
#define EFI_IMAGE_MACHINE_IA32      0x014c
#endif

#if !defined(EFI_IMAGE_MACHINE_IA64)
#define EFI_IMAGE_MACHINE_IA64      0x0200
#endif

#if !defined(EFI_IMAGE_MACHINE_EBC)
#define EFI_IMAGE_MACHINE_EBC      0x0EBC
#endif

#if !defined(EFI_IMAGE_MACHINE_X64)
#define EFI_IMAGE_MACHINE_X64       0x8664
#endif

#if !defined(EFI_IMAGE_MACHINE_ARMTHUMB_MIXED)
#define EFI_IMAGE_MACHINE_ARMTHUMB_MIXED 0x01C2
#endif

#if !defined(EFI_IMAGE_MACHINE_AARCH64)
#define EFI_IMAGE_MACHINE_AARCH64   0xAA64
#endif

#if !defined(EFI_IMAGE_MACHINE_RISCV32)
#define EFI_IMAGE_MACHINE_RISCV32   0x5032
#endif

#if !defined(EFI_IMAGE_MACHINE_RISCV64)
#define EFI_IMAGE_MACHINE_RISCV64   0x5064
#endif

#if !defined(EFI_IMAGE_MACHINE_RISCV128)
#define EFI_IMAGE_MACHINE_RISCV128  0x5128
#endif

// Image Entry prototype

typedef uintn (*EFI_IMAGE_ENTRY_POINT) (
    EFI_HANDLE                   ImageHandle,
    struct _EFI_SYSTEM_TABLE     *SystemTable
    );

typedef uintn (*EFI_IMAGE_LOAD) (
    uint8                        BootPolicy,
    EFI_HANDLE                   ParentImageHandle,
    EFI_DEVICE_PATH              *FilePath,
    void                         *SourceBuffer   ,
    uintn                        SourceSize,
    EFI_HANDLE                  *ImageHandle
    );

typedef uintn (*EFI_IMAGE_START) (
    EFI_HANDLE                   ImageHandle,
    uintn                       *ExitDataSize,
    uint16                      **ExitData  
    );

typedef uintn (*EFI_EXIT) (
    EFI_HANDLE                   ImageHandle,
    uintn                   ExitStatus,
    uintn                        ExitDataSize,
    uint16                       *ExitData 
    );


// Image handle
/*#define LOADED_IMAGE_PROTOCOL      \
    { 0x5B1B31A1, 0x9562, 0x11d2, {0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B} }

#define EFI_IMAGE_INFORMATION_REVISION      0x1000
typedef struct {
    uint32                          Revision;
    EFI_HANDLE                      ParentHandle;
    struct _EFI_SYSTEM_TABLE        *SystemTable;

    // Source location of image
    EFI_HANDLE                      DeviceHandle;
    EFI_DEVICE_PATH                 *FilePath;
    void                            *Reserved;

    // Images load options
    uint32                          LoadOptionsSize;
    void                            *LoadOptions;

    // Location of where image was loaded
    void                            *ImageBase;
    uint64                          ImageSize;
    EFI_MEMORY_TYPE                 ImageCodeType;
    EFI_MEMORY_TYPE                 ImageDataType;

    // If the driver image supports a dynamic unload request
    EFI_IMAGE_UNLOAD                Unload;

} EFI_LOADED_IMAGE;*/


typedef uintn (*EFI_EXIT_BOOT_SERVICES) (
    EFI_HANDLE                   ImageHandle,
    uintn                        MapKey
    );

//
// Misc
//


typedef uintn (*EFI_STALL) (
    uintn                    Microseconds
    );

typedef uintn (*EFI_SET_WATCHDOG_TIMER) (
    uintn                    Timeout,
    uint64                   WatchdogCode,
    uintn                    DataSize,
    uint16                   *WatchdogData 
    );

typedef uintn (*EFI_CONNECT_CONTROLLER) (
    EFI_HANDLE               ControllerHandle,
    EFI_HANDLE               *DriverImageHandle ,
    EFI_DEVICE_PATH          *RemainingDevicePath ,
    uint8                    Recursive
    );

typedef uintn (*EFI_DISCONNECT_CONTROLLER) (
    EFI_HANDLE               ControllerHandle,
    EFI_HANDLE               DriverImageHandle ,
    EFI_HANDLE               ChildHandle 
    );

#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL  0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL        0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL       0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER 0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER           0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE           0x00000020

typedef uintn (*EFI_OPEN_PROTOCOL) (
    EFI_HANDLE               Handle,
    EFI_GUID                 *Protocol,
    void                    **Interface ,
    EFI_HANDLE               AgentHandle,
    EFI_HANDLE               ControllerHandle,
    uint32                   Attributes
    );

typedef uintn (*EFI_CLOSE_PROTOCOL) (
    EFI_HANDLE               Handle,
    EFI_GUID                 *Protocol,
    EFI_HANDLE               AgentHandle,
    EFI_HANDLE               ControllerHandle
    );

typedef struct {
    EFI_HANDLE                  AgentHandle;
    EFI_HANDLE                  ControllerHandle;
    uint32                      Attributes;
    uint32                      OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

typedef uintn (*EFI_OPEN_PROTOCOL_INFORMATION) (
    EFI_HANDLE               Handle,
    EFI_GUID                 *Protocol,
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer,
    uintn                   *EntryCount
    );

typedef uintn (*EFI_PROTOCOLS_PER_HANDLE) (
    EFI_HANDLE               Handle,
    EFI_GUID                ***ProtocolBuffer,
    uintn                   *ProtocolBufferCount
    );

typedef enum {
    AllHandles,
    ByRegisterNotify,
    ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

typedef uintn (*EFI_LOCATE_HANDLE_BUFFER) (
    EFI_LOCATE_SEARCH_TYPE   SearchType,
    EFI_GUID                 *Protocol ,
    void                     *SearchKey ,
    uintn                *NoHandles,
    EFI_HANDLE              **Buffer
    );

typedef uintn (*EFI_LOCATE_PROTOCOL) (
    EFI_GUID                 *Protocol,
    void                     *Registration ,
    void                    **Interface
    );

typedef uintn (*EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
    EFI_HANDLE           *Handle,
    ...
    );

typedef uintn (*EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
    EFI_HANDLE           Handle,
    ...
    );

typedef uintn (*EFI_CALCULATE_CRC32) (
    void                     *Data,
    uintn                    DataSize,
    uint32                  *Crc32
    );

typedef void (*EFI_COPY_MEM) (
    void                     *Destination,
    void                     *Source,
    uintn                    Length
    );

typedef void (*EFI_SET_MEM) (
    void                     *Buffer,
    uintn                    Size,
    uint8                    Value
    );


typedef uintn (*EFI_CREATE_EVENT_EX) (
    uint32                   Type,
    EFI_TPL                  NotifyTpl,
    EFI_EVENT_NOTIFY         NotifyFunction ,
    const void               *NotifyContext ,
    const EFI_GUID           *EventGroup ,
    EFI_EVENT               *Event
    );

typedef enum {
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown
} EFI_RESET_TYPE;

typedef uintn (*EFI_RESET_SYSTEM) (
    EFI_RESET_TYPE           ResetType,
    uintn               ResetStatus,
    uintn                    DataSize,
    uint16                   *ResetData 
    );

typedef uintn (*EFI_GET_NEXT_MONOTONIC_COUNT) (
    uint64                  *Count
    );

typedef uintn (*EFI_GET_NEXT_HIGH_MONO_COUNT) (
    uint32                  *HighCount
    );

typedef struct {
    uint64                      Length;
    union {
        EFI_PHYSICAL_ADDRESS    DataBlock;
       EFI_PHYSICAL_ADDRESS    ContinuationPointer;
    } Union;
} EFI_CAPSULE_BLOCK_DESCRIPTOR;

typedef struct {
    EFI_GUID                    CapsuleGuid;
    uint32                      HeaderSize;
    uint32                      Flags;
    uint32                      CapsuleImageSize;
} EFI_CAPSULE_HEADER;

#define CAPSULE_FLAGS_PERSIST_ACROSS_RESET    0x00010000
#define CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE   0x00020000
#define CAPSULE_FLAGS_INITIATE_RESET          0x00040000

typedef uintn (*EFI_UPDATE_CAPSULE) (
    EFI_CAPSULE_HEADER       **CapsuleHeaderArray,
    uintn                    CapsuleCount,
    EFI_PHYSICAL_ADDRESS     ScatterGatherList 
    );

typedef uintn (*EFI_QUERY_CAPSULE_CAPABILITIES) (
     EFI_CAPSULE_HEADER       **CapsuleHeaderArray,
     uintn                    CapsuleCount,
    uint64                   *MaximumCapsuleSize,
    EFI_RESET_TYPE           *ResetType
    );

typedef uintn (*EFI_QUERY_VARIABLE_INFO) (
     uint32                  Attributes,
    uint64                  *MaximumVariableStorageSize,
    uint64                  *RemainingVariableStorageSize,
    uint64                  *MaximumVariableSize
    );

//
// Protocol handler functions
//

typedef enum {
    EFI_NATIVE_INTERFACE,
    EFI_PCODE_INTERFACE
} EFI_INTERFACE_TYPE;

typedef uintn (*EFI_INSTALL_PROTOCOL_INTERFACE) (
    EFI_HANDLE           *Handle,
    EFI_GUID                 *Protocol,
    EFI_INTERFACE_TYPE       InterfaceType,
    void                     *Interface
    );

typedef uintn (*EFI_REINSTALL_PROTOCOL_INTERFACE) (
    EFI_HANDLE               Handle,
    EFI_GUID                 *Protocol,
    void                     *OldInterface,
    void                     *NewInterface
    );

typedef uintn (*EFI_UNINSTALL_PROTOCOL_INTERFACE) (
    EFI_HANDLE               Handle,
    EFI_GUID                 *Protocol,
    void                     *Interface
    );

typedef uintn (*EFI_HANDLE_PROTOCOL) (
    EFI_HANDLE               Handle,
    EFI_GUID                 *Protocol,
    void                    **Interface
    );

typedef uintn  (*EFI_REGISTER_PROTOCOL_NOTIFY) (
    EFI_GUID                 *Protocol,
    EFI_EVENT                Event,
    void                    **Registration
    );

typedef uintn (*EFI_LOCATE_HANDLE) (
    EFI_LOCATE_SEARCH_TYPE   SearchType,
    EFI_GUID                 *Protocol ,
    void                     *SearchKey ,
    uintn                *BufferSize,
    EFI_HANDLE              *Buffer
    );

typedef uintn (*EFI_LOCATE_DEVICE_PATH) (
    EFI_GUID                 *Protocol,
    EFI_DEVICE_PATH      **DevicePath,
    EFI_HANDLE              *Device
    );

typedef uintn (*EFI_INSTALL_CONFIGURATION_TABLE) (
    EFI_GUID                 *Guid,
    void                     *Table
    );

typedef uintn (*EFI_IMAGE_UNLOAD) (
    EFI_HANDLE                   ImageHandle
    );

typedef uintn (*EFI_RESERVED_SERVICE) (
    );

//
// Standard EFI table header
//

typedef struct _EFI_TABLE_HEADER {
    uint64                      Signature;
    uint32                      Revision;
    uint32                      HeaderSize;
    uint32                      CRC32;
    uint32                      Reserved;
} EFI_TABLE_HEADER;


//
// EFI Runtime Serivces Table
//

#define EFI_RUNTIME_SERVICES_SIGNATURE  0x56524553544e5552
#define EFI_RUNTIME_SERVICES_REVISION   (EFI_SPECIFICATION_MAJOR_REVISION<<16) | (EFI_SPECIFICATION_MINOR_REVISION)

typedef struct  {
    EFI_TABLE_HEADER                Hdr;

    //
    // Time services
    //

    EFI_GET_TIME                    GetTime;
    EFI_SET_TIME                    SetTime;
    EFI_GET_WAKEUP_TIME             GetWakeupTime;
    EFI_SET_WAKEUP_TIME             SetWakeupTime;

    //
    // Virtual memory services
    //

    EFI_SET_VIRTUAL_ADDRESS_MAP     SetVirtualAddressMap;
    EFI_CONVERT_POINTER             ConvertPointer;

    //
    // Variable serviers
    //

    EFI_GET_VARIABLE                GetVariable;
    EFI_GET_NEXT_VARIABLE_NAME      GetNextVariableName;
    EFI_SET_VARIABLE                SetVariable;

    //
    // Misc
    //

    EFI_GET_NEXT_HIGH_MONO_COUNT    GetNextHighMonotonicCount;
    EFI_RESET_SYSTEM                ResetSystem;

    EFI_UPDATE_CAPSULE              UpdateCapsule;
    EFI_QUERY_CAPSULE_CAPABILITIES  QueryCapsuleCapabilities;
    EFI_QUERY_VARIABLE_INFO         QueryVariableInfo;
} EFI_RUNTIME_SERVICES;


//
// EFI Boot Services Table
//

#define EFI_BOOT_SERVICES_SIGNATURE     0x56524553544f4f42
#define EFI_BOOT_SERVICES_REVISION      (EFI_SPECIFICATION_MAJOR_REVISION<<16) | (EFI_SPECIFICATION_MINOR_REVISION)

typedef struct _EFI_BOOT_SERVICES {

    EFI_TABLE_HEADER                Hdr;

    //
    // Task priority functions
    //

    EFI_RAISE_TPL                   RaiseTPL;
    EFI_RESTORE_TPL                 RestoreTPL;

    //
    // Memory functions
    //

    EFI_ALLOCATE_PAGES              AllocatePages;
    EFI_FREE_PAGES                  FreePages;
    EFI_GET_MEMORY_MAP              GetMemoryMap;
    EFI_ALLOCATE_POOL               AllocatePool;
    EFI_FREE_POOL                   FreePool;

    //
    // Event & timer functions
    //

    EFI_CREATE_EVENT                CreateEvent;
    EFI_SET_TIMER                   SetTimer;
    EFI_WAIT_FOR_EVENT              WaitForEvent;
    EFI_SIGNAL_EVENT                SignalEvent;
    EFI_CLOSE_EVENT                 CloseEvent;
    EFI_CHECK_EVENT                 CheckEvent;

    //
    // Protocol handler functions
    //

    EFI_INSTALL_PROTOCOL_INTERFACE  InstallProtocolInterface;
    EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface;
    EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface;
    EFI_HANDLE_PROTOCOL             HandleProtocol;
    EFI_HANDLE_PROTOCOL             PCHandleProtocol;
    EFI_REGISTER_PROTOCOL_NOTIFY    RegisterProtocolNotify;
    EFI_LOCATE_HANDLE               LocateHandle;
    EFI_LOCATE_DEVICE_PATH          LocateDevicePath;
    EFI_INSTALL_CONFIGURATION_TABLE InstallConfigurationTable;

    //
    // Image functions
    //

    EFI_IMAGE_LOAD                  LoadImage;
    EFI_IMAGE_START                 StartImage;
    EFI_EXIT                        Exit;
    EFI_IMAGE_UNLOAD                UnloadImage;
    EFI_EXIT_BOOT_SERVICES          ExitBootServices;

    //
    // Misc functions
    //

    EFI_GET_NEXT_MONOTONIC_COUNT    GetNextMonotonicCount;
    EFI_STALL                       Stall;
    EFI_SET_WATCHDOG_TIMER          SetWatchdogTimer;

    //
    // DriverSupport Services
    //

    EFI_CONNECT_CONTROLLER          ConnectController;
    EFI_DISCONNECT_CONTROLLER       DisconnectController;

    //
    // Open and Close Protocol Services
    //
    EFI_OPEN_PROTOCOL               OpenProtocol;
    EFI_CLOSE_PROTOCOL              CloseProtocol;
    EFI_OPEN_PROTOCOL_INFORMATION   OpenProtocolInformation;

    //
    // Library Services
    //
    EFI_PROTOCOLS_PER_HANDLE        ProtocolsPerHandle;
    EFI_LOCATE_HANDLE_BUFFER        LocateHandleBuffer;
    EFI_LOCATE_PROTOCOL             LocateProtocol;
    EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES InstallMultipleProtocolInterfaces;
    EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces;

    //
    // 32-bit CRC Services
    //
    EFI_CALCULATE_CRC32             CalculateCrc32;

    //
    // Misc Services
    //
    EFI_COPY_MEM                    CopyMem;
    EFI_SET_MEM                     SetMem;
    EFI_CREATE_EVENT_EX             CreateEventEx;
} EFI_BOOT_SERVICES;


//
// EFI Configuration Table and GUID definitions
//

#define MPS_TABLE_GUID    \
    { 0xeb9d2d2f, 0x2d88, 0x11d3, {0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d} }

#define ACPI_TABLE_GUID    \
    { 0xeb9d2d30, 0x2d88, 0x11d3, {0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d} }

#define ACPI_20_TABLE_GUID  \
    { 0x8868e871, 0xe4f1, 0x11d3, {0xbc, 0x22, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81} }

#define SMBIOS_TABLE_GUID    \
    { 0xeb9d2d31, 0x2d88, 0x11d3, {0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d} }

#define SMBIOS3_TABLE_GUID    \
    { 0xf2fd1544, 0x9794, 0x4a2c, {0x99, 0x2e, 0xe5, 0xbb, 0xcf, 0x20, 0xe3, 0x94} }

#define SAL_SYSTEM_TABLE_GUID    \
    { 0xeb9d2d32, 0x2d88, 0x11d3, {0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d} }

#define EFI_DTB_TABLE_GUID \
    { 0xb1b621d5, 0xf19c, 0x41a5, {0x83, 0x0b, 0xd9, 0x15, 0x2c, 0x69, 0xaa, 0xe0} }

typedef struct _EFI_CONFIGURATION_TABLE {
    EFI_GUID                VendorGuid;
    void                    *VendorTable;
} EFI_CONFIGURATION_TABLE;


//
// EFI System Table
//




#define EFI_SYSTEM_TABLE_SIGNATURE      0x5453595320494249
#define EFI_SYSTEM_TABLE_REVISION      (EFI_SPECIFICATION_MAJOR_REVISION<<16) | (EFI_SPECIFICATION_MINOR_REVISION)

typedef struct _EFI_SYSTEM_TABLE {
    EFI_TABLE_HEADER                Hdr;

    uint16                          *FirmwareVendor;
    uint32                          FirmwareRevision;

    EFI_HANDLE                      ConsoleInHandle;
    SIMPLE_INPUT_INTERFACE          *ConIn;

    EFI_HANDLE                      ConsoleOutHandle;
    SIMPLE_TEXT_OUTPUT_INTERFACE    *ConOut;

    EFI_HANDLE                      StandardErrorHandle;
    SIMPLE_TEXT_OUTPUT_INTERFACE    *StdErr;

    EFI_RUNTIME_SERVICES            *RuntimeServices;
    EFI_BOOT_SERVICES               *BootServices;

    uintn                           NumberOfTableEntries;
    EFI_CONFIGURATION_TABLE         *ConfigurationTable;

} EFI_SYSTEM_TABLE;


