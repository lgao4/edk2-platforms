@REM @file
@REM
@REM Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
@REM This program and the accompanying materials
@REM are licensed and made available under the terms and conditions of the BSD License
@REM which accompanies this distribution.  The full text of the license may be found at
@REM http://opensource.org/licenses/bsd-license.php
@REM
@REM THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
@REM WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
@REM

@set SCRIPT_ERROR=0

set /a postbuildstep=0

@echo.
@echo BoardPostBuild.%postbuildstep% python PatchBinFv.py
@set /a postbuildstep=%postbuildstep%+1
echo python %WORKSPACE%\edk2-platforms\Platform\Intel\MinPlatformPkg\Tools\PatchFv\PatchBinFv.py %TARGET% %WORKSPACE%\edk2-non-osi\Silicon\Intel\PurleySiliconBinPkg %WORKSPACE%\Build\BuildReport.txt FvTempMemorySilicon
call python %WORKSPACE%\edk2-platforms\Platform\Intel\MinPlatformPkg\Tools\PatchFv\PatchBinFv.py %TARGET% %WORKSPACE%\edk2-non-osi\Silicon\Intel\PurleySiliconBinPkg %WORKSPACE%\Build\BuildReport.txt FvTempMemorySilicon
if %ERRORLEVEL% NEQ 0 (
  set SCRIPT_ERROR=1
  echo PatchBinFv Error. Exit
  goto :EOF
)
echo python %WORKSPACE%\edk2-platforms\Platform\Intel\MinPlatformPkg\Tools\PatchFv\PatchBinFv.py %TARGET% %WORKSPACE%\edk2-non-osi\Silicon\Intel\PurleySiliconBinPkg %WORKSPACE%\Build\BuildReport.txt FvPreMemorySilicon
call python %WORKSPACE%\edk2-platforms\Platform\Intel\MinPlatformPkg\Tools\PatchFv\PatchBinFv.py %TARGET% %WORKSPACE%\edk2-non-osi\Silicon\Intel\PurleySiliconBinPkg %WORKSPACE%\Build\BuildReport.txt FvPreMemorySilicon
if %ERRORLEVEL% NEQ 0 (
  set SCRIPT_ERROR=1
  echo PatchBinFv Error. Exit
  goto :EOF
)
echo python %WORKSPACE%\edk2-platforms\Platform\Intel\MinPlatformPkg\Tools\PatchFv\PatchBinFv.py %TARGET% %WORKSPACE%\edk2-non-osi\Silicon\Intel\PurleySiliconBinPkg %WORKSPACE%\Build\BuildReport.txt FvPostMemorySilicon
call python %WORKSPACE%\edk2-platforms\Platform\Intel\MinPlatformPkg\Tools\PatchFv\PatchBinFv.py %TARGET% %WORKSPACE%\edk2-non-osi\Silicon\Intel\PurleySiliconBinPkg %WORKSPACE%\Build\BuildReport.txt FvPostMemorySilicon
if %ERRORLEVEL% NEQ 0 (
  set SCRIPT_ERROR=1
  echo PatchBinFv Error. Exit
  goto :EOF
)
echo python %WORKSPACE%\edk2-platforms\Platform\Intel\MinPlatformPkg\Tools\PatchFv\PatchBinFv.py %TARGET% %WORKSPACE%\edk2-non-osi\Silicon\Intel\PurleySiliconBinPkg %WORKSPACE%\Build\BuildReport.txt FvLateSilicon
call python %WORKSPACE%\edk2-platforms\Platform\Intel\MinPlatformPkg\Tools\PatchFv\PatchBinFv.py %TARGET% %WORKSPACE%\edk2-non-osi\Silicon\Intel\PurleySiliconBinPkg %WORKSPACE%\Build\BuildReport.txt FvLateSilicon
if %ERRORLEVEL% NEQ 0 (
  set SCRIPT_ERROR=1
  echo PatchBinFv Error. Exit
  goto :EOF
)

