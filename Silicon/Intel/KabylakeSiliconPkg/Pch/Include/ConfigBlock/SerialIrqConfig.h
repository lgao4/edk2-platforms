/** @file
  Serial IRQ policy

Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
#ifndef _SERIAL_IRQ_CONFIG_H_
#define _SERIAL_IRQ_CONFIG_H_

#define SERIAL_IRQ_CONFIG_REVISION 1
extern EFI_GUID gSerialIrqConfigGuid;

#pragma pack (push,1)

typedef enum {
  PchQuietMode,
  PchContinuousMode
} PCH_SIRQ_MODE;
///
/// Refer to PCH EDS for the details of Start Frame Pulse Width in Continuous and Quiet mode
///
typedef enum {
  PchSfpw4Clk,
  PchSfpw6Clk,
  PchSfpw8Clk
} PCH_START_FRAME_PULSE;

///
/// The PCH_LPC_SIRQ_CONFIG block describes the expected configuration of the PCH for Serial IRQ.
///
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Config Block Header
  UINT32                SirqEnable      :  1;     ///< Determines if enable Serial IRQ. 0: Disable; <b>1: Enable</b>.
  UINT32                SirqMode        :  2;     ///< Serial IRQ Mode Select. Refer to PCH_SIRQ_MODE for each value. <b>0: quiet mode</b> 1: continuous mode.
  UINT32                StartFramePulse :  3;     ///< Start Frame Pulse Width. Refer to PCH_START_FRAME_PULSE for each value. Default is <b>PchSfpw4Clk</b>.
  UINT32                RsvdBits0       : 26;     ///< Reserved bits
} PCH_LPC_SIRQ_CONFIG;

#pragma pack (pop)

#endif // _SERIAL_IRQ_CONFIG_H_
