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
#include <Library/UefiBootServicesTableLib.h>
#include <Library/TestPointCheckLib.h>
#include <Library/TestPointLib.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>

CHAR8 *mMemoryTypeShortName[] = {
  "Reserved  ",
  "LoaderCode",
  "LoaderData",
  "BS_Code   ",
  "BS_Data   ",
  "RT_Code   ",
  "RT_Data   ",
  "Available ",
  "Unusable  ",
  "ACPI_Recl ",
  "ACPI_NVS  ",
  "MMIO      ",
  "MMIO_Port ",
  "PalCode   ",
  "Persistent",
};

CHAR8 mUnknownStr[11];

CHAR8 *
ShortNameOfMemoryType(
  IN UINT32 Type
  )
{
  if (Type < sizeof(mMemoryTypeShortName) / sizeof(mMemoryTypeShortName[0])) {
    return mMemoryTypeShortName[Type];
  } else {
    AsciiSPrint(mUnknownStr, sizeof(mUnknownStr), "[%08x]", Type);
    return mUnknownStr;
  }
}


/**
  Dump memory map.

  @param  MemoryMap              A pointer to the buffer in which firmware places
                                 the current memory map.
  @param  MemoryMapSize          Size, in bytes, of the MemoryMap buffer.
  @param  DescriptorSize         Size, in bytes, of an individual EFI_MEMORY_DESCRIPTOR.
**/
VOID
DumpMemoryMap (
  IN EFI_MEMORY_DESCRIPTOR  *MemoryMap,
  IN UINTN                  MemoryMapSize,
  IN UINTN                  DescriptorSize
  )
{
  EFI_MEMORY_DESCRIPTOR *Entry;
  UINTN                 NumberOfEntries;
  UINTN                 Index;
  UINT64                Pages[EfiMaxMemoryType];

  ZeroMem (Pages, sizeof(Pages));

  DEBUG ((EFI_D_INFO, "MemoryMap:\n"));
  
  Entry = MemoryMap;
  NumberOfEntries = MemoryMapSize / DescriptorSize;
  DEBUG ((DEBUG_INFO, "Type       Start            End              # Pages          Attributes\n"));
  for (Index = 0; Index < NumberOfEntries; Index++) {
    DEBUG ((DEBUG_INFO, ShortNameOfMemoryType(Entry->Type)));
    DEBUG ((DEBUG_INFO, " %016LX-%016LX %016LX %016LX\n",
      Entry->PhysicalStart,
      Entry->PhysicalStart+MultU64x64 (SIZE_4KB,Entry->NumberOfPages) - 1,
      Entry->NumberOfPages,
      Entry->Attribute
      ));
    if (Entry->Type < EfiMaxMemoryType) {
      Pages[Entry->Type] += Entry->NumberOfPages;
    }
    Entry = NEXT_MEMORY_DESCRIPTOR (Entry, DescriptorSize);
  }

  DEBUG ((DEBUG_INFO, "\n"));
  DEBUG ((DEBUG_INFO, "  Reserved  : %14ld Pages (%ld Bytes)\n", Pages[EfiReservedMemoryType],      MultU64x64(SIZE_4KB, Pages[EfiReservedMemoryType])));
  DEBUG ((DEBUG_INFO, "  LoaderCode: %14ld Pages (%ld Bytes)\n", Pages[EfiLoaderCode],              MultU64x64(SIZE_4KB, Pages[EfiLoaderCode])));
  DEBUG ((DEBUG_INFO, "  LoaderData: %14ld Pages (%ld Bytes)\n", Pages[EfiLoaderData],              MultU64x64(SIZE_4KB, Pages[EfiLoaderData])));
  DEBUG ((DEBUG_INFO, "  BS_Code   : %14ld Pages (%ld Bytes)\n", Pages[EfiBootServicesCode],        MultU64x64(SIZE_4KB, Pages[EfiBootServicesCode])));
  DEBUG ((DEBUG_INFO, "  BS_Data   : %14ld Pages (%ld Bytes)\n", Pages[EfiBootServicesData],        MultU64x64(SIZE_4KB, Pages[EfiBootServicesData])));
  DEBUG ((DEBUG_INFO, "  RT_Code   : %14ld Pages (%ld Bytes)\n", Pages[EfiRuntimeServicesCode],     MultU64x64(SIZE_4KB, Pages[EfiRuntimeServicesCode])));
  DEBUG ((DEBUG_INFO, "  RT_Data   : %14ld Pages (%ld Bytes)\n", Pages[EfiRuntimeServicesData],     MultU64x64(SIZE_4KB, Pages[EfiRuntimeServicesData])));
  DEBUG ((DEBUG_INFO, "  ACPI_Recl : %14ld Pages (%ld Bytes)\n", Pages[EfiACPIReclaimMemory],       MultU64x64(SIZE_4KB, Pages[EfiACPIReclaimMemory])));
  DEBUG ((DEBUG_INFO, "  ACPI_NVS  : %14ld Pages (%ld Bytes)\n", Pages[EfiACPIMemoryNVS],           MultU64x64(SIZE_4KB, Pages[EfiACPIMemoryNVS])));
  DEBUG ((DEBUG_INFO, "  MMIO      : %14ld Pages (%ld Bytes)\n", Pages[EfiMemoryMappedIO],          MultU64x64(SIZE_4KB, Pages[EfiMemoryMappedIO])));
  DEBUG ((DEBUG_INFO, "  MMIO_Port : %14ld Pages (%ld Bytes)\n", Pages[EfiMemoryMappedIOPortSpace], MultU64x64(SIZE_4KB, Pages[EfiMemoryMappedIOPortSpace])));
  DEBUG ((DEBUG_INFO, "  PalCode   : %14ld Pages (%ld Bytes)\n", Pages[EfiPalCode],                 MultU64x64(SIZE_4KB, Pages[EfiPalCode])));
  DEBUG ((DEBUG_INFO, "  Available : %14ld Pages (%ld Bytes)\n", Pages[EfiConventionalMemory],      MultU64x64(SIZE_4KB, Pages[EfiConventionalMemory])));
  DEBUG ((DEBUG_INFO, "  Persistent: %14ld Pages (%ld Bytes)\n", Pages[EfiPersistentMemory],        MultU64x64(SIZE_4KB, Pages[EfiPersistentMemory])));
  DEBUG ((DEBUG_INFO, "              -------------- \n"));
}

