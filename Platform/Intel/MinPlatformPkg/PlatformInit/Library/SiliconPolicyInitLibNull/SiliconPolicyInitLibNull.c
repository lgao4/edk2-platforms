/** @file

Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Library/SiliconPolicyInitLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>

VOID *
EFIAPI
SiliconPolicyInitPreMem (
  IN VOID *Policy
  )
{
  return Policy;
}

RETURN_STATUS
EFIAPI
SiliconPolicyDonePreMem (
  IN VOID *Policy
  )
{
  return RETURN_SUCCESS;
}

VOID *
EFIAPI
SiliconPolicyInitPostMem (
  IN VOID *Policy
  )
{
  return Policy;
}

RETURN_STATUS
EFIAPI
SiliconPolicyDonePostMem (
  IN VOID *Policy
  )
{
  return RETURN_SUCCESS;
}

VOID *
EFIAPI
SiliconPolicyInitLate (
  IN VOID *Policy
  )
{
  return Policy;
}

RETURN_STATUS
EFIAPI
SiliconPolicyDoneLate (
  IN VOID *Policy
  )
{
  return RETURN_SUCCESS;
}
