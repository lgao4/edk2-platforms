/** @file

Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _SETUP_TABLE_H_
#define _SETUP_TABLE_H_

#include <Guid/SocketVariable.h>
#include <Guid/SetupVariable.h>
#include <Guid/PchRcVariable.h>

typedef struct {
  SOCKET_CONFIGURATION       SocketConfig;
  SYSTEM_CONFIGURATION       SystemConfig;
  PCH_RC_CONFIGURATION       PchRcConfig;
} SETUP_DATA;

#endif
