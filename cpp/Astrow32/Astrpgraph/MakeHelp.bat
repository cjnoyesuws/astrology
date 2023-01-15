@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by ASTRPGRAPH.HPJ. >"hlp\astrpgraph.hm"
echo. >>"hlp\astrpgraph.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\astrpgraph.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\astrpgraph.hm"
echo. >>"hlp\astrpgraph.hm"
echo // Prompts (IDP_*) >>"hlp\astrpgraph.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\astrpgraph.hm"
echo. >>"hlp\astrpgraph.hm"
echo // Resources (IDR_*) >>"hlp\astrpgraph.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\astrpgraph.hm"
echo. >>"hlp\astrpgraph.hm"
echo // Dialogs (IDD_*) >>"hlp\astrpgraph.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\astrpgraph.hm"
echo. >>"hlp\astrpgraph.hm"
echo // Frame Controls (IDW_*) >>"hlp\astrpgraph.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\astrpgraph.hm"
REM -- Make help for Project ASTRPGRAPH


echo Building Win32 Help files
start /wait hcrtf -x "hlp\astrpgraph.hpj"
echo.
if exist Debug\nul copy "hlp\astrpgraph.hlp" Debug
if exist Debug\nul copy "hlp\astrpgraph.cnt" Debug
if exist Release\nul copy "hlp\astrpgraph.hlp" Release
if exist Release\nul copy "hlp\astrpgraph.cnt" Release
echo.


