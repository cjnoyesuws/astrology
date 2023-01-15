//Microsoft App Studio generated resource script.
//
#include "resource.h"

#define APSTUDIO_READONLY_SYMBOLS
/////////////////////////////////////////////////////////////////////////
//
// Generated from the TEXTINCLUDE 2 resource.
//
#define APSTUDIO_HIDDEN_SYMBOLS
#include "windows.h"
#undef APSTUDIO_HIDDEN_SYMBOLS

/////////////////////////////////////////////////////////////////////////////////////
#undef APSTUDIO_READONLY_SYMBOLS


//////////////////////////////////////////////////////////////////////////////
//
// Icon
//

ASTROWICON              ICON    DISCARDABLE     RES\ASTROWIC.ICO
GRAPHICON               ICON    DISCARDABLE     RES\GRAPHICO.ICO
TEXTICON                ICON    DISCARDABLE     RES\TEXTICON.ICO
TEXTLIST                ICON    DISCARDABLE     RES\TEXTLIST.ICO
GRAPHLIST               ICON    DISCARDABLE     RES\GRAPHLIS.ICO
TEXTGRAPHLIST           ICON    DISCARDABLE     RES\TEXTGRAP.ICO

//////////////////////////////////////////////////////////////////////////////
//
// Bitmap
//

ASTROBMP                BITMAP  MOVEABLE PURE   RES\ASTRO.BMP
CGLYPH                  BITMAP  MOVEABLE PURE   RES\CGLYPH.BMP
CTEXT                   BITMAP  MOVEABLE PURE   RES\CTEXT.BMP

//////////////////////////////////////////////////////////////////////////////
//
// Menu
//

MAINMENU MENU DISCARDABLE 
BEGIN
    POPUP "&File"
    BEGIN
        POPUP "&New"
        BEGIN
            MENUITEM "&File List",                  101
            MENUITEM "&Cover Page",                 102, GRAYED
            MENUITEM "&Comment File",               103, GRAYED
        END
        POPUP "&Open"
        BEGIN
            MENUITEM "&Birth Data",                 105
            MENUITEM "File &List",                  106
            MENUITEM "&Cover Page",                 107, GRAYED
            MENUITEM "Comment &File",               108, GRAYED
        END
        POPUP "&Save"
        BEGIN
            MENUITEM "&Birth Data",                 109
            MENUITEM "File &List",                  110, GRAYED
            MENUITEM "&Comment",                    111, GRAYED
        END
        POPUP "&Save &As"
        BEGIN
            MENUITEM "&Birth Data",                 112
            MENUITEM "File &List",                  113, GRAYED
        END
        MENUITEM "E&xport...",                  114, GRAYED
        MENUITEM "&View...\tEnter",             115, GRAYED
        MENUITEM "&Edit...\tCtrl+E",            116, GRAYED
        MENUITEM "&Kill...",                    117, GRAYED
        MENUITEM SEPARATOR
        MENUITEM "&Print...\tCtrl+P",           118, GRAYED
        POPUP "P&age Setup..."
        BEGIN
            MENUITEM "&Graphics...",                119
            MENUITEM "&Text...",                    120
        END
        POPUP "P&rint Setup..."
        BEGIN
            MENUITEM "&Graphics...",                121
            MENUITEM "&Text...",                    122
        END
        MENUITEM SEPARATOR
        MENUITEM "E&xit",                       123
    END
    POPUP "&Edit"
    BEGIN
        MENUITEM "&Undo\tAlt+Bksp",             201, GRAYED
        MENUITEM "&Redo",                       202, GRAYED
        MENUITEM SEPARATOR
        MENUITEM "Cu&t\tShift+Del",             203, GRAYED
        MENUITEM "C&opy\tCtrl+Ins",             204, GRAYED
        MENUITEM "&Paste\tShift+Ins",           205, GRAYED
        MENUITEM "&Delete\tDel",                206, GRAYED
        MENUITEM SEPARATOR
        MENUITEM "&Find...\tCtrl+F",            207, GRAYED
        MENUITEM "&Next\tCtrl+N",               208, GRAYED
    END
    POPUP "&Data"
    BEGIN
        MENUITEM "&Birth Info...\tCtrl+B",      301
        MENUITEM "&Compatiblity Info...\tCtrl+C",302
        MENUITEM "&Transits Info...",           303
        MENUITEM "Transits &Data...",           304
        MENUITEM "&Progressions Data...",       305
        MENUITEM "&Birth Rectification...\tCtrl+R",306
        MENUITEM "&Compatiblity Rectification...\tCtrl+X",307
        MENUITEM "Return Data...",              308
        MENUITEM "Relocations Data...",         309
    END
    POPUP "&Chart"
    BEGIN
        POPUP "Compile &Natal"
        BEGIN
            MENUITEM "&Default Chart...",           401
            MENUITEM "Birth &Signs Only",           402
            MENUITEM "Birth Signs & &Houses",       403
            MENUITEM "Birth Signs, Houses, & &Aspects...",404
            MENUITEM "&Complete Chart...",          405
            MENUITEM "Complete Chart w/&Basic Midpoints...",406
            MENUITEM "Complete Chart with &Full Midpoints...",407
            MENUITEM "&Numeric Chart...",           408
        END
        POPUP "&Other Charts"
        BEGIN
            MENUITEM "&Compatibility...",           409
            MENUITEM "&Transits...",                410
            MENUITEM "&Progression...",             411
            MENUITEM "C&omposite...",               412
            MENUITEM "Co&mposite Transits...",      413
            MENUITEM "&Relocation...",              414
        END
        POPUP "&Specialty Charts..."
        BEGIN
            MENUITEM "Returns...",                  415
            MENUITEM "Fixed Star...",               416
            MENUITEM "Arabic Points...",            417
            MENUITEM "Heliocentric...",             418
            MENUITEM "Problem...",                  419
        END
    END
    POPUP "O&ptions"
    BEGIN
        MENUITEM "&Setup...",                   601
        MENUITEM "Text &File Conversion...",    602
        MENUITEM "&Graphics Options...",        603
        MENUITEM "G&raphic File Conversion...", 604
        MENUITEM "&Viewer Setup...",            605
        MENUITEM "&Editor Setup...",            606
        MENUITEM "Aspect &Orbs...",             607
        MENUITEM "Print/Convert All Checked",   620, CHECKED
        POPUP "&Chart Options"
        BEGIN
            MENUITEM "&Natal...",                   608
            MENUITEM "&Compatibility...",           609
            MENUITEM "&Transits...",                610
            MENUITEM "&Progression...",             611
            MENUITEM "C&omposite...",               612
            MENUITEM "Co&mposite Transits...",      613
            MENUITEM "&Relocation...",              614
            MENUITEM "Fixed Star...",               616
            MENUITEM "Arabic Points...",            617
            MENUITEM "Numeric...",                  618
        END
    END
    POPUP "&Utilities"
    BEGIN
        MENUITEM "&Read File Into Data",        703, GRAYED
        POPUP "Re&Index Databases"
        BEGIN
            MENUITEM "&Birth Database",             704
            MENUITEM "&Location Database",          705
            MENUITEM "&All Databases",              706
        END
        POPUP "Make &Popups"
        BEGIN
            MENUITEM "&Birth Popup",                707
            MENUITEM "&Location Popup",             708
            MENUITEM "&All Popups",                 709
        END
        POPUP "&Merge Databases"
        BEGIN
            MENUITEM "&Birth Popup...",             710
            MENUITEM "&Location Popup...",          711
        END
        MENUITEM "Rebuild &File List",          712, GRAYED
        MENUITEM "&Clear File List Selection",  713, GRAYED
        MENUITEM "&Edit File List Entry...",    714, GRAYED
        MENUITEM "&Sort File List",             715, GRAYED
        MENUITEM "&Archive Charts...",          716, GRAYED
        MENUITEM "&Unarchive Charts...",        717, GRAYED
    END
    POPUP "&Windows"
    BEGIN
	MENUITEM "&Arange",                     501
	MENUITEM "&Cascade",                    502
	MENUITEM "T&ile",                       503
    END
    POPUP "&Help"
    BEGIN
        MENUITEM "&Contents",                   801, HELP
        MENUITEM "&Search For Help On...",      802, HELP
        MENUITEM "&How to Use Help",            803, HELP
        MENUITEM SEPARATOR
        MENUITEM "&Astrology Help",             804, HELP
        MENUITEM "A&bout ASTRO for Windows",    805, HELP
    END
END