@echo.
@echo BoardPostBuild.%postbuildstep% python RebaseBinFv.py
@set /a postbuildstep=%postbuildstep%+1
echo python %WORKSPACE%\edk2-platforms\Platform\Intel\MinPlatformPkg\Tools\PatchFv\RebaseBinFv.py %TARGET% %WORKSPACE%\edk2-non-osi\Silicon\Intel\PurleySiliconBinPkg %WORKSPACE%\Build\BuildReport.txt FvPreMemorySilicon gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspMBase
call python %WORKSPACE%\edk2-platforms\Platform\Intel\MinPlatformPkg\Tools\PatchFv\RebaseBinFv.py %TARGET% %WORKSPACE%\edk2-non-osi\Silicon\Intel\PurleySiliconBinPkg %WORKSPACE%\Build\BuildReport.txt FvPreMemorySilicon gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspMBase
if %ERRORLEVEL% NEQ 0 (
  set SCRIPT_ERROR=1
  echo RebaseBinFv Error. Exit
  goto :EOF
)

echo python %WORKSPACE%\edk2-platforms\Platform\Intel\MinPlatformPkg\Tools\PatchFv\RebaseBinFv.py %TARGET% %WORKSPACE%\edk2-non-osi\Silicon\Intel\PurleySiliconBinPkg %WORKSPACE%\Build\BuildReport.txt FvPostMemorySilicon gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspSBase
call python %WORKSPACE%\edk2-platforms\Platform\Intel\MinPlatformPkg\Tools\PatchFv\RebaseBinFv.py %TARGET% %WORKSPACE%\edk2-non-osi\Silicon\Intel\PurleySiliconBinPkg %WORKSPACE%\Build\BuildReport.txt FvPostMemorySilicon gMinPlatformPkgTokenSpaceGuid.PcdFlashFvFspSBase
if %ERRORLEVEL% NEQ 0 (
  set SCRIPT_ERROR=1
  echo RebaseBinFv Error. Exit
  goto :EOF
)

@echo.
@echo BoardPostBuild.%postbuildstep% re-generate FDS
@set /a postbuildstep=%postbuildstep%+1
echo build fds
@REM call build fds
if %ERRORLEVEL% NEQ 0 (
  set SCRIPT_ERROR=1
  echo gen FDS Error. Exit
  goto :EOF
)

@echo.
@echo BoardPostBuild.%postbuildstep% python PatchBfv.py
@set /a postbuildstep=%postbuildstep%+1
echo python %WORKSPACE%\edk2-platforms\Platform\Intel\MinPlatformPkg\Tools\PatchFv\PatchBfv.py %WORKSPACE%\Build\%BOARD_PKG%\%BOARD_NAME%\%TARGET%_%TOOL_CHAIN_TAG%\FV\PLATFORM.fd %WORKSPACE%\Build\BuildReport.txt gMinPlatformPkgTokenSpaceGuid.PcdFlashFvPreMemoryBase
call python %WORKSPACE%\edk2-platforms\Platform\Intel\MinPlatformPkg\Tools\PatchFv\PatchBfv.py %WORKSPACE%\Build\%BOARD_PKG%\%BOARD_NAME%\%TARGET%_%TOOL_CHAIN_TAG%\FV\PLATFORM.fd %WORKSPACE%\Build\BuildReport.txt gMinPlatformPkgTokenSpaceGuid.PcdFlashFvPreMemoryBase
if %ERRORLEVEL% NEQ 0 (
  set SCRIPT_ERROR=1
  echo PatchBfv Error. Exit
  goto :EOF
)

:_done

@echo.
@cd %WORKSPACE%
@if "%SCRIPT_ERROR%" == "0" (
  @echo PostBuild SUCCEEDED.
) else (
  @echo PostBuild FAILED.
  Pause 0
)

EXIT /B %SCRIPT_ERROR%
