@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by TEST.HPJ. >"hlp\test.hm"
echo. >>"hlp\test.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\test.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\test.hm"
echo. >>"hlp\test.hm"
echo // Prompts (IDP_*) >>"hlp\test.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\test.hm"
echo. >>"hlp\test.hm"
echo // Resources (IDR_*) >>"hlp\test.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\test.hm"
echo. >>"hlp\test.hm"
echo // Dialogs (IDD_*) >>"hlp\test.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\test.hm"
echo. >>"hlp\test.hm"
echo // Frame Controls (IDW_*) >>"hlp\test.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\test.hm"
REM -- Make help for Project TEST


echo Building Win32 Help files
start /wait hcrtf -x "hlp\test.hpj"
echo.
if exist Debug\nul copy "hlp\test.hlp" Debug
if exist Debug\nul copy "hlp\test.cnt" Debug
if exist Release\nul copy "hlp\test.hlp" Release
if exist Release\nul copy "hlp\test.cnt" Release
echo.


