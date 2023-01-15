#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#include <intpack\zip.hpp>
#include <assert.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "charcons.h"
#include "tabs.hpp"
#include "virttext.hpp"
#include "paths.hpp"
#include "fview.hpp"
#include "asfrmdlg.hpp"
#include "text.hpp"
#include "astromn.h"
#include "inifile.hpp"
#include "repstyle.hpp"
#include "mrufile.hpp"
#include "menuutl.hpp"
#include "acombbox.hpp"
#include "comment.hpp"
#include "coverdat.hpp"
#include "helpid.h"
#include "asframe.hpp"
#ifdef NEW
#ifdef PRO
#include "vwpoped.hpp"
#include "msg.hpp"
#endif
#endif
#include "resstr.hpp"

extern void zYield(int y);
extern void do_parse_file( FILE_DB *pFd );
extern int doPrintFile( FILE_DB *, zWindow * );
extern int doConvText( zWindow *, FILE_DB * );

static int nOpen; /* number of times this is open. */
static int *pnWidReg;
static int *pnWidItal;
static int *pnWidBold;
static int *pnWidHead;

typedef int (zEvH::*KeyProc)(zKeyEvt*);

int FileViewPane::size( zSizeEvt *e)
{
 canvas()->setDirty();
 cxClient=e->width();
 cyClient=e->height();
 cyLines = cyClient / cyChar;
 cxTab = cxClient / 62;
 if ( cxTab < cxChar )
    cxTab = cxChar;
// debug("in Size cx = %d, cy = %d, ct = %d, cxc = %d",
//      cxClient, cyClient, cxTab, cxChar );
 return(1);
}


void FileViewPane::setMetrics()
{
 ReportStyles rs(canvas(), 1);

 rs.getFromIni(ViewerData_SEC);
 cbReg = GetSysColor(COLOR_WINDOW);
 cbSel = GetSysColor(COLOR_HIGHLIGHT);
 cbUsed = cbReg;
 ctReg = rs.checkColor( rs.getRegColor() );
 ctBold = rs.checkColor(rs.getBoldColor() );
 ctItal = rs.checkColor(rs.getItalColor() );
 ctHead = rs.checkColor(rs.getHeadColor() );
 if ( pbBack != NULL )
    delete pbBack;
 pbBack=new zBrush(zColor(GetSysColor(COLOR_WINDOW)) );
 if ( pfReg != NULL )
    delete pfReg;
 pfReg = new zFont( *rs.getRegFont(), canvas() );
 if ( pfBold != NULL )
    delete pfBold;
 pfBold = new zFont( *rs.getBoldFont(), canvas() );
 if ( pfItal != NULL )
    delete pfItal;
 pfItal = new zFont( *rs.getItalFont(), canvas() );
 if ( pfHead != NULL )
    delete pfHead;
 pfHead = new zFont( *rs.getHeadFont(), canvas() );

 canvas()->lock();
 canvas()->pushFont(pfReg);
 zFontInfo *pFi = new zFontInfo( canvas() );
 cxChar = pFi->width();
 cyChar = pFi->height()+pFi->externLead();
 delete pFi;
 if ( pnWidReg != NULL )
    GetCharWidth(*canvas(), 0, 255, pnWidReg);
 canvas()->popFont();
 canvas()->pushFont(pfHead);
 if ( pnWidHead != NULL )
    GetCharWidth(*canvas(), 0, 255, pnWidHead);
 canvas()->popFont();
 canvas()->pushFont(pfBold);
 if ( pnWidBold != NULL )
    GetCharWidth(*canvas(), 0, 255, pnWidBold);
 canvas()->popFont();
 canvas()->pushFont(pfItal);
 if ( pnWidItal != NULL )
    GetCharWidth(*canvas(), 0, 255, pnWidItal);
 canvas()->popFont();
 canvas()->unlock();
 zRect r;
 getInterior(r);
 cxClient = r.width();
 cyClient = r.height();
 cxTab = cxClient / 62;
 cxTab--;
 if ( cxTab < cxChar )
    cxTab = cxChar;
 cyLines = cyClient / cyChar;
 cxStart = cxChar / 3;
 dblclkTime=GetDoubleClickTime();
}

int FileViewPane::up1Page()
{
 int brks[75], nBrk, i;
 unsigned char flgs[75];
 LOC x = top;
 int nLines, l;
 char *pt;

 if ( x.para == 0 ) {
    x.get(pVTBuf,0);
    top = x;
    return( 0 );
    }
 nLines = cyLines;
 if ( x.ofs ) {
    x.get(pVTBuf,x.para);
    pt = pVTBuf->getText(x.para, x.len, x.flags );
    if ( x.len < pVTBuf->getVBlen() && x.ofs < pVTBuf->getVBlen()
	 && pt != NULL ) {
       l = getBreaks( pt, x.ofs+1, x.flags, brks, flgs, 74 );
       nLines -= l;
       }
    }
 do {
    x.get(pVTBuf,x.para-1);
    pt = pVTBuf->getText(x.para, x.len, x.flags );
    if ( pt == NULL )
       return( 0 );
    l = getBreaks( pt, x.len, x.flags, brks, flgs, 74 );
    l--;
    if ( nLines >= l ) {
       nLines -= l;
       l = 0;
       }
    if ( x.para == 0 ) {
       x.get(pVTBuf,0);
       top = x;
       return( 0 );
       }
    } while ( nLines && !l );
 if ( l ) {
    x.ofs = brks[l-nLines+1];
    }
 top = x;
 zScrollInfoVert *pSiv = scrollBarVert();
 pSiv->pos(top.para);
 return( 1 );
}

