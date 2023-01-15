#include "stdafx.h"
#include <stdlib.h>
#include <assert.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "charcons.h"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "fdecomp.hpp"
#include "paths.hpp"
#include "fprint.hpp"
#include "pageopt.hpp"
#include "printopt.hpp"
#include <print.h>
#include "repstyle.hpp"
#include "inifile.hpp"
#include "errors.fns"


int FilePrinter::newFile( char *pName )
{
 char buf[100];
 strcpy( buf, set_path( pName, dirtype ) );
 pTd->closeFile();
 pTd->openFile(buf);
 return( 1 );
}

int FilePrinter::printSetup(zPrinterDisplay *pd, zPrintJob *pj)
{
int i;

 ReportStyles rs(pd);
 rs.getFromIni(PrintData_SEC);
 ctReg = rs.getRegColor();
 ctBold = rs.getBoldColor();
 ctItal = rs.getItalColor();
 ctHead = rs.getHeadColor();
 pdr = pd;
 PrintData prtd;
 prtd.getFromIni();
 fHeadP1 = prtd.getHeadP1();
 fCenterHeads = prtd.getCenterHead();
 if ( pfReg != NULL )
    delete pfReg;

 pfReg = new zFont( *rs.getRegFont(), pd );
 if ( pfBold != NULL )
    delete pfBold;
 pfBold = new zFont(*rs.getBoldFont(), pd  );

 if ( pfItal != NULL )
    delete pfItal;
 pfItal = new zFont( *rs.getItalFont(), pd );
 if ( pfHead != NULL )
    delete pfHead;
 pfHead = new zFont( *rs.getHeadFont(), pd );

 pd->pushFont(pfReg);
 zFontInfo *pFi = new zFontInfo( pd );
 cxChar = pFi->width();
 cyChar = pFi->height()+pFi->externLead();
 delete pFi;
 if ( pnWidReg != NULL ) {
    if ( !GetCharWidth(*pd, 0, 255, pnWidReg) ) {
       for ( i = 0; i < 255; i++ )
	   pnWidReg[i] = cxChar;
       }
    }

 pd->popFont();
 pd->pushFont(pfHead);
 if ( pnWidHead != NULL ) {
    if ( !GetCharWidth(*pd, 0, 255, pnWidHead) ) {
       for ( i = 0; i < 255; i++ )
	   pnWidHead[i] = cxChar;
       }
    }
 zFontInfo *pFi2 = new zFontInfo( pd );
 cyCharHead = pFi2->height()+pFi2->externLead();
 delete pFi2;
 pd->popFont();
 pd->pushFont(pfBold);
 if ( pnWidBold != NULL ) {
    if ( !GetCharWidth(*pd, 0, 255, pnWidBold) ) {
       for ( i = 0; i < 255; i++ )
	   pnWidBold[i] = cxChar;
       }
    }
 pd->popFont();
 pd->pushFont(pfItal);
 if ( pnWidItal != NULL ) {
    if ( !GetCharWidth(*pd, 0, 255, pnWidItal) ) {
       for ( i = 0; i < 255; i++ )
	   pnWidItal[i] = cxChar;
       }
    }
 pd->popFont();
 zDisplayInfo *zd = new zDisplayInfo(pd);
 zd->lock();
 fDrawLine = (zd->numPens() >= 1);
 zd->unlock();
 pd->getVisible(rPage);
 PageData pgdt;
 pgdt.getFromIni(PageOpt_SEC);
 setMargins( pgdt.getMargins() );
 zLoEnglish ledt(rMargins.left(), rMargins.top(), pd);
 zLoEnglish ledb(rMargins.right(), rMargins.bottom(), pd);
 cyTop = ledt.y();
 cxClient = rPage.width() - ledt.x() - ledb.x();
 cyClient = rPage.height() - ledt.y() - ledb.y();
 cyBottom = rPage.height() - ledb.y();
 cxStart = ledt.x();
 int xcw = cxClient - (cxChar*3);
 int xtw = xcw / (cxChar+3);
 pTd->tab_init((xtw<62?62:xtw), cxChar+3);
 cxTab = cxClient / 64;
 cxTab--;
 if ( cxTab < cxChar )
    cxTab = cxChar;
 if ( fDrawLine )
    pLinePen = new zPen(BlackPen);
 pd->backColor(zColor(0xff,0xff,0xff));
 return( 1 );
}

