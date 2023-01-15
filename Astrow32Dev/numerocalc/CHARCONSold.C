/* File Containing global char constant and char array data
   Referenced by file charcons.h for external references*/

#include "stdafx.h"

char ynprompt[] = "Press Y, N or Space to Select.";
char selprompt[] = "Space or First Letter Selects.";
char main_st[] = "  F1-Help   \'Q\'+ENTER-Quit   Cursor Keys or First Letter"
   " then ENTER-Select.";
char screen_st[] = "  F1-Help    F10-Finish    ESC-Escape  ";
char ERROR1[] = "ERROR!";
char ERROR2[] = "ERROR!!";
char error1[] = "Error!";
char error2[] = "Error!!";
char warn1[]  = "Warning!";
char warn2[]  = "Warning!!";
char fil_dev_prompt[] = "Enter File Name or Device.";
char colors[] = { "Black,Blue,Green,Cyan,Red,Magenta,Brown,White" };
char n1filelistname[] = "N1FILES.LST";
char _far P_BOLD_ON[] = "<27>E";
char _far P_BOLD_OFF[] = "<27>F";
char _far P_SCOR_ON[] = "<27>-<1>";
char _far P_SCOR_OFF[] = "<27>-<0>";
char _far P_HEAD_ON[] = "<27>-<1><27>E";
char _far P_HEAD_OFF[] = "<27>-<0><27>F";
char _far def_pinit[] = "<27>1";
char _far def_preset[] = "<12><27>@";
char _far def_peofp[] = "<27>J<1>";
char _far def_hispd[] = "<27>Y<%></>";
char _far def_lowspd[] = "<27>L<%></>";
char _far def_lowdns[] = "<27>K<%></>";
char _far def_quadns[] = "<27>Z<%></>";
char *lfcr[] = { "\n", "\r", "\r\n" };
char _far nohelpmsg[] = { "Problem Starting Help or File Named NUMERO.HLP Not Found, Help Not Available!!" };
char _far hlp[] = { "HELP" };