void FileViewPane::updateLineParaTrans(int ofs )
{
 int *p = pLineParaTrans;

 while ( *p != -1 ) {
       *p++ += ofs;
       }
}

int FileViewPane::scroll( zEvent *e )
{
 LOC l1;
 int o1;
 char *pt1;
 zScrollInfoVert *pSiv = scrollBarVert();
 switch( e->parm1() ) {
       case SB_TOP:
	    pSiv->pos(1);
	    top.get(pVTBuf, 1);
	    canvas()->setDirty();
	    break;
       case SB_BOTTOM:
	    pSiv->pos(pVTBuf->getParaCount()-2);
	    top.get(pVTBuf,pVTBuf->getParaCount()-2);
	    canvas()->setDirty();
	    break;
       case SB_PAGEUP:
	    up1Page();
	    canvas()->setDirty();
	    break;
       case SB_PAGEDOWN:
	    if (bottom.para <= pVTBuf->getParaCount()-2) {
	       pSiv->pos(bottom.para);
	       top = bottom;
	       }
	    canvas()->setDirty();
	    break;
       case SB_THUMBPOSITION:
	    top.get(pVTBuf,pSiv->pos());
	    canvas()->setDirty();
	    break;
       case SB_LINEDOWN:
	    {
	    if (top.para >= pVTBuf->getParaCount()-2) {
	       MessageBeep(-1);
	       return( 1 );
	       }
	    l1 = top;
	    //debug( "top: para = %d, ofs = %d, len = %d", top.para, top.ofs, top.len );
	    pt1 = pVTBuf->getText(l1.para, l1.len, l1.flags );
	    if ( pt1 == NULL ) {
	       MessageBeep(-1);
	       return( 1 );
	       }
	    l1.ofs = getNextBreak( pt1, l1.len, l1.ofs, l1.flags );
	    //debug( "l1: para = %d, ofs = %d, len = %d", l1.para, l1.ofs, l1.len );
	    if ( l1.ofs == -1 || l1.ofs >= l1.len ) {
	       l1.get(pVTBuf,l1.para+1);
	       //debug( "l1: para = %d, ofs = %d, len = %d", l1.para, l1.ofs, l1.len );
	       pSiv->pos(l1.para);
	       }
	    top = l1;
	    //debug( "top: para = %d, ofs = %d, len = %d", top.para, top.ofs, top.len );
	    zRect x(0, 0, cxClient, cyClient);
	    ScrollWindow( *this, 0, -cyChar, NULL,(LPRECT) &x );
	    cyCur = ((cyLines -1) * cyChar);
	    cxCur = cxStart;
	    canvas()->lock();
	    canvas()->pushBrush( pbBack );
	    zRect rx(0, ((cyLines-1) * cyChar), cxClient, cyClient );
	    canvas()->fill(rx, pbBack);
	    l1 = bottom;
	    pt1 = pVTBuf->getText(l1.para, l1.len, l1.flags );
	    if ( pt1 == NULL ) {
               MessageBeep(-1);
	       canvas()->popBrush();
	       canvas()->unlock();
	       return( 1 );
	       }
	    updateLineParaTrans(-cyChar);
	    if ( l1.para == selPara )
	       cbUsed = cbSel;
	    else
	       cbUsed = cbReg;
	    drawPara( pt1+l1.ofs, l1.len-l1.ofs, l1.flags, l1.ofs );
	    canvas()->popBrush();
	    canvas()->unlock();
	    ValidateRect(*this, (LPRECT) &x );
	    if ( l1.ofs >= l1.len )
	       l1.get( pVTBuf, l1.para+1 );
	    bottom = l1;
	    }
	    break;
       case SB_LINEUP:
	    {
            l1 = top;
	    if ( l1.para == 1 )
	       return( 1 );
	    //debug( "top: para = %d, ofs = %d, len = %d", top.para, top.ofs, top.len );
	    if ( l1.ofs == 0 ) {
	       l1.get(pVTBuf, l1.para-1);
	       //debug( "l1: para = %d, ofs = %d, len = %d", l1.para, l1.ofs, l1.len );
	       pt1 = pVTBuf->getText(l1.para, l1.len, l1.flags );
	       if ( pt1 == NULL ) {
                  MessageBeep(-1);
	          return( 1 );
	          }
	       l1.ofs = getPrevBreak( pt1, l1.len, l1.len, l1.flags );
	       //debug( "l1: para = %d, ofs = %d, len = %d", l1.para, l1.ofs, l1.len );
	       pSiv->pos(l1.para);
	       }
	    else {
	       pt1 = pVTBuf->getText(l1.para, l1.len, l1.flags );
	       l1.ofs = getPrevBreak( pt1, l1.len, l1.ofs, l1.flags );
	       //debug( "l1: para = %d, ofs = %d, len = %d", l1.para, l1.ofs, l1.len );
	       }
	    if ( l1.ofs == -1 ) {
	       l1.get(pVTBuf,l1.para-1);
	       //debug( "l1: para = %d, ofs = %d, len = %d", l1.para, l1.ofs, l1.len );
	       pSiv->pos(l1.para);
	       }
	    top = l1;
	    //debug( "top: para = %d, ofs = %d, len = %d", top.para, top.ofs, top.len );
	    zRect y(0, 0, cxClient, cyClient);
	    ScrollWindow( *this, 0, cyChar, NULL,(LPRECT) &y );
	    cyCur = 0;
	    cxCur = cxStart;
	    canvas()->lock();
	    canvas()->pushBrush( pbBack );
	    zRect wy(0, 0, cxClient, cyChar);
	    canvas()->fill(wy, pbBack);
	    pt1 = pVTBuf->getText(l1.para, l1.len, l1.flags );
	    if ( pt1 == NULL ) {
               MessageBeep(-1);
	       canvas()->popBrush();
	       canvas()->unlock();
	       return( 1 );
	       }
	    if ( l1.para == selPara )
	       cbUsed = cbSel;
	    else
	       cbUsed = cbReg;
	    updateLineParaTrans(cyChar);
	    drawPara( pt1+l1.ofs, l1.len-l1.ofs, l1.flags, l1.ofs );
	    canvas()->popBrush();
	    canvas()->unlock();
	    ValidateRect(*this, (LPRECT) &y );
	    l1 = bottom;
	    if ( l1.ofs == 0 ) {
	       l1.get(pVTBuf, l1.para-1);
	       //debug( "l1: para = %d, ofs = %d, len = %d", l1.para, l1.ofs, l1.len );
	       pt1 = pVTBuf->getText(l1.para, l1.len, l1.flags );
	       if ( pt1 == NULL ) {
                  MessageBeep(-1);
	          return( 1 );
	          }
	       l1.ofs = getPrevBreak( pt1, l1.len, l1.len, l1.flags );
	       //debug( "l1: para = %d, ofs = %d, len = %d", l1.para, l1.ofs, l1.len );
	       pSiv->pos(l1.para);
	       }
	    else {
	       pt1 = pVTBuf->getText(l1.para, l1.len, l1.flags );
	       if ( pt1 == NULL ) {
                  MessageBeep(-1);
	          return( 1 );
	          }
	       l1.ofs = getPrevBreak( pt1, l1.len, l1.ofs, l1.flags );
	       //debug( "l1: para = %d, ofs = %d, len = %d", l1.para, l1.ofs, l1.len );
	       }
	    if ( l1.ofs == -1 ) {
	       l1.get(pVTBuf,l1.para-1);
	       //debug( "l1: para = %d, ofs = %d, len = %d", l1.para, l1.ofs, l1.len );
	       pSiv->pos(l1.para);
	       }
	    bottom = l1;
	    }
	    break;
       default :
	    return( 0 );
            break;
	    }
 return( 1 );
}