GRAPH MENU DISCARDABLE 
BEGIN
    POPUP "&Graphics"
    BEGIN
        MENUITEM "Show &Sign Names. ",          1001
        MENUITEM "Show &House Numbers. ",       1002
        MENUITEM "Show House &Degrees. ",       1003
        MENUITEM "Show &Aspects. ",             1004, GRAYED
        MENUITEM "Use &Glyphs.",                1005
        MENUITEM "Show Sign &Lines. ",          1006
        MENUITEM "&Inner House Cusps  ",        1008, GRAYED
        MENUITEM "Sign Tick Wheel",             1009
        MENUITEM "Decan Tick Wheel",            1010
        MENUITEM "Degree Tick Wheel",           1011
        MENUITEM "House Numbers Outside",       1012
        MENUITEM "Plot Classical",              1013
        MENUITEM "Show Planet Degrees",         1014
        MENUITEM "Use &Next Chart.\t[ ",        1015, GRAYED
        MENUITEM "Use &Previous Chart.\t] ",    1016, GRAYED
        MENUITEM "Use &First Chart.\t=",        1017, GRAYED
        MENUITEM "&Decrease House Cusps 1 Deg.\t<",1018
        MENUITEM "&Increase House Cusps 1 Deg.\t>",1019
        MENUITEM "Use &Regular House Cusps. \t@",1020
    END
    POPUP "&View"
    BEGIN
        MENUITEM "Zoom &In.\tNum +",            1021
        MENUITEM "Zoom &Out.\tNum -",           1022
        MENUITEM "Fit Window.\tNum *",          1023
    END
END

BIRTH MENU DISCARDABLE 
BEGIN
    POPUP "&Birth Database"
    BEGIN
        MENUITEM "&Get A Birth From Database.", 1101, GRAYED
        MENUITEM "&Add A New Birth To Database.",1102, GRAYED
        MENUITEM "&Replace A Birth In Database.",1103, GRAYED
        MENUITEM "&Delete A Birth In Database.",1104, GRAYED
        MENUITEM "&Make Popup.",                1105
        MENUITEM "&Copy Birth.",                1106
        MENUITEM "&Paste Birth.",               1107
        MENUITEM "C&lear Birth.",               1108
        MENUITEM "R&eturn.",                    1109
    END
END

LOCAT MENU DISCARDABLE 
BEGIN
    POPUP "&Location Database"
    BEGIN
        MENUITEM "&Get A Location From Database.",1201, GRAYED
        MENUITEM "&Add A New Location To Database.",1202, GRAYED
        MENUITEM "&Replace A Location In Database.",1203, GRAYED
        MENUITEM "&Delete A Location From Database.",1204, GRAYED
        MENUITEM "&Copy Location.",             1205
        MENUITEM "&Paste Location.",            1206
        MENUITEM "C&lear Location.",            1207
        MENUITEM "R&eturn.",                    1208
    END
END

MDIMENU MENU DISCARDABLE 
BEGIN
    MENUITEM "&Arange",                     501
    MENUITEM "&Cascade",                    502
    MENUITEM "T&ile",                       503
END


//////////////////////////////////////////////////////////////////////////////
//
// Dialog
//

RELOC_DAT DIALOG DISCARDABLE  15, 19, 312, 167
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Relocation Information:"
FONT 8, "Helv"
BEGIN
    CONTROL "Place Where Located--&Country:", 117, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 15, 15, 103, 8
    COMBOBOX        119,131,12,124,100,CBS_DROPDOWN | CBS_SORT | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "&State:", 120, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 21, 32, 21, 8
    COMBOBOX        121,51,31,85,70,CBS_DROPDOWN | CBS_SORT | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "&Location:", 122, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 145, 32, 32, 8
    COMBOBOX        123,184,30,108,66,CBS_DROPDOWN | CBS_SORT | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "L&ongitude--Degrees:", 124, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 15, 51, 67, 8
    EDITTEXT        125,90,49,27,12
    CONTROL "Minutes:", 126, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 128, 51, 29, 8
    EDITTEXT        127,168,49,22,12
    CONTROL "East/West:", 129, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 201, 51, 38, 8
    COMBOBOX        128,252,49,40,29,CBS_DROPDOWNLIST | WS_TABSTOP
    CONTROL "L&atitude--Degrees:", 130, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 15, 70, 67, 8
    EDITTEXT        131,90,68,27,12
    CONTROL "Minutes:", 132, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 128, 70, 29, 8
    EDITTEXT        133,168,68,22,12
    CONTROL "North/South:", 135, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 201, 70, 44, 8
    COMBOBOX        134,252,68,40,30,CBS_DROPDOWNLIST | WS_TABSTOP
    CONTROL "Time &Zone:", 136, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 15, 91, 38, 8
    COMBOBOX        151,59,88,87,62,CBS_DROPDOWNLIST | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "Special C&ode:", 138, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 157, 91, 47, 8
    COMBOBOX        139,211,89,90,62,CBS_DROPDOWNLIST | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "GMT Offsets:", 142, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 210, 110, 44, 8
    EDITTEXT        140,197,122,20,12,NOT WS_TABSTOP
    CONTROL "H", 143, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 221, 124, 7, 8
    EDITTEXT        141,231,122,20,12
    CONTROL "M", 144, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 257, 124, 7, 8
    PUSHBUTTON      "Location DB Menu",146,42,117,91,14
    DEFPUSHBUTTON   "OK",1,42,144,56,14
    PUSHBUTTON      "Help",150,136,144,47,14
    PUSHBUTTON      "Cancel",2,220,144,44,14
END

PROGRESS_DATA DIALOG DISCARDABLE  53, 47, 240, 103
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Progressions Data"
FONT 8, "Helv"
BEGIN
    CONTROL "&Progression System:", 101, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 12, 16, 67, 8
    COMBOBOX        102,92,14,140,54,CBS_DROPDOWNLIST | WS_TABSTOP
    CONTROL "&Months:", 103, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 13, 38, 27, 8
    EDITTEXT        106,46,34,25,12
    CONTROL "&Days:", 105, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 87, 38, 20, 8
    EDITTEXT        108,115,34,25,12
    CONTROL "&Years:", 107, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 155, 38, 22, 8
    EDITTEXT        104,182,34,22,12
    CONTROL          "Date Above is &Target Date",110,"Button",
                    BS_AUTOCHECKBOX | WS_TABSTOP,13,57,102,10
    DEFPUSHBUTTON   "OK",1,18,78,40,14
    PUSHBUTTON      "Help",150,93,78,40,14
    PUSHBUTTON      "Cancel",2,171,78,40,14
END

OPTIONS DIALOG DISCARDABLE  15, 8, 234, 204
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Birth Options"
FONT 8, "Helv"
BEGIN
    CONTROL         "&Chart Type", 101, "zGroupBox3dClass", WS_VISIBLE | WS_CHILD |  ZTXT3D_INSET | ZTXT3DLEFT | ZGRP3D_BLACK, 15, 9, 86, 48

    CONTROL          "Tropical Chart.",102,"Button",BS_AUTORADIOBUTTON | 
                    WS_GROUP | WS_TABSTOP,22,23,61,10
    CONTROL          "Sidereal Chart.",103,"Button",BS_AUTORADIOBUTTON | 
                    WS_GROUP | WS_TABSTOP,22,38,61,10
    CONTROL "House &Procedure:", 104, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 109, 12, 60, 8
    COMBOBOX        105,109,23,95,57,CBS_DROPDOWNLIST | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL          "Find &Houses.",106,"Button",BS_AUTOCHECKBOX | WS_GROUP | 
                    WS_TABSTOP,14,67,55,10
    CONTROL          "Find &Aspects.",107,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,14,83,57,10
    CONTROL          "Find Extended Aspects.",108,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,14,99,90,10
    CONTROL          "Miscellaneous &Info.",109,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,14,115,76,10
    CONTROL          "Extended Misc Info.",110,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,14,132,78,10
    CONTROL          "&Summary At End of Report.",111,"Button",
                    BS_AUTOCHECKBOX | WS_TABSTOP,14,148,100,10
    CONTROL          "&Vertex and East Point.",112,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,116,47,86,10
    CONTROL          "Print &Text in Report.",113,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,116,64,79,10
    CONTROL         "&Midpoint Options", 306, "zGroupBox3dClass", WS_VISIBLE | WS_CHILD |  ZTXT3D_INSET | ZTXT3DLEFT | ZGRP3D_BLACK, 117, 81, 103, 83

    CONTROL          "Basic Midpoints.",114,"Button",BS_AUTOCHECKBOX | 
                    WS_GROUP | WS_TABSTOP,126,99,66,10
    CONTROL          "One-Half Midpoints.",116,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,126,115,77,10
    CONTROL          "Full Midpoints.",115,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,126,131,60,10
    CONTROL          "Aspects With Midpoints.",117,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,126,147,91,10
    PUSHBUTTON      "OK",1,17,176,57,20
    PUSHBUTTON      "Help",150,88,176,57,20
    PUSHBUTTON      "Cancel",2,160,176,57,20
END

