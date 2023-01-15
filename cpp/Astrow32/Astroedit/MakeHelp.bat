@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by ASTROEDIT.HPJ. >"hlp\Astroedit.hm"
echo. >>"hlp\Astroedit.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\Astroedit.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\Astroedit.hm"
echo. >>"hlp\Astroedit.hm"
echo // Prompts (IDP_*) >>"hlp\Astroedit.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\Astroedit.hm"
echo. >>"hlp\Astroedit.hm"
echo // Resources (IDR_*) >>"hlp\Astroedit.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\Astroedit.hm"
echo. >>"hlp\Astroedit.hm"
echo // Dialogs (IDD_*) >>"hlp\Astroedit.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\Astroedit.hm"
echo. >>"hlp\Astroedit.hm"
echo // Frame Controls (IDW_*) >>"hlp\Astroedit.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\Astroedit.hm"
REM -- Make help for Project ASTROEDIT


echo Building Win32 Help files
start /wait hcrtf -x "hlp\Astroedit.hpj"
echo.
if exist Debug\nul copy "hlp\Astroedit.hlp" Debug
if exist Debug\nul copy "hlp\Astroedit.cnt" Debug
if exist Release\nul copy "hlp\Astroedit.hlp" Release
if exist Release\nul copy "hlp\Astroedit.cnt" Release
echo.


