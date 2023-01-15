// AstroviewView.cpp : implementation of the CAstroviewView class
//

#include "stdafx.h"
#include "Astrow.h"
#include <assert.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "fptr.h"
#include "charcons.h"
#include "tabs.hpp"
#include "virttext.hpp"
#include "paths.hpp"
#ifdef PRO
#include "coverdat.hpp"
#endif
#include "AstroviewDoc.h"
#include "AstroviewView.h"
#ifdef PRO
#include "findtext.h"
#endif
#include "inifile.hpp"
#include "repstyle.hpp"
#include "reportstyles.h"
#include "pageopt.hpp"
#include "pagesetp.h"
#include "attrib.h"
#include "convopt.hpp"
#include "convertdata.h"
#include "coverdat.hpp"
#include "sexcodes.hpp"
#include "prtrdrv.hpp"
#include "asfil2tx.hpp"
#ifdef PRO
#include "rtffuncs.h"
#include "paraedit.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static int nOpen; /* number of times this is open. */
static int *pnWidReg;
static int *pnWidItal;
static int *pnWidBold;
static int *pnWidHead;


// for cover page printing
char agmap[] = {"abcdefghijklwxyz{|}~\x7f\x80\x81\x82" };
char wdmap[] = {"^_`abcdefghi" };
char apmap[] = {"YZ[\\]^_`abcdABCDEFGHIJKLefgh"};
char aprmap[] ={"ijklmnopqrstMNOPQRSTUVWXuvwx"};
char byline[] = { "Produced by\n{ASTRO}--The Program for Astrological"
      " Analysis.\n(C) 1988 - 1999 by Christopher J. Noyes\n" };

char *maps[] = {agmap, apmap, aprmap, wdmap};

CBitmap *loadBitmap( char *file, CDC *dsp );

#define OKVAL 0x12129898

/////////////////////////////////////////////////////////////////////////////
// CAstroviewView

IMPLEMENT_DYNCREATE(CAstroviewView, CView)

BEGIN_MESSAGE_MAP(CAstroviewView, CView)
	//{{AFX_MSG_MAP(CAstroviewView)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_VIEW_LARGERFONT, OnViewLargerfonts)
	ON_COMMAND(ID_VIEW_SMALLERFONT, OnViewSmallerfonts)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LARGERFONT, OnUpdateViewLargerfonts)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SMALLERFONT, OnUpdateViewSmallerfonts)
	ON_COMMAND(ID_EDIT_SEARCH, OnEditSearch)
	ON_COMMAND(ID_EDIT_SEARCHCONTINUE, OnEditSearchcontinue)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SEARCH, OnUpdateEditSearch)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SEARCHCONTINUE, OnUpdateEditSearchcontinue)
	ON_COMMAND(ID_OPTIONS_VIEWER, OnOptionsViewersetup)
	ON_COMMAND(ID_FILE_PAGE_SETUP, OnFilePageSetup)
	ON_COMMAND(ID_OPTIONS_TEXT, OnOptionsConversionsetup)
	ON_COMMAND(ID_OPTIONS_PRINTING, OnOptionsPrinting)
	ON_COMMAND(ID_FILE_EXPORT, OnFileSaveAs)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDel)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDel)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_MOUSEWHEEL()
	ON_WM_CREATE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAstroviewView construction/destruction

CAstroviewView::CAstroviewView()
{
	// TODO: add construction code here
 //stream = 0;
 cyChar = 100;
 ok = OKVAL;
 pLineParaTrans = new int[200];
 if ( !nOpen ) {
    nOpen++;
    pnWidReg = new int[256];
    pnWidItal = new int[256];
    pnWidBold = new int[256];
    pnWidHead = new int[256];
    }
 else
    nOpen++;
 dirty = 0;
 selPara = -1;
 lineDelta.cy = 1;
 pbBack = NULL;
 pfReg = NULL;
 pfReg = NULL;
 pfBold = NULL;
 pfItal = NULL;
 pfHead = NULL;
 fontScale = 1.2; 
 search = "";
 pageCount = 0;
 pfGlyph = NULL;
 pBmUser = NULL;
 }

CAstroviewView::~CAstroviewView()
{
ok = 0xFFFFFFFF;
nOpen--;
if ( !nOpen ) {
   delete pnWidReg;;
   delete pnWidItal;
   delete pnWidBold;
   delete pnWidHead;
   }
if ( pbBack != NULL )
   delete pbBack;
if ( pfReg != NULL )
   delete pfReg;
if ( pfBold != NULL )
   delete pfBold;
if ( pfItal != NULL )
   delete pfItal;
if ( pfHead != NULL )
   delete( pfHead );
if ( pfGlyph != NULL )
    delete pfGlyph;
if ( pBmUser != NULL )
    delete pBmUser;
delete pLineParaTrans;
}

BOOL CAstroviewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= (WS_VSCROLL|CS_DBLCLKS);
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAstroviewView drawing

void CAstroviewView::OnDraw(CDC* pDC)
{
 	// TODO: add draw code for native data here
 if ( ok != OKVAL )
	return;  
 CAstroviewDoc *pDoc = GetDocument();
 pVTBuf = pDoc->GetVirtBuf();
 if ( pVTBuf == NULL || pDoc->IsCover())
    return;
 LOC x;
 int l=1, *plp = pLineParaTrans;
 char *pText;
 CBrush *old;

 old = pDC->SelectObject( pbBack );
 pDC->FillRect(&rActive, pbBack );
 cyCur = cyHead;
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
    pDC->SelectObject(old);
    return;
    }
 assert( pText != NULL );
 assert( x.ofs <= x.len );
 if ( x.ofs ) {
    if ( x.para == selPara ) {
       cbUsed = cbSel;
	   }
    else {
       cbUsed = cbReg;
	   }
    l = drawPara( pText+x.ofs, x.len-x.ofs, x.flags, x.ofs, pDC );
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
       } while ( drawPara( pText, x.len, x.flags, x.ofs, pDC ) );
    x.para--;
    }
 pDC->SelectObject(old);
 if ( x.ofs > x.len )
    x.get( pVTBuf, x.para+1 );
 bottom = x;
 *plp++ = cyCur;
 *plp++ = -1;
}

/////////////////////////////////////////////////////////////////////////////
// CAstroviewView printing

BOOL CAstroviewView::OnPreparePrinting(CPrintInfo* pInfo)
{
//stream = fopen("c:\\debug.txt", "wt" );
//fprintf( stream, "OnPreparePrinting pageCount=%d\n",pageCount);
	// default preparation
	if ( pageCount )
	   pInfo->SetMaxPage(pageCount);
	return DoPreparePrinting(pInfo);
}

