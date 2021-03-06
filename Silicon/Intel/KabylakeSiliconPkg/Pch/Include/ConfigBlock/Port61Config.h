/** @file
  Port 61h policy

Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
#ifndef _PORT_61_CONFIG_H_
#define _PORT_61_CONFIG_H_

#define PORT_61_CONFIG_REVISION 1
extern EFI_GUID gPort61ConfigGuid;

#pragma pack (push,1)

/**
  This structure is used for the emulation feature for Port61h read. The port is trapped
  and the SMI handler will toggle bit4 according to the handler's internal state.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                             ///< Config Block Header
  UINT32                Enable                    :  1;     ///< 0: Disable; <b>1: Enable</b> the emulation
  UINT32                RsvdBits0                 :  31;    ///< Reserved bits
} PCH_PORT61H_SMM_CONFIG;

#pragma pack (pop)

#endif // _PORT_61_CONFIG_H_
