#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "abutton.hpp"

#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )

YNButton::YNButton(zDialogFrame *pDf,int id, char *pY, char *pN)
		        		       : zButton(pDf,id)
{
 yes = pY;
 no = pN;
 val = 0;

 text(no);
 setNotifyClicked(this,(NotifyProc)&YNButton::notifyClick);
 }

int YNButton::notifyClick(zEvent *e)
{
 if ( val ) {
    val = 0;
    text(no);
    }
 else {
    val = 1;
    text(yes);
    }
 return( 1 );
}

YNButton::buttonVal(int v)
{
 val = v;
 if ( val ) {
    text(yes);
    }
 else {
    text(no);
    }
 return( val );
}