BOOL FilePrinter::morePages()
{
 if ( doRange && ( nPage+1 >= last ) )
    return( 0 );
 if ( pTd->anyMore() || !pTd->isFinished() )
    return( 1 );
 else if ( flist[fno+1] != NULL ) {
    fno++;
    if ( dirtype == HELP_F )
       tlist++;
    pTd->setTitle( *tlist );
    newFile( flist[fno] );
    cyCur = cyBottom;
    return( 1 );
    }
 return( 0 );
}

int FilePrinter::print(zPrinterDisplay *pr, zRect *r)
{
 int l, len = nLlen, ofs = nLofs, mor, depth=0, eor=1, atr;
 char *pText;

// debug("Print() Init--rect: top %d, left %d, bottom %d, right %d\n",
//      r->top(), r->left(), r->bottom(), r->right() );
//  debug("rPage: top %d, left %d, bottom %d, right %d\n",
//      rPage.top(), rPage.left(), rPage.bottom(), rPage.right() );
//  debug("rActive: top %d, left %d, bottom %d, right %d\n",
//      rActive.top(), rActive.left(), rActive.bottom(), rActive.right() );
//  debug("nPage = %d, ofs %d, len %d, cyCur %d\n", nPage, ofs, len, cyCur );

 nLofs = 0;
 nLlen = 0;
 theAtr = 0;
 if ( pTd->isFinished() && !pTd->anyMore() ) {
    theAtr = 0;
    nLofs = 0;
    nLlen = 0;
    return( 1 );
    }
 pr->getVisible(rActive);
 cxCur = cxStart;
//  debug("(Should Not be 0) rActive: top %d, left %d, bottom %d, right %d\n",
//      rActive.top(), rActive.left(), rActive.bottom(), rActive.right() );
//  debug( "Start Print Loop--ofs = %d, len = %d, fin = %d, any = %d\n",
//       ofs, len, pTd->isFinished(), pTd->anyMore() );
 if ( rPage.top() == rActive.top() )
    printHeader();
 do {
   if ( ofs > len ) {
      pTd->finished(1);
      len = 0;
      ofs = 0;
      }
   if ( pTd->isFinished() && !pTd->anyMore() ) {
      theAtr = 0;
      nLlen = 0;
      nLofs = 0;
      if ( flist[fno+1] != NULL ) {
	 fno++;
	 newFile(flist[fno]);
	 cyCur = cyBottom;
	 }
      else
	 return( 1 );
      }
   pText = pTd->getText( len, atr );
   if ( checkDepth( pText+ofs, len-ofs, atr, depth ) ) {
      pTd->finished(0);
      theAtr = 0;
      nLofs = 0;
      nLlen = 0;
      if ( doRange && ( nPage+1 <= first || nPage+1 > last ) ) {
	 zYield(0);
	 printHeader();
	 if ( doRange && ( nPage+1 <= first || nPage+1 > last ) ) {
	    pTd->finished(1);
	    cyCur += depth;
	    continue;
	    }
	 }
      else {
	 return( 1 );
	 }
      }
   if ( doRange && ( nPage+1 <= first || nPage+1 > last ) ) {
      pTd->finished(1);
      zYield(0);
      cyCur += depth;
      }
   else
      eor = drawPara( pText, len, atr, ofs );

   } while ( eor );
 if ( ofs < len ) {
    nLofs = ofs;
    theAtr = atr;
    nLlen = len;
    pTd->finished(0);
    }
 else {
    nLofs = 0;
    theAtr = 0;
    nLlen = 0;
    pTd->finished(1);
    }
 return(1);
}

int FilePrinter::checkDepth( char *pt, int len, int atr, int &depth )
{
 getDepth( pt, len, atr, depth );
//  debug( "checkDepth()--pt = %-50.50s\nlen = %d, depth = %d, cyCur = %d, cyBottom = %d\n",
//    pt, len, depth, cyCur, cyBottom );
 if ( cyCur + depth > cyBottom )
    return( 1 );
 else
    return( 0 );
}


