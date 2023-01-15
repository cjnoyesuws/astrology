// TransWiz.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "TransWiz.h"
#include "transbase.h"
#include "settransdir.h"
#include "newlanguage.h"
#include "setlanguage.h"
#include "setup.h"
#include "fileary.hpp"
#include "symbol.hpp"
#include "textbloc.hpp"
#include "strtransform.h"
#include "texttypeary.hpp"
#include "rtffuncs.h"
#include "dreporttext1.h"
#include "dhelptxt1.h"
#include "daspecttext1.h"
#include "progress.h"
#include "basedbexport.h"
#include "regdbexport.h"
#include "aspdbexport.h"
#include "hlpdbexport.h"
#include "reptdbexport.h"
#include "dregtext1.h"
#include "importhelp.h"
#include "importRegText.h"
#include "importAspText.h"
#include "importreporttext.h"
#include "fileSelector.h"
#include "selectTextItem.h"
#include "directoryselect.h"
#include "batchmgr.h"
#include "batchwriter.h"
#include "direct.h"
// CTransWiz dialog

#ifdef _UNICODE
CString GetTextDir() {
  CString str = AfxGetApp()->GetProfileString(_T("Translation"),_T("BaseDir"));
  if ( str.GetLength() ) {
     if ( str.Right(1)!=_T("\\"))
		 str += _T("\\");
	 str += _T("srcs");
  }
  else
	 AfxMessageBox(_T("Must Set Base Dir First"));
  return str;
}

CString GetTransDir() {
  CString str = AfxGetApp()->GetProfileString(_T("Translation"),_T("BaseDir"));
  if ( str.GetLength() ) {
     if ( str.Right(1)!=_T("\\"))
		 str += _T("\\");
  }
  else {
	 AfxMessageBox(_T("Must Set Base Dir First"));
     return str;
     }
  CString trn;
  trn= AfxGetApp()->GetProfileString(_T("Translation"),_T("TransDir"));
  if ( trn.GetLength() )
	  str += trn;
  else {
	  AfxMessageBox(_T("Must Set Translation Dir First"));
      return trn;
      }
  return str;
}

IMPLEMENT_DYNAMIC(CTransWiz, CDialog)
CTransWiz::CTransWiz(CWnd* pParent /*=NULL*/)
	: CDialog(CTransWiz::IDD, pParent)
	, m_aspexp(TRUE)
	, m_aspimp(TRUE)
	, m_hlpexp(TRUE)
	, m_hlpimp(TRUE)
	, m_regexp(TRUE)
	, m_reptimp(TRUE)
{
}

CTransWiz::~CTransWiz()
{
}

void CTransWiz::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_ASPEXP, m_aspexp);
	DDX_Check(pDX, IDC_ASPIMP, m_aspimp);
	DDX_Check(pDX, IDC_HLPEXP, m_hlpexp);
	DDX_Check(pDX, IDC_HLPIMP, m_hlpimp);
	DDX_Check(pDX, IDC_REGEXP, m_regexp);
	DDX_Check(pDX, IDC_REGIMP, m_regimp);
	DDX_Check(pDX, IDC_REPTEXP, m_reptexp);
	DDX_Check(pDX, IDC_REPTIMP, m_reptimp);

	if ( pDX->m_bSaveAndValidate ) {
	   CString sels;
	   if ( m_aspexp )
		   sels += _T("Y");
	   else
		   sels += _T("N");
       if ( m_aspimp )
		   sels += _T("Y");
	   else
		   sels += _T("N");
	   if ( m_regexp )
		   sels += _T("Y");
	   else
		   sels += _T("N");
	   if ( m_regimp )
		   sels += _T("Y");
	   else
		   sels += _T("N");
	   if ( m_hlpexp )
		   sels += _T("Y");
	   else
		   sels += _T("N");
	   if ( m_hlpimp )
		   sels += _T("Y");
	   else
		   sels += _T("N");
	   if ( m_reptexp )
		   sels += _T("Y");
	   else
		   sels += _T("N");
	   if ( m_reptimp )
		   sels += _T("Y");
	   else
		   sels += _T("N");
	   AfxGetApp()->WriteProfileString(_T("Translation"),_T("ExpImpChoices"),sels);
	}
}