BOOLEAN
IsGoodMemoryMap (
  IN EFI_MEMORY_DESCRIPTOR  *MemoryMap,
  IN UINTN                  MemoryMapSize,
  IN UINTN                  DescriptorSize
  )
{
  EFI_MEMORY_DESCRIPTOR *Entry;
  UINTN                 NumberOfEntries;
  UINTN                 Index;
  UINT64                EntryCount[EfiMaxMemoryType];

  ZeroMem (EntryCount, sizeof(EntryCount));

  Entry = MemoryMap;
  NumberOfEntries = MemoryMapSize / DescriptorSize;
  for (Index = 0; Index < NumberOfEntries; Index++) {
    if (Entry->Type < EfiMaxMemoryType) {
      EntryCount[Entry->Type] ++;
    }
    Entry = NEXT_MEMORY_DESCRIPTOR (Entry, DescriptorSize);
  }
  if ((EntryCount[EfiRuntimeServicesCode] > 1) ||
      (EntryCount[EfiRuntimeServicesData] > 1) ||
      (EntryCount[EfiACPIReclaimMemory] > 1) ||
      (EntryCount[EfiACPIMemoryNVS] > 1) ) {
    return FALSE;
  } else {
    return TRUE;
  }
}

EFI_STATUS
TestPointDumpMemMap (
  VOID
  )
{
  EFI_STATUS            Status;
  UINTN                 MapKey;
  UINT32                DescriptorVersion;
  EFI_MEMORY_DESCRIPTOR *MemoryMap;
  UINTN                 UefiMemoryMapSize;
  UINTN                 UefiDescriptorSize;
  BOOLEAN               Result;
  
  DEBUG ((DEBUG_INFO, "==== TestPointDumpMemMap - Enter\n"));
  UefiMemoryMapSize = 0;
  MemoryMap = NULL;
  Status = gBS->GetMemoryMap (
                  &UefiMemoryMapSize,
                  MemoryMap,
                  &MapKey,
                  &UefiDescriptorSize,
                  &DescriptorVersion
                  );
  ASSERT (Status == EFI_BUFFER_TOO_SMALL);

  do {
    Status = gBS->AllocatePool (EfiBootServicesData, UefiMemoryMapSize, (VOID **)&MemoryMap);
    ASSERT (MemoryMap != NULL);
    if (MemoryMap == NULL) {
      Status = EFI_OUT_OF_RESOURCES;
      goto Done ;
    }

    Status = gBS->GetMemoryMap (
                    &UefiMemoryMapSize,
                    MemoryMap,
                    &MapKey,
                    &UefiDescriptorSize,
                    &DescriptorVersion
                    );
    if (EFI_ERROR (Status)) {
      gBS->FreePool (MemoryMap);
      MemoryMap = NULL;
    }
  } while (Status == EFI_BUFFER_TOO_SMALL);

  if (MemoryMap == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Done ;
  }
  
  DumpMemoryMap (MemoryMap, UefiMemoryMapSize, UefiDescriptorSize);

  Result = IsGoodMemoryMap (MemoryMap, UefiMemoryMapSize, UefiDescriptorSize);
  if (!Result) {
    TestPointLibAppendErrorString (
      PLATFORM_TEST_POINT_ROLE_PLATFORM_IBV,
      NULL,
      TEST_POINT_BYTE2_END_OF_DXE_ERROR_CODE_2 TEST_POINT_END_OF_DXE TEST_POINT_BYTE2_END_OF_DXE_ERROR_STRING_2
      );
    Status = EFI_INVALID_PARAMETER;
  } else {
    Status = EFI_SUCCESS;
  }

  gBS->FreePool (MemoryMap);

Done:
  DEBUG ((DEBUG_INFO, "==== TestPointDumpMemMap - Exit\n"));
  return Status;
}
