#include "scwin32.h"

extern char szAppName[];
extern ATOM aMyAppAtom, aAppAtom;
extern DTHETAID ASTROReport;
extern HWND		hAppLnkWnd;
extern HANDLE		hInst;
extern LPMAC_TOKEN	lpTknData;
extern LPMAC_RETURNVAL lpMacRetVal;
extern HINSTANCE 	hSCDll;

extern WPIDTHETACREATE lpfnWpidThetaCreate;
extern WPIDDYNATHETAADD lpfnWpidDynaThetaAdd;
extern WPIDDYNATHETALISTGETTEMPID lpfnWpidDynaThetaListGetTempID;
extern WPIDTHETADESTROY lpfnWpidThetaDestroy;
extern W6WZTOAZ lpfnW6wzToaz;
extern W6AZTOWZ lpfnW6azTowz;
extern WPIDMENUITEMINSERT lpfnWpidMenuItemInsert; 
extern WPIDMENUITEMAPPEND lpfnWpidMenuItemAppend;
extern WPIDMENUCREATEPOPUP lpfnWpidMenuCreatePopup;
extern WWSTRLEN lpfnwwstrlen;



#define BUF_SIZE		40
#define MAX_TEXT_LEN	50

typedef LPVOID PARAMETER;


/* Standard WOAPI functions */
void FAR PASCAL InitTkn (WORD nParmCount);
void FAR PASCAL AddTknParm (WORD cParmNum, MAC_VALUE_TYPE eType, 
								WORD wFlags, PARAMETER Param);
DWORD FAR PASCAL SendTkn (MAC_TOKENID wTknID);
void  FAR PASCAL FreeTkn();

DTHETAID FAR PASCAL CreateTheta (LPSTR szThetaName,	ATOM aAtomApp,
								LPSTR szMenuTxt, LPSTR szBBarTxt,
								LPSTR szPromptTxt, LPSTR szBitmap,
								WORD wpMenuGroup, BOOL bOverwrite);
LPVOID FAR PASCAL AllocPtr (int nSize, WORD wFlags);
void FAR PASCAL FreePtr (LPVOID lpvPtr);
BOOL FAR PASCAL SetSharedCodeFuncPtrs();
VOID FAR PASCAL FreeSharedCode();

typedef struct FONT {
      char   lfFaceName[40];
      short  lfHeight;
      short  lfWeight;
      short  lfItalic;
      short  lfUnderline;
      unsigned short  lfPitchAndFamily;
      } FONT;

extern FONT thefonts[];
extern COLORREF theColors[];
extern int doColors, doFonts;


extern void InsertText( char *text );
extern void InsertHardRet();
extern void FontName(char *family );
extern void FontSize( int size );
extern void FontItalicToggle();
extern void FontBoldToggle();
extern void InsertTab();
extern void ClearTabs();
extern void AddTab(int tabval );
extern void JustLeft();
extern void JustCenter();
extern void SetColor( char *color, short r, short b, short g );
extern void doImport();

#define _REG_		0
#define _HEAD_		1
#define _BOLD_		2
#define _UITAL_		3

#define _OPEN_		'{'
#define _CLOSE_		'}'
#define _HEADC_		'H'
#define _BOLDC_		'B'
#define _UITALC_    'U'
#define _TAB_		'T'
#define _SET_       'S'

