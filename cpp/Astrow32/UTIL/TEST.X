FILE_NAME DIALOG DISCARDABLE  55, 38, 240, 100
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Name For Chart in File List"
FONT 8, "Helv"
BEGIN
    LTEXT           "&Name:",101,14,12,22,8
    EDITTEXT        102,71,7,154,12,ES_AUTOHSCROLL
    LTEXT           "&Comments:",103,14,30,36,8
    EDITTEXT        104,71,29,154,12,ES_AUTOHSCROLL
    LTEXT           "Chart Type:",105,14,50,39,9
    LTEXT           "*",106,73,50,154,10,SS_NOPREFIX
    PUSHBUTTON      "OK",1,13,74,64,14
    PUSHBUTTON      "Help",150,87,74,64,14
    PUSHBUTTON      "Cancel",2,160,74,64,14
END

FILE_EDIT DIALOG DISCARDABLE  55, 29, 240, 122
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "Edit Name For Chart in File List."
FONT 8, "Helv"
BEGIN
    LTEXT           "&Name:",101,14,17,22,8
    EDITTEXT        102,71,12,154,12,ES_AUTOHSCROLL
    LTEXT           "&Comments:",103,14,35,36,8
    EDITTEXT        104,71,34,154,12,ES_AUTOHSCROLL
    LTEXT           "Chart Type:",105,14,55,39,9
    LTEXT           "*",106,73,55,154,10,SS_NOPREFIX
    LTEXT           "File Name:",107,14,71,39,9
    LTEXT           "*",108,73,71,154,10,SS_NOPREFIX
    PUSHBUTTON      "OK",1,13,93,64,14
    PUSHBUTTON      "Help",150,87,93,64,14
    PUSHBUTTON      "Cancel",2,160,93,64,14
END

FILE_KILL DIALOG DISCARDABLE  68, 21, 215, 139
STYLE DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
CAPTION "OK To Delete File?"
FONT 8, "Helv"
BEGIN
    LTEXT           "Name:",101,19,14,22,8
    LTEXT           "*",102,78,14,123,8
    LTEXT           "Comments:",103,19,27,36,8
    LTEXT           "*",104,78,27,123,8
    LTEXT           "Chart Type:",105,19,41,39,9
    LTEXT           "*",106,78,40,123,10
    LTEXT           "File Name:",107,19,55,39,9
    LTEXT           "*",108,78,54,123,10
    CONTROL         "Continue To Ask?",109,"Button",BS_AUTOCHECKBOX |
		    BS_LEFTTEXT | WS_TABSTOP,19,71,71,10
    PUSHBUTTON      "OK--Delete",1,32,89,68,16
    PUSHBUTTON      "No--Don't",200,112,89,68,16
    PUSHBUTTON      "Help",150,112,113,68,16
    PUSHBUTTON      "Cancel",2,32,113,68,16
END