void CAstroviewView::OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo)
{
	// TODO: add extra initialization before printing
//fprintf( stream, "OnBeginPrinting\n" );
xtop = top;
xbottom = bottom;
pageParas = new int[400];
paginate(pDC,pInfo);
top.get(pVTBuf,1);
CAstroviewDoc *pDoc = GetDocument();
//if ( pDoc->HasMoreFiles() )
//   fprintf(stream, "Has more files pageCount = %d \n", pageCount );
//else
//   fprintf(stream, "No more files pageCount = %d \n", pageCount ); 
if ( !pDoc->HasMoreFiles())
   pInfo->SetMaxPage(pageCount);
}

void CAstroviewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
//fprintf( stream, "onEndPrinting\n" );
top = xtop;
bottom = xbottom;
delete pageParas;
}

/////////////////////////////////////////////////////////////////////////////
// CAstroviewView diagnostics

#ifdef _DEBUG
void CAstroviewView::AssertValid() const
{
	CView::AssertValid();
}

void CAstroviewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAstroviewDoc* CAstroviewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAstroviewDoc)));
	return (CAstroviewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAstroviewView message handlers


int CAstroviewView::getBreaks( char *pTxt, int len,
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

int CAstroviewView::getPrevBreak( char *pText, int len, int offset, unsigned char &flags )
{
 int brks[75], nBrk, i;
 unsigned char flgs[75];

 nBrk = getBreaks( pText, len, flags, brks, flgs, 74 );
 if ( nBrk == -1 )
    return( -1 );
 for ( i = nBrk-1; i >= 0; i-- ) {
     if ( offset > brks[i] )
	return( brks[i] );
     }
 return( -1 );
}                       

int CAstroviewView::getNextBreak( char *pText, int len, int offset, unsigned char &flags )
{
 int brks[75], nBrk, i;
 unsigned char flgs[75];

 nBrk = getBreaks( pText, len, flags, brks, flgs, 74 );
 if ( nBrk == -1 )
    return( -1 );
 for ( i = 0; i < nBrk; i++ ) {
     if ( brks[i] > offset )
	return( brks[i] );
     }
 return( -1 );
}

int CAstroviewView::drawPara( char *pTxt, int len, unsigned char &flags, int &ofs, CDC *cv )
{
 char buf[400], *p;
 int i, l, wid = 0, xpos = cxStart, w, spwid=0, *pnWid, headFlag = 0;
 char *space = buf;
 unsigned char atr = flags, spatr;
 CFont *old;		   
 if ( pTxt == NULL )
    return( 0 );
 cv->SetBkColor(cbUsed);
 if ( isBold(atr) ) {
    if ( pnWidBold )
       pnWid = pnWidBold;
    else
       pnWid = pnWidReg;
    old = cv->SelectObject(pfBold);
	cv->SetTextColor(ctBold);
    }
 else if ( isItal(atr) ) {
    if ( pnWidItal )
       pnWid = pnWidItal;
    else
       pnWid = pnWidReg;
    old = cv->SelectObject(pfItal);
	cv->SetTextColor(ctItal);
	}
 else if ( isHead(atr) ) {
    if ( pnWidHead )
       pnWid = pnWidHead;
    else
       pnWid = pnWidReg;
    old = cv->SelectObject(pfHead);
	cv->SetTextColor(ctHead);
	}
 else {
    
	pnWid = pnWidReg;
    old = cv->SelectObject(pfReg);
	cv->SetTextColor(ctReg);
	}
 for ( i = 0, p = pTxt, l = 0; i < len; i++, p++ ) {
     switch( (unsigned char) *p ) {
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
	   case '\r' :
		   break;
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
		   cv->TextOut( xpos, cyCur, buf, l );
		l = 0;
		wid = (((int)(*p)) * cxTab);
		xpos = cxStart+(((int)(*p)) * cxTab);
		break;
	   case '{' :
		atr |= _BOLD_;
                if ( l ) {
		   cv->TextOut( xpos, cyCur, buf, l );
		   xpos += cv->GetTextExtent(buf, l).cx;     
		   space = buf;
		   l = 0;
		   }
		if ( pnWidBold )
                   pnWid = pnWidBold;
                else
                   pnWid = pnWidReg;
		
		cv->SetTextColor(ctBold);
		cv->SelectObject(pfBold );
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
		   cv->TextOut( xpos, cyCur, buf, l );
		   xpos += cv->GetTextExtent(buf, l).cx;
		           }
		space = buf;
		if ( *p == ']' && *(p+1) == '\n' )
		   cyCur += 3;
		l = 0;
		cv->SetTextColor(ctReg);
		cv->SelectObject(pfReg );
		break;
	   case '<' :
		atr |= _ITAL_;
		if ( l ) {
		   cv->TextOut( xpos, cyCur, buf, l );
		   xpos += cv->GetTextExtent(buf, l).cx;
		   l = 0;
		   space = buf;
		   }
		if ( pnWidItal )
                   pnWid = pnWidItal;
                else
                   pnWid = pnWidReg;
		cv->SetTextColor(ctItal);
		cv->SelectObject( pfItal );
		break;
	   case '[' :
                atr |= _HEAD_;
		 headFlag = 1;
		 if ( l ) {
		   cv->TextOut( xpos, cyCur, buf, l );
		   xpos += cv->GetTextExtent(buf, l).cx;	
		   l = 0;
		   space = buf;
		   }
		if ( pnWidHead )
                   pnWid = pnWidHead;
                else
		   pnWid = pnWidReg;
		cv->SetTextColor(ctHead);
		cv->SelectObject(pfHead );
		break;
	   case (unsigned char)'\x80' :
	   case '\n' :
		{
		if ( *p == '\n' && *(p+1) == '\x80' )
			p++;
		else if ( *p == '\x80' && *(p+1) =='\r' )
			p++;
		else if ( *p == '\x80' && *(p+1) == '\n' )
			p++;
		else if ( *p == '\x80' && *(p+1) == ' ' && *(p+2) == '\n' )
			p+=2;
		/*CRect xx(0, cyCur, cxClient, cyCur+cyChar);
		if ( !cv->IsPrinting() )
		   cv->FillRect(&xx,pbBack);*/
                if ( l )
		
		cv->TextOut( xpos, cyCur, buf, l );
		l = 0;
		wid = 0;
		if ( headFlag )
		   cyCur += cyHead;
		else
		   cyCur += cyChar;
		xpos = cxStart;
		space = buf;
		spwid = 0;
                spatr = atr;
		if ( cyCur > rActive.bottom-cyChar ) {
	           cv->SelectObject(old);
		   ofs += i+1;
	           flags = atr;
	           return( 0 );
		   }
		headFlag = 0;
		}
		break;
	   case '@' :
        if ( !strnicmp( p, "@TB", 3 ) || !strnicmp( p, "@TR", 3 ) )
		   p+=2;
		else if ( !strnicmp( p, "@GF", 3 ) )
		   p+= 3;
		else if ( !strnicmp( p, "@GP", 3 ) || !strnicmp( p, "@GS", 3 ) )
           p+=4;
		else
		   buf[l++] = *p;
		break;
	   default:
		buf[l++] = *p;
		wid += pnWid[(unsigned char)*p];
		break;
	   }
     if ( wid > cxClient ) {
	if ( !l ) {
	   xpos = cxStart;
	   if ( headFlag )
		  cyCur += cyHead;
		else
	      cyCur += cyChar;
	   space = buf;
	   spwid = 0;
           spatr = atr;
	   wid = 0;
           }
	else if ( space == &buf[0] ) {
	   xpos = cxStart;
	   if ( headFlag )
		  cyCur += cyHead;
		else
	      cyCur += cyChar;
          /* CRect rw(0, cyCur, cxClient, cyCur+cyChar );
	   	if ( !cv->IsPrinting() )
		   cv->FillRect(&rw, pbBack);
       cv->TextOut( xpos, cyCur, buf, l ); */
	   w = cv->GetTextExtent(buf, l).cx;    
	   	   l = 0;
	   wid = w;
           spwid = w;
	   xpos = cxStart + w;
           }
        else {
	   /*CRect xx2(xpos, cyCur, cxClient, cyCur+cyChar);
	   if ( !cv->IsPrinting() )
		  cv->FillRect(&xx2,pbBack);*/
	   cv->TextOut( xpos, cyCur, (char *)buf, space-buf );
	   memmove( buf, space, l - (space-buf) );
	   l -= (space-buf);
	   space = buf;
	   wid -= spwid;
           spwid = 0;
           atr = spatr;
	   cyCur += cyChar;
	   xpos = cxStart;
	   }
	   if ( cyCur > rActive.bottom-cyChar ) {
	      cv->SelectObject(old);
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
 cv->SelectObject(old);
 flags = atr;
 ofs += i;
 return( 1 );
}


int CAstroviewView::up1Page()
{
 int brks[75], nBrk, i;
 unsigned char flgs[75];
 LOC x = top;
 int nLines, l;
 char *pt;

 if ( x.para == 0 ) {
    x.get(pVTBuf,0);
    top = x;
    SetScrollPos(SB_VERT,top.para,TRUE);
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
 SetScrollPos(SB_VERT,top.para,TRUE);
 return( 1 );
}


void CAstroviewView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
   Invalidate(TRUE);
   cxClient=cx;
   cyClient=cy;
   cyLines = cyClient / cyChar;
   cxTab = cxClient / 80;
   if ( cxTab < cxChar )
      cxTab = cxChar;
   pageDelta.cy = cyLines;
}



void CAstroviewView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnVScroll(nSBCode, nPos, pScrollBar);
	LOC l1;
    int o1;
    char *pt1;
    CDC *dc;
	CBrush *old=NULL;
	switch( nSBCode ) {
       case SB_TOP:		 
		top.get(pVTBuf, 1);
	    SetScrollPos(SB_VERT,0,TRUE);
		Invalidate(TRUE);
		break;
       case SB_BOTTOM:
	    top.get(pVTBuf,pVTBuf->getParaCount()-2);
		SetScrollPos(SB_VERT,pVTBuf->getParaCount()-2,TRUE);
		Invalidate(TRUE);
		break;
       case SB_PAGEUP:
		up1Page();
		Invalidate(TRUE);
		break;
       case SB_PAGEDOWN:
	    if (bottom.para <= pVTBuf->getParaCount()-2) {
	       SetScrollPos(SB_VERT,bottom.para,TRUE);
	       top = bottom;
	       }
        Invalidate(TRUE);
		break;
       case SB_THUMBPOSITION:
	    top.get(pVTBuf,nPos);
		SetScrollPos(SB_VERT,nPos,TRUE);
		Invalidate(TRUE);
		break;
       case SB_LINEDOWN:
	    {
	    if (top.para >= pVTBuf->getParaCount()-2) {
	       MessageBeep(-1);
	       return;
	       }
	    l1 = top;
	    pt1 = pVTBuf->getText(l1.para, l1.len, l1.flags );
	    if ( pt1 == NULL ) {
	       MessageBeep(-1);
	       return;
	       }
	    l1.ofs = getNextBreak( pt1, l1.len, l1.ofs, l1.flags );
	    if ( l1.ofs == -1 || l1.ofs >= l1.len ) {
	       l1.get(pVTBuf,l1.para+1);
	       SetScrollPos(SB_VERT,l1.para,TRUE);
		   }
	    top = l1;
	    CRect x(0, 0, cxClient, cyClient);
	    ScrollWindow( 0, -cyChar, NULL,(LPRECT) &x );
	    cyCur = ((cyLines -1) * cyChar);
	    cxCur = cxStart;
	    dc = GetDC();
		CBrush *old = dc->SelectObject( pbBack );
	    CRect rx(0, ((cyLines-1) * cyChar), cxClient, cyClient );
	    dc->FillRect(&rx, pbBack);
	    l1 = bottom;
	    pt1 = pVTBuf->getText(l1.para, l1.len, l1.flags );
	    if ( pt1 == NULL ) {
               MessageBeep(-1);
	       dc->SelectObject(old);
	       ReleaseDC(dc);
		   return;
	       }
	    updateLineParaTrans(-cyChar);
	    if ( l1.para == selPara )
	       cbUsed = cbSel;
	    else
	       cbUsed = cbReg;
	    drawPara( pt1+l1.ofs, l1.len-l1.ofs, l1.flags, l1.ofs, dc );
	    dc->SelectObject(old);
	    ReleaseDC(dc);
	    ValidateRect((LPRECT) &x );
	    if ( l1.ofs >= l1.len )
	       l1.get( pVTBuf, l1.para+1 );
	    bottom = l1;
	    int p = GetScrollPos(SB_VERT);
		SetScrollPos(SB_VERT,p+1,TRUE);
		}
		break;
       case SB_LINEUP:
		{
        l1 = top;
	    if ( l1.para == 1 )
	       return;
	    if ( l1.ofs == 0 ) {
	       l1.get(pVTBuf, l1.para-1);
	       pt1 = pVTBuf->getText(l1.para, l1.len, l1.flags );
	       if ( pt1 == NULL ) {
              MessageBeep(-1);
	          return;
	          }
	       l1.ofs = getPrevBreak( pt1, l1.len, l1.len, l1.flags );
	       SetScrollPos(SB_VERT,l1.para,TRUE);
		   }
	    else {
	       pt1 = pVTBuf->getText(l1.para, l1.len, l1.flags );
	       l1.ofs = getPrevBreak( pt1, l1.len, l1.ofs, l1.flags );
	       }
	    if ( l1.ofs == -1 ) {
	       l1.get(pVTBuf,l1.para-1);
	       SetScrollPos(SB_VERT,l1.para,TRUE);
		   }
	    top = l1;
	    CRect y(0, 0, cxClient, cyClient);
	    ScrollWindow( 0, cyChar, NULL,(LPRECT) &y );
	    cyCur = 0;
	    cxCur = cxStart;
	    dc = GetDC();
		dc->SelectObject( pbBack );
	    CRect wy(0, 0, cxClient, cyChar);
	    dc->FillRect(&wy, pbBack);
	    pt1 = pVTBuf->getText(l1.para, l1.len, l1.flags );
	    if ( pt1 == NULL ) {
           MessageBeep(-1);
	       dc->SelectObject(old);
	       ReleaseDC(dc);
	       return;
	       }
	    if ( l1.para == selPara )
	       cbUsed = cbSel;
	    else
	       cbUsed = cbReg;
	    updateLineParaTrans(cyChar);
	    drawPara( pt1+l1.ofs, l1.len-l1.ofs, l1.flags, l1.ofs, dc );
	    dc->SelectObject(old);
	    ReleaseDC(dc);
	    ValidateRect((LPRECT) &y );
	    l1 = bottom;
	    if ( l1.ofs == 0 ) {
	       l1.get(pVTBuf, l1.para-1);
	       //debug( "l1: para = %d, ofs = %d, len = %d", l1.para, l1.ofs, l1.len );
	       pt1 = pVTBuf->getText(l1.para, l1.len, l1.flags );
	       if ( pt1 == NULL ) {
              MessageBeep(-1);
	          return;
	          }
	       l1.ofs = getPrevBreak( pt1, l1.len, l1.len, l1.flags );
	       //debug( "l1: para = %d, ofs = %d, len = %d", l1.para, l1.ofs, l1.len );
	       SetScrollPos(SB_VERT,l1.para,TRUE);
		   }
	    else {
	       pt1 = pVTBuf->getText(l1.para, l1.len, l1.flags );
	       if ( pt1 == NULL ) {
              MessageBeep(-1);
	          return;
	          }
	       l1.ofs = getPrevBreak( pt1, l1.len, l1.ofs, l1.flags );
	       }
	    if ( l1.ofs == -1 ) {
	       l1.get(pVTBuf,l1.para-1);
	       SetScrollPos(SB_VERT,l1.para,TRUE);
	       }
	    bottom = l1;
	    }
		break;
       default :
	    break;
       }
}

 
void CAstroviewView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	 switch( nChar ) {
          case VK_PRIOR:
			OnVScroll(SB_PAGEUP, 0, NULL );
		    break;
          case VK_NEXT:
	       	OnVScroll(SB_PAGEDOWN, 0, NULL );
			break;
          case VK_UP:
	        OnVScroll(SB_LINEUP, 0, NULL );
			break;
          case VK_DOWN:
	       	OnVScroll(SB_LINEDOWN, 0, NULL );
			break;
          case VK_HOME:
	        OnVScroll(SB_TOP, 0, NULL );
	        break;
          case VK_END:
	        OnVScroll(SB_BOTTOM, 0, NULL );
	       break;
         default :
	       break;
	       }
	 
}

void CAstroviewView::OnInitialUpdate() 
{
	// TODO: Add your specialized code here and/or call the base class
	CAstroviewDoc *pDoc = GetDocument();
	pVTBuf = pDoc->GetVirtBuf();
	if ( pVTBuf == NULL )
	   return;
	top.get(pVTBuf,1);
	SetScrollRange( SB_VERT, 0, pVTBuf->getParaCount(), TRUE );
	Invalidate(TRUE);
}


void CAstroviewView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CAstroviewDoc *pDoc = GetDocument();
	pVTBuf = pDoc->GetVirtBuf();
	top.get(pVTBuf,1);
	SetScrollRange( SB_VERT, 0, pVTBuf->getParaCount(), TRUE );
	Invalidate(TRUE);
}

void CAstroviewView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
if ( ok != OKVAL )
   return;
//if ( stream != 0 )
//   fprintf( stream, "OnPrepareDC\n");
CView::OnPrepareDC(pDC, pInfo);
CAstroviewDoc *pDoc = GetDocument();
if ( pInfo == NULL && !pDoc->canClose() )
   return;
pVTBuf = pDoc->GetVirtBuf();
if ( pVTBuf == NULL )
   return; 
ReportStyles rs(pDC, (pInfo != NULL)?1:0);
pDC->SetTextAlign(TA_LEFT|TA_BASELINE);
pDC->SetBkMode(TRANSPARENT);
if ( pInfo != NULL )
   rs.getFromIni(PrintData_SEC);
else
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
 pbBack=new CBrush(GetSysColor(COLOR_WINDOW));
 if ( pfReg != NULL )
    delete pfReg;
 pfReg = new CFont();
 if ( pInfo == NULL ) 
 	FontSize(rs.getRegFont());
 pfReg->CreateFontIndirect(rs.getRegFont());
 if ( pfBold != NULL )
    delete pfBold;
 pfBold = new CFont();
 if ( pInfo == NULL ) 
 	FontSize(rs.getBoldFont());
 pfBold->CreateFontIndirect(rs.getBoldFont());
 if ( pfItal != NULL )
    delete pfItal;
 pfItal = new CFont();
 if ( pInfo == NULL ) 
 	FontSize(rs.getItalFont());
 pfItal->CreateFontIndirect(rs.getItalFont());
 if ( pfHead != NULL )
    delete pfHead;
 pfHead = new CFont();
 if ( pInfo == NULL ) 
 	FontSize(rs.getHeadFont());
 pfHead->CreateFontIndirect( rs.getHeadFont() );
 CFont *cfold;
 cfold = pDC->SelectObject(pfReg);
 TEXTMETRIC tm;
 pDC->GetTextMetrics(&tm);
 cxChar = tm.tmAveCharWidth;
 cyChar = tm.tmHeight+tm.tmExternalLeading;
 lineDelta.cy=cyChar;
 if ( pnWidReg != NULL )
    pDC->GetCharWidth(0, 255, pnWidReg);
 pDC->SelectObject(pfHead);
 if ( pnWidHead != NULL )
    pDC->GetCharWidth(0, 255, pnWidHead);
 pDC->GetTextMetrics(&tm);
 cyHead = tm.tmHeight+tm.tmExternalLeading;
 pDC->SelectObject(pfBold);
 if ( pnWidBold != NULL )
    pDC->GetCharWidth(0, 255, pnWidBold);
 pDC->SelectObject(pfItal);
 if ( pnWidItal != NULL )
    pDC->GetCharWidth(0, 255, pnWidItal);
 pDC->SelectObject(cfold);
 rActive = CRect(0,0,cxClient,cyClient);
 cxTab = cxClient / 62;
 cxTab--;
 if ( cxTab < cxChar )
    cxTab = cxChar;
 cyLines = cyClient / cyChar;
 pageDelta = cyLines;
 cxStart = cxChar / 3;
 if ( pInfo != NULL ) {
    PageData pd;
	pd.getFromIni(PageOpt_SEC);
	margins = pd.getMargins();
	margins.top *= pDC->GetDeviceCaps(LOGPIXELSY);
	margins.top /=100;
	margins.bottom *= pDC->GetDeviceCaps(LOGPIXELSY);
	margins.bottom /=100;
   	margins.left *= pDC->GetDeviceCaps(LOGPIXELSX);
	margins.left /=100;
	margins.right *= pDC->GetDeviceCaps(LOGPIXELSX);
	margins.right /=100;
	cyStart = (4*cyChar) + margins.top;
	cxStart = margins.left;
	CRect r(0, 0, pDC->GetDeviceCaps(HORZRES), 
	   pDC->GetDeviceCaps(VERTRES));
//    if ( stream != 0 )
//    	fprintf( stream, "r.right = %d, r.bottom = %d\n",r.right,r.bottom);
	r.right -= (margins.right+margins.left);
	r.bottom -= (cyStart);
//	if ( stream != 0 )
//		fprintf( stream, "r.right = %d, r.bottom = %d\n",r.right,r.bottom);
	rActive = r; 
//   	if ( stream != 0 ) {
//       fprintf( stream, "curPage = %d, pageCount = %d\n", pInfo->m_nCurPage, pageCount);
//	   if (	!pDoc->HasMoreFiles() )
//		  fprintf( stream, "no More docs\n");
//	}
	if ( pInfo->m_nCurPage <= pageCount)
       pInfo->m_bContinuePrinting = TRUE;
	else if (!pDoc->HasMoreFiles())
	   pInfo->m_bContinuePrinting = FALSE;
	else {
	   pDoc->DoNextFile();		
	   pInfo->m_bContinuePrinting = TRUE;
	   pInfo->m_nCurPage = 1;
	   paginate(pDC,pInfo);
       if (!pDoc->HasMoreFiles() )
		  pInfo->SetMaxPage(pageCount);
	   }
	cxClient = rActive.Width();
    cyClient = rActive.Height();
   }
#ifdef PRO
 if ( pDoc->IsCover() ) 
    SetupPrintCover(pDC, pInfo, pDoc->GetCoverData() );
 else 
#endif
	 SetScrollRange( SB_VERT, 0, pVTBuf->getParaCount(), TRUE ); 
}


