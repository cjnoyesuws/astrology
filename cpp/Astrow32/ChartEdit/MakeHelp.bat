@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by CHARTEDIT.HPJ. >"hlp\ChartEdit.hm"
echo. >>"hlp\ChartEdit.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\ChartEdit.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\ChartEdit.hm"
echo. >>"hlp\ChartEdit.hm"
echo // Prompts (IDP_*) >>"hlp\ChartEdit.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\ChartEdit.hm"
echo. >>"hlp\ChartEdit.hm"
echo // Resources (IDR_*) >>"hlp\ChartEdit.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\ChartEdit.hm"
echo. >>"hlp\ChartEdit.hm"
echo // Dialogs (IDD_*) >>"hlp\ChartEdit.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\ChartEdit.hm"
echo. >>"hlp\ChartEdit.hm"
echo // Frame Controls (IDW_*) >>"hlp\ChartEdit.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\ChartEdit.hm"
REM -- Make help for Project CHARTEDIT


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\ChartEdit.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\ChartEdit.hlp" goto :Error
if not exist "hlp\ChartEdit.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\ChartEdit.hlp" Debug
if exist Debug\nul copy "hlp\ChartEdit.cnt" Debug
if exist Release\nul copy "hlp\ChartEdit.hlp" Release
if exist Release\nul copy "hlp\ChartEdit.cnt" Release
echo.
goto :done

:Error
echo hlp\ChartEdit.hpj(1) : error: Problem encountered creating help file

:done
echo.