BEGIN_MESSAGE_MAP(CTransWiz, CDialog)
	ON_BN_CLICKED(IDC_EXPORT, OnBnClickedExport)
	ON_BN_CLICKED(IDC_IMPORT, OnBnClickedImport)
	ON_BN_CLICKED(IDC_MERGE, OnBnClickedMerge)
	ON_BN_CLICKED(IDC_PREPARE, OnBnClickedPrepare)
	ON_BN_CLICKED(IDC_SETBASEDIR, OnBnClickedSetbasedir)
	ON_BN_CLICKED(IDC_SETCURRLANG, OnBnClickedSetcurrlang)
	ON_BN_CLICKED(IDC_SETTRANSDIR, OnBnClickedSettransdir)
	ON_BN_CLICKED(IDC_ADDNEWLANG, OnBnClickedAddnewlang)
	ON_BN_CLICKED(IDC_CHECK, OnBnClickedCheck)
END_MESSAGE_MAP()


// CTransWiz message handlers

BOOL CTransWiz::OnInitDialog()
{
	CDialog::OnInitDialog();
    CString str =AfxGetApp()->GetProfileString( _T("Translation"),_T("ExpImpChoices"),_T("YYYYYYYY"));
	m_aspexp = (str.Mid(0,1)==_T("Y")?TRUE:FALSE);
	m_aspimp = (str.Mid(1,1)==_T("Y")?TRUE:FALSE);
    m_regexp = (str.Mid(2,1)==_T("Y")?TRUE:FALSE);
	m_regimp = (str.Mid(3,1)==_T("Y")?TRUE:FALSE);
	m_hlpexp = (str.Mid(4,1)==_T("Y")?TRUE:FALSE);
	m_hlpimp = (str.Mid(5,1)==_T("Y")?TRUE:FALSE);
	m_reptexp = (str.Mid(6,1)==_T("Y")?TRUE:FALSE);
	m_reptimp = (str.Mid(7,1)==_T("Y")?TRUE:FALSE);
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTransWiz::OnBnClickedExport()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_aspexp) {
		ExportAspectText();
	}
	if (m_hlpexp) {
       ExportHelpText();		
	}
	if (m_regexp) {
	   ExportRegularText();
	}
	if (m_reptexp) {
	   ExportReportText();	
	}
}

void CTransWiz::OnBnClickedImport()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_aspimp) {
	   ImportAspectFiles();	
	}
	if (m_hlpimp) {
	   ImportHelpFiles();
	}
	if (m_regimp) {
	   ImportPlanetFiles(); 	
	}
	if (m_reptimp) {
	   ImportReportFiles();
	}
}

void CTransWiz::OnBnClickedMerge()
{
	// TODO: Add your control notification handler code here
	CString prog = _T("txttransmerge");
	CString trn;
    trn= AfxGetApp()->GetProfileString(_T("Translation"),_T("TransDir"));
	if ( !trn.GetLength() ) {
	  AfxMessageBox(_T("Must Set Translation Dir First"));
      return;
      }
	CString args = _T("MRGS SPLS ");
	args += trn;
	WriteABatch(_T("mergeaspects"),prog,args,_T("Aspects"));
	WriteABatch(_T("mergeregular"),prog,args,_T("Regular"));
	WriteABatch(_T("mergehelp"),prog,args,_T("Help"));
	prog = _T("reptransmerge");
	WriteABatch(_T("mergereports"),prog,args,_T("Reports"));
	int drive = _getdrive();
	wchar_t buf[250];
	wchar_t *cd=_wgetdcwd(drive,buf,250);
	if ( cd!=NULL) {
	   CString olddir = cd;
       WriteABatch(_T("chdir"),olddir,args,NULL);
	}
  CString base = AfxGetApp()->GetProfileString(_T("Translation"),_T("BaseDir"));
  if ( base.GetLength() ) {
     if ( base.Right(1)!=_T("\\"))
		 base += _T("\\");
  }
  CString merge = base + _T("Merge.cmd");
  WinExec((LPCTSTR)merge,SW_SHOW);
}

void CTransWiz::OnBnClickedPrepare()
{
	// TODO: Add your control notification handler code here
    CString prog = _T("txttransprep");
	CString args = _T("SRCS SPLS TXTS");
	WriteABatch(_T("prepaspects"),prog,args,_T("Aspects"));
	WriteABatch(_T("prepregular"),prog,args,_T("Regular"));
	WriteABatch(_T("prephelp"),prog,args,_T("Help"));
	prog = _T("reptransprep");
	WriteABatch(_T("prepreports"),prog,args,_T("Reports"));
	int drive = _getdrive();
	wchar_t buf[250];
	wchar_t *cd=_wgetdcwd(drive,buf,250);
	if ( cd!=NULL) {
	   CString olddir = cd;
       WriteABatch(_T("chdir"),olddir,args,NULL);
	}
	if ( base.GetLength() ) {
     if ( base.Right(1)!=_T("\\"))
		 base += _T("\\");
  }
  CString prepare = base + _T("Prepare.cmd");
  WinExec((LPCTSTR)prepare,SW_SHOW);
}