RETURN_DATA DIALOG DISCARDABLE  61, 16, 222, 206
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Enter Return Chart Data"
FONT 8, "Helv"
BEGIN
    CONTROL "&Body of Interest:", 101, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 11, 11, 120, 8
    COMBOBOX        102,76,9,49,40,CBS_DROPDOWNLIST | WS_TABSTOP
    CONTROL "&Starting Date--", 103, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 11, 26, 49, 8
    CONTROL "Month:", 104, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 11, 40, 22, 8
    EDITTEXT        105,46,38,24,12
    CONTROL "Day:", 106, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 82, 39, 16, 8
    EDITTEXT        107,111,37,23,12
    CONTROL "Year:", 108, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 146, 40, 19, 8
    EDITTEXT        109,176,38,28,12
    CONTROL "&Ending Date--", 110, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 11, 58, 46, 8
    CONTROL "Month:", 111, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 11, 72, 22, 8
    EDITTEXT        112,47,70,24,12
    CONTROL "Day:", 113, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 84, 71, 16, 8
    EDITTEXT        114,113,69,23,12
    CONTROL "Year:", 115, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 148, 72, 19, 8
    EDITTEXT        116,181,70,27,12
    CONTROL          "",117,"Static",SS_BLACKRECT,10,91,197,2
    CONTROL          "&Progress Return Chart?",118,"Button",BS_AUTOCHECKBOX | 
                    BS_LEFTTEXT | WS_TABSTOP,10,99,88,10
    CONTROL "Progression &System:", 119, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 11, 118, 67, 8
    COMBOBOX        120,91,116,111,54,CBS_DROPDOWNLIST | WS_TABSTOP
    CONTROL "Progression &Offset:", 121, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 12, 136, 63, 8
    CONTROL "Months:", 122, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 12, 149, 27, 8
    EDITTEXT        125,47,147,25,12
    CONTROL "Days:", 124, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 87, 149, 20, 8
    EDITTEXT        127,117,147,25,12
    CONTROL "Years:", 126, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 157, 149, 22, 8
    EDITTEXT        123,185,147,22,12
    CONTROL          "Date  Above is &Target Date",129,"Button",
                    BS_AUTOCHECKBOX | WS_TABSTOP,13,165,102,10
    DEFPUSHBUTTON   "OK",1,14,183,40,14
    PUSHBUTTON      "Help",150,89,183,40,14
    PUSHBUTTON      "Cancel",2,169,183,40,14
END

FILE_NAME DIALOG DISCARDABLE  55, 38, 240, 100
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Name For Chart in File List"
FONT 8, "Helv"
BEGIN
    CONTROL "&Name:", 101, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 12, 22, 8
    EDITTEXT        102,71,7,154,12,ES_AUTOHSCROLL
    CONTROL "&Comments:", 103, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 30, 36, 8
    EDITTEXT        104,71,29,154,12,ES_AUTOHSCROLL
    CONTROL "Chart Type:", 105, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 50, 39, 9
    CONTROL "*", 106, "zStatTxt3dClass",SS_NOPREFIX WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 73, 50, 154, 10
    PUSHBUTTON      "OK",1,13,74,64,14
    PUSHBUTTON      "Help",150,87,74,64,14
    PUSHBUTTON      "Cancel",2,160,74,64,14
END

FILE_EDIT DIALOG DISCARDABLE  55, 29, 240, 122
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Edit Name For Chart in File List."
FONT 8, "Helv"
BEGIN
    CONTROL "&Name:", 101, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 17, 22, 8
    EDITTEXT        102,71,12,154,12,ES_AUTOHSCROLL
    CONTROL "&Comments:", 103, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 35, 36, 8
    EDITTEXT        104,71,34,154,12,ES_AUTOHSCROLL
    CONTROL "Chart Type:", 105, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 55, 39, 9
    CONTROL "*", 106, "zStatTxt3dClass",SS_NOPREFIX WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 73, 55, 154, 10
    CONTROL "File Name:", 107, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 71, 39, 9
    CONTROL "*", 108, "zStatTxt3dClass",SS_NOPREFIX WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 73, 71, 154, 10
    PUSHBUTTON      "OK",1,13,93,64,14
    PUSHBUTTON      "Help",150,87,93,64,14
    PUSHBUTTON      "Cancel",2,160,93,64,14
END

FILE_KILL DIALOG DISCARDABLE  68, 21, 215, 139
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "OK To Delete File?"
FONT 8, "Helv"
BEGIN
    CONTROL "Name:", 101, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 19, 14, 22, 8
    CONTROL "*", 102, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 78, 14, 123, 8
    CONTROL "Comments:", 103, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 19, 27, 36, 8
    CONTROL "*", 104, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 78, 27, 123, 8
    CONTROL "Chart Type:", 105, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 19, 41, 39, 9
    CONTROL "*", 106, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 78, 40, 123, 10
    CONTROL "File Name:", 107, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 19, 55, 39, 9
    CONTROL "*", 108, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 78, 54, 123, 10
    CONTROL          "Continue To Ask?",109,"Button",BS_AUTOCHECKBOX | 
                    BS_LEFTTEXT | WS_TABSTOP,19,71,71,10
    PUSHBUTTON      "OK--Delete",1,32,89,68,16
    PUSHBUTTON      "No--Don't",200,112,89,68,16
    PUSHBUTTON      "Help",150,112,113,68,16
    PUSHBUTTON      "Cancel",2,32,113,68,16
END

CUSTOM DIALOG DISCARDABLE  25, 16, 248, 151
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Birth Options"
FONT 8, "Helv"
BEGIN
    CONTROL         "Chart Options.", 100, "zGroupBox3dClass",WS_GROUP WS_VISIBLE | WS_CHILD |  ZTXT3D_INSET | ZTXT3DLEFT | ZGRP3D_BLACK, 17, 9, 87, 72

    CONTROL          "&Relocate Chart.",101,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,27,25,64,10
    CONTROL          "&Progress Chart.",102,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,27,42,63,10
    CONTROL          "Progress &Cusps.",103,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,27,59,65,10
    CONTROL         "Output Options.", 105, "zGroupBox3dClass",WS_GROUP WS_VISIBLE | WS_CHILD |  ZTXT3D_INSET | ZTXT3DLEFT | ZGRP3D_BLACK, 118, 9, 116, 63

    CONTROL          "&Text Chart File.",106,"Button",BS_AUTOCHECKBOX | 
                    WS_GROUP | WS_TABSTOP,127,25,63,10
    CONTROL          "&Graphics Cartwheel.",107,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,127,41,78,10
    CONTROL          "&Data File(s)",108,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,127,57,50,10
    CONTROL "Data File Type:", 109, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 118, 76, 51, 8
    COMBOBOX        110,118,87,103,35,CBS_DROPDOWNLIST
    PUSHBUTTON      "Customize Options",111,16,94,90,18
    DEFPUSHBUTTON   "OK--Continue",1,16,121,67,18
    PUSHBUTTON      "Help",150,90,121,67,18
    PUSHBUTTON      "Cancel",2,165,121,67,18
END

TRANS_DATA DIALOG DISCARDABLE  65, 18, 209, 159
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Transit Data"
FONT 8, "Helv"
BEGIN
    CONTROL "&Number of Transit Charts To Do:", 101, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 18, 15, 107, 8
    EDITTEXT        114,147,14,27,12
    CONTROL "Planet Range To Work With--", 103, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 19, 33, 98, 8
    CONTROL "&Starting Planet:", 104, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 19, 49, 52, 8
    COMBOBOX        105,91,47,99,91,CBS_DROPDOWNLIST | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "&Ending Planet:", 106, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 20, 69, 49, 8
    COMBOBOX        107,91,67,99,73,CBS_DROPDOWNLIST | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "Separation Period Between Each Transit Chart--", 108, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 20, 91, 157, 8
    CONTROL "&Months:", 109, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 21, 109, 27, 8
    EDITTEXT        110,61,108,25,12
    CONTROL "&Days:", 111, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 105, 110, 20, 8
    EDITTEXT        112,141,108,26,12
    DEFPUSHBUTTON   "OK",1,15,130,52,17
    PUSHBUTTON      "Help",150,77,130,52,17
    PUSHBUTTON      "Cancel",2,141,130,52,17
END

