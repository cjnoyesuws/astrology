// RTFFuncs.cpp: implementation of the RTFFuncs class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TBT32.h"
#include "RTFFuncs.h"
#include "strtransform.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

typedef struct StreamData {
   char *buffer;
   LONG offset;
   LONG len;
   } SreamData;



extern CString AstToRTF( CString &str );
extern CString RTFToAst( CString &str );

DWORD CALLBACK EditStreamInCallback(
  DWORD dwCookie, // application-defined value
  LPBYTE pbBuff,  // pointer to a buffer
  LONG cb,        // number of bytes to read or write
  LONG *pcb       // pointer to number of bytes transferred
)
{
 StreamData *pData= (StreamData *)dwCookie;
 LONG len;
 len=strlen(pData->buffer+pData->offset);
 if ( len > cb )
    len = cb;
 memcpy(pbBuff,pData->buffer+pData->offset,(size_t)len);
 *pcb=len;
 pData->offset+=len;
 return( 0 );
}

DWORD CALLBACK EditStreamOutCallback(
  DWORD dwCookie, // application-defined value
  LPBYTE pbBuff,  // pointer to a buffer
  LONG cb,        // number of bytes to read or write
  LONG *pcb       // pointer to number of bytes transferred
)
{
 CString *pStr= (CString *)dwCookie;
 char *poutbuf = new char[cb+1];
 memcpy(poutbuf,pbBuff,(size_t)cb);
 *pcb=cb;
 poutbuf[(size_t)cb]='\0';
 (*pStr) += poutbuf;
 delete poutbuf;
 return( 0 );
}



CString RTFFuncs::GetRTF( int id )
{
EDITSTREAM estr; 
CString *pStr = new CString();
estr.dwCookie= (DWORD) pStr;
estr.pfnCallback = EditStreamOutCallback;
CRichEditCtrl *pctrl=GetCtrl(id);
pctrl->StreamOut(SF_RTF,estr);
CString strOut=RTFToAst(*pStr);
delete pStr;
pTransformers->ToReplacements(strOut);
BasicString = strOut;
CString nstr;
 if ( tabstring.GetLength() > 0 ) {
	 nstr= tabstring+_T("\r\n");
	 nstr += strOut;
    }
 else
    nstr = strOut;
return( nstr );
}

void RTFFuncs::SetRTF( int id, CString &str )
{
 char *buf;
 splitTabs(str);
 pTransformers->ToSymbols(str);
 CString strRtf = AstToRTF(str);
 EDITSTREAM estr;
 StreamData data; 
 data.len=strRtf.GetLength();

#ifdef _UNICODE
 buf = new char[data.len+10];
 memset(buf,0,data.len+10);
 wcstombs(buf,strRtf.LockBuffer(),data.len);
 data.buffer = buf;
#else
  data.buffer=strRtf.LockBuffer();
#endif
 data.offset=0;
 estr.dwCookie= (DWORD) &data;
 estr.pfnCallback = EditStreamInCallback;
 CRichEditCtrl *pctrl = GetCtrl(id);
 pctrl->StreamIn(SF_RTF,estr);
 pctrl->SetModify(FALSE);
#ifdef _UNICODE
 delete buf;
#else
 strRtf.ReleaseBuffer();
#endif
}

void RTFFuncs::NewRTF( int id )
{
 char *buf;
 CString strRtf = _T("{\\rtf1\\ansi\\ansicpg1252\\deff0\\deflang1033{\\fonttbl{\\f0\\fswiss\\fprq2\\fcharset0 Arial;}");
 strRtf += _T("{\\f1\\froman\\fprq2\\fcharset0 Times New Roman;}}\r\n{\\colortbl ;\\red0\\green0\\blue255;\\red255\\green0\\blue0;");
 strRtf += _T("\\red0\\green255\\blue0;\\red255\\green0\\blue255;}\\viewkind4\\uc1\\pard\\f1\\b0\\i0\\cf0\\fs24\\ql\\par");
 EDITSTREAM estr;
 StreamData data; 
 data.len=strRtf.GetLength();
 #ifdef _UNICODE
 buf = new char[data.len+10];
  memset(buf,0,data.len+10);
 wcstombs(buf,strRtf.LockBuffer(),data.len);
 data.buffer = buf;
#else
  data.buffer=strRtf.LockBuffer();
#endif
 data.offset=0;
 estr.dwCookie= (DWORD) &data;
 estr.pfnCallback = EditStreamInCallback;
 CRichEditCtrl *pctrl = GetCtrl(id);
 pctrl->StreamIn(SF_RTF,estr);
 pctrl->SetModify(FALSE);
 #ifdef _UNICODE
 delete buf;
#else
 strRtf.ReleaseBuffer();
#endif
 DoUnHeading(id);
}


