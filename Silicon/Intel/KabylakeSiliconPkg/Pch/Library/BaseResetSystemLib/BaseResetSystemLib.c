/** @file
  System reset library services.

Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/PciLib.h>
#include <Library/ResetSystemLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <PchAccess.h>

GLOBAL_REMOVE_IF_UNREFERENCED UINT16           mBaseResetSystemABase;

/**
  Calling this function causes a system-wide reset. This sets
  all circuitry within the system to its initial state. This type of reset
  is asynchronous to system operation and operates without regard to
  cycle boundaries.

  System reset should not return, if it returns, it means the system does
  not support cold reset.
**/
VOID
EFIAPI
ResetCold (
  VOID
  )
{
  IoWrite8 (R_PCH_RST_CNT, V_PCH_RST_CNT_FULLRESET);
}

/**
  Calling this function causes a system-wide initialization. The processors
  are set to their initial state, and pending cycles are not corrupted.

  System reset should not return, if it returns, it means the system does
  not support warm reset.
**/
VOID
EFIAPI
ResetWarm (
  VOID
  )
{
  IoWrite8 (R_PCH_RST_CNT, V_PCH_RST_CNT_HARDRESET);
}

/**
  Calling this function causes the system to enter a power state equivalent
  to the ACPI G2/S5 or G3 states.

  System shutdown should not return, if it returns, it means the system does
  not support shut down reset.
**/
VOID
EFIAPI
ResetShutdown (
  VOID
  )
{
  UINT16         ABase;
  UINT32         Data32;

  ABase = mBaseResetSystemABase;
  if (ABase == 0) {
    PchAcpiBaseGet (&ABase);
  }
  ///
  /// Firstly, GPE0_EN should be disabled to avoid any GPI waking up the system from S5
  ///
  IoWrite32 ((UINTN) (ABase + R_PCH_ACPI_GPE0_EN_127_96), 0);

  ///
  /// Secondly, PwrSts register must be cleared
  ///
  /// Write a "1" to bit[8] of power button status register at
  /// (PM_BASE + PM1_STS_OFFSET) to clear this bit
  ///
  IoWrite16 ((UINTN) (ABase + R_PCH_ACPI_PM1_STS), B_PCH_ACPI_PM1_STS_PWRBTN);

  ///
  /// Finally, transform system into S5 sleep state
  ///
  Data32 = IoRead32 ((UINTN) (ABase + R_PCH_ACPI_PM1_CNT));

  Data32 = (UINT32) ((Data32 &~(B_PCH_ACPI_PM1_CNT_SLP_TYP + B_PCH_ACPI_PM1_CNT_SLP_EN)) | V_PCH_ACPI_PM1_CNT_S5);

  IoWrite32 ((UINTN) (ABase + R_PCH_ACPI_PM1_CNT), Data32);

  Data32 = Data32 | B_PCH_ACPI_PM1_CNT_SLP_EN;

  IoWrite32 ((UINTN) (ABase + R_PCH_ACPI_PM1_CNT), Data32);

  return;
}

/**
  Calling this function causes the system to enter a power state for platform specific.

  @param[in] ResetStatus          The status code for the reset.
  @param[in] DataSize             The size of ResetData in bytes.
  @param[in] ResetData            Optional element used to introduce a platform specific reset.
                                  The exact type of the reset is defined by the EFI_GUID that follows
                                  the Null-terminated Unicode string.

**/
VOID
EFIAPI
ResetPlatformSpecific (
  IN EFI_STATUS       ResetStatus,
  IN UINTN            DataSize,
  IN VOID             *ResetData OPTIONAL
  )
{
  IoWrite8 (R_PCH_RST_CNT, V_PCH_RST_CNT_FULLRESET);
}

/**
  Calling this function causes the system to enter a power state for capsule update.

  Reset update should not return, if it returns, it means the system does
  not support capsule update.

**/
VOID
EFIAPI
EnterS3WithImmediateWake (
  VOID
  )
{
  ASSERT (FALSE);
}

/**
  The library constructuor.

  The function does the necessary initialization work for this library instance.

  @retval     EFI_SUCCESS       The function always return EFI_SUCCESS for now.
**/
EFI_STATUS
EFIAPI
BaseResetSystemLibConstructor (
  VOID
  )
{
  PchAcpiBaseGet (&mBaseResetSystemABase);

  return EFI_SUCCESS;
}