RECT_DATA DIALOG DISCARDABLE  41, 20, 255, 147
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Rectification Data"
FONT 8, "Helv"
BEGIN
    CONTROL          "Check if Birth time is &Known to Within \2611 hour?",
                    101,"Button",BS_AUTOCHECKBOX | BS_LEFTTEXT | WS_TABSTOP,
                    14,6,166,10
    CONTROL "&Birth Rectification Method:", 102, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 25, 88, 8
    COMBOBOX        103,125,24,109,76,CBS_DROPDOWNLIST | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "&Trial Birth Time To Use--", 104, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 43, 81, 8
    CONTROL "Hours:", 105, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 57, 23, 8
    EDITTEXT        106,48,55,24,12,ES_AUTOHSCROLL
    CONTROL "Minutes:", 107, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 83, 57, 29, 8
    EDITTEXT        108,124,55,28,12,ES_AUTOHSCROLL
    CONTROL "AM or PM", 109, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 163, 57, 33, 8
    COMBOBOX        110,204,54,32,30,CBS_DROPDOWNLIST | CBS_SORT | 
                    WS_VSCROLL | WS_TABSTOP
    CONTROL "Known &Angle To Use:", 111, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 81, 72, 8
    COMBOBOX        112,104,79,115,67,CBS_DROPDOWNLIST | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "Sign:", 113, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 15, 98, 18, 8
    COMBOBOX        114,43,95,34,50,CBS_DROPDOWNLIST | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "Degrees:", 115, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 91, 98, 31, 8
    EDITTEXT        116,134,97,26,12,ES_AUTOHSCROLL
    CONTROL "Minutes:", 117, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 172, 99, 29, 8
    EDITTEXT        118,212,98,24,12,ES_AUTOHSCROLL
    PUSHBUTTON      "OK",1,14,123,40,14
    PUSHBUTTON      "Help",150,107,123,40,14
    PUSHBUTTON      "Cancel",2,197,123,40,14
END

BIRTH_INF DIALOG DISCARDABLE  15, -3, 314, 224
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Birth Information:"
FONT 8, "Helv"
BEGIN
    CONTROL "Person's &Name", 101, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 15, 14, 50, 8
    COMBOBOX        102,73,13,141,80,CBS_DROPDOWN | CBS_SORT | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "Sex:", 103, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 222, 14, 20, 8
    COMBOBOX        104,252,12,40,28,CBS_DROPDOWNLIST | WS_TABSTOP
    CONTROL "&Date of Birth--Month:", 105, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 15, 33, 70, 8
    EDITTEXT        106,97,31,22,12
    CONTROL "Day:", 107, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 136, 33, 18, 8
    EDITTEXT        108,162,31,22,12
    CONTROL "Year:", 109, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 204, 33, 20, 8
    EDITTEXT        110,240,31,32,12
    CONTROL "&Time of Day--Hours:", 111, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 15, 52, 66, 8
    EDITTEXT        112,95,50,21,12
    CONTROL "Minutes:", 113, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 130, 52, 29, 8
    EDITTEXT        114,177,50,23,12
    CONTROL "AM or PM:", 115, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 218, 52, 35, 8
    COMBOBOX        116,260,50,32,30,CBS_DROPDOWNLIST | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "&Place Where Located--", 117, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 15, 70, 76, 8
    CONTROL "Country:", 118, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 102, 70, 28, 8
    COMBOBOX        119,140,67,124,78,CBS_DROPDOWN | CBS_SORT | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "&State:", 120, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 22, 88, 21, 8
    COMBOBOX        121,52,87,85,66,CBS_DROPDOWN | CBS_SORT | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "Lo&cation:", 122, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 146, 88, 32, 8
    COMBOBOX        123,185,86,108,71,CBS_DROPDOWN | CBS_SORT | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "&Longitude--Degrees:", 124, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 16, 107, 67, 8
    EDITTEXT        125,91,105,27,12
    CONTROL "Minutes:", 126, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 129, 107, 29, 8
    EDITTEXT        127,169,105,22,12
    CONTROL "East/West:", 129, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 202, 107, 38, 8
    COMBOBOX        128,253,105,40,29,CBS_DROPDOWNLIST | WS_TABSTOP
    CONTROL "L&atitude--Degrees:", 130, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 16, 126, 67, 8
    EDITTEXT        131,91,124,27,12
    CONTROL "Minutes:", 132, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 129, 126, 29, 8
    EDITTEXT        133,169,124,22,12
    CONTROL "North/South:", 135, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 202, 126, 44, 8
    COMBOBOX        134,253,124,40,30,CBS_DROPDOWNLIST | WS_TABSTOP
    CONTROL "Time &Zone:", 136, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 16, 147, 38, 8
    COMBOBOX        151,60,144,96,62,CBS_DROPDOWNLIST | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "Special C&ode:", 138, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 167, 147, 47, 8
    COMBOBOX        139,224,145,77,51,CBS_DROPDOWNLIST | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "GMT Offsets:", 142, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 237, 163, 44, 8
    EDITTEXT        140,224,175,20,12
    CONTROL "H", 143, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 248, 177, 7, 8
    EDITTEXT        141,258,175,20,12
    CONTROL "M", 144, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 284, 177, 7, 8
    PUSHBUTTON      "Birth DB Menu",145,18,166,82,17
    PUSHBUTTON      "Birth Rectification",147,113,166,82,17
    PUSHBUTTON      "Location DB Menu",146,18,195,70,17
    DEFPUSHBUTTON   "OK",1,101,195,59,17
    PUSHBUTTON      "Help",150,170,195,59,17
    PUSHBUTTON      "Cancel",2,239,195,59,17
END

TRANS_INFO DIALOG DISCARDABLE  18, -9, 313, 220
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Transits Information."
FONT 8, "Helv"
BEGIN
    CONTROL "&Event of Interest:", 101, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 15, 14, 58, 8
    COMBOBOX        102,82,13,145,76,CBS_DROPDOWN | CBS_SORT | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "&Date of Event--Month:", 105, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 15, 33, 74, 8
    EDITTEXT        106,101,31,22,12
    CONTROL "Day:", 107, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 137, 33, 18, 8
    EDITTEXT        108,167,31,22,12
    CONTROL "Year:", 109, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 206, 33, 20, 8
    EDITTEXT        110,240,31,32,12
    CONTROL "&Time of Day--Hours:", 111, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 15, 52, 66, 8
    EDITTEXT        112,95,50,21,12
    CONTROL "Minutes:", 113, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 130, 52, 29, 8
    EDITTEXT        114,177,50,23,12
    CONTROL "AM or PM:", 115, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 218, 52, 35, 8
    COMBOBOX        116,260,50,32,32,CBS_DROPDOWNLIST | WS_TABSTOP
    CONTROL "&Place Where Located--", 117, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 15, 70, 76, 8
    CONTROL "Country:", 118, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 102, 70, 28, 8
    COMBOBOX        119,140,67,124,96,CBS_DROPDOWN | CBS_SORT | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "&State:", 120, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 22, 88, 21, 8
    COMBOBOX        121,52,87,85,64,CBS_DROPDOWN | CBS_SORT | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "Lo&cation:", 122, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 146, 88, 32, 8
    COMBOBOX        123,185,86,108,61,CBS_DROPDOWN | CBS_SORT | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "&Longitude--Degrees:", 124, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 16, 107, 67, 8
    EDITTEXT        125,91,105,27,12
    CONTROL "Minutes:", 126, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 129, 107, 29, 8
    EDITTEXT        127,169,105,22,12
    CONTROL "East/West:", 129, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 202, 107, 38, 8
    COMBOBOX        128,253,105,40,29,CBS_DROPDOWNLIST | WS_TABSTOP
    CONTROL "L&atitude--Degrees:", 130, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 16, 126, 67, 8
    EDITTEXT        131,91,124,27,12
    CONTROL "Minutes:", 132, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 129, 126, 29, 8
    EDITTEXT        133,169,124,22,12
    CONTROL "North/South:", 135, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 202, 126, 44, 8
    COMBOBOX        134,253,124,40,30,CBS_DROPDOWNLIST | WS_TABSTOP
    CONTROL "Time &Zone:", 136, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 16, 147, 38, 8
    COMBOBOX        151,59,144,88,63,CBS_DROPDOWNLIST | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "Special C&ode:", 138, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 154, 147, 47, 8
    COMBOBOX        139,207,145,90,56,CBS_DROPDOWNLIST | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "GMT Offsets:", 142, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 194, 162, 44, 8
    EDITTEXT        140,181,174,20,12
    CONTROL "H", 143, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 205, 176, 7, 8
    EDITTEXT        141,215,174,20,12
    CONTROL "M", 144, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 241, 176, 7, 8
    PUSHBUTTON      "Location DB Menu",146,43,167,98,15
    DEFPUSHBUTTON   "OK",1,19,193,70,17
    PUSHBUTTON      "Help",150,113,193,79,17
    PUSHBUTTON      "Cancel",2,215,193,72,17
END