void CAstroviewView::updateLineParaTrans(int ofs )
{
 int *p = pLineParaTrans;

 while ( *p != -1 ) {
       *p++ += ofs;
       }
}

void CAstroviewView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	CString page;
	CFont *old;
	
//	fprintf( stream, "OnPrint\n" );
	CAstroviewDoc *pDoc = GetDocument();
#ifdef PRO
	if ( pDoc->IsCover() )
       PrintCover(pDC, pInfo, pDoc->GetCoverData());
    else
#else
	if ( true ) 
#endif
	{ 
	//print header
//	   fprintf( stream, "Print Header\n");
	   top.get(pVTBuf,pageParas[pInfo->m_nCurPage-1]);
	   pDC->SetTextColor(ctReg);
	   old = pDC->SelectObject(pfReg);
	   pDC->TextOut( margins.left, margins.top, pVTBuf->getFileDb().name, strlen(pVTBuf->getFileDb().name));
	   pDC->TextOut( margins.left, margins.top+cyChar, pVTBuf->getFileDb().comment, strlen(pVTBuf->getFileDb().comment));
	   CSize x = pDC->GetTextExtent(long_types[pVTBuf->getFileDb().type],strlen(long_types[pVTBuf->getFileDb().type]));
	   pDC->TextOut( rActive.Width()-x.cx, margins.top, long_types[pVTBuf->getFileDb().type], strlen(long_types[pVTBuf->getFileDb().type]));
	   page.Format( "Page: %d",pInfo->m_nCurPage);
	   pDC->TextOut( rActive.Width()-x.cx, margins.top+cyChar, page );
	   CPen *opn, *pn = new CPen(PS_SOLID,pDC->GetDeviceCaps(LOGPIXELSY)/120,ctReg);
	   opn = pDC->SelectObject(pn);
	   pDC->MoveTo(margins.left,margins.top+cyChar+cyChar);
	   pDC->LineTo(margins.left+rActive.Width(),margins.top+cyChar+cyChar);
	   pDC->SelectObject(opn);
	   pDC->SelectObject(old);
	   //print report page
	   DrawPrint(pDC, pInfo);
	}
    
}

