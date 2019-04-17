/** @file

Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Uefi.h>
#include <PiDxe.h>
#include <Library/TestPointCheckLib.h>
#include <Library/TestPointLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DevicePathLib.h>
#include <Library/PeCoffGetEntryPointLib.h>
#include <Protocol/LoadedImage.h>

BOOLEAN
IsRuntimeImage (
  IN VOID  *Pe32Data
  )
{
  EFI_IMAGE_DOS_HEADER                  *DosHdr;
  EFI_IMAGE_OPTIONAL_HEADER_PTR_UNION   Hdr;
  UINT16                                Magic;
  UINT16                                Subsystem;

  ASSERT (Pe32Data   != NULL);

  DosHdr = (EFI_IMAGE_DOS_HEADER *)Pe32Data;
  if (DosHdr->e_magic == EFI_IMAGE_DOS_SIGNATURE) {
    //
    // DOS image header is present, so read the PE header after the DOS image header.
    //
    Hdr.Pe32 = (EFI_IMAGE_NT_HEADERS32 *)((UINTN) Pe32Data + (UINTN) ((DosHdr->e_lfanew) & 0x0ffff));
  } else {
    //
    // DOS image header is not present, so PE header is at the image base.
    //
    Hdr.Pe32 = (EFI_IMAGE_NT_HEADERS32 *)Pe32Data;
  }

  if (Hdr.Pe32->Signature == EFI_IMAGE_NT_SIGNATURE) {
    //
    // NOTE: We use Machine field to identify PE32/PE32+, instead of Magic.
    //       It is due to backward-compatibility, for some system might
    //       generate PE32+ image with PE32 Magic.
    //
    switch (Hdr.Pe32->FileHeader.Machine) {
    case IMAGE_FILE_MACHINE_I386:
      //
      // Assume PE32 image with IA32 Machine field.
      //
      Magic = EFI_IMAGE_NT_OPTIONAL_HDR32_MAGIC;
      break;
    case IMAGE_FILE_MACHINE_X64:
    case IMAGE_FILE_MACHINE_IA64:
      //
      // Assume PE32+ image with x64 or IA64 Machine field
      //
      Magic = EFI_IMAGE_NT_OPTIONAL_HDR64_MAGIC;
      break;
    default:
      //
      // For unknow Machine field, use Magic in optional Header
      //
      Magic = Hdr.Pe32->OptionalHeader.Magic;
    }

    if (Magic == EFI_IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
      Subsystem = Hdr.Pe32->OptionalHeader.Subsystem;
    } else if (Hdr.Pe32->OptionalHeader.Magic == EFI_IMAGE_NT_OPTIONAL_HDR64_MAGIC) {
      Subsystem = Hdr.Pe32Plus->OptionalHeader.Subsystem;
    }
    if (Subsystem == EFI_IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER) {
      return TRUE;
    }
  }

  return FALSE;
}

VOID
DumpLoadedImage (
  IN UINTN                                  Index,
  IN EFI_LOADED_IMAGE_PROTOCOL              *LoadedImage,
  IN EFI_DEVICE_PATH_PROTOCOL               *DevicePath,
  IN EFI_DEVICE_PATH_PROTOCOL               *LoadedImageDevicePath
  )
{
  CHAR16                            *Str;
  CHAR8                             *PdbPointer;

  DEBUG ((DEBUG_INFO, "[0x%04x]:", Index));
  if (IsRuntimeImage (LoadedImage->ImageBase)) {
    DEBUG ((DEBUG_INFO, " (RT)"));
  } else {
    DEBUG ((DEBUG_INFO, "     "));
  }
  DEBUG ((DEBUG_INFO, " 0x%016lx-0x%016lx", (UINT64)(UINTN)LoadedImage->ImageBase, LoadedImage->ImageSize));

  if (LoadedImageDevicePath != NULL) {
    Str = ConvertDevicePathToText(LoadedImageDevicePath, TRUE, TRUE);
    DEBUG ((DEBUG_INFO, " LoadedImageDevicePath=%s", Str));
    if (Str != NULL) {
      FreePool (Str);
    }
  } else {
    if (LoadedImage->FilePath != NULL) {
      Str = ConvertDevicePathToText(LoadedImage->FilePath, TRUE, TRUE);
      DEBUG ((DEBUG_INFO, " FilePath=%s", Str));
      if (Str != NULL) {
        FreePool (Str);
      }
    }

    if (DevicePath != NULL) {
      Str = ConvertDevicePathToText(DevicePath, TRUE, TRUE);
      DEBUG ((DEBUG_INFO, " DevicePath=%s", Str));
      if (Str != NULL) {
        FreePool (Str);
      }
    }
  }

  PdbPointer = PeCoffLoaderGetPdbPointer (LoadedImage->ImageBase);
  if (PdbPointer != NULL) {
    DEBUG ((DEBUG_INFO, " (pdb - %a)", PdbPointer));
  }

  DEBUG ((DEBUG_INFO, "\n"));
}

EFI_STATUS
TestPointDumpLoadedImage (
  VOID
  )
{
  EFI_STATUS                             Status;
  EFI_LOADED_IMAGE_PROTOCOL              *LoadedImage;
  UINTN                                  Index;
  EFI_HANDLE                             *HandleBuf;
  UINTN                                  HandleCount;
  EFI_DEVICE_PATH_PROTOCOL               *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL               *LoadedImageDevicePath;
  
  DEBUG ((DEBUG_INFO, "==== TestPointDumpLoadedImage - Enter\n"));
  HandleBuf = NULL;
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiLoadedImageProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuf
                  );
  if (EFI_ERROR (Status)) {
    goto Done ;
  }
  
  DEBUG ((DEBUG_INFO, "LoadedImage (%d):\n", HandleCount));
  for (Index = 0; Index < HandleCount; Index++) {
    Status = gBS->HandleProtocol (
                    HandleBuf[Index],
                    &gEfiLoadedImageProtocolGuid,
                    (VOID **)&LoadedImage
                    );
    if (EFI_ERROR(Status)) {
      continue;
    }

    Status = gBS->HandleProtocol (LoadedImage->DeviceHandle, &gEfiDevicePathProtocolGuid, (VOID **)&DevicePath);
    if (EFI_ERROR(Status)) {
      DevicePath = NULL;
    }

    Status = gBS->HandleProtocol (HandleBuf[Index], &gEfiLoadedImageDevicePathProtocolGuid, (VOID **)&LoadedImageDevicePath);
    if (EFI_ERROR(Status)) {
      LoadedImageDevicePath = NULL;
    }

    DumpLoadedImage (Index, LoadedImage, DevicePath, LoadedImageDevicePath);
  }

Done:

  if (HandleBuf != NULL) {
    FreePool (HandleBuf);
  }

  DEBUG ((DEBUG_INFO, "==== TestPointDumpLoadedImage - Exit\n"));

  // Check - TBD
  return EFI_SUCCESS;
}