CONV_OPT DIALOG DISCARDABLE  67, 26, 208, 145
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "File Conversion Options."
FONT 8, "Helv"
BEGIN
    CONTROL "&Left Margin (In Inches):", 101, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 12, 12, 78, 8
    EDITTEXT        102,115,10,35,12,ES_AUTOHSCROLL
    CONTROL "Text File &Width (In Inches):", 103, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 12, 29, 90, 8
    EDITTEXT        104,115,27,35,12,ES_AUTOHSCROLL
    CONTROL          "Convert &Comment Files.",105,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,12,44,89,10
    CONTROL          "Convert Cover &Page.",106,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,114,45,82,10
    CONTROL          "Comment Pages &Before Report.",116,"Button",
                    BS_AUTOCHECKBOX | WS_TABSTOP,41,59,114,10
    CONTROL "&File Format:", 104, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 11, 75, 39, 8
    COMBOBOX        108,57,77,135,65,CBS_DROPDOWNLIST | WS_VSCROLL | 
                    WS_TABSTOP
    PUSHBUTTON      "Setup &Styles...",114,11,97,81,17
    PUSHBUTTON      "Pseudo &ASCII...",115,110,97,81,17
    PUSHBUTTON      "OK",1,10,120,51,14
    PUSHBUTTON      "Help",150,74,120,51,14
    PUSHBUTTON      "Cancel",2,141,120,51,14
END

MESSAGE_BOX DIALOG DISCARDABLE  64, 43, 187, 58
STYLE WS_POPUP | WS_VISIBLE | WS_CAPTION
CAPTION "ASTRO is Working..."
FONT 10, "System"
BEGIN
    CONTROL "Processing...", 101, "zStatTxt3dClass",SS_NOPREFIX WS_VISIBLE | WS_CHILD | SS_CENTER | ZTXT3D_INSET, 12, 14, 164, 8
    PUSHBUTTON      "Cancel",2,59,36,67,12
END

PRINT_OPT DIALOG DISCARDABLE  54, 24, 236, 141
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Print Options."
FONT 8, "Helv"
BEGIN
    CONTROL         "&Options.", 105, "zGroupBox3dClass",WS_GROUP | WS_TABSTOP WS_VISIBLE | WS_CHILD |  ZTXT3D_INSET | ZTXT3DLEFT | ZGRP3D_BLACK, 14, 10, 107, 92

    CONTROL          "&Print Cover Page.",101,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,24,24,70,10
    CONTROL          "Print &Comments.",102,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,24,38,63,10
    CONTROL          "&Header on Page 1.",118,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,24,53,74,10
    CONTROL          "Comments &Before Text.",119,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,24,68,86,10
    CONTROL          "Ce&nter Heads.",120,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,24,84,59,10
    CONTROL         "P&rint.", 106, "zGroupBox3dClass",WS_GROUP | WS_TABSTOP WS_VISIBLE | WS_CHILD |  ZTXT3D_INSET | ZTXT3DLEFT | ZGRP3D_BLACK, 132, 11, 89, 91

    CONTROL          "&All Pages...",107,"Button",BS_AUTORADIOBUTTON | 
                    WS_GROUP | WS_TABSTOP,144,24,50,10
    CONTROL          "&Range...",108,"Button",BS_AUTORADIOBUTTON,144,39,41,10
    CONTROL "&From:", 109, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 153, 59, 19, 8
    EDITTEXT        110,179,58,28,12
    CONTROL "&To:", 111, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 153, 79, 12, 8
    EDITTEXT        112,179,78,28,12
    DEFPUSHBUTTON   "OK",1,14,114,47,17
    PUSHBUTTON      "Help",150,68,114,47,17
    PUSHBUTTON      "&Styles...",121,121,114,47,17
    PUSHBUTTON      "Cancel",2,174,114,47,17
END

QUIT DIALOG DISCARDABLE  84, 38, 175, 98
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Do You Want To Save File List?"
FONT 8, "Helv"
BEGIN
    CONTROL "Do You Want To Save File List?", 101, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 24, 9, 114, 8
    CONTROL "If You Choose No, All Files In File List ", 102, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 24, 20, 136, 9
    CONTROL "Will Be Deleted!", 103, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 24, 32, 68, 8
    PUSHBUTTON      "Yes",1,18,50,63,14
    PUSHBUTTON      "No",200,95,50,63,14
    PUSHBUTTON      "Help",150,18,70,63,14
    PUSHBUTTON      "Cancel",2,95,70,63,14
END

DIRECTORIES DIALOG DISCARDABLE  26, 18, 292, 148
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Directory Setup"
FONT 8, "Helv"
BEGIN
    CONTROL "&Main Directory:", 101, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 18, 17, 51, 8
    EDITTEXT        106,97,15,176,12,ES_AUTOHSCROLL
    CONTROL "&Help Directory:", 102, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 18, 37, 50, 8
    EDITTEXT        107,97,35,176,12,ES_AUTOHSCROLL
    CONTROL "Data&base Directory:", 103, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 18, 57, 66, 8
    EDITTEXT        108,97,55,176,12,ES_AUTOHSCROLL
    CONTROL "&Data Directory:", 104, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 18, 77, 51, 8
    EDITTEXT        109,97,76,176,12,ES_AUTOHSCROLL
    CONTROL "&User Directory:", 105, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 18, 97, 50, 8
    EDITTEXT        110,97,97,176,12,ES_AUTOHSCROLL
    DEFPUSHBUTTON   "OK",1,19,118,72,19
    PUSHBUTTON      "Help",150,109,118,72,19
    PUSHBUTTON      "Cancel",2,201,118,72,19
END

PAGE_OPT DIALOG DISCARDABLE  70, 40, 195, 99
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Page Setup"
FONT 8, "Helv"
BEGIN
    CONTROL "Margins (Inches):", 106, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 19, 10, 58, 8
    CONTROL "&Left:", 102, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 28, 26, 16, 8
    EDITTEXT        103,66,24,26,12,ES_AUTOHSCROLL
    CONTROL "&Right:", 104, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 107, 26, 21, 8
    EDITTEXT        105,145,24,26,12,ES_AUTOHSCROLL
    CONTROL "&Top:", 111, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 28, 47, 16, 8
    EDITTEXT        112,66,45,26,12,ES_AUTOHSCROLL
    CONTROL "&Bottom:", 113, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 107, 47, 26, 8
    EDITTEXT        114,145,45,26,12,ES_AUTOHSCROLL
    DEFPUSHBUTTON   "OK",1,12,70,52,19
    PUSHBUTTON      "Help",150,70,70,52,19
    PUSHBUTTON      "Cancel",2,129,70,52,19
END

ORB_EDIT DIALOG DISCARDABLE  25, 5, 312, 193
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Edit Aspect Orbs"
FONT 8, "Helv"
BEGIN
    CONTROL "&Aspect Context:", 101, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 85, 9, 53, 8
    COMBOBOX        102,149,7,81,70,CBS_DROPDOWNLIST | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "Aspect:", 103, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 12, 26, 24, 8
    CONTROL "Degrees:Minutes:", 104, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 60, 26, 58, 8
    CONTROL "Include:", 105, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 124, 26, 28, 8
    CONTROL "Aspect:", 106, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 164, 26, 24, 8
    CONTROL "Degrees:Minutes:", 107, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 211, 26, 58, 8
    CONTROL "Include:", 108, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 276, 26, 28, 8
    CONTROL          "",145,"Static",SS_BLACKRECT,12,37,288,1
    CONTROL "&Conjunct", 109, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 12, 43, 32, 8
    EDITTEXT        110,73,41,30,12,ES_AUTOHSCROLL
    CONTROL          "",111,"Button",BS_AUTOCHECKBOX | WS_TABSTOP,133,42,10,
                    10
    CONTROL "&Sextile", 112, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 12, 58, 23, 8
    EDITTEXT        113,73,56,30,12,ES_AUTOHSCROLL
    CONTROL          "",114,"Button",BS_AUTOCHECKBOX | WS_TABSTOP,133,57,10,
                    10
    CONTROL "&Trine", 115, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 12, 73, 18, 8
    EDITTEXT        116,73,71,30,12,ES_AUTOHSCROLL
    CONTROL          "",117,"Button",BS_AUTOCHECKBOX | WS_TABSTOP,133,72,10,
                    10
    CONTROL "&Opposed", 118, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 12, 88, 30, 8
    EDITTEXT        119,73,86,30,12,ES_AUTOHSCROLL
    CONTROL          "",120,"Button",BS_AUTOCHECKBOX | WS_TABSTOP,133,87,10,
                    10
    CONTROL "S&quared", 121, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 12, 102, 28, 8
    EDITTEXT        122,73,100,30,12,ES_AUTOHSCROLL
    CONTROL          "",123,"Button",BS_AUTOCHECKBOX | WS_TABSTOP,133,101,10,
                    10
    CONTROL "S&emi-Sextile", 124, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 12, 117, 41, 8
    EDITTEXT        125,73,115,30,12,ES_AUTOHSCROLL
    CONTROL          "",126,"Button",BS_AUTOCHECKBOX | WS_TABSTOP,133,116,10,
                    10
    CONTROL "Se&misequiquad.", 127, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 12, 132, 52, 8
    EDITTEXT        128,73,130,30,12,ES_AUTOHSCROLL
    CONTROL          "",129,"Button",BS_AUTOCHECKBOX | WS_TABSTOP,133,131,10,
                    10
    CONTROL "Q&uincunx", 130, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 12, 148, 32, 8
    EDITTEXT        131,73,146,30,12,ES_AUTOHSCROLL
    CONTROL          "",132,"Button",BS_AUTOCHECKBOX | WS_TABSTOP,133,147,10,
                    10
    CONTROL "B&i-Quintile", 133, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 164, 43, 35, 8
    EDITTEXT        134,226,41,30,12,ES_AUTOHSCROLL
    CONTROL          "",135,"Button",BS_AUTOCHECKBOX | WS_TABSTOP,286,42,10,
                    10
    CONTROL "Qui&ntile", 136, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 164, 58, 26, 8
    EDITTEXT        137,226,56,30,12,ES_AUTOHSCROLL
    CONTROL          "",138,"Button",BS_AUTOCHECKBOX | WS_TABSTOP,286,57,10,
                    10
    CONTROL "Tredec&ile", 139, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 164, 73, 32, 8
    EDITTEXT        140,226,71,30,12,ES_AUTOHSCROLL
    CONTROL          "",141,"Button",BS_AUTOCHECKBOX | WS_TABSTOP,286,72,10,
                    10
    CONTROL "&Decile", 142, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 164, 88, 22, 8
    EDITTEXT        143,226,86,30,12,ES_AUTOHSCROLL
    CONTROL          "",144,"Button",BS_AUTOCHECKBOX | WS_TABSTOP,286,87,10,
                    10
    CONTROL          "",146,"Static",SS_BLACKRECT,164,107,134,2
    CONTROL "Non-&Planet Orb:", 147, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 164, 117, 54, 8
    EDITTEXT        148,226,115,30,12,ES_AUTOHSCROLL
    CONTROL "&House Cusp Orb:", 151, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 164, 132, 56, 8
    EDITTEXT        152,226,130,30,12,ES_AUTOHSCROLL
    CONTROL          "",153,"Button",BS_AUTOCHECKBOX | BS_LEFTTEXT | 
                    WS_TABSTOP,284,131,9,10
    PUSHBUTTON      "OK",1,12,169,62,14
    PUSHBUTTON      "Help",150,125,169,62,14
    PUSHBUTTON      "Cancel",2,232,169,62,14
