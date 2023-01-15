#include "StdAfx.h"
#include ".\folders.h"
#include "paths.hpp"
#include "errors.fns"
#include "direct.h"
#ifndef CHARTVIEW
#include "foldersset.h"
#endif

CFolders::CFolders()
{
 FldCount=0;
 CurFolder = DEFAULT_FLD;
 CurFolderName = "";
 SetSize(10,5);
 SetAt(0,"");
}

CFolders::~CFolders()
{
 RemoveAll();
}

void CFolders::ChangeFolder(int fld)
{
 if ( fld > 0 && fld <= FldCount+DEFAULT_FLD ) {
	CurFolder = fld;
	CurFolderName = GetAt(fld-DEFAULT_FLD);
    }
 else
    alert_box("Error","Invalid Folder");
}

void CFolders::AddFolder(CString &fn)
{
 char buf[300];
 SetAtGrow(++FldCount,fn);
 strcpy(buf, set_path((char *)(const char *)fn,USER_F));
 _mkdir(buf);
 //SaveToIni();
#ifndef CHARTVIEW
 try {
	  CFoldersSet fld;
	  fld.Open();
	  fld.AddNew();
	  fld.m_folder_num = FldCount;
	  fld.m_folder_name = fn;
	  fld.Update();
	}
	catch ( CDaoException *e ) {
	  char buf[500];
      e->GetErrorMessage(buf,500);
      alert_box("Database Error", buf );
	}
#endif
}

void CFolders::RenameFolder(CString &newn)
{
 char buf[300], newb[300];
 if ( CurFolder != DEFAULT_FLD ) {
    strcpy(newb, set_path((char *)(const char *)newn,USER_F));
	strcpy(buf, set_path((char *)(const char *)CurFolderName,USER_F));
    rename(buf,newb);
	SetAt(CurFolder-DEFAULT_FLD,newn);
#ifndef CHARTVIEW 
	sprintf(buf,"select * from folders where folder_num=%d",CurFolder-DEFAULT_FLD); 
	try {
	  CFoldersSet fld;
	  fld.Open(-1,buf);
	  if ( !fld.IsBOF() ) {
		  fld.Edit();
		  fld.m_folder_name = newn;
		  fld.Update();
	  }
	}
	catch ( CDaoException *e ) {
	  char buf[500];
      e->GetErrorMessage(buf,500);
      alert_box("Database Error", buf );
	}
 }
 else
	 alert_box("Error","Can't Rename Default Folder");
#else
 }
#endif
 //SaveToIni();
}

void CFolders::getFromIni()
{
#ifndef CHARTVIEW
 CFoldersSet fld;
 try {
   fld.Open();
   if ( !fld.IsBOF() && !fld.IsEOF() ) {
	   do {
		   SetAtGrow(fld.m_folder_num,fld.m_folder_name);
		   if ( FldCount < fld.m_folder_num )
              FldCount < fld.m_folder_num;
		   fld.MoveNext();
	   } while ( !fld.IsBOF() && !fld.IsEOF());
   }
 }
 catch ( CDaoException *e ) {
   char buf[500];
   e->GetErrorMessage(buf,500);
   alert_box("Database Error", buf );
 }
 FldCount++;
#endif
}

void CFolders::SaveToIni()
{
 /*char buf[25];
 AfxGetApp()->WriteProfileString("Folders","FolderCount",itoa(FldCount,buf,10));
 for ( int i = 0; i < FldCount; i++ ) {
     sprintf(buf,"Folder%d",i);
	 AfxGetApp()->WriteProfileString("Folders",buf,GetAt(i+1));
     }*/
}

void CFolders::toCombo(CComboBox *p)
{
 if ( !FldCount )
	 return;
 p->ResetContent();
 p->AddString("Default");
 for ( int i = 0; i < FldCount; i ++ )
	 p->AddString(GetAt(i));
}

CString CFolders::GetFolder(int f)
{
 if ( f > DEFAULT_FLD && f < DEFAULT_FLD+FldCount )
	 return GetAt(f-DEFAULT_FLD);
 else
	 return "";
}