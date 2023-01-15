@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by ASTROWDAOFILELIST.HPJ. >"hlp\AstrowDaoFileList.hm"
echo. >>"hlp\AstrowDaoFileList.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\AstrowDaoFileList.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\AstrowDaoFileList.hm"
echo. >>"hlp\AstrowDaoFileList.hm"
echo // Prompts (IDP_*) >>"hlp\AstrowDaoFileList.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\AstrowDaoFileList.hm"
echo. >>"hlp\AstrowDaoFileList.hm"
echo // Resources (IDR_*) >>"hlp\AstrowDaoFileList.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\AstrowDaoFileList.hm"
echo. >>"hlp\AstrowDaoFileList.hm"
echo // Dialogs (IDD_*) >>"hlp\AstrowDaoFileList.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\AstrowDaoFileList.hm"
echo. >>"hlp\AstrowDaoFileList.hm"
echo // Frame Controls (IDW_*) >>"hlp\AstrowDaoFileList.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\AstrowDaoFileList.hm"
REM -- Make help for Project ASTROWDAOFILELIST


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\AstrowDaoFileList.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\AstrowDaoFileList.hlp" goto :Error
if not exist "hlp\AstrowDaoFileList.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\AstrowDaoFileList.hlp" Debug
if exist Debug\nul copy "hlp\AstrowDaoFileList.cnt" Debug
if exist Release\nul copy "hlp\AstrowDaoFileList.hlp" Release
if exist Release\nul copy "hlp\AstrowDaoFileList.cnt" Release
echo.
goto :done

:Error
echo hlp\AstrowDaoFileList.hpj(1) : error: Problem encountered creating help file

:done
echo.
