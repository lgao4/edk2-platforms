/** @file
  HSIO pcie policy

Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
#ifndef _HSIO_PCIE_CONFIG_H_
#define _HSIO_PCIE_CONFIG_H_

#define HSIO_PCIE_PREMEM_CONFIG_REVISION 1
extern EFI_GUID gHsioPciePreMemConfigGuid;

#pragma pack (push,1)

/**
  The PCH_HSIO_PCIE_LANE_CONFIG describes HSIO settings for PCIe lane
**/
typedef struct {
  //
  // HSIO Rx Eq
  // Refer to the EDS for recommended values.
  // Note that these setting are per-lane and not per-port
  //
  UINT32  HsioRxSetCtleEnable           : 1;      ///< <b>0: Disable</b>; 1: Enable PCH PCIe Gen 3 Set CTLE Value
  UINT32  HsioRxSetCtle                 : 6;      ///< PCH PCIe Gen 3 Set CTLE Value
  UINT32  HsioTxGen1DownscaleAmpEnable  : 1;      ///< <b>0: Disable</b>; 1: Enable PCH PCIe Gen 1 TX Output Downscale Amplitude Adjustment value override
  UINT32  HsioTxGen1DownscaleAmp        : 6;      ///< PCH PCIe Gen 1 TX Output Downscale Amplitude Adjustment value
  UINT32  HsioTxGen2DownscaleAmpEnable  : 1;      ///< <b>0: Disable</b>; 1: Enable PCH PCIe Gen 2 TX Output Downscale Amplitude Adjustment value override
  UINT32  HsioTxGen2DownscaleAmp        : 6;      ///< PCH PCIe Gen 2 TX Output Downscale Amplitude Adjustment value
  UINT32  HsioTxGen3DownscaleAmpEnable  : 1;      ///< <b>0: Disable</b>; 1: Enable PCH PCIe Gen 3 TX Output Downscale Amplitude Adjustment value override
  UINT32  HsioTxGen3DownscaleAmp        : 6;      ///< PCH PCIe Gen 3 TX Output Downscale Amplitude Adjustment value
  UINT32  RsvdBits0                     : 4;      ///< Reserved Bits

  UINT32  HsioTxGen1DeEmphEnable        : 1;      ///< <b>0: Disable</b>; 1: Enable PCH PCIe Gen 1 TX Output De-Emphasis Adjustment Setting value override
  UINT32  HsioTxGen1DeEmph              : 6;      ///< PCH PCIe Gen 1 TX Output De-Emphasis Adjustment Setting
  UINT32  HsioTxGen2DeEmph3p5Enable     : 1;      ///< <b>0: Disable</b>; 1: Enable PCH PCIe Gen 2 TX Output -3.5dB Mode De-Emphasis Adjustment Setting value override
  UINT32  HsioTxGen2DeEmph3p5           : 6;      ///< PCH PCIe Gen 2 TX Output -3.5dB Mode De-Emphasis Adjustment Setting
  UINT32  HsioTxGen2DeEmph6p0Enable     : 1;      ///< <b>0: Disable</b>; 1: Enable PCH PCIe Gen 2 TX Output -6.0dB Mode De-Emphasis Adjustment Setting value override
  UINT32  HsioTxGen2DeEmph6p0           : 6;      ///< PCH PCIe Gen 2 TX Output -6.0dB Mode De-Emphasis Adjustment Setting
  UINT32  RsvdBits1                     : 11;     ///< Reserved Bits
} PCH_HSIO_PCIE_LANE_CONFIG;

/**
  The PCH_HSIO_PCIE_CONFIG block describes the configuration of the HSIO for PCIe lanes
  <b>Revision 1</b>:
  - Initial version.
  <b>Revision 2</b>:
  - Add PciePllSsc support.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Config Block Header
  ///
  /// These members describe the configuration of HSIO for PCIe lanes.
  ///
  PCH_HSIO_PCIE_LANE_CONFIG         Lane[PCH_MAX_PCIE_ROOT_PORTS];
  /**
    Specifies the Pcie Pll Spread Spectrum Percentage
    The value of this policy is in 1/10th percent units.
    Valid spread range is 0-20. A value of 0xFF is reserved for AUTO.
    A value of 0 is SSC of 0.0%. A value of 20 is SSC of 2.0%
    The default is <b>0xFF: AUTO - No BIOS override</b>.
  **/
  UINT8  PciePllSsc;
  UINT8  Reserved[3];
} PCH_HSIO_PCIE_PREMEM_CONFIG;

#pragma pack (pop)

#endif // _HSIO_PCIE_LANE_CONFIG_H_
