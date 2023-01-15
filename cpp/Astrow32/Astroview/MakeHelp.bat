@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by ASTROVIEW.HPJ. >"hlp\Astroview.hm"
echo. >>"hlp\Astroview.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\Astroview.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\Astroview.hm"
echo. >>"hlp\Astroview.hm"
echo // Prompts (IDP_*) >>"hlp\Astroview.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\Astroview.hm"
echo. >>"hlp\Astroview.hm"
echo // Resources (IDR_*) >>"hlp\Astroview.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\Astroview.hm"
echo. >>"hlp\Astroview.hm"
echo // Dialogs (IDD_*) >>"hlp\Astroview.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\Astroview.hm"
echo. >>"hlp\Astroview.hm"
echo // Frame Controls (IDW_*) >>"hlp\Astroview.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\Astroview.hm"
REM -- Make help for Project ASTROVIEW


echo Building Win32 Help files
start /wait hcrtf -x "hlp\Astroview.hpj"
echo.
if exist Debug\nul copy "hlp\Astroview.hlp" Debug
if exist Debug\nul copy "hlp\Astroview.cnt" Debug
if exist Release\nul copy "hlp\Astroview.hlp" Release
if exist Release\nul copy "hlp\Astroview.cnt" Release
echo.