int FileViewPane::command( zCommandEvt *e )
{
 if ( (HWND)*this != GetFocus() ) 
    return( 0 );
 switch( (unsigned int)e->cmd() ) {
      case IDM_FPRINT :
	   doPrintFile( &pVTBuf->getFileDb(), this );
	   break;
      case IDM_FEXPORT :
	   doConvText( this, &pVTBuf->getFileDb() );
	   break;
      case IDM_UPARSE :
	   do_parse_file( &pVTBuf->getFileDb() );
	   break;
#ifdef NEW
      case IDM_FCLOSE :
	   //PostMessage((HWND)(*this),WM_CLOSE,0,0L);
	   PostMessage((HWND)(*parent()),WM_CLOSE,0,0L);
	   break;
#endif
#ifdef PRO
#ifdef NEW
      case IDM_EUNDO :
           pVTBuf->undo();
           canvas()->setDirty();
           break;
      case IDM_ECOPY :
      case IDM_ECUT :
	   if ( selPara != -1 ) {
	      int l;
	      unsigned char f;
	      char *p = pVTBuf->getText(selPara,l,f);
	      char *b = new char[l+1];
	      memcpy( b, p, l );
	      b[l] = '\0';
	      EditTextBlock e;
	      e.set(b,l);
	      e.preProcess();
	      ((AstroAppFrame *)(app->rootWindow()))->pClip->add((char *)e.get());
	      delete b;
	      }
	   if ( e->cmd() == IDM_ECOPY )
	      break;
      case IDM_EDEL :
	   if ( selPara != -1 ) {
	      pVTBuf->deletePara(selPara);
	      canvas()->setDirty();
	      }
      break;
      case IDM_EPASTE :
	   {
	   if ( selPara != -1 && (AstroAppFrame *)
		((AstroAppFrame *)(app->rootWindow()))->pClip->isTextAvail() ) {
	      pVTBuf->insertParaAt(selPara);
	      EditTextBlock e;
	      char *p = ((AstroAppFrame *)
		  (app->rootWindow()))->pClip->getText();
	      e.set(p,strlen(p));
	      e.postProcess();
	      pVTBuf->replaceParaAt(selPara, 0, (char *)e.get() );
	      }
	   canvas()->setDirty();
	   }
	   break;
	   if ( selPara != -1 ) {
	      int l;
	      unsigned char f;
	      ((AstroAppFrame *)(app->rootWindow()))->pClip->add(
		  pVTBuf->getText(selPara,l,f) );
	      }
#endif

      case IDM_EFIND :
      case IDM_ENEXT :
	   {
	   zScrollInfoVert *pSiv = scrollBarVert();
	   int par;
	   if ( e->cmd() == IDM_EFIND ) {
	      TextToSearchDlgf *tts = new TextToSearchDlgf(this, &search);
	      if ( !tts->completed() ) {
		 delete tts;
		 return( 1 );
		 }
	      delete tts;
	      par = pVTBuf->findFirst((char far *)search);
	      }
	   else {
	      par = pVTBuf->findCont((char far *)search, pSiv->pos()+1);
	      }
	   if ( par == -1 )
	      return( 1 );
	   pSiv->pos(par);
	   top.get(pVTBuf,par);
	   canvas()->setDirty();
	   return( 1 );
	   }
	   break;
      case IDM_FNEWCFL :
      case IDM_FOPENCFL :
	   {
	   CommentEditor *ce = new CommentEditor(app->rootWindow(), &pVTBuf->getFileDb());
	   ce->show();
	   ce->setFocus();
	   }
	   break;
      case IDM_FNEWCPG :
      case IDM_FOPENCPG :
	   {
	   CoverPageEditor *cpe = new CoverPageEditor( this,
		     &pVTBuf->getFileDb() );
	   delete cpe;
	   canvas()->setDirty();
	   }
	   break;

#endif
      default :
	   return( 0 );
	   break;
      }
return( 1 );
}