END

ABORT_DLG DIALOG DISCARDABLE  108, 58, 142, 63
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Now Printing"
FONT 8, "Helv"
BEGIN
    PUSHBUTTON      "Cancel",2,33,41,72,14
    CONTROL "Now Printing Page: ", 101, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_CENTER | ZTXT3D_INSET, 27, 16, 66, 8
    CONTROL "Now Printing Page: ", 101, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 2850, 32, 0, 255",102,103,16,20,8
    CONTROL "Now Printing Page: ", 101, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 2850, 32, 0, 255",103,135,48,4,8
END

COVER_DAT DIALOG DISCARDABLE  30, 0, 293, 227
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Cover Page Information."
FONT 8, "Helv"
BEGIN
    CONTROL "Font File To Use:", 111, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 15, 63, 8
    COMBOBOX        112,99,13,132,86,CBS_DROPDOWNLIST | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "Image To Display:", 101, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 35, 63, 8
    COMBOBOX        102,99,33,132,86,CBS_DROPDOWNLIST | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "File Name of Graphic:", 103, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 55, 72, 8
    EDITTEXT        104,99,53,174,12,ES_AUTOHSCROLL
    CONTROL "Cover Page Title:", 105, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 74, 58, 8
    EDITTEXT        106,99,72,174,12,ES_AUTOHSCROLL
    CONTROL "Subject's Name:", 107, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 93, 74, 8
    EDITTEXT        108,98,92,174,12,ES_AUTOHSCROLL
    CONTROL "Astrologer's Name", 113, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 15, 113, 74, 8
    EDITTEXT        114,99,112,174,12,ES_AUTOHSCROLL
    CONTROL "Comments:", 109, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 130, 36, 8
    EDITTEXT        110,14,143,262,50,ES_MULTILINE | ES_AUTOVSCROLL | 
                    WS_VSCROLL | 0x1000
    DEFPUSHBUTTON   "OK",1,14,202,72,16
    PUSHBUTTON      "Help",150,109,202,72,16
    PUSHBUTTON      "Cancel",2,205,202,72,16
END

AST_HELP DIALOG DISCARDABLE  0, 0, 215, 128
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "ASTRO-Helper Files"
FONT 8, "Helv"
BEGIN
    CONTROL "Select &Files.", 106, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 16, 12, 42, 8
    LISTBOX         101,16,26,108,87,LBS_MULTIPLESEL | WS_VSCROLL | 
                    WS_TABSTOP
    PUSHBUTTON      "View File",102,137,12,59,15
    PUSHBUTTON      "Print Files",103,137,32,59,15
    DEFPUSHBUTTON   "Cancel",2,139,92,59,15
    PUSHBUTTON      "Convert Files.",104,138,52,59,15
    PUSHBUTTON      "Help",150,139,72,59,15
END

GRAPH_OPT DIALOG DISCARDABLE  45, 16, 259, 180
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Graphic Wheel Options."
FONT 8, "Helv"
BEGIN
    CONTROL          "Show &Sign Names.",101,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,16,10,74,10
    CONTROL          "Show &House Cusp Degrees.",102,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,16,24,103,10
    CONTROL          "Show House Cusp &Numbers.",103,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,16,38,104,10
    CONTROL          "Show Sign &Lines.",104,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,16,52,69,10
    CONTROL          "Show &Aspect Lines.",105,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,16,66,77,10
    CONTROL          "Use &Glyphs.",106,"Button",BS_AUTOCHECKBOX | WS_TABSTOP,
                    16,81,52,10
    CONTROL          "House Numbers &Outside.",107,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,16,96,93,10
    CONTROL          "Plot &Classically.",108,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,16,112,64,10
    CONTROL          "Show Planet Degrees.",121,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,16,128,80,10
    CONTROL         "&Tick Wheel Options.", 109, "zGroupBox3dClass", WS_VISIBLE | WS_CHILD |  ZTXT3D_INSET | ZTXT3DLEFT | ZGRP3D_BLACK, 130, 11, 108, 65

    CONTROL          "S&ign Tick Wheel.",110,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,147,26,69,10
    CONTROL          "D&ecan Tick Wheel.",111,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,147,41,76,10
    CONTROL          "&Degree Tick Wheel.",112,"Button",BS_AUTOCHECKBOX | 
                    WS_TABSTOP,147,56,78,10
    CONTROL "F&ont Size Factor:", 113, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 132, 87, 57, 8
    EDITTEXT        114,206,86,33,12,ES_AUTOHSCROLL
    PUSHBUTTON      "&Fonts...",115,188,108,51,17
    PUSHBUTTON      "&Colors...",117,118,108,57,17
    PUSHBUTTON      "OK",1,16,150,65,17
    PUSHBUTTON      "Cancel",2,95,150,65,17
    PUSHBUTTON      "Help",150,174,150,65,17
END

ABOUT_BOX DIALOG DISCARDABLE  89, 40, 173, 100
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "About ASTRO For Windows"
FONT 8, "MS Sans Serif"
BEGIN
    ICON            "AstrowIcon",101,14,66,18,20
    CONTROL "ASTRO For Windows", 103, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 49, 10, 70, 8
    CONTROL "\251 Copyright 1993 By Christopher J. Noyes", 104, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 15, 25, 138, 8
    CONTROL "All Right Reserved.", 105, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 52, 40, 64, 8
    CONTROL "Version: 1.04", 106, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 62, 55, 50, 8
    PUSHBUTTON      "OK",1,78,76,40,14
END

PRINT DIALOG DISCARDABLE  81, 58, 161, 64
STYLE WS_POPUP | WS_VISIBLE | WS_CAPTION
CAPTION "Now Printing..."
BEGIN
    DEFPUSHBUTTON   "Cancel",2,58,42,42,14
    CONTROL "Printing:", 101, "zStatTxt3dClass",NOT WS_GROUP WS_VISIBLE | WS_CHILD | SS_CENTER | ZTXT3D_INSET, 7, 9, 150, 10
    CONTROL "Page:", 102, "zStatTxt3dClass",NOT WS_GROUP WS_VISIBLE | WS_CHILD | SS_CENTER | ZTXT3D_INSET, 40, 25, 75, 10
    CONTROL "Page:", 102, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 2850, 32, 0, 255",103,10,47,0,0,NOT WS_GROUP
END

