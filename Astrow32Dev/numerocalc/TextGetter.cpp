// TextGetter.cpp : Implementation of CTextGetter

#include "stdafx.h"
#include "TextGetter.h"
#include ".\textgetter.h"
#include <comutil.h>

// CTextGetter


STDMETHODIMP CTextGetter::put_Row(SHORT newVal)
{
	// TODO: Add your implementation code here
    row = newVal;
	return S_OK;
}

STDMETHODIMP CTextGetter::put_Col(SHORT newVal)
{
	// TODO: Add your implementation code here
    col = newVal;
	return S_OK;
}

STDMETHODIMP CTextGetter::get_Text(BSTR* pVal)
{
	// TODO: Add your implementation code here
	_bstr_t bstr("Text Returned");
	*pVal = bstr.GetBSTR();
	return S_OK;
}
