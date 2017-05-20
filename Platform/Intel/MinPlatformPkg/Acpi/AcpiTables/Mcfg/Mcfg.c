/** @file
  This file contains a structure definition for the ACPI Memory Mapped Configuration
  Address Space table (MCFG).  Any changes to the number of entries in the table require
  updating the structure count in Mcfg.h and then adding the structure to the
  MCFG defined in this file.  The table layout is defined in Mcfg.h and the
  table contents are defined in the MemoryMappedConfigurationSpaceAccessTable.h.

Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

//
// Statements that include other files
//

#include "Mcfg.h"

//
// Multiple APIC Description Table
//

EFI_ACPI_MEMORY_MAPPED_CONFIGURATION_SPACE_ACCESS_DESCRIPTION_TABLE Mcfg = {
  {
    EFI_ACPI_3_0_PCI_EXPRESS_MEMORY_MAPPED_CONFIGURATION_SPACE_BASE_ADDRESS_DESCRIPTION_TABLE_SIGNATURE,
    sizeof (EFI_ACPI_MEMORY_MAPPED_CONFIGURATION_SPACE_ACCESS_DESCRIPTION_TABLE),
    EFI_ACPI_MEMORY_MAPPED_CONFIGURATION_SPACE_ACCESS_TABLE_REVISION,

    //
    // Checksum will be updated at runtime
    //
    0x00,

    //
    // It is expected that these values will be programmed at runtime
    //
    { ' ', ' ', ' ', ' ', ' ', ' ' },

    0,
    EFI_ACPI_OEM_MCFG_REVISION,
    0,
    0
  },

  //
  // Reserved
  //
  0x0000000000000000,

  //
  // MCFG specific fields
  //
  {
    {
      //
      // Sample Base Address Structure
      //
      //0x0000000000000000,                                           // BaseAddress
      //0x0000,                                                       // PciSegmentGroupNumber
      //0x00,                                                         // StartBusNumber
      //0x00,                                                         // EndBusNumber
      //0x00000000,                                                   // Reserved

      FixedPcdGet64 (PcdPciExpressBaseAddress),                       // BaseAddress
      0x0000,                                                         // PciSegmentGroupNumber
      0x00,                                                           // StartBusNumber
      ((FixedPcdGet32 (PcdPciExpressRegionLength) / 0x100000) - 1),   // EndBusNumber
      0x00000000                                                      // Reserved
    }
  }
};