void CAstroviewView::FontSize(LOGFONT *p)
{
 float h = ((float)p->lfHeight * fontScale);
 p->lfHeight = (int)h;
}

void CAstroviewView::OnViewLargerfonts() 
{
	// TODO: Add your command handler code here
	fontScale *= 1.15;
	Invalidate(TRUE);
}

void CAstroviewView::OnViewSmallerfonts() 
{
	// TODO: Add your command handler code here
	fontScale*= .8695652;
	Invalidate(TRUE);
}

void CAstroviewView::OnEditSearch() 
{
	// TODO: Add your command handler code here
#ifdef PRO 
	CFindText cft;
	cft.SetData(search);
	if ( cft.DoModal()== IDOK )
	   cft.GetData(search);
	else
	   return;
	int par = pVTBuf->findFirst((char *)(LPCTSTR)search);
	if ( par != -1 ) {
	   SetScrollPos(SB_VERT,par,TRUE);  
	   top.get(pVTBuf,par);
	   Invalidate(TRUE);
	   }
	else {
	   CString s;
	   s.Format("Text Searched For: \"%s\" Not Found!", search );
	   MessageBox( s, "Error!" );
	   }
#endif
}

void CAstroviewView::OnEditSearchcontinue() 
{
#ifdef PRO
	// TODO: Add your command handler code here
	if ( search.GetLength() == 0 )
	   OnEditSearch();
	int par = pVTBuf->findCont((char *)(LPCTSTR)search, GetScrollPos(SB_VERT)+1);
	if ( par != -1 ) {
	   SetScrollPos(SB_VERT,par,TRUE);  
	   top.get(pVTBuf,par);
	   Invalidate(TRUE);
	   }
	else {
	   CString s;
	   s.Format("Text Searched For: \"%s\" Not Found!", search );
	   MessageBox( s, "Error!" );
	   }
#endif
}