REP_STYLES DIALOG DISCARDABLE  84, 34, 180, 106
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Report Styles"
FONT 8, "MS Sans Serif"
BEGIN
    PUSHBUTTON      "&Regular Style...",101,14,17,67,17
    PUSHBUTTON      "&Bold Style...",102,97,17,67,17
    PUSHBUTTON      "&Headline Style...",103,14,46,67,17
    PUSHBUTTON      "&Italic Style...",104,97,46,67,17
    DEFPUSHBUTTON   "OK",1,16,77,40,14
    PUSHBUTTON      "Cancel",2,123,77,40,14
    PUSHBUTTON      "Help",150,69,77,40,14
    CONTROL          "",108,"Static",SS_BLACKRECT,14,38,150,4
    CONTROL          "",109,"Static",SS_BLACKRECT,87,17,3,45
END

GRA_COLOR DIALOG DISCARDABLE  58, 15, 229, 156
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Graphics Colors"
FONT 8, "MS Sans Serif"
BEGIN
    DEFPUSHBUTTON   "OK",1,40,133,40,14
    PUSHBUTTON      "Cancel",2,147,133,40,14
    PUSHBUTTON      "Help",150,93,133,40,14
    PUSHBUTTON      "&Background Color...",101,18,11,87,14
    PUSHBUTTON      "&Sign Color...",103,18,36,87,14
    PUSHBUTTON      "&House Color...",105,18,61,87,14
    PUSHBUTTON      "&Planet Color...",108,18,85,87,14
    PUSHBUTTON      "&Ascend Color...",115,121,11,87,14
    PUSHBUTTON      "Bright S&ign Color...",111,121,36,87,14
    PUSHBUTTON      "Bright H&ouse Color...",113,121,61,87,14
    PUSHBUTTON      "&Bright Planet Color...",116,121,85,87,14
    PUSHBUTTON      "&Circle Color...",109,71,108,87,14
    CONTROL          "",110,"Static",SS_BLACKRECT,72,103,86,2
    CONTROL          "",111,"Static",SS_BLACKRECT,111,10,2,94
    CONTROL          "",112,"Static",SS_BLACKRECT,18,29,190,3
    CONTROL          "",113,"Static",SS_BLACKRECT,18,54,190,3
    CONTROL          "",114,"Static",SS_BLACKRECT,18,79,190,3
END

GRA_FONT DIALOG DISCARDABLE  101, 39, 170, 95
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Graphic Fonts."
FONT 8, "MS Sans Serif"
BEGIN
    PUSHBUTTON      "&Glyph Font...",101,43,44,80,17
    PUSHBUTTON      "&Data Font...",102,44,15,79,17
    DEFPUSHBUTTON   "OK",1,10,76,40,14
    PUSHBUTTON      "Cancel",2,117,76,40,14
    PUSHBUTTON      "Help",150,63,76,40,14
    CONTROL          "",108,"Static",SS_BLACKRECT,45,36,77,4
END

PSEUDO_DAT DIALOG DISCARDABLE  88, 21, 194, 140
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Psuedo ASCII Options"
FONT 8, "MS Sans Serif"
BEGIN
    EDITTEXT        101,79,11,98,12,ES_AUTOHSCROLL
    EDITTEXT        102,79,27,98,12,ES_AUTOHSCROLL
    EDITTEXT        103,79,43,98,12,ES_AUTOHSCROLL
    EDITTEXT        104,79,60,98,12,ES_AUTOHSCROLL
    EDITTEXT        105,79,77,98,12,ES_AUTOHSCROLL
    EDITTEXT        106,79,94,98,12,ES_AUTOHSCROLL
    CONTROL "Start Head:", 107, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 13, 39, 8
    CONTROL "End Head:", 108, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 30, 36, 8
    CONTROL "Start Bold:", 109, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 45, 39, 8
    CONTROL "End Bold:", 110, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 62, 36, 8
    CONTROL "Start Underscore:", 111, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 79, 59, 8
    CONTROL "End Underscore:", 112, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 95, 56, 8
    DEFPUSHBUTTON   "OK",1,23,116,40,14
    PUSHBUTTON      "Cancel",2,130,116,40,14
    PUSHBUTTON      "Help",150,76,116,40,14
END

PR_SETUP DIALOG DISCARDABLE  71, 24, 219, 113
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Setup Printer"
FONT 8, "Helv"
BEGIN
    LISTBOX         101,16,25,124,75,LBS_SORT | WS_VSCROLL | WS_TABSTOP
    CONTROL "&Printers:", 102, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 17, 8, 28, 8
    DEFPUSHBUTTON   "OK",1,155,10,49,14
    PUSHBUTTON      "Cancel",2,155,29,49,14
    PUSHBUTTON      "Help",150,155,49,49,14
    PUSHBUTTON      "&Setup...",106,155,69,49,14
    PUSHBUTTON      "&Options...",107,155,89,48,14
END

EDIT_DAT DIALOG DISCARDABLE  62, 44, 219, 108
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Editor"
FONT 8, "Helv"
BEGIN
    CONTROL "&Editor Program and Path:", 101, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 13, 13, 83, 8
    EDITTEXT        102,13,28,191,12,ES_AUTOHSCROLL
    CONTROL "&Options:", 103, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 54, 28, 8
    EDITTEXT        104,51,53,85,12,ES_AUTOHSCROLL
    PUSHBUTTON      "OK",1,18,81,51,14
    PUSHBUTTON      "Help",150,82,81,51,14
    PUSHBUTTON      "Cancel",2,149,81,51,14
END

FIND_TXT DIALOG DISCARDABLE  52, 44, 235, 85
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Text To Find."
FONT 8, "MS Sans Serif"
BEGIN
    CONTROL "Text To Find:", 101, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 11, 22, 45, 8
    EDITTEXT        102,59,21,161,12,ES_AUTOHSCROLL
    PUSHBUTTON      "OK",1,25,54,51,14
    PUSHBUTTON      "Help",150,89,54,51,14
    PUSHBUTTON      "Cancel",2,156,54,51,14
END

ARCHIVE_DAT DIALOG DISCARDABLE  55, 28, 239, 120
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Archive Information"
FONT 8, "Helv"
BEGIN
    CONTROL "Archive &Name and Path:", 101, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 18, 80, 8
    EDITTEXT        102,101,16,125,12,ES_AUTOHSCROLL
    CONTROL         "&Archive Program", 106, "zGroupBox3dClass",WS_GROUP WS_VISIBLE | WS_CHILD |  ZTXT3D_INSET | ZTXT3DLEFT | ZGRP3D_BLACK, 13, 34, 115, 28

    CONTROL          "&LHA",107,"Button",BS_AUTORADIOBUTTON,30,46,27,10
    CONTROL          "&PKZIP",108,"Button",BS_AUTORADIOBUTTON,75,46,34,10
    CONTROL          "&Delete Archived Files.",105,"Button",BS_AUTOCHECKBOX | 
                    WS_GROUP | WS_TABSTOP,142,44,84,10
    CONTROL "Archive Program &Command String:", 103, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 72, 111, 8
    EDITTEXT        104,136,70,90,12,ES_AUTOHSCROLL
    PUSHBUTTON      "OK",1,31,96,51,14,WS_GROUP
    PUSHBUTTON      "Help",150,95,96,51,14
    PUSHBUTTON      "Cancel",2,162,96,51,14
END

GRAPH_FILE_OPT DIALOG DISCARDABLE  62, 22, 246, 146
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Graphic File Options."
FONT 8, "Helv"
BEGIN
    CONTROL "Graphic File &Format:", 102, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 14, 67, 8
    COMBOBOX        101,89,13,150,94,CBS_DROPDOWNLIST | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "Image Size &Units:", 107, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 36, 58, 8
    COMBOBOX        108,80,34,79,49,CBS_DROPDOWNLIST | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "Image &Resolution:", 111, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 56, 60, 8
    COMBOBOX        112,84,55,66,51,CBS_DROPDOWNLIST | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL "&Height (units):", 103, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 14, 76, 47, 8
    EDITTEXT        105,68,74,32,12,ES_AUTOHSCROLL
    CONTROL "&Width (units):", 104, "zStatTxt3dClass", WS_VISIBLE | WS_CHILD | SS_LEFT | ZTXT3D_INSET, 112, 76, 45, 8
    EDITTEXT        106,166,75,32,12,ES_AUTOHSCROLL
    CONTROL          "R&everse Graphic.",109,"Button",BS_AUTOCHECKBOX |
                    WS_GROUP | WS_TABSTOP,14,95,90,10
    PUSHBUTTON      "OK",1,15,119,51,14,WS_GROUP
    PUSHBUTTON      "Help",150,99,119,51,14
    PUSHBUTTON      "Cancel",2,186,119,51,14
END


//////////////////////////////////////////////////////////////////////////////
//
// Accelerator
//