FilePrinter::~FilePrinter()
{
 delete pTd;
 if ( pfReg != NULL )
    delete pfReg;
 if ( pfBold != NULL )
    delete pfBold;
 if ( pfItal != NULL )
    delete pfItal;
 if ( pfHead != NULL )
    delete pfHead;
 delete pnWidReg;
 delete pnWidItal;
 delete pnWidBold;
 delete pnWidHead;
}

FilePrinter::FilePrinter(char **pNames, int dir, char **pTlist)
{
 char buf[100];
 dirtype = dir;
 flist = pNames;
 tlist = pTlist;
 fno = 0;
 pTd = new TextDecompressor();
 pTd->tab_init(62);
 if ( dir == HELP_F )
    pTd->setTitle( *pTlist );
 else 
    pTd->setTitle( NULL );

 strcpy( buf, set_path( *flist, dirtype ) );
 pTd->openFile(buf);
 pnWidReg = new int[256];
 pnWidItal = new int[256];
 pnWidBold = new int[256];
 pnWidHead = new int[256];
 nPage = 0;
 doRange = 0;
 first = -1;
 last = -1;
 nLofs = 0;
 nLlen = 0;
 theAtr = 0;
}

FilePrinter::FilePrinter()
{
 pTd = new TextDecompressor();
 pTd->tab_init(62);
 pnWidReg = new int[256];
 pnWidItal = new int[256];
 pnWidBold = new int[256];
 pnWidHead = new int[256];
 nPage = 0;
 doRange = 0;
 first = -1;
 last = -1;
}


int FilePrinter::printHeader()
{
 int x, wid, spanish=0;
 FILE_DB *p = pTd->getFpt();
 char buf[150];

 if ( !nPage && !fHeadP1 ||
	 ( doRange && (nPage+1 < first || nPage+1 >= last) ) ) {
    if (!nPage && !fHeadP1)
       cyCur = cyTop;
    else
       cyCur = cyTop+cyChar+cyChar+cyChar+cyChar;
    ++nPage;
    return( 1 );
    }
 spanish = (int) GetPrivateProfileInt( Misc_SEC, "Spanish", spanish, APPNAME );
 if ( spanish ) {
    pdr->pushFont(pfReg);
 	sprintf( buf, "Nombre: %-50s", p->name );
 	pdr->text( cxStart, cyTop, buf );
 	if ( p->type == -1 )
	    strcpy(buf, "ayuda" );
 	else if ( p->type == -2 )
	    strcpy(buf, "Comentario" );
 	else if ( p->type > 0 )
	    sprintf( buf, "Tipo: %-15s", types(p->type) );
 	else
	    strcpy(buf, "Invalid" );
 	x = cxClient-pdr->getTextDim(buf).width()+cxStart;
 	pdr->text( x, cyTop, buf );
 	sprintf( buf, "Comentarios: %-50s", p->comment );
 	pdr->text( cxStart, cyTop+cyChar, buf );
 	sprintf( buf, "Pagina: %d", ++nPage );
 	pdr->text( x, cyTop+cyChar, buf );
    }
 else {
 	pdr->pushFont(pfReg);
 	sprintf( buf, CResStr(_FPT_NAMESP)/*"Name: %-50s"*/, p->name );
 	pdr->text( cxStart, cyTop, buf );
 	if ( p->type == -1 )             
	    strcpy(buf, CResStr(_FPT_HELP)/*"Help"*/ );
 	else if ( p->type == -2 )
	    strcpy(buf, CResStr(_FPT_COMT)/*"Comment"*/ );
 	else if ( p->type > 0 )
	    sprintf( buf, CResStr(_FPT_TYPESP)/*"Type: %-15s"*/, types(p->type) );
 	else
	    strcpy(buf, CResStr(_FPT_INVALID)/*"Invalid"*/ );
 	x = cxClient-pdr->getTextDim(buf).width()+cxStart;
 	pdr->text( x, cyTop, buf );
 	sprintf( buf, CResStr(_FPT_COMTSP)/*"Comments: %-50s"*/, p->comment );
 	pdr->text( cxStart, cyTop+cyChar, buf );
 	sprintf( buf, CResStr(_FPT_PAGESP)/*"Page: %d"*/, ++nPage );
 	pdr->text( x, cyTop+cyChar, buf );
 	}
 if ( fDrawLine ) {
    pdr->pushPen(pLinePen);
    pdr->moveTo(cxClient+cxStart, cyTop+cyChar+cyChar+(cyChar/2) );
    pdr->lineTo(cxStart, cyTop+cyChar+cyChar+(cyChar/2) );
    pdr->popPen();
    }
 else {
    wid = cyClient/cxChar;
    if ( wid > 149 )
       wid = 149;
    for ( x = 0; x < wid; x++ )
	buf[x] = '-';
    buf[wid] = '\0';
    pdr->text( cxStart, cyTop+cyChar+cyChar, buf );
    }
 cyCur = cyTop+cyChar+cyChar+cyChar+cyChar;
 pdr->popFont();
 return( 1 );
}


