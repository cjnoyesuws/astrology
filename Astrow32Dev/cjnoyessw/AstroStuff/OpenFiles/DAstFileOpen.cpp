// DAstFileOpen.cpp : implementation file
//

#include "stdafx.h"
#include "OpenFiles.h"
#include "direc.hpp"
#include "FileListSet.h"
#include "foldersset.h"
#include "DAstFileOpen.h"
#include ".\dastfileopen.h"


// CDAstFileOpen dialog

IMPLEMENT_DYNAMIC(CDAstFileOpen, CDialog)
CDAstFileOpen::CDAstFileOpen(CWnd* pParent /*=NULL*/)
	: CDialog(CDAstFileOpen::IDD, pParent)
	, m_graphs(TRUE)
	, m_grids(TRUE)
	, m_reports(TRUE)
	, m_folderno(10)
	, m_sort(_T("name"))
	, m_caption(_T("Open Files"))
{
}

CDAstFileOpen::~CDAstFileOpen()
{
}

void CDAstFileOpen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FOLDER, m_folders);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Check(pDX, IDC_GRAPHS, m_graphs);
	DDX_Check(pDX, IDC_GRIDS, m_grids);
	DDX_Check(pDX, IDC_REPORTS, m_reports);
}


BEGIN_MESSAGE_MAP(CDAstFileOpen, CDialog)
	ON_NOTIFY(HDN_ITEMCLICK, 0, OnHdnItemclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnNMRclickList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnNMClickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
	ON_CBN_SELCHANGE(IDC_FOLDER, OnCbnSelchangeFolder)
	ON_BN_CLICKED(IDC_GRAPHS, OnBnClickedGraphs)
	ON_BN_CLICKED(IDC_GRIDS, OnBnClickedGrids)
	ON_BN_CLICKED(IDC_REPORTS, OnBnClickedReports)
END_MESSAGE_MAP()


// CDAstFileOpen message handlers

void CDAstFileOpen::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	while ( pos != NULL ) {
		m_selected.Add(m_filenames.GetAt(m_list.GetNextSelectedItem(pos)));
	}

	CDialog::OnOK();
}

BOOL CDAstFileOpen::OnInitDialog()
{
	CDialog::OnInitDialog();
    UpdateData(FALSE);
   
	SetWindowText(m_caption);
	m_list.InsertColumn(0,"Name", LVCFMT_LEFT,320,-1);
	m_list.InsertColumn(1,"Comments", LVCFMT_LEFT,300,1);
	m_list.InsertColumn(3,"File Type", LVCFMT_LEFT,300,3);
	m_reportbmp.LoadBitmap(IDB_REPORT);
	m_graphbmp.LoadBitmap(IDB_GRAPH);
	m_gridbmp.LoadBitmap(IDB_GRID);
	m_images.Create(24,24,ILC_COLOR4,3,1);
	m_images.Add(&m_reportbmp,&m_reportbmp);
    m_images.Add(&m_graphbmp,&m_graphbmp);
	m_images.Add(&m_gridbmp,&m_gridbmp);
	m_list.SetImageList(&m_images,LVSIL_SMALL);
	LoadList();
    LoadFolders();
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDAstFileOpen::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: Add your control notification handler code here
	switch( phdr->iItem ) {
	  case 0:
		  m_sort = "name";
		  break;
	  case 1:
		  m_sort = "comments";
		  break;
	  case 2:
		  m_sort = "FileType";
		  break;
	  default:
		  break;
	}
	LoadList();
	*pResult = 0;
}

void CDAstFileOpen::OnNMRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CDAstFileOpen::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CDAstFileOpen::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CDAstFileOpen::OnCbnSelchangeFolder()
{
	// TODO: Add your control notification handler code here
	int sel = m_folders.GetCurSel();
	if ( AfxMessageBox("Ok To Lose Your Selections?", MB_YESNO) == IDYES ) {
	   m_folderno = (int) m_folders.GetItemData(sel);
	   LoadList();
	}
}

void CDAstFileOpen::OnBnClickedGraphs()
{
	// TODO: Add your control notification handler code here
    UpdateData();
	LoadList();
}

void CDAstFileOpen::OnBnClickedGrids()
{
	// TODO: Add your control notification handler code here
    UpdateData();
	LoadList();
}

void CDAstFileOpen::OnBnClickedReports()
{
	// TODO: Add your control notification handler code here
    UpdateData();
	LoadList();
}

void CDAstFileOpen::LoadList()
{
  m_list.DeleteAllItems();
  m_filenames.RemoveAll();
  m_filelist.m_strSort = m_sort;
  m_filelist.m_strFilter = MakeFilter();
  m_filelist.Open();
  int nItem=0, nImage = 0;
  if ( !m_filelist.IsEOF() ) {
	  while ( !m_filelist.IsEOF() ) {
		  if ( m_filelist.m_ListType == "GRA")
			  nImage = 1;
		  else if ( m_filelist.m_ListType == "GRD")
			  nImage = 2;
		  else
			  nImage = 0;
		  m_list.InsertItem(nItem,m_filelist.m_name,nImage);
		  m_list.SetItemText(nItem,1,m_filelist.m_comments);
		  m_list.SetItemText(nItem,2,long_types[m_filelist.m_FileType]);
		  m_filenames.SetAtGrow(nItem,m_filelist.m_filename);
		  m_filelist.MoveNext();
	      nItem++;
	  }
  }
  m_filelist.Close();
}

void CDAstFileOpen::LoadFolders()
{
  m_folders.ResetContent();
  int item =m_folders.AddString("Default Folder");
  m_folders.SetItemData(item, 10);
  m_foldersset.Open();
  if ( !m_foldersset.IsBOF() && !m_foldersset.IsEOF() ) {
	  while ( !m_foldersset.IsEOF() ) {
		  item =m_folders.AddString(m_foldersset.m_folder_name);
		  m_folders.SetItemData(item, m_foldersset.m_folder_num);
		  m_foldersset.MoveNext();
	  }
  }
  m_folders.SetCurSel(0);
}

CString CDAstFileOpen::MakeFilter()
{
    char *inlist = NULL, buf[300];
	if (m_graphs && m_grids && m_reports)
       inlist = "in ('GRD','OUT','GRA')";
	else if (!m_graphs && m_grids && m_reports)
       inlist = "in ('GRD','OUT')";
    else if (m_graphs && !m_grids && m_reports)
	   inlist = "in ('GRA','OUT')";
	else if (m_graphs && m_grids && !m_reports)
	   inlist = "in ('GRA','GRD')";
	else if ( m_graphs )
	   inlist = "='GRA'";
	else if ( m_grids )
	   inlist = "='GRD'";
	else
	   inlist = "='OUT'";
    sprintf( buf, "ListType %s and Folder=%d", inlist, m_folderno );
	return ( CString(buf));
}
