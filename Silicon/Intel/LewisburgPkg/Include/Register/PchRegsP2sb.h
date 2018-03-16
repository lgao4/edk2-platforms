/** @file

Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _PCH_REGS_P2SB_H_
#define _PCH_REGS_P2SB_H_

//
// PCI to P2SB Bridge Registers (D31:F1)
//
#define PCI_DEVICE_NUMBER_PCH_P2SB                 31
#define PCI_FUNCTION_NUMBER_PCH_P2SB               1

#define V_PCH_P2SB_VENDOR_ID                       V_PCH_INTEL_VENDOR_ID
#define R_PCH_P2SB_SBREG_BAR                       0x10
#define B_PCH_P2SB_SBREG_RBA                       0xFF000000
#define R_PCH_P2SB_SBREG_BARH                      0x14
#define B_PCH_P2SB_SBREG_RBAH                      0xFFFFFFFF
#define R_PCH_P2SB_VBDF                            0x50
#define B_PCH_P2SB_VBDF_BUF                        0xFF00
#define B_PCH_P2SB_VBDF_DEV                        0x00F8
#define B_PCH_P2SB_VBDF_FUNC                       0x0007
#define R_PCH_P2SB_ESMBDF                          0x52
#define B_PCH_P2SB_ESMBDF_BUF                      0xFF00
#define B_PCH_P2SB_ESMBDF_DEV                      0x00F8
#define B_PCH_P2SB_ESMBDF_FUNC                     0x0007
#define R_PCH_P2SB_RCFG                            0x54
#define B_PCH_P2SB_RCFG_RPRID                      0x0000FF00
#define B_PCH_P2SB_RCFG_RSE                        BIT0
#define R_PCH_P2SB_HPTC                            0x60
#define B_PCH_P2SB_HPTC_AE                         BIT7
#define B_PCH_P2SB_HPTC_AS                         0x0003
#define N_PCH_HPET_ADDR_ASEL                       12
#define V_PCH_HPET_BASE0                           0xFED00000
#define V_PCH_HPET_BASE1                           0xFED01000
#define V_PCH_HPET_BASE2                           0xFED02000
#define V_PCH_HPET_BASE3                           0xFED03000
#define R_PCH_P2SB_IOAC                            0x64
#define B_PCH_P2SB_IOAC_AE                         BIT8
#define B_PCH_P2SB_IOAC_ASEL                       0x00FF
#define N_PCH_IO_APIC_ASEL                         12
#define R_PCH_IO_APIC_INDEX                        0xFEC00000
#define R_PCH_IO_APIC_DATA                         0xFEC00010
#define R_PCH_IO_APIC_EOI                          0xFEC00040
#define R_PCH_P2SB_IBDF                            0x6C
#define B_PCH_P2SB_IBDF_BUF                        0xFF00
#define B_PCH_P2SB_IBDF_DEV                        0x00F8
#define B_PCH_P2SB_IBDF_FUNC                       0x0007
#define R_PCH_P2SB_HBDF                            0x70
#define B_PCH_P2SB_HBDF_BUF                        0xFF00
#define B_PCH_P2SB_HBDF_DEV                        0x00F8
#define B_PCH_P2SB_HBDF_FUNC                       0x0007
#define R_PCH_P2SB_80                              0x80
#define R_PCH_P2SB_84                              0x84
#define R_PCH_P2SB_88                              0x88
#define R_PCH_P2SB_8C                              0x8C
#define R_PCH_P2SB_90                              0x90
#define R_PCH_P2SB_94                              0x94
#define R_PCH_P2SB_98                              0x98
#define R_PCH_P2SB_9C                              0x9C
#define R_PCH_P2SB_DISPBDF                         0xA0
#define B_PCH_P2SB_DISPBDF_DTBLK                   0x00070000
#define B_PCH_P2SB_DISPBDF_BUF                     0x0000FF00
#define B_PCH_P2SB_DISPBDF_DEV                     0x000000F8
#define B_PCH_P2SB_DISPBDF_FUNC                    0x00000007
#define R_PCH_P2SB_ICCOS                           0xA4
#define B_PCH_P2SB_ICCOS_MODBASE                   0xFF00
#define B_PCH_P2SB_ICCOS_BUFBASE                   0x00FF

//
// Definition for SBI
//
#define R_PCH_P2SB_SBIADDR                         0xD0
#define B_PCH_P2SB_SBIADDR_DESTID                  0xFF000000
#define B_PCH_P2SB_SBIADDR_RS                      0x000F0000
#define B_PCH_P2SB_SBIADDR_OFFSET                  0x0000FFFF
#define R_PCH_P2SB_SBIDATA                         0xD4
#define B_PCH_P2SB_SBIDATA_DATA                    0xFFFFFFFF
#define R_PCH_P2SB_SBISTAT                         0xD8
#define B_PCH_P2SB_SBISTAT_OPCODE                  0xFF00
#define B_PCH_P2SB_SBISTAT_POSTED                  BIT7
#define B_PCH_P2SB_SBISTAT_RESPONSE                0x0006
#define N_PCH_P2SB_SBISTAT_RESPONSE                1
#define B_PCH_P2SB_SBISTAT_INITRDY                 BIT0
#define R_PCH_P2SB_SBIRID                          0xDA
#define B_PCH_P2SB_SBIRID_FBE                      0xF000
#define B_PCH_P2SB_SBIRID_BAR                      0x0700
#define B_PCH_P2SB_SBIRID_FID                      0x00FF
#define R_PCH_P2SB_SBIEXTADDR                      0xDC
#define B_PCH_P2SB_SBIEXTADDR_ADDR                 0xFFFFFFFF

//
// Others
//
#define R_PCH_P2SB_E0                              0xE0
#define R_PCH_P2SB_F4                              0xF4
#endif