void CAstroviewView::OnUpdateEditSearch(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO
	if ( pVTBuf != NULL )
	   pCmdUI->Enable(TRUE);
	else
	   pCmdUI->Enable(FALSE);
#endif
}

void CAstroviewView::OnUpdateEditSearchcontinue(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO
	if ( pVTBuf != NULL )
	   pCmdUI->Enable(TRUE);
    else
	   pCmdUI->Enable(FALSE);
#endif
}

void CAstroviewView::OnOptionsViewersetup() 
{
	// TODO: Add your command handler code here
	CDC *dc = GetDC();
	ReportStyles rs(dc, 1);
	rs.getFromIni(ViewerData_SEC);
	CReportStyles crs;
	crs.SetData(&rs);
	if ( crs.DoModal()==IDOK )
	   rs.saveToIni(ViewerData_SEC);
}

void CAstroviewView::OnFilePageSetup() 
{
	// TODO: Add your command handler code here
	PageData pd;
	pd.getFromIni(PageOpt_SEC);
	CPageSetp cps;
	cps.SetData(pd);
	if ( cps.DoModal() == IDOK ) {
	   cps.GetData(pd);
	   pd.saveToIni(PageOpt_SEC);
	   }
}

void CAstroviewView::OnOptionsConversionsetup() 
{
	// TODO: Add your command handler code here
CDC *dc = GetDC();	
ReportStyles rs(dc);
rs.getFromIni(ConvData_SEC);
ConvData cd;
cd.getFromIni();
CConvertData cdd(this);
cdd.SetData(cd,rs);
if ( cdd.DoModal() == IDOK ) {
   cdd.GetData(cd);
   rs.saveToIni(ConvData_SEC);
   cd.saveToIni();
   }
	
}