typedef int (zEvH::*MouseClickProc)(zMouseClickEvt*);

int FileViewPane::kbhnd(zKeyEvt *e)
{
 zEvent ev;
 ev.Msg = 0;
 switch( e->parm1() ) {
       case VK_PRIOR:
	    ev.wParam = SB_PAGEUP;
	    break;
       case VK_NEXT:
	    ev.wParam = SB_PAGEDOWN;
	    break;
       case VK_UP:
	    ev.wParam = SB_LINEUP;
	    break;
       case VK_DOWN:
	    ev.wParam = SB_LINEDOWN;
	    break;
       case VK_HOME:
	    ev.wParam = SB_TOP;
	    break;
       case VK_END:
	    ev.wParam = SB_BOTTOM;
	    break;
#ifdef NEW
#ifdef PRO
       case VK_RETURN:
	    if ( selPara != -1 ) {
	      pVTBuf->insertParaAt(selPara);
	      canvas()->setDirty();
	      }
	    return( 1 );
	    break;
       case VK_DELETE:
	    ev.Msg = WM_COMMAND;
	    ev.wParam = IDM_EDEL;
	    return(command((zCommandEvt *)&ev));
	    break;
#endif
#endif
       case VK_F1:
	    WinHelp(*this, set_path("ASTROW.HLP", HELP_F ),
					  HELP_CONTEXT, HELPID_FVIEW );
	    break;
       default:
	    return( 0 );
            break;
       }
 return( scroll(&ev) );
}


int FileViewPane::mouseButtonDown( zMouseClickEvt *e )
{
#ifdef NEW
#ifdef PRO
 static unsigned long lastClk;
 unsigned long t;
 int y, *plp = pLineParaTrans, par = 0;
 zPoint p = *e;

 if ( e->isButtonDown(1) ) {
    t=GetCurrentTime();
    y = p.y();
    while ( *plp != -1 ) {
	  if ( *plp <= y && *(plp+1) > y )
	     break;
	  else {
	     par++;
	     plp++;
	     }
	  }
    par += top.para;
    if ( par == selPara && lastClk+dblclkTime>=t ) {
       ViewPopEdit *ve = new ViewPopEdit((zFrameWin *)app->rootWindow(), pVTBuf, selPara );
       ve->show();
       }
    else if ( par == selPara ) {
       selPara = -1;
       canvas()->setDirty();
       }
    else {
       selPara = par;
       canvas()->setDirty();
       }
   }
 lastClk = t;
#endif
#endif
 return( 1 );
}


void FileViewPane::updateScroller()
{
 zScrollInfoVert *pSiv = scrollBarVert();
 pSiv->limits(zRange(1,pVTBuf->getParaCount()-2));
 pSiv->moveDelta(1);
 pSiv->pageDelta(cyClient/cyChar);
}