int FilePrinter::getDepth( char *pTxt, int len, int flags, int &depth )
{
 int sp = 0, w, i, x = 0, spw, dp = 0, it=0;
 int *pnWid = pnWidReg;
 char *p;
 int spfl;

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
 for ( p = pTxt, w = 0, i = 0; i < len; i++, p++ ) {
     switch( *p ) {
	   case ' ':
		if ( w+pnWid[' '] < cxClient ) {
		   sp = i+1;
		   spfl = flags;
		   w += pnWid[' '];
		   spw = w;
		   }
		break;
	   case '\n' :
		x++;
		if ( isHead(flags) )
		   dp += cyCharHead;
		else
		   dp += cyChar;
		w = 0;
		it = 0;
		pTd->resetTab();
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
		spw = w;
		w = pTd->nextTab();
		if ( w == -1 ) {
		   w = spw;
		   if ( w+pnWid[' '] < cxClient ) {
		      sp = i+1;
		      spfl = flags;
		      w += pnWid[' '];
		      spw = w;
		      }
		   }
		if ( w > cxClient/2 )
		   it=1;
		sp = i;
		spfl = flags;
		break;
	   default :
		w += pnWid[*p];
		break;
	   }
     if ( w > cxClient && !it ) {
	if ( isHead(flags) )
	   dp += cyCharHead;
	else
	   dp += cyChar;
	if ( sp ) {
	   flags = spfl;
	   w -= spw;
	   i = sp;
	   p = pTxt + i;
	   }
	else {
	   w = 0;
	   i++;
	   p++;
	   }
	x++;
	}
     }
 depth = dp;
 return( x );
}


