/** @file

Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef   __SOCKET_PCI_RESOURCE_CONFIG_DATA_H__
#define   __SOCKET_PCI_RESOURCE_CONFIG_DATA_H__


#include <UncoreCommonIncludes.h>
#include "SocketConfiguration.h"

extern EFI_GUID gEfiSocketPciResourceDataGuid;
#define SOCKET_PCI_RESOURCE_CONFIGURATION_DATA_NAME L"SocketPciResourceConfigData"

#pragma pack(1)
typedef struct {
  //
  // Used by the PciHostBridge DXE driver, these variables don't need to be exposed through setup options
  // The variables are used as a communication vehicle from the PciHostBridge DXE driver to an OEM hook
  // which updates the KTI resource map
  //
  UINT16  PciSocketIoBase[MAX_SOCKET];
  UINT16  PciSocketIoLimit[MAX_SOCKET];
  UINT32  PciSocketMmiolBase[MAX_SOCKET];
  UINT32  PciSocketMmiolLimit[MAX_SOCKET];
  UINT64  PciSocketMmiohBase[MAX_SOCKET];
  UINT64  PciSocketMmiohLimit[MAX_SOCKET];
  UINT16  PciResourceIoBase[TOTAL_IIO_STACKS];
  UINT16  PciResourceIoLimit[TOTAL_IIO_STACKS];
  UINT32  PciResourceMem32Base[TOTAL_IIO_STACKS];
  UINT32  PciResourceMem32Limit[TOTAL_IIO_STACKS];
  UINT64  PciResourceMem64Base[TOTAL_IIO_STACKS];
  UINT64  PciResourceMem64Limit[TOTAL_IIO_STACKS];
} SOCKET_PCI_RESOURCE_CONFIGURATION_DATA;
#pragma pack()

#endif // __SOCKET_PCI_RESOURCE_CONFIG_DATA_H__


