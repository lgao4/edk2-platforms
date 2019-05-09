/** @file
  Platform Hook Library instances

Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <PiPei.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/BoardInitLib.h>
#include <Library/MultiBoardInitSupportLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>

#include <KabylakeRvp3Id.h>

EFI_STATUS
EFIAPI
KabylakeRvp3BoardInitBeforeSiliconInit (
  VOID
  );

BOARD_POST_MEM_INIT_FUNC  mKabylakeRvp3BoardInitFunc = {
  KabylakeRvp3BoardInitBeforeSiliconInit,
  NULL, // BoardInitAfterSiliconInit
};

EFI_STATUS
EFIAPI
PeiKabylakeRvp3MultiBoardInitLibConstructor (
  VOID
  )
{
  if (LibPcdGetSku () == BoardIdKabyLakeYLpddr3Rvp3) {
    return RegisterBoardPostMemInit (&mKabylakeRvp3BoardInitFunc);
  }
  return EFI_SUCCESS;
}
