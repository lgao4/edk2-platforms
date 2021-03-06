/** @file
  Main System Agent Policy structure definition which will contain several config blocks during runtime.

Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
#ifndef _SA_POLICY_COMMON_H_
#define _SA_POLICY_COMMON_H_

#include <Uefi.h>
#include <Library/SmbusLib.h>
#include <SaAccess.h>
#include <ConfigBlock.h>
#include <Library/ConfigBlockLib.h>
#include <ConfigBlock/MemoryConfig.h>
#include <ConfigBlock/SaMiscPeiPreMemConfig.h>
#include <ConfigBlock/GraphicsPeiConfig.h>
#include <ConfigBlock/VtdConfig.h>



//
// Extern the GUID for PPI users.
//
extern EFI_GUID gSiPolicyPpiGuid;
extern EFI_GUID gSiPreMemPolicyPpiGuid;
extern EFI_GUID gSaMiscPeiPreMemConfigGuid;
extern EFI_GUID gGraphicsPeiConfigGuid;
extern EFI_GUID gVtdConfigGuid;
extern EFI_GUID gMemoryConfigGuid;
extern EFI_GUID gMemoryConfigNoCrcGuid;

#endif // _SA_POLICY_COMMON_H_