void CAstroviewView::OnOptionsPrinting() 
{
	// TODO: Add your command handler code here
	CDC *dc;
	CPrintDialog pd(FALSE);
	pd.DoModal();		  
    HDC hdc = pd.GetPrinterDC();
	dc = dc->FromHandle( hdc );
    ReportStyles rs(dc);
    rs.getFromIni(PrintData_SEC);
    CReportStyles crs(this);
    crs.SetData(&rs);
    if ( crs.DoModal() == IDOK ) {
       rs.saveToIni(PrintData_SEC);
      }
 }

void CAstroviewView::DrawPrint(CDC *pDC, CPrintInfo *pInfo )
{
 CAstroviewDoc *pDoc = GetDocument();
 pVTBuf = pDoc->GetVirtBuf();
 if ( pVTBuf == NULL )
    return;
 int breaks[75];
 unsigned char flags[75];
 LOC x;
 int l=1, lines;
 char *pText;
 
// fprintf( stream, "DrawPrint\n"); 
// fprintf( stream, "ractive.bottom = %d", rActive.bottom );
// fprintf( stream, "cyChar = %d\n", cyChar );
 cxCur = cxStart;
 cyCur = cyStart;
 if ( top.ofs == top.len ) 
    top.get(pVTBuf, top.para+1);
 x = top;
 pText = pVTBuf->getText( x.para, x.len, x.flags );
 if ( pText == NULL || top.para >= pVTBuf->getParaCount()
          || x.len == 0 ) {
//    fprintf( stream, "bad vbuf\n");
	MessageBeep(-1);
    return;
    }
 assert( pText != NULL );
 assert( x.ofs <= x.len );
 if ( x.ofs ) {
    cbUsed = cbReg;
//    fprintf( stream, "partial para\n");
	l = drawPara( pText+x.ofs, x.len-x.ofs, x.flags, x.ofs, pDC );
//    fprintf( stream, "l=%d\n",l);
	x.para++;
    }
 if ( l ) {
//    fprintf( stream, "At Do\n");
	 do {
       x.ofs = 0;
       pText = pVTBuf->getText( x.para, x.len, x.flags );
       x.para++;
       if ( pText == NULL ) {
//	      fprintf( stream, "pText is null\n");
		  break;
		}
       lines = getBreaks( pText, x.len, x.flags, breaks, flags, 75 );
	   lines *= cyChar;
//	   fprintf( stream, "lines = %d\n", lines );
	   if (cyCur+lines > rActive.bottom+cyChar ) {
	   	  x.ofs = 1;
//	      fprintf( stream, "break a para\n");
		  break;
	      }
	   } while ( drawPara( pText, x.len, x.flags, x.ofs, pDC ) );
    x.para--;
    }
 bottom = x;
}					   


void CAstroviewView::paginate(CDC *pDC, CPrintInfo *pInfo )
{
 int page=0;
 int *ptr;
 HMETAFILE hmf;
 
// fprintf( stream, "Paginate\n" ); 
 CAstroviewDoc *pDoc = GetDocument();
 if ( pDoc->IsCover() ) {
	*pageParas = 1;
	pageCount = 1;
	return;
	}	

 CMetaFileDC *pmDC = new CMetaFileDC();
 pmDC->Create(NULL);
 pmDC->SetAttribDC(pDC->m_hAttribDC);
 OnPrepareDC(pmDC, pInfo );
 top.get(pVTBuf,1);
 bottom.para = 1;
 ptr = pageParas;
 do {
 	*ptr++ = top.para;
    page++;
	DrawPrint(pmDC,pInfo);
 	top = bottom;
	} while ( bottom.para < pVTBuf->getParaCount() );
pageCount = page;
//fprintf(stream, "pageCount = %d\n", pageCount );
hmf = pmDC->Close();
pmDC->SetAttribDC(NULL);
delete pmDC;
DeleteMetaFile(hmf);
}

void CAstroviewView::OnFileSaveAs() 
{
 int n=0;
 char nbuf[200], nbuf2[200];
 static CStringArray ar;
 astroFileToText *txt;
 ConvData *pcd;
 
 ar.SetSize(4,1);
 txt = new astroFileToText(-1);
 if ( !txt->getSetup(&pcd ) ) {
    delete txt;					
    return;
    }
 ar[n] = (char *)(LPCTSTR)pVTBuf->getSourceName();
 n++;
 ar[n] = "NULL";
 txt->setFiles( &ar, n > 1 );
 txt->doConvert(NULL);
 delete txt;
}

