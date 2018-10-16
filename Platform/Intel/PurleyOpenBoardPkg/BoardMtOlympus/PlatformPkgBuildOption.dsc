### @file
#
# Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
#
# This program and the accompanying materials are licensed and made available under
# the terms and conditions of the BSD License which accompanies this distribution.
# The full text of the license may be found at
# http://opensource.org/licenses/bsd-license.php
#
# THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
# WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#
###

[BuildOptions.Common.EDKII]
# Append build options for EDK and EDKII drivers (= is Append, == is Replace)

  DEFINE CRB_EDKII_BUILD_OPTIONS         = -D CRB_FLAG
  DEFINE EDKII_CPU_BUILD_OPTIONS         = -D PURLEY_FLAG 
  DEFINE TRAD_BUILD_OPTION               = -D TRAD_FLAG=1
  DEFINE SUS_WELL_RESTORE_BUILD_OPTION   = -D SUS_WELL_RESTORE=1
  DEFINE PCH_BUILD_OPTION                = -D PCH_SERVER_BIOS_FLAG=1
  DEFINE SERVER_BUILD_OPTION             = -D SERVER_BIOS_FLAG=1
  DEFINE PCH_PKG_OPTIONS                 = -D PCH_SPT
  DEFINE MAX_SOCKET_OPTIONS              = -D MAX_SOCKET=4

  DEFINE EDKII_ALL_PPO_OPTIONS           = $(EDKII_CPU_BUILD_OPTIONS)
  DEFINE PCH_BIOS_BUILD_OPTIONS          = $(TRAD_BUILD_OPTION) $(ULT_BUILD_OPTION) $(PCH_BUILD_OPTION) $(SUS_WELL_RESTORE_BUILD_OPTION) $(SERVER_BUILD_OPTION)
  DEFINE EDKII_DSC_FEATURE_BUILD_OPTIONS = $(CRB_EDKII_BUILD_OPTIONS) $(PCH_BIOS_BUILD_OPTIONS) $(PCH_PKG_OPTIONS) $(EDKII_ALL_PPO_OPTIONS) $(SPARING_SCRATCHPAD_OPTION) $(TRACE_HUB_DEBUG_BUILD_OPTIONS) $(TRACE_HUB_INIT_BUILD_OPTIONS) $(MAX_SOCKET_OPTIONS) -D EFI_PCI_IOV_SUPPORT -D WHEA_SUPPORT -D SKX_HOST -D CLX_HOST

!if $(TARGET) == "DEBUG"
  DEFINE DEBUG_BUILD_FLAG = -D SERIAL_DBG_MSG=1
!else
  DEFINE DEBUG_BUILD_FLAG = -D MDEPKG_NDEBUG -D SILENT_MODE 
!endif

  DEFINE EDKII_DSC_FEATURE_BUILD_OPTIONS     = $(EDKII_DSC_FEATURE_BUILD_OPTIONS) $(DEBUG_BUILD_FLAG)
#
# PC_BUILD_END
#


  DEFINE EDKII_DSC_FEATURE_BUILD_OPTIONS     = $(EDKII_DSC_FEATURE_BUILD_OPTIONS)


  *_*_IA32_CC_FLAGS    = $(EDKII_DSC_FEATURE_BUILD_OPTIONS)
  *_*_IA32_VFRPP_FLAGS = $(EDKII_DSC_FEATURE_BUILD_OPTIONS)
  *_*_IA32_APP_FLAGS   = $(EDKII_DSC_FEATURE_BUILD_OPTIONS)
  *_*_IA32_PP_FLAGS    = $(EDKII_DSC_FEATURE_BUILD_OPTIONS)
  *_*_IA32_ASLPP_FLAGS = $(EDKII_DSC_FEATURE_BUILD_OPTIONS)
  *_*_IA32_ASLCC_FLAGS = $(EDKII_DSC_FEATURE_BUILD_OPTIONS)

  *_*_X64_CC_FLAGS     = $(EDKII_DSC_FEATURE_BUILD_OPTIONS)
  *_*_X64_VFRPP_FLAGS  = $(EDKII_DSC_FEATURE_BUILD_OPTIONS)
  *_*_X64_APP_FLAGS    = $(EDKII_DSC_FEATURE_BUILD_OPTIONS)
  *_*_X64_PP_FLAGS     = $(EDKII_DSC_FEATURE_BUILD_OPTIONS)
  *_*_X64_ASLPP_FLAGS  = $(EDKII_DSC_FEATURE_BUILD_OPTIONS)
  *_*_X64_ASLCC_FLAGS  = $(EDKII_DSC_FEATURE_BUILD_OPTIONS)



#
# Enable source level debugging for RELEASE build
#
!if $(TARGET) == "RELEASE"
  DEFINE EDKII_RELEASE_SRCDBG_ASM_BUILD_OPTIONS   = /Zi
  DEFINE EDKII_RELEASE_SRCDBG_CC_BUILD_OPTIONS    = /Zi /Gm
  DEFINE EDKII_RELEASE_SRCDBG_DLINK_BUILD_OPTIONS = /DEBUG

  MSFT:*_*_*_ASM_FLAGS    = $(EDKII_RELEASE_SRCDBG_ASM_BUILD_OPTIONS)
  MSFT:*_*_*_CC_FLAGS     = $(EDKII_RELEASE_SRCDBG_CC_BUILD_OPTIONS)
  MSFT:*_*_*_DLINK_FLAGS  = $(EDKII_RELEASE_SRCDBG_DLINK_BUILD_OPTIONS)
!endif


#
# Override the existing iasl path in tools_def.template
#
#  MSFT:*_*_*_ASL_PATH == c:/Iasl/iasl.exe

#
# Override the VFR compile flags to speed the build time
#

*_*_*_VFR_FLAGS                     ==  -n

# Force PE/COFF sections to be aligned at 4KB boundaries to support page level protection
[BuildOptions.common.EDKII.DXE_SMM_DRIVER, BuildOptions.common.EDKII.SMM_CORE]
  MSFT:*_*_*_DLINK_FLAGS = /ALIGN:4096
  GCC:*_*_*_DLINK_FLAGS = -z common-page-size=0x1000
  
# Force PE/COFF sections to be aligned at 4KB boundaries to support MemoryAttribute table
[BuildOptions.common.EDKII.DXE_RUNTIME_DRIVER]
  MSFT:*_*_*_DLINK_FLAGS = /ALIGN:4096
  GCC:*_*_*_DLINK_FLAGS = -z common-page-size=0x1000