void RTFFuncs::DoBold( int id )
{
 CHARFORMAT cf;
 cf.dwMask = CFM_BOLD|CFM_COLOR;
 cf.dwEffects = CFE_BOLD;
 cf.crTextColor = RGB(0xff,0,0);
 cf.cbSize = sizeof(CHARFORMAT);
 CRichEditCtrl *pctr=GetCtrl(id);
 pctr->SetSelectionCharFormat(cf);
}

void RTFFuncs::DoItalic( int id )
{
 CHARFORMAT cf;
 cf.dwMask = CFM_ITALIC|CFM_COLOR;
 cf.crTextColor = RGB(0,0xff,0);
 cf.dwEffects= CFE_ITALIC;
 CRichEditCtrl *pctr=GetCtrl(id);
 cf.cbSize = sizeof(CHARFORMAT);
 pctr->SetSelectionCharFormat(cf);
}

void RTFFuncs::DoUnBold( int id )
{
 CHARFORMAT cf;
 cf.dwMask = CFM_BOLD|CFM_COLOR;
 cf.dwEffects = 0;
 cf.crTextColor = RGB(0xff,0xff,0xff);
 cf.cbSize = sizeof(CHARFORMAT);
 CRichEditCtrl *pctr=GetCtrl(id);
 pctr->SetSelectionCharFormat(cf);
}

void RTFFuncs::DoUnItalic( int id )
{
 CHARFORMAT cf;
 cf.dwMask = CFM_ITALIC|CFM_COLOR;
 cf.crTextColor = RGB(0xff,0xff,0xff);
 cf.dwEffects=0;
 CRichEditCtrl *pctr=GetCtrl(id);
 cf.cbSize = sizeof(CHARFORMAT);
 pctr->SetSelectionCharFormat(cf);
}


void RTFFuncs::DoHeading( int id )
{
 CHARFORMAT cf;
 cf.dwMask = CFM_BOLD|CFM_COLOR|CFM_FACE|CFM_SIZE;
 cf.dwEffects = CFE_BOLD;
 cf.yHeight = 320;
 cf.crTextColor = RGB(0,0,0xff);
 cf.cbSize = sizeof(CHARFORMAT);
 cf.bPitchAndFamily = FF_SWISS;
 _tcscpy(cf.szFaceName,_T("Arial"));
 CRichEditCtrl *pctr=GetCtrl(id);
 pctr->SetSelectionCharFormat(cf);
 PARAFORMAT pf;
 pf.cbSize=sizeof(PARAFORMAT);
 pf.dwMask=PFM_ALIGNMENT;
 pf.wAlignment=PFA_CENTER;
 pctr->SetParaFormat(pf);
}

// also now Normal
void RTFFuncs::DoUnHeading( int id )
{
 CHARFORMAT cf;
 cf.dwMask = CFM_BOLD|CFM_COLOR|CFM_FACE|CFM_SIZE|CFM_ITALIC;
 cf.dwEffects = 0;
 cf.yHeight = 240;
 cf.crTextColor = RGB(0,0,0);
 cf.cbSize = sizeof(CHARFORMAT);
 cf.bPitchAndFamily = FF_ROMAN;
 _tcscpy(cf.szFaceName,_T("Times New Roman"));
 CRichEditCtrl *pctr=GetCtrl(id);
 pctr->SetSelectionCharFormat(cf);
 PARAFORMAT pf;
 pf.cbSize=sizeof(PARAFORMAT);
 pf.dwMask=PFM_ALIGNMENT;
 pf.wAlignment=PFA_LEFT;
 pctr->SetParaFormat(pf);
}

void RTFFuncs::splitTabs( CString &s )
{
 if ( s.Left(2)==_T("^@") || s.Left(4)==_T("Tabs") || s.Left(4) == _T("TABS") ||
	 s.Left(4)==_T("tabs") || s.Left(7)==_T("DEFTABS") || s.Left(7)==_T("DefTabs")||
	 s.Left(7)==_T("deftabs") || s.Left(7)==_T("Deftabs") ) {
     int pos = s.Find(_T('\n'));
	 if ( pos != -1 ) {
	    tabstring = s.Left(pos+1);
		s = s.Mid(pos+1,s.GetLength()-(pos+1));
	    }	 
	 else {
	    tabstring = s;
		s = _T("");
	   }
    }	 
}