void CAstroviewView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
#ifdef PRO	
	int y, *plp = pLineParaTrans, par = 0;
	CView::OnLButtonDown(nFlags, point);
		
	y = point.y;
    
	while ( *plp != -1 ) {
	  if ( *plp <= y && *(plp+1) > y )
	     break;
	  else {
	     par++;
	     plp++;
	     }
	  }
    par += top.para;
    if ( par == selPara ) {
       selPara = -1;
       Invalidate(TRUE);
       }
    else {
       selPara = par;
       Invalidate(TRUE);
	   }
#endif
}
 
void CAstroviewView::OnEditUndo() 
{
	// TODO: Add your command handler code here
#ifdef PRO
	pVTBuf->undo();
	Invalidate(TRUE);
	CAstroviewDoc *pDoc = (CAstroviewDoc *)GetDocument();
	pDoc->SetModifiedFlag(TRUE);
#endif
}

void CAstroviewView::OnEditDel() 
{
#ifdef PRO
	// TODO: Add your command handler code here
 if ( selPara != -1 ) {
	  pVTBuf->deletePara(selPara);
	  Invalidate(TRUE);
	  CAstroviewDoc *pDoc = (CAstroviewDoc *)GetDocument();
	  pDoc->SetModifiedFlag(TRUE);
 
    }
      	
#endif
}

void CAstroviewView::OnEditCopy() 
{
#ifdef PRO
	// TODO: Add your command handler code here
if ( selPara != -1 ) {
   int l;
   unsigned char f;
   char *ptr= pVTBuf->getText(selPara,l,f);
   CString b(ptr,l); 
   EditTextBlock e;
   e.set(b);
   e.preProcess();
   if ( OpenClipboard() ) {
      EmptyClipboard();
      HANDLE hmem = GlobalAlloc(GMEM_DDESHARE, e.get().GetLength()+2);
	  char * ptr = (char *)GlobalLock(hmem);
	  memcpy(ptr,(LPCTSTR)e.get(),e.get().GetLength()+1);
	  GlobalUnlock(hmem);
	  SetClipboardData(CF_TEXT,hmem);
	  CloseClipboard();
	  }
   
  CAstroviewDoc *pDoc = (CAstroviewDoc *)GetDocument();
  pDoc->SetModifiedFlag(TRUE); 
  }
#endif
}

void CAstroviewView::OnEditCut() 
{
	// TODO: Add your command handler code here
#ifdef PRO
	OnEditCopy();
    if ( selPara != -1 ) {
	   pVTBuf->deletePara(selPara);
	   Invalidate(TRUE);
	   CAstroviewDoc *pDoc = (CAstroviewDoc *)GetDocument();
	   pDoc->SetModifiedFlag(TRUE);
	   }
#endif
}

void CAstroviewView::OnEditPaste() 
{
	// TODO: Add your command handler code here
#ifdef PRO
 if ( OpenClipboard() ) {
	pVTBuf->insertParaAt(selPara);
    EditTextBlock e;
	HANDLE hmem = GetClipboardData(CF_TEXT);
	CloseClipboard();
	CString b = (char *) GlobalLock(hmem);
	GlobalFree( hmem );
	e.set(b);
	e.postProcess();
	pVTBuf->replaceParaAt(selPara, 0, (char *)(LPCTSTR)e.get() );
	}
 CAstroviewDoc *pDoc = (CAstroviewDoc *)GetDocument();
 pDoc->SetModifiedFlag(TRUE);
 Invalidate(TRUE);
#endif
}

void CAstroviewView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO 
if (IsClipboardFormatAvailable(CF_TEXT) )
	pCmdUI->Enable(TRUE);
 else
	pCmdUI->Enable(FALSE);
#endif	
}

void CAstroviewView::OnUpdateEditDel(CCmdUI* pCmdUI) 
{
#ifdef PRO
	// TODO: Add your command update UI handler code here
	if ( selPara != -1 ) 
	   pCmdUI->Enable(TRUE);
    else
	   pCmdUI->Enable(FALSE);
#endif
}

void CAstroviewView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
#ifdef PRO	
	// TODO: Add your command update UI handler code here
	OnUpdateEditDel(pCmdUI);
#endif
}

void CAstroviewView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
#ifdef PRO
	// TODO: Add your command update UI handler code here
	OnUpdateEditDel(pCmdUI);
#endif
}

void CAstroviewView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
#ifdef PRO
	// TODO: Add your message handler code here and/or call default


    unsigned char f; 
 	int l, y, *plp = pLineParaTrans, par = 0;
	
	CView::OnLButtonDblClk(nFlags, point);		
	y = point.y;
    
	while ( *plp != -1 ) {
	  if ( *plp <= y && *(plp+1) > y )
	     break;
	  else {
	     par++;
	     plp++;
	     }
	  }
    par += top.para;
	par--;
    selPara = par;
	CParaEdit ed( this );
	char *ptr = pVTBuf->getText(selPara,l,f);
	CString b((LPCTSTR)ptr,l);
	ed.SetData(b);
	CAstroviewDoc *pDoc = (CAstroviewDoc *)GetDocument();
	pDoc->SetModifiedFlag(TRUE);
	if ( ed.DoModal() == IDOK )	{
	   ed.GetData(b);
	   pVTBuf->replaceParaAt(selPara, f, (char *)(LPCTSTR)b );
	   }
	   Invalidate(TRUE);
#endif
}

void CAstroviewView::OnUpdateViewLargerfonts(CCmdUI* pCmdUI) 
{
pCmdUI->Enable(TRUE);
}