int FilePrinter::drawPara( char *pTxt, int len, int &flags, int &ofs )
{
 char buf[250], *p;
 int i, l=0, wid = 0, xpos = cxStart, w, spWid, *pnWid, svOfs = 0, hwid, it=0;
 char *space = buf;
 int atr = flags, spAtr, svAtr = flags;

 if ( pTxt == NULL )
    return( 0 );
 if ( isBold(atr) ) {
    if ( pnWidBold )
       pnWid = pnWidBold;
    else
       pnWid = pnWidReg;
    pdr->pushFont(pfBold );
    pdr->textColor(ctBold);
    }
 else if ( isItal(atr) ) {
    if ( pnWidItal )
       pnWid = pnWidItal;
    else
       pnWid = pnWidReg;
    pdr->pushFont(pfItal );
    pdr->textColor(ctItal);
    }
 else if ( isHead(atr) ) {
    if ( pnWidHead )
       pnWid = pnWidHead;
    else
       pnWid = pnWidReg;
    pdr->pushFont(pfHead );
    pdr->textColor(ctHead);
    }
 else {
    pnWid = pnWidReg;
    pdr->pushFont(pfReg );
    pdr->textColor(ctReg);
    }
 if ( cyCur == 0 )
    cyCur = cyTop;
 for ( i = 0, p = pTxt + ofs, l = 0; i < len-ofs; i++, p++ ) {
     switch( *p ) {
	   case '~' :
		p++;
		i++;
		wid += pnWid[*p];
		buf[l++] = *p;
		break;
	   case ' ' :
		if ( l > 225 ) {
		   pdr->text( xpos, cyCur, buf, l );
		   xpos += pdr->getTextDim( buf, l ).width();
		   l = 0;
		   }
		spAtr = atr;
		buf[l++] = *p;
		space = &buf[l];
		spWid = wid;
		wid += pnWid[' '];
                break;
	   case '|' :
		space = buf;
                if ( l )
		   pdr->text( xpos, cyCur, buf, l );
		l = 0;
		int xwid;
		xwid = pTd->nextTab();
		if ( xwid != -1 )
		   wid = xwid;
		else if ( xwid == -1 )
		   wid += pnWid[' '];
		if ( wid > cxClient /2 )
		   it = 1;
		xpos = cxStart + wid;
		break;
	   case '{' :
		atr |= _BOLD_;
                if ( l ) {
		   pdr->text( xpos, cyCur, buf, l );
		   xpos += pdr->getTextDim( buf, l ).width();
		   space = buf;
		   l = 0;
		   }
		if ( pnWidBold )
                   pnWid = pnWidBold;
                else
                   pnWid = pnWidReg;
		pdr->popFont();
		pdr->textColor(ctBold);
		pdr->pushFont(pfBold );
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
		   if ( fCenterHeads && *p == ']' )
		      hwid = (cxClient - pdr->getTextDim( buf, l ).width())/2;
		   else
		      hwid = 0;
                   xpos += hwid;
		   pdr->text( xpos, cyCur, buf, l );
		   xpos += pdr->getTextDim( buf, l ).width();
                   }
		space = buf;
		l = 0;
		pdr->popFont();
		pdr->textColor(ctReg);
		pdr->pushFont(pfReg );
		break;
	   case '<' :
		atr |= _ITAL_;
		if ( l ) {
		   pdr->text( xpos, cyCur, buf, l );
		   xpos += pdr->getTextDim( buf, l ).width();
		   l = 0;
		   space = buf;
		   }
		if ( pnWidItal )
                   pnWid = pnWidItal;
                else
                   pnWid = pnWidReg;
		pdr->popFont();
		pdr->textColor(ctItal);
		pdr->pushFont( pfItal );
		break;
	   case '[' :
                atr |= _HEAD_;
		if ( l ) {
		   pdr->text( xpos, cyCur, buf, l );
		   xpos += pdr->getTextDim( buf, l ).width();
		   l = 0;
		   space = buf;
		   }
		if ( pnWidHead )
                   pnWid = pnWidHead;
                else
		   pnWid = pnWidReg;
		pdr->popFont();
		pdr->textColor(ctHead);
		pdr->pushFont(pfHead );
		break;
	   case '\n' :
		if ( isHead(atr) && fCenterHeads ) {
		   if ( l ) {
		      hwid = (cxClient - pdr->getTextDim( buf, l ).width())/2;
		      xpos += hwid;
		      }
		   }
                if ( l )
		   pdr->text( xpos, cyCur, buf, l );
		l = 0;
		it = 0;
		wid = 0;
		pTd->resetTab();
		xpos = cxStart;
		space = buf;
		spWid = 0;
		spAtr = atr;
//                 debug("new Line--cyCur = %d, cyCharHead = %d, rActive.bottom()=%d\n",
//                    cyCur, cyCharHead, rActive.bottom() );
		if ( cyCur+cyCharHead >= rActive.bottom() ) {
		   pdr->popFont();
		   ofs = svOfs;
		   flags = svAtr;
		   return( 0 );
		   }
		if ( isHead(atr) )
		   cyCur += cyCharHead;
		else
		   cyCur += cyChar;
		svOfs = i+1;
		svAtr = atr;
		break;
	   default:
		buf[l++] = *p;
		wid += pnWid[*p];
		break;
	   }
     if ( wid > cxClient && !it ) {
	if ( !l ) {
	   xpos = cxStart;
	   space = buf;
	   spWid = 0;
           spAtr = atr;
	   wid = 0;
           }
	else if ( space == &buf[0] ) {
	   xpos = cxStart;
	   if ( isHead(atr) )
	      cyCur += cyCharHead;
	   else
	      cyCur += cyChar;
	   if ( isHead(atr) && fCenterHeads ) {
	      if ( l ) {
	         hwid = (cxClient - pdr->getTextDim( buf, l ).width())/2;
	         xpos += hwid;
	         }
	      }
	   pdr->text( xpos, cyCur, buf, l );
	   if ( isHead(atr) )
	      cyCur -= cyCharHead;
	   else
	      cyCur -= cyChar;
	   w = pdr->getTextDim( buf, l ).width();
           l = 0;
	   wid = w;
           spWid = w;
	   xpos = cxStart + w;
           }
        else {
	   if ( space < buf ) {
	      alert_box("ERROR", _FPT_ERR/*"\"Space < buf\"--Error call Technical Support!"*/ );
	      space = buf;
	      }
	   if ( isHead(atr) && fCenterHeads ) {
	      if ( l ) {
		 hwid = (cxClient - pdr->getTextDim( buf, space-buf ).width())/2;
		 xpos += hwid;
		 }
	      }
	   pdr->text( xpos, cyCur, buf, space-buf );
	   memmove( buf, space, l - (space-buf) );
	   l -= (space-buf);
	   space = buf;
	   wid -= spWid;
           spWid = 0;
           atr = spAtr;
	   xpos = cxStart;
	   }
	if ( cyCur+cyCharHead >= rActive.bottom() ) {
	   pdr->popFont();
	   if ( l ) 
	      i -= l;
	   atr = spAtr;
	   ofs = svOfs;
	   flags = svAtr;
	   return( 0 );
	   }
	else {
	   if ( isHead(atr) )
	      cyCur += cyCharHead;
	   else
	      cyCur += cyChar;
	   svOfs = i+1;
	   svAtr = atr;
	   }
        }
     }
 pdr->popFont();
 flags = atr;
 ofs = len+1;
 return( 1 );
}