void CTransWiz::OnBnClickedSetbasedir()
{
	// TODO: Add your control notification handler code here
   CTransBase bs(this);
   bs.DoModal();
}

void CTransWiz::OnBnClickedSetcurrlang()
{
	// TODO: Add your control notification handler code here
	CSetLanguage se(this);
	se.DoModal();
}

void CTransWiz::OnBnClickedSettransdir()
{
	// TODO: Add your control notification handler code here
	CSetTransDir td(this);
	td.DoModal();
}

void CTransWiz::OnBnClickedAddnewlang()
{
	// TODO: Add your control notification handler code here
	CNewLanguage nl(this);
	nl.DoModal();
}

void RunGrep( char *pat ) 
{
 char buf[200];
 CString str = GetTransDir();
 CString base = AfxGetApp()->GetProfileString(_T("Translation"),_T("BaseDir"));
 if ( base.Right(1)!=_T("\\"))
    base += _T("\\");
 sprintf( buf, "grep -C -ns -e %s %ls*.txt >> %ls\\trans.err", pat, (LPCTSTR)str, (LPCTSTR)base );
 system(buf);
}

void viewGrepOut() 
{
 CString base = AfxGetApp()->GetProfileString(_T("Translation"),_T("BaseDir"));
 if ( base.Right(1)!=_T("\\"))
    base += _T("\\");
 CString cmd = "Notepad ";
 cmd += base;
 cmd += _T("trans.err");
 WinExec((LPCTSTR),SW_SHOW);
}


void CTransWiz::OnBnClickedCheck()
{
	// TODO: Add your control notification handler code here
}

void CTransWiz::ExportAspectText()
{
	// TODO: Add your command handler code here
	CString dir = GetTextDir();
	if ( dir.GetLength() == 0 )
		return;
	CString Lang = "";
    Lang = GetCurLanguage();
	CProgress prog(this);
	CAspDbExport exp(dir,&prog,pATextTypes->TypeCount(3),Lang);
	CBatchMgr bm(CString(_T("Aspect")),dir);
	exp.SetArray((CStringArray *)&bm);
	exp.Process();
	bm.Write();
}

void CTransWiz::ExportHelpText()
{
	// TODO: Add your command handler code here
	CString dir = GetTextDir();
	if ( dir.GetLength() == 0 )
		return;
	CString Lang = "";
    Lang = GetCurLanguage();	
	CProgress prog(this);
	CHlpDbExport exp(dir,&prog,pATextTypes->TypeCount(0),Lang);
	CBatchMgr bm(CString(_T("Help")),dir);
	exp.SetArray((CStringArray *)&bm);
	exp.Process();
	bm.Write();
}


void CTransWiz::ExportRegularText()
{
	// TODO: Add your command handler code here
	CString dir = GetTextDir();
	if ( dir.GetLength() == 0 )
		return;
	CString Lang = "";
    Lang = GetCurLanguage();
	CProgress prog(this);
	CRegDbExport exp(dir,&prog,pATextTypes->TypeCount(2),Lang);
	CBatchMgr bm(CString(_T("Regular")),dir);
	exp.SetArray((CStringArray *)&bm);
	exp.Process();
	bm.Write();
}


void CTransWiz::ExportReportText()
{
	// TODO: Add your command handler code here
    CString dir = GetTextDir();
	if ( dir.GetLength() == 0 )
		return;
	CString Lang = "";
    Lang = GetCurLanguage();
	CProgress prog(this);
	CReptDbExport exp(dir,&prog,pATextTypes->TypeCount(1),Lang);
	CBatchMgr bm(CString(_T("Report")),dir);
	exp.SetArray((CStringArray *)&bm);
	exp.Process();
	bm.Write();
}