int FileViewPane::draw( zDrawEvt *e )
{
 LOC x;
 int l, *plp = pLineParaTrans;
 char *pText;

 if ( e != NULL )
    canvas()->getDirty(rActive);
 else
    getInterior(rActive);
 canvas()->lock();
 canvas()->pushBrush( pbBack );
 zRect r;
 getInterior(r);
 canvas()->fill(r, pbBack );
 cyCur = 0;
 *plp++ = 0;
 cxCur = cxStart;
 if ( top.ofs == top.len ) 
    top.get(pVTBuf, top.para+1);
 x = top;
 //debug( "top: para = %d, ofs = %d, len = %d", top.para, top.ofs, top.len );
 pText = pVTBuf->getText( x.para, x.len, x.flags );
 if ( pText == NULL || top.para >= pVTBuf->getParaCount()
          || x.len == 0 ) {
    MessageBeep(-1);
    canvas()->popBrush();
    canvas()->unlock();
    return( 1 );
    }
 assert( pText != NULL );
 assert( x.ofs <= x.len );
 if ( x.ofs ) {
    if ( x.para == selPara )
       cbUsed = cbSel;
    else
       cbUsed = cbReg;
    l = drawPara( pText+x.ofs, x.len-x.ofs, x.flags, x.ofs );
    x.para++;
    }
 if ( l ) {
    do {
       x.ofs = 0;
       pText = pVTBuf->getText( x.para, x.len, x.flags );
       if ( x.para == selPara )
	  cbUsed = cbSel;
       else
	  cbUsed = cbReg;
       x.para++;
       if ( pText == NULL )
	  break;
       if ( cyCur )
	  *plp++ = cyCur;
       } while ( drawPara( pText, x.len, x.flags, x.ofs ) );
    x.para--;
    }
 canvas()->popBrush();
 canvas()->unlock();
 if ( x.ofs > x.len )
    x.get( pVTBuf, x.para+1 );
 bottom = x;
 *plp++ = cyCur;
 *plp++ = -1;
 return(1);
}


FileViewPane::~FileViewPane()
{
 if ( pLineParaTrans )
    delete pLineParaTrans;
 if ( pbBack != NULL )
    delete pbBack;
 delete pVTBuf;
 if ( pfReg != NULL )
    delete pfReg;
 if ( pfBold != NULL )
    delete pfBold;
 if ( pfItal != NULL )
    delete pfItal;
 if ( pfHead != NULL )
    delete pfHead;
 if ( nOpen > 1 )
    nOpen--;
 else {
    nOpen--;
    delete pnWidReg;
    delete pnWidItal;
    delete pnWidBold;
    delete pnWidHead;
    }
 removeHandler(this, (NotifyProc)(KeyProc)&FileViewPane::kbhnd, WM_KEYDOWN);
}

FileViewPane::FileViewPane(char *pName, zWindow *w, int dir) : zPane(w,new zSizeWithParent,zSCROLLV)
{
 pLineParaTrans = new int[200];
 pVTBuf = new VirtualTextBuffer();
 pVTBuf->tab_init(62);
 pVTBuf->virtualizeFile(pName, dir);
 pVTBuf->openVbuf();
 top.get(pVTBuf,0);
 if ( !nOpen ) {
    nOpen++;
    pnWidReg = new int[256];
    pnWidItal = new int[256];
    pnWidBold = new int[256];
    pnWidHead = new int[256];
    }
 else
    nOpen++;
 setMetrics();
 setHandler(this, (NotifyProc)(KeyProc)&FileViewPane::kbhnd, WM_KEYDOWN);
 dirty = 0;
 selPara = -1;
}


int FileViewPane::getBreaks( char *pTxt, int len,
		  unsigned char flags, int *array, unsigned char *flary, int nBrkMax )
{
 int sp = 0, w, i, x = 0, spw;
 int *pnWid = pnWidReg;
 char *p;
 unsigned char spfl;

 if ( pTxt == NULL )
    return( -1 );

 if ( isBold(flags)  ) {
    if ( pnWidBold )
       pnWid = pnWidBold;
    else
       pnWid = pnWidReg;
    }
 else if ( isItal(flags)  ) {
    if ( pnWidItal )
       pnWid = pnWidItal;
    else
       pnWid = pnWidReg;
    }
 else if ( isHead(flags) ) {
    if ( pnWidHead )
       pnWid = pnWidHead;
    else
       pnWid = pnWidReg;
    }
 *(array+x)= 0;
 *(flary+x)= flags;
 x++;

 for ( p = pTxt, w = 0, i = 0; i < len; i++, p++ ) {
     switch( (unsigned char)*p ) {
#ifdef NEW
#ifdef PRO
	   case '\1':
		{
		*p++;
		i++;
		unsigned char lx = *p++;
		i++;
		p+=lx;
		i+=lx;
		}
		break;
#endif
#endif
	   case ' ':
		sp = i+1;
		spfl = flags;
                spw = w;
		w += pnWid[' '];
		break;
	   case (unsigned char)'\x80' :
	   case '\n' :
		if ( x >= nBrkMax )
		   return( x );
		*(array+x)= i+1;
		*(flary+x)= flags;
		x++;
		w = 0;
		break;
	   case '{':
		flags |= _BOLD_;
		if ( pnWidBold )
                   pnWid = pnWidBold;
                else
		   pnWid = pnWidReg;
		break;
	   case '}':
		pnWid = pnWidReg;
		flags ^= _BOLD_;
		break;
	   case '[':
		if ( pnWidHead )
                   pnWid = pnWidHead;
                else
		   pnWid = pnWidReg;
		flags |= _HEAD_;
		break;
	   case ']':
		pnWid = pnWidReg;
		flags ^= _HEAD_;
		break;
	   case '<':
		if ( pnWidItal )
                   pnWid = pnWidItal;
                else
		   pnWid = pnWidReg;
		flags |= _ITAL_;
		break;
	   case '>':
		pnWid = pnWidReg;
		flags ^= _ITAL_;
		break;
	   case '|' :
		p++;
		i++;
		w = ((int) *p ) * cxTab;
		break;
	   default :
		w += pnWid[(unsigned char)*p];
		break;
	   }
     if ( w > cxClient ) {
	if ( x >= nBrkMax )
	   return( x );
	*(array+x)= sp;
	*(flary+x)= spfl;
	x++;
	flags = spfl;
	w -= spw;
	i = sp;
	p = pTxt + i;
	}
     }
 if ( x >= nBrkMax )
    return( x );
 *(array+x)= sp;
 *(flary+x)= flags;
 return( x );
}

