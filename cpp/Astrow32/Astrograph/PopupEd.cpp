// PopupEd.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "PopupEd.h"
#include <stdio.h>
#include "errors.fns"
#include <io.h>
extern int decompress( char *inbuf, char **outbuf, int in_size, int *out_size, int notabs );

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPopupEd dialog


CPopupEd::CPopupEd(CWnd* pParent /*=NULL*/)
	: CDialog(CPopupEd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPopupEd)
	m_text = _T("");
	//}}AFX_DATA_INIT
}


void CPopupEd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPopupEd)
	DDX_Text(pDX, IDC_EDIT1, m_text);
	DDV_MaxChars(pDX, m_text, 2000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPopupEd, CDialog)
	//{{AFX_MSG_MAP(CPopupEd)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopupEd message handlers

int CPopupEd::load(char *name)
{
 int nlen;
 int len;
 FILE *stream;
 char *bf;

 if ( (stream = fopen(name, "rb")) == NULL ) {
    do_error(name);
    return( 0 );
    }
 len = (int)filelength(fileno(stream));
 char *rb = new char[len+2];
 if (rb == NULL) {
    do_mem_error(0);
    fclose( stream );
    return( 0 );
    }
 if ( (len = fread(rb, 1, len, stream)) < len ) {
    do_error( name );
    fclose( stream );
    return( 0 );
    }
 rb[len] = '\0';
 nlen = len * 2; 
 bf = m_text.GetBufferSetLength(nlen);
 m_text.ReleaseBuffer();
 decompress( rb, (char **)&bf, len, &nlen, 0 );
 delete rb;
 fclose( stream );
 return( 1 );
 }
