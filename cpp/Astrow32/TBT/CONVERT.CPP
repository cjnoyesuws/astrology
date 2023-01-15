#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#include "asfrmdlg.hpp"
#include "acombbox.hpp"
#include <stdlib.h>
#include <io.h>
#include "tbtoptn.hpp"
#include "tbtutil.h"
#include "asfrmdlg.hpp"
#include "msg.hpp"

extern int doExec( char *fnc, char *p1, char *p2 );

int convertEditorFile( char *old, char *newn, int cnv_to )
{
 zString command;
 int ren = 0, _break = 0;

 if ( cnv_to )
    command = theTbtOptions.getTextFormatKey() & "TOAST";
 else
    command =  "AST2" & theTbtOptions.getTextFormatKey();
 ProcMessage * pm = new ProcMessage( " Converting File... ", &_break );
 doExec( (char *)command, old, newn );
 delete pm;
 return( 1 );
}
                                            