void CAstroviewView::OnUpdateViewSmallerfonts(CCmdUI* pCmdUI) 
{
pCmdUI->Enable(TRUE);
}
#ifdef PRO
int CAstroviewView::SetupPrintCover(CDC *pdc, CPrintInfo *pi, CoverPageData *data )
{
#ifdef PRO
 char fbuf[100], chrs[70], fnt[50], stl[4], set[4];
 int sz;
 char *ptr;
 LPLOGFONT lf = 0;
 char *fnames[] = { "AstGlyphs", "AstPi1", "AstPi1", "WingDings" };
 
 if ( pfGlyph != NULL )
    delete pfGlyph;
 if ( data->getFont() == USER_FNT ) {
    strcpy( fbuf, (char *) (LPCTSTR)data->getFile() );
    sscanf( fbuf, "%[^\\]\\%d\\%[^\\]\\%[^\\]\\%s", fnt, &sz, stl, set, chrs );
    pfGlyph = new CFont();
	ptr = new char[sizeof(LOGFONT)+100];
	lf = (LPLOGFONT)ptr;
	strcpy( lf->lfFaceName, fnt );
	lf->lfWeight=(stl[0]=='B'||stl[1]=='B'?FW_BOLD:FW_NORMAL);
    lf->lfItalic = (stl[0]=='I'||stl[1]=='I'?TRUE:FALSE);
    lf->lfUnderline = 0;
	lf->lfStrikeOut = 0;
    lf->lfEscapement = 0;
	lf->lfOrientation = 0;
	lf->lfCharSet =(stl[0]=='A'||stl[1]=='A'?ANSI_CHARSET:SYMBOL_CHARSET);
	lf->lfPitchAndFamily = FF_DONTCARE|VARIABLE_PITCH;
    lf->lfHeight = sz * 10;
    lf->lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf->lfOutPrecision = OUT_TT_PRECIS;
    lf->lfQuality = DEFAULT_QUALITY;     
 pfGlyph->CreatePointFontIndirect(lf,pdc);	
 }
 else if ( data->getFont() == USER_BMP ) {
    pBmUser = loadBitmap( (char *)(LPCTSTR) data->getFile(), pdc );
    }
 else {
    pfGlyph = new CFont();
	if ( lf != NULL )
	   delete lf;	
	ptr = new char[sizeof(LOGFONT)+100];
	lf = (LPLOGFONT)ptr;
	strcpy( lf->lfFaceName, fnames[data->getFont()] );
	lf->lfWidth = 0;
	lf->lfHeight = 1440;
	lf->lfWeight=FW_NORMAL;
    lf->lfItalic = 0;
    lf->lfUnderline = 0;
	lf->lfStrikeOut = 0;
    lf->lfEscapement = 0;
	lf->lfOrientation = 0;
	lf->lfCharSet =SYMBOL_CHARSET;
	lf->lfPitchAndFamily = FF_DONTCARE|VARIABLE_PITCH;
	lf->lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf->lfOutPrecision = OUT_TT_PRECIS;
    lf->lfQuality = DEFAULT_QUALITY;     
	pfGlyph->CreatePointFontIndirect(lf,pdc)		;
	delete lf;   
 }
#endif
 return(1);
}
#endif
#ifdef PRO
int CAstroviewView::PrintCover(CDC *pdc, CPrintInfo *pi, CoverPageData *data)
{
#ifdef PRO 
 int wid;
 char buf[150], name[100], *map;
 char fnt[50], stl[4], set[4];
 int sz;
 unsigned char fl;
 int ofs;
 int xinch, yinch;
 char fmt[] = "Name: {%s}\n\n\n\nComments:\n\n";
 char fmt2[] = "Astrologer: {%s}\n";
 
 CFont *fold;

 xinch = pdc->GetDeviceCaps(LOGPIXELSX);
 yinch = pdc->GetDeviceCaps(LOGPIXELSY);

 if (pfGlyph != NULL) {
    fold = pdc->SelectObject(pfGlyph);
    if ( data->getFont() == USER_FNT ) {
       strcpy( name, (char *)(LPCTSTR) data->getFile() );
       sscanf( name, "%[^\\]\\%d\\%[^\\]\\%[^\\]\\%s", fnt, &sz, stl, set, buf );
       }
    else {
       map = maps[data->getFont()];
       buf[0] = map[data->getImage()];
       buf[1] = '\0';
       }
    pdc->SetTextColor(ctHead);
    CSize sz = pdc->GetTextExtent(buf, strlen(buf));
	pdc->TextOut(cxStart, cyStart+yinch, buf);
    pdc->SelectObject(fold);
    }
 if ( pBmUser != NULL ) {
           
	CDC *tmp = new CDC();
	tmp->CreateCompatibleDC(pdc);
	BITMAP b;
	tmp->SelectObject(pBmUser);
	tmp->SetMapMode(pdc->GetMapMode());
 	
	pBmUser->GetObject(sizeof(BITMAP),(LPSTR)&b);
	CPoint si(b.bmWidth,b.bmHeight);
	CPoint org(0,0);

	pdc->DPtoLP(&si,1);
	tmp->DPtoLP(&org,1);
	
	pdc->BitBlt(0,0,si.x,si.y,tmp,org.x,org.y,SRCCOPY);
	delete tmp;
    }
 fold = pdc->SelectObject(pfHead);
 pdc->SetTextColor(ctHead);
 wid = pdc->GetTextExtent((char *)(LPCTSTR)data->getTitle()).cx;
 pdc->TextOut(cxStart+((cxClient-wid)/2),(int)((double)yinch * 1.75)+cyStart,
     (char *)(LPCTSTR)data->getTitle() );
 pdc->SelectObject(fold);
 cyCur = (int)((double)yinch * 2.75)+cyStart;
 
 sprintf( buf, fmt, (char *)(LPCTSTR)data->getName() );
 fl = 0;
 ofs = 0;
 drawPara( buf, strlen(buf), fl, ofs, pdc );
 fl = 0;
 ofs = 0; 
 data->getComments().SetAt(data->getComments().GetLength()-1,'\n');
 drawPara( (char *)(LPCTSTR)data->getComments(), data->getComments().GetLength(), fl, ofs, pdc );
 cyCur = rActive.bottom- (yinch*2);
 fl = 0;
 ofs = 0;
 sprintf( buf, fmt2, (char *)(LPCTSTR)data->getAstName() );
 drawPara( buf, strlen(buf), fl, ofs, pdc );
 fl = 0;
 ofs = 0;
 cyCur = rActive.bottom - yinch;
 drawPara( byline, strlen(byline), fl, ofs, pdc );
#endif
 return( 1 );
}

#endif
void CAstroviewView::DoPrint()
{
CAstroviewDoc *pDoc = GetDocument();
//stream = fopen("c:\\debug.txt", "wt" );
//fprintf( stream, "DoPrint\n");
pDoc->SetCanClose(0);
CView::OnFilePrint();
//fclose(stream);
//stream = 0;
((CAstrowApp *)AfxGetApp())->_Yield(8);
pDoc->SetCanClose(1);
}
BOOL CAstroviewView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	if ( zDelta > 0 ) {
	  OnKeyDown(VK_UP,zDelta*3,0);
	}
	else {
	  OnKeyDown(VK_DOWN,abs(zDelta)*3,0);
	}
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

int CAstroviewView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CView::OnCreate(lpCreateStruct);
	return 0;
}
