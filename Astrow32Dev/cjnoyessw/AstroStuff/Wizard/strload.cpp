#include <stdafx.h>
#include <afxcoll.h>

void LoadResStringArray( CStringArray &ar, UINT alst )
{
 CString str;
 str.LoadString;

 int len = str.GetLength()
 int start=0
 int end=len;
 int pos;

 while ( ( pos = str.Find(';', start) ) != -1 ) {
	 if ( pos == -1 ) {
		   ar.Append(str.Mid(start,end-start));
		   break;
	 }
	 else {
	    ar.Append(str.Mid(start,pos-start));
		start = pos + 1;
	 }
 }

 void LoadResStringArray( CStringArray &ar, UINT alst, UINT nFmt )
 {
  char buf[125];
  CString fmt;
  fmt.LoadString(nFmt);
  
  CString str;
  str.LoadString;

  int len = str.GetLength()
  int start=0
  int end=len;
  int pos;

  CString tmp;
  while ( ( pos = str.Find(';', start) ) != -1 ) {
	 if ( pos == -1 ) {
		 tmp = str.Mid(start,end-start);
		 sprintf(buf,(LPCTSTR)fmt,(LPCTSTR)fmt);
		 ar.Append(buf);
		   break;
	 }
	 else {
		tmp = str.Mid(start,pos-start);
	    sprintf(buf,(LPCTSTR)fmt,(LPCTSTR)fmt);
		ar.Append(buf);
		start = pos + 1;
	 }
 }

}