void CTransWiz::ImportAspectFiles()
{
	// TODO: Add your command handler code here
    char buf1[25], buf2[25], buf3[25];;
	CString dir = GetTransDir();
	if ( dir.GetLength() == 0 )
		return;
	CFileSelector sel(this);
	sel.m_type=3;
	sel.m_bExport = TRUE;
	if ( sel.DoModal() != IDOK )
		return;
	CProgress prog(this);
	for ( int i = 0; i < sel.m_FileAry.GetSize(); i++ ) {
	    CString str = sel.m_FileAry[i];
		if ( str.GetLength()==0)
			continue;
		memset(buf1,0,25);
		memset(buf2,0,25);
		memset(buf3,0,25);
		strcpy(buf1, pFileList->toFileName( str) );
        strcpy(buf2, buf1 );
		sprintf(buf3,"3-%s", buf1);
		ImportAspText *imp = new ImportAspText(buf3,buf2, &prog, dir);
	    imp->Process();
	    delete imp;
		}
}


void CTransWiz::ImportHelpFiles()
{
	// TODO: Add your command handler code here
	CString dir = GetTransDir();
	if ( dir.GetLength() == 0 )
		return;
	CProgress prog(this);
	ImportHelp *imp = new ImportHelp(&prog,dir,TRUE);
	imp->Process();
	delete imp;
}


void CTransWiz::ImportPlanetFiles()
{
	// TODO: Add your command handler code here
	char buf1[25], buf2[25], buf3[25];
	CString dir = GetTransDir();
	if ( dir.GetLength() == 0 )
		return;
	CFileSelector sel(this);
	sel.m_bExport = TRUE;
	sel.m_type=2;
	if ( sel.DoModal() != IDOK )
		return;
	CProgress prog(this);
	for ( int i = 0; i < sel.m_FileAry.GetSize(); i++ ) {
	    CString str = sel.m_FileAry[i];
	    if ( str.GetLength()==0)
		   continue;
		memset(buf1,0,25);
		memset(buf2,0,25);
		memset(buf3,0,25);
	    strcpy(buf1, pFileList->toFileName(str) );
        strcpy(buf2, buf1);
		sprintf(buf3,"2-%s", buf1);
		ImportRegText *imp = new ImportRegText(buf3,buf2, &prog, dir);
	    imp->Process();
	    delete imp;
		}
}


void CTransWiz::ImportReportFiles()
{
	// TODO: Add your command handler code here
	char buf1[25], buf2[50], buf3[50];
	CString dir = GetTransDir();
	if ( dir.GetLength() == 0 )
		return;
	CFileSelector sel(this);
	sel.m_bExport = TRUE;
	sel.m_type=1;
	if ( sel.DoModal() != IDOK )
		return;
	CProgress prog(this);
	ImportReportText *imp;
	CString str;
	int i = 0;
	for ( i = 0; i < sel.m_FileAry.GetSize(); i++ ) {
	    str = sel.m_FileAry[i];
	    if (str.GetLength()==0)
		   continue;
		memset(buf1,0,25);
		memset(buf2,0,50);
		memset(buf3,0,50);
	    strcpy(buf1, pFileList->toFileName((CString &)str) );
        strcpy(buf2, buf1);
		sprintf(buf3,"1-%s",buf1);
		imp = new ImportReportText(buf3,buf2,&prog, dir);
		imp->Process();
	    delete imp;
		}
}

void CTransWiz::WriteABatch(LPCTSTR name, CString &prog, CString &args, LPCTSTR bid )
{
  static FILE *batchstream=NULL;
  CString base = AfxGetApp()->GetProfileString(_T("Translation"),_T("BaseDir"));
  if ( base.GetLength() ) {
     if ( base.Right(1)!=_T("\\"))
		 base += _T("\\");
  }
  else {
	 AfxMessageBox(_T("Must Set Base Dir First"));
     return;
  }
  if ( batchstream == NULL ) {
     CString file=base;
	 if ( !wcsnicmp(name,_T("prep"),4) )
        file += _T("prepare.cmd");
	 else
		file += _T("merge.cmd");
	 batchstream = _wfopen((LPCTSTR)file,_T("wt"));
	 if ( batchstream == NULL ) {
	    do_error((LPCTSTR)file);
		return;
	 }
  }
  else if ( !wcsicmp(name,_T("chdir")) ) {
     fputs("chdir ",batchstream);
	 fprintf(batchstream,"%ls\n", (LPCTSTR)prog);
	 fclose(batchstream);
	 batchstream = NULL;
	 return;
  }
  CString str = base;
  str += name;
  str += _T(".cmd");
  fprintf(batchstream,"call %ls\n", (LPCTSTR)str);
  CString batch = bid;
  CString path = _T("C:\\program files\\astro for windows\\tbt\\");
  CBatchMgr bm(batch,base);
  bm.Read();
  CBatchWriter wrtr(str,path,prog,args,(CStringArray *)&bm);
  wrtr.WriteBatch();
}
#endif