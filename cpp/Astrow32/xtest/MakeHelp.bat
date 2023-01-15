@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by XTEST.HPJ. >"hlp\xtest.hm"
echo. >>"hlp\xtest.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\xtest.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\xtest.hm"
echo. >>"hlp\xtest.hm"
echo // Prompts (IDP_*) >>"hlp\xtest.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\xtest.hm"
echo. >>"hlp\xtest.hm"
echo // Resources (IDR_*) >>"hlp\xtest.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\xtest.hm"
echo. >>"hlp\xtest.hm"
echo // Dialogs (IDD_*) >>"hlp\xtest.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\xtest.hm"
echo. >>"hlp\xtest.hm"
echo // Frame Controls (IDW_*) >>"hlp\xtest.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\xtest.hm"
REM -- Make help for Project XTEST


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\xtest.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\xtest.hlp" goto :Error
if not exist "hlp\xtest.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\xtest.hlp" Debug
if exist Debug\nul copy "hlp\xtest.cnt" Debug
if exist Release\nul copy "hlp\xtest.hlp" Release
if exist Release\nul copy "hlp\xtest.cnt" Release
echo.
goto :done

:Error
echo hlp\xtest.hpj(1) : erroj: Problem encountered creating help file

:done
echo.
