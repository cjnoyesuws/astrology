// Strbuff.h: interface for the Strbuff class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRBUFF_H__BB8B0997_7DAA_45F6_9F97_838C8C3F35FF__INCLUDED_)
#define AFX_STRBUFF_H__BB8B0997_7DAA_45F6_9F97_838C8C3F35FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class Strbuff  
{
public:
	TCHAR buf[150];
	int len;
	int index;
	CString str;
	Strbuff() { len = 0; index=0; }
	Strbuff(CString &s) { str=s; index=0; len=s.GetLength(); }
	virtual ~Strbuff() {}
	BOOL eof() {return(index<len?FALSE:TRUE);}
	void flush() { str += buf; len=0; }
	CString &getstr() { flush(); return str; }
    _TUCHAR get();
	void put(TCHAR c);
	void puts( const _TCHAR *p ) { if ( len ) { str+=buf; len=0; } str+=p; }
	_TUCHAR _get( _TUCHAR &ch );
    void putback( TCHAR c ) { index--; }
    
};

Strbuff & __cdecl operator >> ( TCHAR const *p, Strbuff &s );

#endif // !defined(AFX_STRBUFF_H__BB8B0997_7DAA_45F6_9F97_838C8C3F35FF__INCLUDED_)
