#include <windows.h>
#include "scwin32.h"
#include "sctypes.h"
#include "wpwp7us.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "WPCVT.h"




FONT theFonts[4];
COLORREF theColors[4];
int doColors, doFonts;
TCHAR  szFile[MAX_PATH];
TCHAR  szBuf[MAX_PATH+30];
	

FILE *GetTheFile(LPSTR lpFileName)
{
    FILE *stream;
	OPENFILENAME OpenFileName;
	char *lpBufPtr;

    strcpy( szFile, "TEXT.WPI");


	// Fill in the OPENFILENAME structure to support a template and hook.
	OpenFileName.lStructSize       = sizeof(OPENFILENAME);
    OpenFileName.hwndOwner         = NULL;
    OpenFileName.hInstance         = 0;
    OpenFileName.lpstrFilter       = "WordPerfect Import Files\x00*.WPI\x00All Files\x00*.*\x00\x00";
    OpenFileName.lpstrCustomFilter = NULL;
    OpenFileName.nMaxCustFilter    = 0;
    OpenFileName.nFilterIndex      = 0;
    OpenFileName.lpstrFile         = szFile;
    OpenFileName.nMaxFile          = sizeof(szFile);
    OpenFileName.lpstrFileTitle    = NULL;
    OpenFileName.nMaxFileTitle     = 0;
    OpenFileName.lpstrInitialDir   = NULL;
    OpenFileName.lpstrTitle        = "File To Import";
    OpenFileName.nFileOffset       = 0;
    OpenFileName.nFileExtension    = 0;
    OpenFileName.lpstrDefExt       = NULL;
    OpenFileName.lCustData         = NULL;
	OpenFileName.lpfnHook 		   = NULL;
	OpenFileName.lpTemplateName    = NULL;
    OpenFileName.Flags             = OFN_SHOWHELP | OFN_EXPLORER ;

	// Call the common dialog function.
    if (GetOpenFileName(&OpenFileName)) {
	   strcpy(lpFileName,szFile);
	   }
	else
	   return( NULL );
 if ((stream = fopen(szFile, "rb"))!= NULL )
	return( stream );
 else {
	sprintf( szBuf, "Can\'t Open File To Import: %s!", szFile );
	MessageBox( NULL, szBuf, "Error Opening...", MB_OK|MB_ICONERROR );
	return( NULL );
	}
}


void TestFonts()
{
 if ( !strcmpi(theFonts[0].lfFaceName, theFonts[1].lfFaceName) &&
	  !strcmpi(theFonts[0].lfFaceName, theFonts[2].lfFaceName) &&
	  !strcmpi(theFonts[0].lfFaceName, theFonts[3].lfFaceName) &&
	  theFonts[0].lfHeight == theFonts[1].lfHeight &&
	  theFonts[0].lfHeight == theFonts[2].lfHeight &&
	  theFonts[0].lfHeight == theFonts[3].lfHeight )
	doFonts=0;
 else
	doFonts=1;
}


void TestColors()
{
 if ( (DWORD)theColors[0]==0L && (DWORD)theColors[1]==0L && 
	 (DWORD)theColors[2]==0L && (DWORD)theColors[3]==0L )
	doColors=0;
 else
	doColors=1;

}


void InitializeData(FILE *stream )
{
 fread( theFonts, sizeof(FONT), 4, stream );
 fread( theColors, sizeof(COLORREF), 4, stream );
 TestFonts();
 TestColors();
}


void StartReg()
{
 FontName(theFonts[0].lfFaceName);
 FontSize(theFonts[0].lfHeight); 
 if (theFonts[0].lfWeight >= FW_BOLD ) 
	FontBoldToggle();
 if (theFonts[0].lfItalic || theFonts[0].lfUnderline) 
	FontItalicToggle();
 if (doColors)					 
	SetColor("Reg", GetRValue(theColors[0]),GetBValue(theColors[0]),GetGValue(theColors[0]) );
}