int FileViewPane::getPrevBreak( char *pText, int len, int offset, unsigned char &flags )
{
 int brks[75], nBrk, i;
 unsigned char flgs[75];

 //debug( "offset = %d, len = %d", offset, len );
 //debug( "Prev Text = %100.100s", pText );
 nBrk = getBreaks( pText, len, flags, brks, flgs, 74 );
 //debug( "breaks {%d} %d %d %d %d", nBrk, brks[0], brks[1],
 //   brks[2], brks[3] );
 if ( nBrk == -1 )
    return( -1 );
 for ( i = nBrk-1; i >= 0; i-- ) {
     if ( offset > brks[i] )
	return( brks[i] );
     }
 return( -1 );
}                       

int FileViewPane::getNextBreak( char *pText, int len, int offset, unsigned char &flags )
{
 int brks[75], nBrk, i;
 unsigned char flgs[75];

 //debug( "offset = %d, len = %d", offset, len );
 //debug( "Next Text = %100.100s", pText );
 nBrk = getBreaks( pText, len, flags, brks, flgs, 74 );
 //debug( "breaks {%d} %d %d %d %d", nBrk, brks[0], brks[1],
 //  brks[2], brks[3] );
 if ( nBrk == -1 )
    return( -1 );
 for ( i = 0; i < nBrk; i++ ) {
     if ( brks[i] > offset )
	return( brks[i] );
     }
 return( -1 );
}

