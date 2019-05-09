/** @file
  Default PCI Segment Information Library that returns one segment whose
  segment base address equals to PcdPciExpressBaseAddress.

  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials are
  licensed and made available under the terms and conditions of
  the BSD License which accompanies this distribution.  The full
  text of the license may be found at
  http://opensource.org/licenses/bsd-license.php.

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Base.h>
#include <Library/PciSegmentInfoLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/PcdLib.h>

#define PCI_SEGMENT_INFO_HOB_GUID { \
  0x6eab7169, 0x9b21, 0x450e, 0x99, 0xe8, 0xe, 0xb1, 0x1b, 0x7d, 0xfe, 0xcb \
  }

EFI_GUID  mPciSegmentInfoHobGuid = PCI_SEGMENT_INFO_HOB_GUID;

/**
  Return an array of PCI_SEGMENT_INFO holding the segment information.

  Note: The returned array/buffer is owned by callee.

  @param  Count  Return the count of segments.

  @retval A callee owned array holding the segment information.
**/
PCI_SEGMENT_INFO *
EFIAPI
GetPciSegmentInfo (
  OUT UINTN  *Count
  )
{
  VOID              *Hob;
  PCI_SEGMENT_INFO  *PciSegmentInfo;

  if (Count == NULL) {
    return NULL;
  }

  *Count = 1;
  Hob = GetFirstGuidHob (&mPciSegmentInfoHobGuid);
  if (Hob != NULL) {
    PciSegmentInfo = GET_GUID_HOB_DATA(Hob);
  } else {
    PciSegmentInfo = BuildGuidHob (&mPciSegmentInfoHobGuid, sizeof(PCI_SEGMENT_INFO));
    ASSERT(PciSegmentInfo != NULL);
    if (PciSegmentInfo == NULL) {
      return NULL;
    }
    PciSegmentInfo->SegmentNumber = 0;
    PciSegmentInfo->BaseAddress = PcdGet64(PcdPciExpressBaseAddress);
    PciSegmentInfo->StartBusNumber = 0;
    PciSegmentInfo->EndBusNumber = 0xFF;
  }
  return PciSegmentInfo;
}
