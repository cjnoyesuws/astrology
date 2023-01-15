#include "zapp.hpp"
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "dialogs.h"
#include "asfrmdlg.hpp"
#include "text.hpp"
#include <io.h>
#include <stdlib.h>
#include <string.h>
#include "acombbox.hpp"
#include "basedcs.h"



TextToSearchDlgf::TextToSearchDlgf( zWindow *pPar, zString *p ) :
		    FormDlgf(pPar,zResId("FIND_TXT"), HELPID_DLG_DEFAULT )
{
 new zStringEdit(this, IDC_TXTEXT, p, "X(100)", FLD_ALPHANUMERIC);
 centerDialog( this );
 show();
 modal();
}