void EndBoldScoreHead(int index )
{
 if(doFonts && strcmpi(theFonts[0].lfFaceName, theFonts[index].lfFaceName) ) 
   FontName(theFonts[0].lfFaceName);
 if (theFonts[0].lfHeight!=theFonts[index].lfHeight)
    FontSize(theFonts[0].lfHeight); 
 if (theFonts[0].lfWeight < theFonts[index].lfWeight || theFonts[0].lfWeight > theFonts[index].lfWeight) 
	FontBoldToggle();
 if ((theFonts[0].lfItalic != theFonts[index].lfItalic)||(theFonts[0].lfUnderline !=theFonts[index].lfUnderline))
 	FontItalicToggle();
 if (doColors && (DWORD)theColors[0] != (DWORD)theColors[index]) 
	SetColor("Reg", GetRValue(theColors[0]),GetBValue(theColors[0]),GetGValue(theColors[0]) );
}

void BeginBoldScoreHead(int index, char *name )
{
 if(doFonts && strcmpi(theFonts[0].lfFaceName, theFonts[index].lfFaceName) ) 
   FontName(theFonts[index].lfFaceName);
 if (theFonts[0].lfHeight!=theFonts[index].lfHeight)
    FontSize(theFonts[index].lfHeight); 
 if (theFonts[0].lfWeight < theFonts[index].lfWeight || theFonts[0].lfWeight > theFonts[index].lfWeight) 
	FontBoldToggle();
 if ((theFonts[0].lfItalic != theFonts[index].lfItalic)||(theFonts[0].lfUnderline !=theFonts[index].lfUnderline))
 	FontItalicToggle();
 if (doColors && (DWORD)theColors[0] != (DWORD)theColors[index]) 
	SetColor(name, GetRValue(theColors[index]),	GetBValue(theColors[index]),GetGValue(theColors[index]) );
}


void doSetTabs(int *tabs, int c)
{
int i;
  
ClearTabs();
for ( i = 0; i < c; i++ )
    AddTab(tabs[i]);
}


void doSwitch(FILE *stream)
{
 static char buf[10000];
 int tabs[20];
 int index=0;
 int rd = 0;
 do {
    rd = fgetc(stream); 
	if (rd != EOF) {
	   switch((unsigned char )rd) {
	   case _OPEN_ :
		   rd = fgetc(stream); 
		   buf[index++]=(char)0;
		   index = 0;
		   InsertText(buf);
		   InsertHardRet();
		   switch((unsigned char )rd) {
		   case _BOLDC_:
			   BeginBoldScoreHead(_BOLD_, "Bold" );
			   break;
		   case _HEADC_:
			   BeginBoldScoreHead(_HEAD_, "Head" );
			   break;
		   case _UITALC_:
			   BeginBoldScoreHead(_UITAL_, "UItal" );
			   break;
		   case _TAB_:
			   InsertTab;
			   break;
		   case _SET_:
			   rd = fgetc(stream); 
			   fread(tabs,2,rd,stream);
			   doSetTabs(tabs, rd);
			   break;
		   default:
			  break;
		   }
			 break;
	   case _CLOSE_ :
		   rd = fgetc(stream); 
		   buf[index++]=(char)0;
		   index = 0;
		   InsertText(buf);
		   switch((unsigned char )rd) {
		   case _BOLDC_:
			   EndBoldScoreHead(_BOLD_);
			   break;
		   case _HEADC_:
			   EndBoldScoreHead(_HEAD_);
			   break;
		   case _UITALC_:
			   EndBoldScoreHead(_UITAL_);
			   break;
		   default:
			  break;
		   }
		   break;
	   case '\n':
	   case (unsigned char )'\x80':
		   rd = fgetc(stream); 
		   buf[index++]=(char)0;
		   index = 0;
		   InsertText(buf);
		   break;
	   default:
		   buf[index++]=(char)rd;
		   break;
	      
	   }
	}   
  } while ( !feof(stream) && ! ferror(stream) );
}

void doImport()
{
 TCHAR szFile[MAX_PATH]      = "\0";	
 FILE *stream;
 
 if ((stream = GetTheFile(szFile))!=NULL) {
	InitializeData(stream);
	doSwitch(stream);
	fclose(stream);
 	}

}