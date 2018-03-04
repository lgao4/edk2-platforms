/** @file
  BMC Event Log functions.

Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/IpmiCommandLib.h>

EFI_STATUS
EFIAPI
CheckIfSelIsFull (
  VOID
  );

/*++

  Routine Description:
    This function verifies the BMC SEL is full and When it is reports the error to the Error Manager.

  Arguments:
    None

  Returns:
    EFI_SUCCESS
    EFI_DEVICE_ERROR

--*/
EFI_STATUS
WaitTillErased (
  UINT8                                 *ResvId
  )
/*++

Routine Description:

Arguments:

  BmcElogPrivateData  - Bmc event log instance
  ResvId              - Reserved ID

Returns:

  EFI_SUCCESS
  EFI_NO_RESPONSE

--*/
{
  INTN                     Counter;
  IPMI_CLEAR_SEL_REQUEST   ClearSel;
  IPMI_CLEAR_SEL_RESPONSE  ClearSelResponse;

  Counter   = 0x200;

  while (TRUE) {
    ZeroMem (&ClearSel, sizeof(ClearSel));
    ClearSel.Reserve[0]  = ResvId[0];
    ClearSel.Reserve[1]  = ResvId[1];
    ClearSel.AscC        = 0x43;
    ClearSel.AscL        = 0x4C;
    ClearSel.AscR        = 0x52;
    ClearSel.Erase       = 0x00;

    IpmiClearSel (
      &ClearSel,
      &ClearSelResponse
      );

    if ((ClearSelResponse.ErasureProgress & 0xf) == 1) {
      return EFI_SUCCESS;
    }
    //
    //  If there is not a response from the BMC controller we need to return and not hang.
    //
    --Counter;
    if (Counter == 0x0) {
      return EFI_NO_RESPONSE;
    }
  }
}

EFI_STATUS
EfiActivateBmcElog (
  IN BOOLEAN                            *EnableElog,
  OUT BOOLEAN                           *ElogStatus
  )
/*++

Routine Description:

Arguments:

  This        - Protocol pointer
  DataType    - indicate event log type
  EnableElog  - Enable/Disable event log
  ElogStatus  - return log status

Returns:

  EFI_STATUS

--*/
{
  EFI_STATUS                           Status;
  UINT8                                ElogStat;
  IPMI_SET_BMC_GLOBAL_ENABLES_REQUEST  SetBmcGlobalEnables;
  IPMI_GET_BMC_GLOBAL_ENABLES_RESPONSE GetBmcGlobalEnables;
  UINT8                                CompletionCode;

  Status              = EFI_SUCCESS;
  ElogStat            = 0;

  Status = IpmiGetBmcGlobalEnables (&GetBmcGlobalEnables);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  if (EnableElog == NULL) {
    *ElogStatus = GetBmcGlobalEnables.SystemEventLogging;
  } else {
    if (Status == EFI_SUCCESS) {
      if (*EnableElog) {
        ElogStat = 1;
      }

      CopyMem (&SetBmcGlobalEnables, (UINT8 *)&GetBmcGlobalEnables + sizeof(UINT8), sizeof(UINT8));
      SetBmcGlobalEnables.EnableSystemEventLogging = ElogStat;

      Status = IpmiSetBmcGlobalEnables (&SetBmcGlobalEnables, &CompletionCode);
    }
  }

  return Status;
}

EFI_STATUS
SetElogRedirInstall (
  VOID
  )
/*++

Routine Description:

Arguments:

  None

Returns:

  EFI_SUCCESS

--*/
{
  BOOLEAN     EnableElog;
  BOOLEAN     ElogStatus;

  //
  // Activate the Event Log (This should depend upon Setup).
  //
  EfiActivateBmcElog (&EnableElog, &ElogStatus);
  return EFI_SUCCESS;
}

EFI_STATUS
InitializeBmcElogLayer (
  IN EFI_HANDLE             ImageHandle,
  IN EFI_SYSTEM_TABLE       *SystemTable
  )
/*++

Routine Description:

Arguments:

  ImageHandle - ImageHandle of the loaded driver
  SystemTable - Pointer to the System Table

Returns:

  EFI_STATUS

--*/
{
  SetElogRedirInstall ();

  CheckIfSelIsFull ();

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
CheckIfSelIsFull (
  VOID
  )
/*++

  Routine Description:
    This function verifies the BMC SEL is full and When it is reports the error to the Error Manager.

  Arguments:
    None

  Returns:
    EFI_SUCCESS
    EFI_DEVICE_ERROR

--*/
{
  EFI_STATUS                  Status;
  UINT8                       SelIsFull;
  IPMI_GET_SEL_INFO_RESPONSE  SelInfo;

  Status = IpmiGetSelInfo (&SelInfo);
  if (EFI_ERROR (Status)) {
    return EFI_DEVICE_ERROR;
  }

  //
  // Check the Bit7 of the OperationByte if SEL is OverFlow.
  //
  SelIsFull = (SelInfo.OperationSupport & 0x80);
  DEBUG ((DEBUG_INFO, "SelIsFull - 0x%x\n", SelIsFull));

  return EFI_SUCCESS;
}