int FileViewPane::drawPara( char *pTxt, int len, unsigned char &flags, int &ofs )
{
 char buf[300], *p;
 zDisplay *cv = canvas();
 int i, l, wid = 0, xpos = cxStart, w, spwid=0, *pnWid;
 char *space = buf;
 unsigned char atr = flags, spatr;
 if ( pTxt == NULL )
    return( 0 );
 cv->backColor(cbUsed);
 if ( isBold(atr) ) {
    if ( pnWidBold )
       pnWid = pnWidBold;
    else
       pnWid = pnWidReg;
    cv->pushFont(pfBold );
    cv->textColor(ctBold);
    }
 else if ( isItal(atr) ) {
    if ( pnWidItal )
       pnWid = pnWidItal;
    else
       pnWid = pnWidReg;
    cv->pushFont(pfItal );
    cv->textColor(ctItal);
    }
 else if ( isHead(atr) ) {
    if ( pnWidHead )
       pnWid = pnWidHead;
    else
       pnWid = pnWidReg;
    cv->pushFont(pfHead );
    cv->textColor(ctHead);
    }
 else {
    pnWid = pnWidReg;
    cv->pushFont(pfReg );
    cv->textColor(ctReg);
    }
 for ( i = 0, p = pTxt, l = 0; i < len; i++, p++ ) {
     switch( (unsigned char) *p ) {
#ifdef NEW
#ifdef PRO
	   case '\1':
		{
		*p++;
		i++;
		unsigned char lx = *p++;
		i++;
		p+= lx;
		i+=lx;
		}
		break;
#endif
#endif
	   case '~' :
		p++;
		i++;
		wid += pnWid[*p];
		buf[l++] = *p;
		break;
	   case ' ' :
		spatr = atr;
		buf[l++] = *p;
		space = &buf[l];
                spwid = wid;
		wid += pnWid[' '];
                break;
	   case '|' :
		p++;
		i++;
		space = buf;
                if ( l )
		   cv->text( xpos, cyCur, buf, l );
		l = 0;
		wid = (((int)(*p)) * cxChar);
		xpos = cxStart+(((int)(*p)) * cxChar);
		break;
	   case '{' :
		atr |= _BOLD_;
                if ( l ) {
		   cv->text( xpos, cyCur, buf, l );
		   xpos += cv->getTextDim( buf, l ).width();
		   space = buf;
		   l = 0;
		   }
		if ( pnWidBold )
                   pnWid = pnWidBold;
                else
                   pnWid = pnWidReg;
		cv->popFont();
		cv->textColor(ctBold);
		cv->pushFont(pfBold );
		break;
	   case '}' :
		atr ^= _BOLD_;
	   case '>' :
		if ( *p == '>' )
		   atr ^= _ITAL_;
	   case ']' :
		if ( *p == ']' )
                   atr ^= _HEAD_;
                pnWid = pnWidReg;
                if ( l ) {
		   cv->text( xpos, cyCur, buf, l );
		   xpos += cv->getTextDim( buf, l ).width();
                   }
		space = buf;
		if ( *p == ']' && *(p+1) == '\n' )
		   cyCur += 3;
		l = 0;
		cv->popFont();
		cv->textColor(ctReg);
		cv->pushFont(pfReg );
		break;
	   case '<' :
		atr |= _ITAL_;
		if ( l ) {
		   cv->text( xpos, cyCur, buf, l );
		   xpos += cv->getTextDim( buf, l ).width();
		   l = 0;
		   space = buf;
		   }
		if ( pnWidItal )
                   pnWid = pnWidItal;
                else
                   pnWid = pnWidReg;
		cv->popFont();
                cv->textColor(ctItal);
		cv->pushFont( pfItal );
		break;
	   case '[' :
                atr |= _HEAD_;
		if ( l ) {
		   cv->text( xpos, cyCur, buf, l );
		   xpos += cv->getTextDim( buf, l ).width();
		   l = 0;
		   space = buf;
		   }
		if ( pnWidHead )
                   pnWid = pnWidHead;
                else
		   pnWid = pnWidReg;
		cv->popFont();
		cv->textColor(ctHead);
		cv->pushFont(pfHead );
		break;
	   case (unsigned char)'\x80' :
	   case '\n' :
		{
		zRect xx(xpos, cyCur, cxClient, cyCur+cyChar);
		cv->fill(xx,pbBack);
                if ( l )
		   cv->text( xpos, cyCur, buf, l );
		l = 0;
		wid = 0;
		cyCur += cyChar;
		xpos = cxStart;
		space = buf;
		spwid = 0;
                spatr = atr;
		if ( cyCur > rActive.bottom()-cyChar ) {
	           cv->popFont();
		   ofs += i+1;
	           flags = atr;
	           return( 0 );
		   }
		}
		break;
	   default:
		buf[l++] = *p;
		wid += pnWid[(unsigned char)*p];
		break;
	   }
     if ( wid > cxClient ) {
	if ( !l ) {
	   xpos = cxStart;
	   cyCur += cyChar;
	   space = buf;
	   spwid = 0;
           spatr = atr;
	   wid = 0;
           }
	else if ( space == &buf[0] ) {
	   xpos = cxStart;
	   cyCur += cyChar;
           zRect rw(0, cyCur, cxClient, cyCur+cyChar );
	   cv->fill(rw, pbBack);
           cv->text( xpos, cyCur, (char _far *)buf, l );
	   w = cv->getTextDim( (char _far *)buf, l ).width();
           l = 0;
	   wid = w;
           spwid = w;
	   xpos = cxStart + w;
           }
        else {
	   zRect xx2(xpos, cyCur, cxClient, cyCur+cyChar);
	   cv->fill(xx2,pbBack);
	   cv->text( xpos, cyCur, (char _far *)buf, space-buf );
	   memmove( buf, space, l - (space-buf) );
	   l -= (space-buf);
	   space = buf;
	   wid -= spwid;
           spwid = 0;
           atr = spatr;
	   cyCur += cyChar;
	   xpos = cxStart;
	   }
	   if ( cyCur > rActive.bottom()-cyChar ) {
	      cv->popFont();
	      if ( l ) {
	         i -= l;
	         atr = spatr;
	         }
	      ofs += i+1;
	      flags = atr;
	      return( 0 );
	      }
        }
     }
 cv->popFont();
 flags = atr;
 ofs += i;
 return( 1 );
}

#ifdef PRO
int FileViewPane::findTopic( char *topic )
{
 zScrollInfoVert *pSiv = scrollBarVert();
 int par;
 par = pVTBuf->findCont( topic, 0 );
 if ( par == -1 )
    return( 0 );
 pSiv->pos(par);
 top.get(pVTBuf,par);
 canvas()->setDirty();
 return( 1 );
}
#endif

int FileViewFrame::MDIActivate(zActivateEvt *actEvt)
{
 if ( (actEvt->active()) && (pane!=0) ) {
    pane->updateScroller();
    pane->setFocus();
    setupEditMenu(1);
#ifdef NEW
    ((AstroAppFrame *)app->rootWindow())->pStatusLine->text(ZSL_MAINITEM, 
        CResStr(_FVW_STATUS)/*"Click on a Paragraph to Highlight, Double Click to Edit The Paragraph."*/);
#endif
    }
 else if ( !actEvt->active() && pane!=0 ) {
    setupEditMenu(0);
#ifdef NEW
    ((AstroAppFrame *)app->rootWindow())->pStatusLine->text(ZSL_MAINITEM, "");
#endif
    }
 return 0;
}

