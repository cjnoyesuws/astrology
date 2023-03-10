// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "pfconvrt.h"

/////////////////////////////////////////////////////////////////////////////
// CPFConvrt

IMPLEMENT_DYNCREATE(CPFConvrt, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CPFConvrt properties

CString CPFConvrt::GetSource()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void CPFConvrt::SetSource(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

CString CPFConvrt::GetDestination()
{
	CString result;
	GetProperty(0x2, VT_BSTR, (void*)&result);
	return result;
}

void CPFConvrt::SetDestination(LPCTSTR propVal)
{
	SetProperty(0x2, VT_BSTR, propVal);
}

long CPFConvrt::GetSourceType()
{
	long result;
	GetProperty(0x3, VT_I4, (void*)&result);
	return result;
}

void CPFConvrt::SetSourceType(long propVal)
{
	SetProperty(0x3, VT_I4, propVal);
}

long CPFConvrt::GetDestinationType()
{
	long result;
	GetProperty(0x4, VT_I4, (void*)&result);
	return result;
}

void CPFConvrt::SetDestinationType(long propVal)
{
	SetProperty(0x4, VT_I4, propVal);
}

BOOL CPFConvrt::GetWriteDefaults()
{
	BOOL result;
	GetProperty(0x5, VT_BOOL, (void*)&result);
	return result;
}

void CPFConvrt::SetWriteDefaults(BOOL propVal)
{
	SetProperty(0x5, VT_BOOL, propVal);
}

BOOL CPFConvrt::GetExternalGraphicsFile()
{
	BOOL result;
	GetProperty(0x6, VT_BOOL, (void*)&result);
	return result;
}

void CPFConvrt::SetExternalGraphicsFile(BOOL propVal)
{
	SetProperty(0x6, VT_BOOL, propVal);
}

BOOL CPFConvrt::GetPleaseWait()
{
	BOOL result;
	GetProperty(0x7, VT_BOOL, (void*)&result);
	return result;
}

void CPFConvrt::SetPleaseWait(BOOL propVal)
{
	SetProperty(0x7, VT_BOOL, propVal);
}

BOOL CPFConvrt::GetSkipPrefix()
{
	BOOL result;
	GetProperty(0x8, VT_BOOL, (void*)&result);
	return result;
}

void CPFConvrt::SetSkipPrefix(BOOL propVal)
{
	SetProperty(0x8, VT_BOOL, propVal);
}

long CPFConvrt::GetWPGFlags()
{
	long result;
	GetProperty(0x9, VT_I4, (void*)&result);
	return result;
}

void CPFConvrt::SetWPGFlags(long propVal)
{
	SetProperty(0x9, VT_I4, propVal);
}

long CPFConvrt::GetDestinationTypeEnum()
{
	long result;
	GetProperty(0xa, VT_I4, (void*)&result);
	return result;
}

void CPFConvrt::SetDestinationTypeEnum(long propVal)
{
	SetProperty(0xa, VT_I4, propVal);
}

long CPFConvrt::GetSourceTypeEnum()
{
	long result;
	GetProperty(0xb, VT_I4, (void*)&result);
	return result;
}

void CPFConvrt::SetSourceTypeEnum(long propVal)
{
	SetProperty(0xb, VT_I4, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CPFConvrt operations

long CPFConvrt::Execute()
{
	long result;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

short CPFConvrt::DetectFileFormat()
{
	short result;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
	return result;
}

void CPFConvrt::SetFlags()
{
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CPFConvrt::OCXToPF(long OCXType)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		OCXType);
	return result;
}

long CPFConvrt::PFToOCX(long PFType)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		PFType);
	return result;
}

CString CPFConvrt::ErrorString(long ErrNum)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		ErrNum);
	return result;
}

void CPFConvrt::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