void FilePrintJobDlg::setPage( int page )
{
 char buf[10];

 pgnum = page;
 itoa( page, buf, 10 );
 pageInfo->text(buf);
}

FilePrintJobDlg::FilePrintJobDlg() : zPrJobDlg(app->rootWindow(), zResId("ABORT_DLG"))
{
 pgnum = 0;
 cancel = new zDefPushButton(this,IDCANCEL);
 cancel->setCommand(this, (NotifyProc)&FilePrintJobDlg::doCancel);
 pageInfo = new zStaticText(this,102);
 show();
 setCursor( zCursor(Hourglass) );
 captureMouse();
}

FilePrintJobDlg::~FilePrintJobDlg() {
//
 releaseMouse();
}

int FilePrintJobDlg::doCancel(zEvent *e) {
//
	if (job) {
		job->abort(0);
		shutdown();
	}
	return 1;
}

int FilePrinter::doPrint()
{
 char buf[150];

 if ( !pTd->ok() )
    return( 0 );
 PrinterSetup ps;
 ps.getFromIni(PrintData_SEC);
 zPrinterDisplay *pr = new zPrinterDisplay(ps.getSpec(), ps.toDevMode(0,0) );
 if ( !pr->isValid() ) {
    delete pr;
    return( 0 );
    }
 FilePrintJobDlg *pjd = new  FilePrintJobDlg();
 zPrintJob *pj = new zPrintJob(pr, pjd);
 pj->banding()=0;
 pj->setSetup(this, (zPrSetupProc)&FilePrinter::printSetup);
 pj->setPrint(this, (zPrintProc)&FilePrinter::print);
 pj->setMorePages(this, (zPrMorePagesProc)&FilePrinter::morePages);
 sprintf( buf, "%s, %s", pTd->getFpt()->name, pTd->getFpt()->comment );
 pj->setJobName((char *)buf);
 pj->go();
 return( 1 );
}
