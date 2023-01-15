@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by COMMENT.HPJ. >"hlp\Comment.hm"
echo. >>"hlp\Comment.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\Comment.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\Comment.hm"
echo. >>"hlp\Comment.hm"
echo // Prompts (IDP_*) >>"hlp\Comment.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\Comment.hm"
echo. >>"hlp\Comment.hm"
echo // Resources (IDR_*) >>"hlp\Comment.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\Comment.hm"
echo. >>"hlp\Comment.hm"
echo // Dialogs (IDD_*) >>"hlp\Comment.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\Comment.hm"
echo. >>"hlp\Comment.hm"
echo // Frame Controls (IDW_*) >>"hlp\Comment.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\Comment.hm"
REM -- Make help for Project COMMENT


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\Comment.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\Comment.hlp" goto :Error
if not exist "hlp\Comment.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\Comment.hlp" Debug
if exist Debug\nul copy "hlp\Comment.cnt" Debug
if exist Release\nul copy "hlp\Comment.hlp" Release
if exist Release\nul copy "hlp\Comment.cnt" Release
echo.
goto :done

:Error
echo hlp\Comment.hpj(1) : erroj: Problem encountered creating help file

:done
echo.
