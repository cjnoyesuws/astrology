@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by ASTROW.HPJ. >"hlp\Astrow.hm"
echo. >>"hlp\Astrow.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\Astrow.hm"
e:\msvc\bin\makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\Astrow.hm"
echo. >>"hlp\Astrow.hm"
echo // Prompts (IDP_*) >>"hlp\Astrow.hm"
e:\msvc\bin\makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\Astrow.hm"
echo. >>"hlp\Astrow.hm"
echo // Resources (IDR_*) >>"hlp\Astrow.hm"
e:\msvc\bin\makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\Astrow.hm"
echo. >>"hlp\Astrow.hm"
echo // Dialogs (IDD_*) >>"hlp\Astrow.hm"
e:\msvc\bin\makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\Astrow.hm"
echo. >>"hlp\Astrow.hm"
echo // Frame Controls (IDW_*) >>"hlp\Astrow.hm"
e:\msvc\bin\makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\Astrow.hm"
REM -- Make help for Project ASTROW


echo Building Win32 Help files
start /wait hcrtf -x "hlp\Astrow.hpj"
echo.
if exist Debug\nul copy "hlp\Astrow.hlp" Debug
if exist Debug\nul copy "hlp\Astrow.cnt" Debug
if exist Release\nul copy "hlp\Astrow.hlp" Release
if exist Release\nul copy "hlp\Astrow.cnt" Release
echo.