void FileViewFrame::setupEditMenu(int i)
{
#ifdef NEW
#ifdef PRO
 static int vmitms[] = {IDM_EUNDO, IDM_ECOPY, IDM_EPASTE, IDM_ECUT,
     IDM_EDEL, IDM_EFIND, IDM_ENEXT, IDM_FPRINT, IDM_UPARSE, IDM_FEXPORT,
     IDM_FNEWCFL, IDM_FNEWCPG, IDM_FOPENCFL, IDM_FOPENCPG, IDM_FCLOSE, 0 };
#else
 static int vmitms[] = {IDM_FPRINT, IDM_UPARSE, IDM_FEXPORT, IDM_FCLOSE, 0 };
#endif
#else
 static int vmitms[] = { IDM_EFIND, IDM_ENEXT, IDM_FPRINT, IDM_UPARSE,
     IDM_FEXPORT, IDM_FNEWCFL, IDM_FNEWCPG, IDM_FOPENCFL, IDM_FOPENCPG, 0 };
#endif
 if ( i )
    enableMenuItems(pane->pMenu, vmitms );
 else
    disableMenuItems(pane->pMenu, vmitms );
}

FileViewFrame::focus(zFocusEvt *focEvt)
{
 char buf[150];

 if ( (focEvt->gainFocus()) && (pane!=0) ) {
    pane->setFocus();
    pane->updateScroller();
    pane->canvas()->setDirty();
    if (pane->pVTBuf != NULL )
       pane->pVTBuf->openVbuf();
    strcpy( buf, CResStr(_FVW_VIEWTX)/*"View Text: "*/ );
    strcat( buf, pane->pVTBuf->getFileDb().name );
    strcat( buf, ", " );
    strcat( buf, pane->pVTBuf->getFileDb().comment );
    caption( zString( buf ) );
    }
 if ( (!focEvt->gainFocus()) && (pane!=0) ) {
    if (pane->pVTBuf != NULL )
       pane->pVTBuf->closeVbuf();
    }
   return 0;
}

int FileViewFrame::kill(zEvent *e)
{
#ifdef NEW
#ifdef PRO
 if ( pane->pVTBuf->dirty() ) {
    zMessage *mp = new zMessage(this, CResStr(_FVW_QUSAVE)
       /*"Text Has Changes, Do You Want to Save?"*/, CResStr(_FVW_QUSAVE2)/*"Changed Text"*/, MB_YESNOCANCEL);
    if ( mp->isYes() ) {
       int b;
       ((AstroAppFrame *)app->rootWindow())->pStatusLine->text(ZSL_MAINITEM, CResStr(_FVW_STATSAVE)/*"Saving The Text..."*/);
       ProcMessage *pm = new ProcMessage(CResStr(_FVW_MSG_SAVE)/*"Saving File..."*/, &b );
       zYield(0);
       zYield(0);
       pane->pVTBuf->saveFile();
       delete pm;
       }
    if ( mp->isCancel() ) {
       return( 1 );
       }
    }
#endif
#endif
#ifdef PRO
 AstMruList.check(set_path((char *)name, _dir), _TEXT_);
#endif
 pane->pMenu->removeCommand(pane,(CommandProc)&FileViewPane::command );
 return( 0 );
}

FileViewFrame::FileViewFrame(zFrameWin *pPar, char *pName, int dir):zMDIChildFrame(pPar,new zSizer,zSTDFRAME,CResStr(_FVW_VIEWAF)/*"View A File"*/)
{
 static char *types[] = { "ASTRO Reports (*.OUT)", "*.OUT", 0, 0 };
 if ( pName == NULL ) {
    zFileOpenForm *fof = new zFileOpenForm(this, "File to View", "*.out", types );
    if ( fof->completed() )
       pane=new FileViewPane(fof->name(), this, -1);
    delete fof;
    }
 else
    pane=new FileViewPane(pName, this, dir);
 if ( GetPrivateProfileInt( "Windows", "TextMax", 0, APPNAME ))
    maximize(1);
 _dir = dir;
 name = pName;
 pane->pMenu = pPar->menu();
 pane->pMenu->setCommand(pane,(CommandProc)&FileViewPane::command,
   IDM_FEXPORT );
 pane->pMenu->setCommand(pane,(CommandProc)&FileViewPane::command,
   IDM_FPRINT );
#ifdef NEW
 pane->pMenu->setCommand(pane,(CommandProc)&FileViewPane::command,
   IDM_FCLOSE );
#endif
#ifdef PRO
#ifdef NEW
 pane->pMenu->setCommand(pane,(CommandProc)&FileViewPane::command,
   IDM_EUNDO, IDM_ENEXT );
#else
 pane->pMenu->setCommand(pane,(CommandProc)&FileViewPane::command,
   IDM_EFIND, IDM_ENEXT );
#endif
 pane->pMenu->setCommand(pane,(CommandProc)&FileViewPane::command,
   IDM_FNEWCPG, IDM_FNEWCFL );
 pane->pMenu->setCommand(pane,(CommandProc)&FileViewPane::command,
   IDM_FOPENCPG, IDM_FOPENCFL );
#endif
 pane->pMenu->setCommand(pane,(CommandProc)&FileViewPane::command,
   IDM_UPARSE );
 pane->addVertScrollBar();
 setIcon(new zIcon(zResId("TextIcon")));
 pane->updateScroller();
 pane->show();
 deleteOnClose(TRUE);
}


/*
void zApp::main()
{
   debugOn(1);
   FileViewFrame* pViewFrame=new FileViewFrame(NULL);
   pViewFrame->show();
   go();
   delete pViewFrame;
}
*/
