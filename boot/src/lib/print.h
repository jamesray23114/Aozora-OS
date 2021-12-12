#pragma once

#include <efi.h>
#include <efilib.h>

struct {
    EFI_STATUS      Code;
    WCHAR	        *Desc;
} Etable[] = {
	{  EFI_SUCCESS,                L"Success\n"},
	{  EFI_LOAD_ERROR,             L"Load Error\n"},
	{  EFI_INVALID_PARAMETER,      L"Invalid Parameter\n"},
	{  EFI_UNSUPPORTED,            L"Unsupported\n"},
	{  EFI_BAD_BUFFER_SIZE,        L"Bad Buffer Size\n"},
	{  EFI_BUFFER_TOO_SMALL,       L"Buffer Too Small\n"},
	{  EFI_NOT_READY,              L"Not Ready\n"},
	{  EFI_DEVICE_ERROR,           L"Device Error\n"},
	{  EFI_WRITE_PROTECTED,        L"Write Protected\n"},
	{  EFI_OUT_OF_RESOURCES,       L"Out of Resources\n"},
	{  EFI_VOLUME_CORRUPTED,       L"Volume Corrupt\n"},
	{  EFI_VOLUME_FULL,            L"Volume Full\n"},
	{  EFI_NO_MEDIA,               L"No Media\n"},
	{  EFI_MEDIA_CHANGED,          L"Media changed\n"},
	{  EFI_NOT_FOUND,              L"Not Found\n"},
	{  EFI_ACCESS_DENIED,          L"Access Denied\n"},
	{  EFI_NO_RESPONSE,            L"No Response\n"},
	{  EFI_NO_MAPPING,             L"No mapping\n"},
	{  EFI_TIMEOUT,                L"Time out\n"},
	{  EFI_NOT_STARTED,            L"Not started\n"},
	{  EFI_ALREADY_STARTED,        L"Already started\n"},
	{  EFI_ABORTED,                L"Aborted\n"},
	{  EFI_ICMP_ERROR,             L"ICMP Error\n"},
	{  EFI_TFTP_ERROR,             L"TFTP Error\n"},
	{  EFI_PROTOCOL_ERROR,         L"Protocol Error\n"},
	{  EFI_INCOMPATIBLE_VERSION,   L"Incompatible Version\n"},
	{  EFI_SECURITY_VIOLATION,     L"Security Policy Violation\n"},
	{  EFI_CRC_ERROR,              L"CRC Error\n"},
	{  EFI_END_OF_MEDIA,           L"End of Media\n"},
	{  EFI_END_OF_FILE,            L"End of File\n"},
	{  EFI_INVALID_LANGUAGE,       L"Invalid Languages\n"},
	{  EFI_COMPROMISED_DATA,       L"Compromised Data\n"},

	// warnings
	{  EFI_WARN_UNKNOWN_GLYPH,     L"Warning Unknown Glyph\n"},
	{  EFI_WARN_DELETE_FAILURE,    L"Warning Delete Failure\n"},
	{  EFI_WARN_WRITE_FAILURE,     L"Warning Write Failure\n"},
	{  EFI_WARN_BUFFER_TOO_SMALL,  L"Warning Buffer Too Small\n"},
	{  0, NULL}
};

void errstrcpy(CHAR16 *Buffer, EFI_STATUS Status)
{
    for (int Index = 0; Etable[Index].Desc; Index +=1) {
        if (Etable[Index].Code == Status) {

            for(int i = 0; Etable[Index].Desc[i]; i++)
            {
                Buffer[i] = Etable[Index].Desc[i];
            }
	        return;
        }
    }
}

void print_efi_status(EFI_STATUS status)
{
    WCHAR buf[256] = {0};
    errstrcpy(buf, status);

    ST->ConOut->OutputString(ST->ConOut, buf);
}