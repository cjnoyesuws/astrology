// NumerowCalcer.cpp : Implementation of CNumerowCalcer

#include "stdafx.h"
#include "numdll.h"
#include "NumerowCalcer.h"
#include ".\numerowcalcer.h"
#include <comutil.h>
#include <atlcomtime.h>


char *checkptr( char *p )
{
 static char zero[2] = "";

 if ( p == NULL )
	 return zero;
 else
	 return p;
}

// CNumerowCalcer

char *CNumerowCalcer::get_name_ptr(int which)
{
 NAME_REC *np;

 switch( index ) {
 case 1:
    np = &theChartInfo.at_birth;
    break;
 case 2:
    np = &theChartInfo.current;
    break;
 case 3:
    np = &theChartInfo.opt1;
    break;
 case 4:
    np = &theChartInfo.opt2;
    break;
 default :
	return NULL;
	break;
 }
 np->include = 1;
 switch( which ) {
 case 1:
    return( np->first );;
    break;
 case 2:
    return( np->middle );
    break;
 case 3:
    return( np->last );
    break;
  default :
	return NULL;
	break;
 }

}

STDMETHODIMP CNumerowCalcer::put_Index(SHORT newVal)
{
	// TODO: Add your implementation code here
    index = newVal;
	return S_OK;
}

STDMETHODIMP CNumerowCalcer::put_FirstName(BSTR newVal)
{
	// TODO: Add your implementation code here
	_bstr_t bstr(newVal);
    strcpy(get_name_ptr(1),checkptr((char *)bstr));
	return S_OK;
}


STDMETHODIMP CNumerowCalcer::put_MiddleName(BSTR newVal)
{
	// TODO: Add your implementation code here
	_bstr_t bstr(newVal);
	strcpy(get_name_ptr(2),checkptr((char *)bstr));
	return S_OK;
}

STDMETHODIMP CNumerowCalcer::put_LastName(BSTR newVal)
{
	// TODO: Add your implementation code here
	_bstr_t bstr(newVal);
	strcpy(get_name_ptr(3),checkptr((char *)bstr));
	return S_OK;
}

STDMETHODIMP CNumerowCalcer::put_BirthDate(DATE newVal)
{
	// TODO: Add your implementation code here
    COleDateTime dt(newVal);
	theChartInfo.birth_date.day = dt.GetDay();
	theChartInfo.birth_date.month = dt.GetMonth();
	theChartInfo.birth_date.year = dt.GetYear();
	theChartInfo.birth_date.include;
	return S_OK;
}

STDMETHODIMP CNumerowCalcer::CalcChart(CHAR* file, CHAR* person, CHAR* comments, CHAR* type, SHORT typecode)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CNumerowCalcer::put_TransStart(SHORT newVal)
{
	// TODO: Add your implementation code here
    start = newVal;
	return S_OK;
}

STDMETHODIMP CNumerowCalcer::put_TransEnd(SHORT newVal)
{
	// TODO: Add your implementation code here
    end = newVal;
	return S_OK;
}

STDMETHODIMP CNumerowCalcer::put_FontName(BSTR newVal)
{
	// TODO: Add your implementation code here
	_bstr_t bstr(newVal);
	strcpy(theFonts[index].lfFaceName, checkptr((char *)bstr));
	return S_OK;
}

STDMETHODIMP CNumerowCalcer::put_FontSize(SHORT newVal)
{
	// TODO: Add your implementation code here
	theFonts[index].lfHeight = newVal;
	return S_OK;
}

STDMETHODIMP CNumerowCalcer::put_FontCodes(SHORT newVal)
{
	// TODO: Add your implementation code here
	theFonts[index].lfUnderline = (newVal & _UNDERLINE_?1:0);
	theFonts[index].lfPitchAndFamily = newVal & _PITCH_;
	theFonts[index].lfItalic = (newVal & _ITALIC_?1:0);
	theFonts[index].lfWeight = (newVal & _ISBOLD_?FW_BOLD:FW_NORMAL);
	return S_OK;
}

STDMETHODIMP CNumerowCalcer::put_FontColor(ULONG newVal)
{
	// TODO: Add your implementation code here
    theColors[index] = (ULONG) newVal;
	return S_OK;
}

STDMETHODIMP CNumerowCalcer::put_LeftMargin(SHORT newVal)
{
	// TODO: Add your implementation code here
    left_offset = newVal;
	return S_OK;
}

STDMETHODIMP CNumerowCalcer::put_TextWidth(SHORT newVal)
{
	// TODO: Add your implementation code here
    width = newVal;
	return S_OK;
}

STDMETHODIMP CNumerowCalcer::put_DemoMode(SHORT newVal)
{
	// TODO: Add your implementation code here
    demo_mode = newVal;
	return S_OK;
}

STDMETHODIMP CNumerowCalcer::ConvertFile(CHAR* in_name, CHAR* out_name, SHORT type)
{
	// TODO: Add your implementation code here

	return S_OK;
}