IDA_ASTRO ACCELERATORS DISCARDABLE 
BEGIN
    "B",            301,                    VIRTKEY,CONTROL, NOINVERT
    "O",            302,                    VIRTKEY,CONTROL, NOINVERT
    "F",            207,                    VIRTKEY,CONTROL, NOINVERT
    "N",            208,                    VIRTKEY,CONTROL, NOINVERT
    "R",            306,                    VIRTKEY,CONTROL, NOINVERT
    "X",            307,                    VIRTKEY,CONTROL, NOINVERT
    "E",            116,                    VIRTKEY,CONTROL, NOINVERT
    "P",            118,                    VIRTKEY,CONTROL, NOINVERT
    VK_ADD,         1021,                   VIRTKEY,NOINVERT
    VK_BACK,        201,                    VIRTKEY,ALT, NOINVERT
    VK_INSERT,      204,                    VIRTKEY,CONTROL, NOINVERT
    VK_INSERT,      205,                    VIRTKEY,SHIFT, NOINVERT
    VK_MULTIPLY,    1023,                   VIRTKEY,NOINVERT
    VK_SUBTRACT,    1022,                   VIRTKEY,NOINVERT
END


//////////////////////////////////////////////////////////////////////////////
//
// ST_BLK
//

101 ST_BLK DISCARDABLE
BEGIN
    "Secondary (Day for a Year)\1Tertiary (Day for a Lunar "
    "Month)\1Minor (Lunar Month for a Year)\0"
END

102 ST_BLK DISCARDABLE
BEGIN
    "Male\1Female\0"
END

103 ST_BLK DISCARDABLE
BEGIN
    "AM\1PM\0"
END

104 ST_BLK DISCARDABLE
BEGIN
    "Plain ASCII Text (DOS)\1Plain ASCII Text (Windows)\1Plain "
    "ASCII No Line Breaks (DOS)\1Plain ASCII No Line Breaks "
    "(Windows)\1Coded ASCII Text (DOS)\1Coded ASCII Text "
    "(Windows)\1Coded ASCII No Line Breaks (DOS)\1Coded ASCII "
    "No Line Breaks (Windows)\1WordStar Version 3.x\1WordStar "
    "Version 4.x\1WordPerfect 4.x\1WordPerfect 5.x\1XYWrite\1"
    "XYWrite No Line Breaks\1Microsoft Word DOS (RTF)\1Microsoft "
    "Word Windows (RTF)\1Windows Write\1Lotus AMI Pro\0"
END

107 ST_BLK DISCARDABLE
BEGIN
    "Equal House\1Koch\1Placidus\1M House\1Campanus\1Regiomantanus\1"
    "Morinus\0"
END

108 ST_BLK DISCARDABLE
BEGIN
    "Comma Delimited\1Binary File\0"
END

109 ST_BLK DISCARDABLE
BEGIN
    "Natal Charts\1Relocation Charts\1Compatability Charts\1"
    "Composite Charts\1Transit Charts\1Progressed Charts\1"
    "Arabic Charts\1Fixed Charts\0"
END

110 ST_BLK DISCARDABLE
BEGIN
    "ARI\1TAU\1GEM\1CAN\1LEO\1VIR\1LIB\1SCO\1SAG\1CAP\1AQU\1"
    "PIS\0"
END

111 ST_BLK DISCARDABLE
BEGIN
    "1st House/Asc.\1"
    "2nd House\1"
    "3rd House\1"
    "4th House/IC\1"
    "5th House\1"
    "6th House\1"
    "7th House/Desc.\1"
    "8th House\1"
    "9th House\1"
    "10th House/MC\1"
    "11th House\1"
    "12th House\1Ascendant\1Descendant\1"
    "Medium Coeli/Midheaven\1Immum Coeli/Nadir\0"
END

112 ST_BLK DISCARDABLE
BEGIN
    "Solar Chart Method\1Flat Chart Method\1Sunrise Birth-Time\1"
    "Trial & Error\1Use Known Angle\0"
END

113 ST_BLK DISCARDABLE
BEGIN
    "North\1South\0"
END

114 ST_BLK DISCARDABLE
BEGIN
    "West\1East\0"
END

115 ST_BLK DISCARDABLE
BEGIN
    "Standard Time\1War Time\1Daylight Savings\1Double British "
    "Summer\1Summer Time\1Winter Time\1Other\0"
END

117 ST_BLK DISCARDABLE
BEGIN
    "Sun\1Moon\0"
END

118 ST_BLK DISCARDABLE
BEGIN
    "Ascendant\1Sun\1Moon\1Mercury\1Venus\1Mars\1Jupiter\1"
    "Saturn\1Uranus\1Neptune\1Pluto\1North Node\1South Node\1"
    "Medium Coeli\1Immum Coeli\1Part Of Fortune\1Vertex\1East "
    "Point\0"
END

116 ST_BLK DISCARDABLE
BEGIN
    "Eastern Atlantic\1Atlantic Standard\1Eastern Standard\1"
    "Central Standard\1Mountain Standard\1Pacific Standard\1"
    "Hawaii\1Greenwich Mean\1Western European\1Eastern Europe\1"
    "Eurasia\1China\1Japan\1Indochina\1New Zealand\1E. Australia\1"
    "S. Australia\1W. Australia\1India\1Samoa\1Int'l Date "
    "Line\1Other\0"
END

105 ST_BLK DISCARDABLE
BEGIN
    "ASTRO Glyphs Font\1ASTRO Pi (Normal)\1ASTRO Pi (Reverse)\1"
    "WingDings\1User Font and Text\1User Bitmap\0"
END

106 ST_BLK DISCARDABLE
BEGIN
    "Sun Planet Glyph\1Moon Planet Glyph\1Mercury Planet "
    "Glyph\1Venus Planet Glyph\1Mars Planet Glyph\1Jupiter "
    "Planet Glyph\1Saturn Planet Glyph\1Uranus Planet Glyph\1"
    "Neptune Planet Glyph\1Pluto Planet Glyph\1North Node "
    "Glyph\1South Node Glyph\1Aries Sign Glyph\1Taurus Sign "
    "Glyph\1Gemini Sign Glyph\1Cancer Sign Glyph\1Leo Sign "
    "Glyph\1Virgo Sign Glyph\1Libra Sign Glyph\1Scorpio Sign "
    "Glyph\1Sagittarius Sign Glyph\1Capricorn Sign Glyph\1"
    "Aquarius Sign Glyph\1Pisces Sign Glyph\0"
END

122 ST_BLK DISCARDABLE
BEGIN
    "Aries Sign Glyph\1Taurus Sign Glyph\1Gemini Sign Glyph\1"
    "Cancer Sign Glyph\1Leo Sign Glyph\1Virgo Sign Glyph\1"
    "Libra Sign Glyph\1Scorpio Sign Glyph\1Sagittarius Sign "
    "Glyph\1Capricorn Sign Glyph\1Aquarius Sign Glyph\1Pisces "
    "Sign Glyph\0"
END

119 ST_BLK DISCARDABLE
BEGIN
    "Placeable Mono Windows Metafile .WMF\1Placeable Color "
    "Windows Metafile .WMF\1Mono Windows Metafile .WMF\1Color "
    "Windows Metafile .WMF\1Monochrome Bitmap\1Color Bitmap\1"
    "Color .EPS\1Color GIF\1Monochrome .PCX\1Color .PCX\1Monochrome "
    "TIFF\1Color TIFF (Uncompressed)\1Color TIFF (Compressed)\0"
END

120 ST_BLK DISCARDABLE
BEGIN
    "Dots\1Inches\1Millimiters\0"
END

121 ST_BLK DISCARDABLE
BEGIN
    "Screen Res.\1"
    "100 dpi\1"
    "150 dpi\1"
    "180 dpi\1"
    "300 dpi\0"
END




#ifdef APSTUDIO_INVOKED
//////////////////////////////////////////////////////////////////////////////
//
// TEXTINCLUDE
//

1 TEXTINCLUDE DISCARDABLE 
BEGIN
    "resource.h\0"
END

2 TEXTINCLUDE DISCARDABLE 
BEGIN
    "#define APSTUDIO_HIDDEN_SYMBOLS\r\n"
    "#include ""windows.h""\r\n"
    "#undef APSTUDIO_HIDDEN_SYMBOLS\r\n"
    "\0"
END

3 TEXTINCLUDE DISCARDABLE 
BEGIN
    "\r\n"
    "\0"
END

/////////////////////////////////////////////////////////////////////////////////////
#endif    // APSTUDIO_INVOKED


#ifndef APSTUDIO_INVOKED
////////////////////////////////////////////////////////////////////////////////
//
// Generated from the TEXTINCLUDE 3 resource.
//


/////////////////////////////////////////////////////////////////////////////////////
#endif    // not APSTUDIO_INVOKED

#endifÿ