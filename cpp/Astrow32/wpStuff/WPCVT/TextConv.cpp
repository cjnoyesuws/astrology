#include <windows.h>
#include <malloc.h>
#include "scwin32.h"
#include "sctypes.h"
#include "wpwp7us.h"
#include "WPCVT.h"


void InsertText( char *text )
{
InitTkn( 1 );
LPWZ lpwzBuf = (LPWZ)AllocPtr( strlen(text)*2, GHND );
lpfnW6azTowz( (unsigned char *)text, (unsigned short *)lpwzBuf );
AddTknParm( 0, eParmStringWord, 0x0000, (PARAMETER)lpwzBuf );
FreePtr( lpwzBuf );
SendTkn( WP_Type );
FreeTkn( );
}

void InsertHardRet()
{							  
InitTkn( 0 );
SendTkn( WP_HardReturn );
FreeTkn( );
}

void FontName(char *family )
{
InitTkn( 8 );
LPVOID lpwzBuf = AllocPtr( (int)(strlen(family)*2)+2, GHND );
lpfnW6azTowz( (unsigned char *)family, (unsigned short *)lpwzBuf );
AddTknParm( 0, eParmStringWord, 0x0000, (PARAMETER)lpwzBuf );
FreePtr( lpwzBuf );
AddTknParm( 1, eParmEnumeration, 0x8000, (PARAMETER)0 );
AddTknParm( 2, eParmEnumeration, 0x8000, (PARAMETER)0 );
AddTknParm( 3, eParmEnumeration, 0x8000, (PARAMETER)0 );
AddTknParm( 4, eParmEnumeration, 0x8000, (PARAMETER)0 );
AddTknParm( 5, eParmEnumeration, 0x8000, (PARAMETER)0 );
AddTknParm( 6, eParmEnumeration, 0x8000, (PARAMETER)0 );
AddTknParm( 7, eParmEnumeration, 0x0000, (PARAMETER)0 );
SendTkn( WP_Font );
FreeTkn( );
}

void FontSize( int size )
{
InitTkn( 1 );
AddTknParm( 0, eParmWPUUnsigned, 0x0000, (PARAMETER)14400 );
SendTkn( WP_FontSize );
FreeTkn( );
}

void FontItalicToggle()
{
InitTkn( 0 );
SendTkn( WP_FontItalicToggle );
FreeTkn( );
}

void FontBoldToggle()
{
InitTkn( 0 );						
SendTkn( WP_BoldKey );
FreeTkn( );
}

void insertTab()
{
InitTkn( 0 );
SendTkn( WP_TabInsert );
FreeTkn( );
}

void ClearTabs()
{
InitTkn( 0 );
SendTkn( WP_TabClearAll );
FreeTkn( );
}

void AddTab(int tabval )
{
InitTkn( 3 );
AddTknParm( 0, eParmWPUUnsigned, 0x0000, (PARAMETER)tabval );
AddTknParm( 1, eParmEnumeration, 0x0000, (PARAMETER)0 );
AddTknParm( 2, eParmWPUUnsigned, 0x0000, (PARAMETER)0 );
SendTkn( WP_TabAdd );
FreeTkn( );
}

void JustLeft()
{
InitTkn( 0 );
SendTkn( WP_JustifyLeft );
FreeTkn( );
}

void JustCenter()
{
InitTkn( 0 );
SendTkn( WP_JustifyCenter );
FreeTkn( );
}


void SetColor( char *color, short r, short b, short g )
{
 InitTkn( 4 );
 LPVOID lpwzBuf = AllocPtr( (int)(strlen(color)+1)*2, GHND );
 lpfnW6azTowz( (unsigned char *)color, (unsigned short *)lpwzBuf );
 AddTknParm( 0, eParmStringWord, 0x0000, (PARAMETER)lpwzBuf );
 FreePtr( lpwzBuf );
 AddTknParm( 1, eParmByteUnsigned, 0x0000, (PARAMETER)r );
 AddTknParm( 2, eParmByteUnsigned, 0x0000, (PARAMETER)b );
 AddTknParm( 3, eParmByteUnsigned, 0x0000, (PARAMETER)g );
 SendTkn( WP_TextColor );
 FreeTkn( );
}
