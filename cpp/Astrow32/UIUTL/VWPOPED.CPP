#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "tabs.hpp"
#include "fptr.h"
#include "sexcodes.hpp"
#include "virttext.hpp"
#include "vwpoped.hpp"
#include "errors.fns"
#include "basedcs.h"
#include "astromn.h"
#include "menuutl.hpp" 
#include "resstr.hpp"

extern int centerDialog( zFrameWin *fw );
static int itm[] = {IDM_EUNDO, IDM_ECUT, IDM_ECOPY, IDM_EPASTE, IDM_EDEL, 0 };

ViewPopEdit::ViewPopEdit(zFrameWin *pPar, VirtualTextBuffer *pv, int pa ) :
	   zMDIChildFrame(pPar, new zSizer(150,150,300,200),zSTDFRAME,CResStr(_VWP_TEXT)/*"Text to Edit"*/)
{
 para = pa;
 pVirt = pv;
 edit = new zEditBox(this,new zSizeWithParent,zSCROLLV|ES_WANTRETURN,"",101 );
 edit->setStoreAddr((zString *)&buf);
 load();
 centerDialog( this );
 edit->show();
 deleteOnClose(TRUE);
 app->rootWindow()->menu()->setCommand(this,(CommandProc)&ViewPopEdit::command,
   IDM_EUNDO, IDM_EDEL );
}

int ViewPopEdit::load()
{
 char *gbuf;
 int len;

 gbuf = pVirt->getText(para, len, flags);
 buf.set( gbuf, len );
 buf.preProcess();
 edit->setToDefault();
 edit->hasChanged( 0 );
 return( 1 );
}

void EditTextBlock::set( char *p, int l )
{
 buf.reSize(l+2);
 memcpy((char *)buf, p, l );
 buf[(unsigned)l]= (unsigned char)'\0';
 l = buf.length();
}


int ViewPopEdit::save()
{
 edit->storeData();
 edit->hasChanged(0);
 buf.postProcess();
 pVirt->replaceParaAt(para, flags, (char *)buf.get() );
 pVirt->dirty() = 1;
 return( 1 );
}

void EditTextBlock::preProcess()
{
 char *gpt, *npt, *nbuf;
 int len, i, t, l;

 nsr = 0;
 nTabs = 0;
 memset(tabbuf, 0, sizeof(tabbuf));
 len = buf.length();
 nbuf = new char[len+20];
 for ( gpt = (char *)buf, npt = nbuf, t = 0, i = 0; i < len; i++ ) {
     if ( *gpt == '\1' ) {
	l = *(gpt+1);
	l += 2;
	memcpy( tabbuf, gpt, l );
	tabbuf[l]='\0';
	gpt += l;
	i += l;
	}
     if ( *gpt == '\n' ) {
	*npt++ = '\r';
	*npt++ = *gpt++;
	}
     else if ( *gpt == '\x80' ) {
	stickRet[nsr++] = i+1;
	*npt++ = '\r';
	*npt++ = '\n';
	gpt++;
	}
     else if ( *gpt == '|' ) {
	*npt++ = *gpt++;
	tabs[t++] = *gpt++;
	}
     else
	*npt++ = *gpt++;
     }
 if ( t )
    nTabs = t++;
 *npt++ = '\0';
 *npt++ = '\0';
 for ( i = 0; i < nsr; i++ ) {
     if ( stickRet[i] > 2 )
        stickRet[i] = stickRet[i]-len;
     }   
 buf = nbuf;
 delete nbuf;
}

void EditTextBlock::postProcess()
{
 char *xp, *bp;
 int i, j, t;
 zString x(buf.length()+20+strlen(tabbuf));

 x = tabbuf;
 for ( t = 0, xp = (char *)x+x.length(), bp = (char *)buf, i = 0, j = 0; i < buf.length(); i++ ) {
     if (bp[i] == '\t') {
	xp[j++] = ' ';
	}
     else if ( bp[i] == '|' ) {
	xp[j++]=bp[i];
	if ( t < nTabs )
	   xp[j++]=tabs[t++];
	else
	   xp[j++]=(unsigned char)i;
	}
     else if ( bp[i] != '\r' ) {
	xp[j++]=bp[i];
	}
     }
 for ( i = 0; i < nsr; i++ ) {
    switch( stickRet[i] ) {
          case 1:
	       if ( xp[0] == '\n' )
   	          xp[0] = 0x80;
	       break;
          case 2:
	       if ( xp[1] == '\n' )
   	          xp[1] = 0x80;
	       break;
          case -1:
	       if ( xp[j-1] == '\n' )
   	          xp[j-1] = 0x80;
	       break;
          case -2:
	       if ( xp[j-2] == '\n' )
	          xp[j-2] = 0x80;
	       break;
          default :
	        break;
          }
       }   
 xp[j++] = '\0';
 buf = x;
}

int ViewPopEdit::kill(zEvent *e)
{
 if ( edit->hasChanged() ) {
    zMessage *mp = new zMessage( this, CResStr(_VWP_CHQUCL)/*"Text Has Changed, do You Want to Save"*/,
          CResStr(_VWP_TXTCH)/*"Text Has Changed"*/, MB_YESNOCANCEL );
    if ( mp->isCancel() )
       return( 1 );
    else if ( mp->isYes() ) {
       save();
       return( 0 );
       }
    else
       return( 0 );
    }

 app->rootWindow()->menu()->removeCommand(this,(CommandProc)&ViewPopEdit::command );
 return( 0 );
}

int ViewPopEdit::command(zCommandEvt *e)
{
 if ( (HWND)*this != GetFocus() && (HWND)*edit != GetFocus()  )
    return( 0 );
 switch( e->cmd() ) {
       case IDM_ECOPY :
	    edit->copy();
	    break;
       case IDM_EPASTE :
	    edit->paste();
	    break;
       case IDM_ECUT :
	    edit->cut();
	    break;
       case IDM_EDEL :
	   edit->replaceSelection("");
	   break;
       case IDM_EUNDO :
	   if ( edit->canUndo() )
	      edit->undo();
	   break;
       default :
	   return( 0 );
	   break;
       }
 return( 1 );
}


int ViewPopEdit::MDIActivate(zActivateEvt *e)
{
 if ( e->active() )
    enableMenuItems(app->rootWindow()->menu(), itm );
 else
    disableMenuItems(app->rootWindow()->menu(), itm );
 return( 0 );
}
