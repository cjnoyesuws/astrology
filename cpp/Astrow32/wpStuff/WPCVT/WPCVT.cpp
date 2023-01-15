#include <windows.h>
#include <malloc.h>
#include "scwin32.h"
#include "sctypes.h"
#include "wpwp7us.h"
#include "WPCVT.h"		   

#define DLLEXPORT __declspec( dllexport) 

char szAppName[] = "WPCVT";
ATOM aMyAppAtom, aAppAtom;
DTHETAID ASTROReport;
HWND		hAppLnkWnd;
HANDLE		hInst;
LPMAC_TOKEN	lpTknData;
LPMAC_RETURNVAL lpMacRetVal;
HINSTANCE 	hSCDll;

/* Global declarations of function types */
WPIDTHETACREATE lpfnWpidThetaCreate;
WPIDDYNATHETAADD lpfnWpidDynaThetaAdd;
WPIDDYNATHETALISTGETTEMPID lpfnWpidDynaThetaListGetTempID;
WPIDTHETADESTROY lpfnWpidThetaDestroy;
W6WZTOAZ lpfnW6wzToaz;
W6AZTOWZ lpfnW6azTowz;
WPIDMENUITEMINSERT lpfnWpidMenuItemInsert; 
WPIDMENUITEMAPPEND lpfnWpidMenuItemAppend;
WPIDMENUCREATEPOPUP lpfnWpidMenuCreatePopup;
WWSTRLEN lpfnwwstrlen;


/* Add functions for menus and buttons */


/*FUNCTION***********************************************************
	;TPHVersion
	DESCRIPTION:  Allows a DLL to register its major and minor 
	version with Shared Code.
	
	IN:
	OUT:
	GLOBALS:  hInst - Instance handle obtained when DLL was loaded
	
	RETURNS:  Version - must be non-zero, otherwise it will fail
********************************************************************/
DLLEXPORT DWORD FAR PASCAL TPHVersion (VOID)
{
	return MAKELONG (1, hInst);
}/* End TPHVersion */

               




/*FUNCTION***********************************************************
	;TPHCompatibility
	DESCRIPTION:  Check which application and shared code version 
	has loaded the DLL.
	
	IN:       	AppName - The atom name of the calling application
				AppVersion - Major (low byte) and Minor (high byte)
				version of shared code.
				
	OUT:      
	GLOBALS:  
	
	RETURNS:  TRUE - Load the DLL, otherwise FALSE
********************************************************************/
DLLEXPORT DWORD FAR PASCAL TPHCompatibility (ATOM AppName, WORD AppVersion)
{                          
	
	char szAppName [BUF_SIZE];

	GlobalGetAtomName (AppName, szAppName, BUF_SIZE-1);	
	aAppAtom = AppName;

	if( lstrcmpi(szAppName, "WordPerfect") ==0 )
	{
		ASTROReport=CreateTheta("ASTROReport", aAppAtom, "ASTRO Report", NULL, "Insert ASTRO or Numero Report", NULL, 0, TRUE);
		return 1;
	}
	else
    
	return (DWORD) TRUE;
}/* End TPHCompatibility */	
	



/*FUNCTION***********************************************************
	;TPHTimeStamp
	DESCRIPTION:  Allows the DLL to register its time stamp.  
	Currently not used by shared code.
	
	IN:		
	OUT:      
	GLOBALS:  
	
	RETURNS:  Must return 0
********************************************************************/
DLLEXPORT DWORD FAR PASCAL TPHTimeStamp (VOID)
{                                                                  
	return 0;
}/* End TPHTimeStamp */	     
	
	                                                              



/*FUNCTION***********************************************************
	;TPHEntry
	DESCRIPTION:  Allows the DLL to do any intitialization, prior to
	the application sending any PerfectScript command's to the DLL.  
	
	IN:		wLanguage - Language of the application.  i,e, "US" - 
			low byte: "U", high byte: "S"
	OUT:      
	GLOBALS:   	hRequester - DLL requester atom.
				szAppName - DLL Identifier
					
	RETURNS:  Must return 1
********************************************************************/
DLLEXPORT WORD FAR PASCAL TPHEntry (WORD wLanguage)
{   

	aMyAppAtom = GlobalAddAtom (szAppName);      
	lpMacRetVal= NULL;

	return 1;
}/* End TPHEntry */




/*FUNCTION***********************************************************
	;TPHExit
	DESCRIPTION:  Allows the DLL to do any de-intitialization, prior to
	the DLL being unloaded from memory.
	
	IN:	
	OUT:      
	GLOBALS:   	hRequester - DLL requester atom.
					
	RETURNS:  Must return 1
*******************************************************************/
DLLEXPORT WORD FAR PASCAL TPHExit (VOID) 
{
	GlobalDeleteAtom (aMyAppAtom);
	return 1;
}/* End TPHExit */	




/*FUNCTION***********************************************************
	;TPHHandleTokenValReturn
	DESCRIPTION:  Used to manage PerfectScript commands sent by a 
	Perfect Office application.
	
	IN:			lpRetData - PerfectScript command information sent by the 
				application.
				hLink - The applications window handle.  This handle
				is used to send new PerfectScript commands back to the application.
				msg - The type of message sent.  This is currently only
				WPLM_EXECUTE_TOKEN.
	OUT:      
					
	RETURNS:  See return values documented in WOAPI
********************************************************************/




DLLEXPORT int FAR PASCAL TPHHandleTokenValReturn (LPTPH_RETURNVAL 	lpRetData,
								HWND		hLinkWnd,
								WORD		msg)
{
	WMEMOBJECT MenuHandle;
	WPBBAR_THIRDPARTY TBarInfo;
	char szBuf[32];
	LPWZ lpwzBuf;

	hAppLnkWnd = hLinkWnd;
	if( lpRetData->lpTokenData->wTokenID  == MENULOAD_TKN)
	{
		MenuHandle =(WMEMOBJECT) lpRetData->lpTokenData->DataBlock[0].uData.dwValue;
		lpfnWpidMenuItemAppend (MenuHandle, WP_ToolsMenu, 0, ASTROReport, 0, NULL, 0);
	
	}

	if( lpRetData->lpTokenData->wTokenID  == ASTROReport)
	{
		/*Enter the code that will be called when your menu or button is selected*/
		doImport();
	}


	return DLL_HAN_NOT_HANDLED;
}/* End TPHHandleToken */
		
		

/*FUNCTION***********************************************************
	;TPHValidateToken
	DESCRIPTION:  Used to validate menu items
	
	IN:			lpTokenData - Command information, i.e., ID, Parameters
				lpDataType - Pointer to the TPValInfo structure.
	OUT:      
	GLOBALS:   	
		
	RETURNS:  See return values documented in WOAPI
********************************************************************/
DLLEXPORT DWORD FAR PASCAL TPHValidateToken (LPMAC_TOKEN lpTokenData, LPVOID lpDataType)
{   

/*	If creating your own menu items, validate them using the commented code below. */


	if (lpTokenData->wTokenID == ASTROReport) 			
	   return (DWORD)DLL_VAL_VALIDATED|MT_MENU_ITEM_ENABLED;
	else
	   return DLL_VAL_UNKNOWN_TOKEN;

 return DLL_VAL_UNKNOWN_TOKEN;
}/* End TPHValidateToken */                               
	
	


/*FUNCTION***********************************************************
	;InitTkn
	DESCRIPTION:  Used to send a PerfectScript command back to a 
	PerfectOffice Application. This function is used in conjunction 
	with AddTknParm() and SendTkn().
	
	NOTE:  You must call FreeTkn for each command sent using SendTkn;

	IN:	        nParmCount - Number of parameters for the command.
	OUT:      
	GLOBALS:   	lpTknData - long pointer to the PerfectScript command 
	structure.
********************************************************************/
void FAR PASCAL InitTkn (WORD nParmCount)
{	
	
	if (!(lpTknData = (LPMAC_TOKEN)AllocPtr (sizeof (MAC_TOKEN) + 
						(sizeof (MAC_PARAM) * 
							(nParmCount)), GHND)))
	{
		lpTknData = (LPMAC_TOKEN)NULL;
	}
	lpTknData->cParam = nParmCount;
}/* End InitTkn */ 
	




/*FUNCTION***********************************************************
	;AddTknParm
	DESCRIPTION:  Used to add parameters to the currently allocated 
	PerfectScript Command.  Must be called for each parameter used 
	for the command's definition.  InitTkn must be called prior to 
	using this function.  This function is used in conjunction with 
	InitTkn() and SendTkn() to create PerfectScript commands to send 
	back to the Perfect Office application.
	
	IN:	        cParmNum - Number of Parameters used by the command.
				eType - Parameter Type (See PerfectScript command definition 
						in the appname.TXT file, and the WOAPI, Structure and
						Types documentation.
				wFlags - 	0x0000: Use parameter
							0x8000: Application should ignore parameter 
				Param -  	BOOL, BYTE, int, long, WORD, DWORD, float, 
							or double literal, or long pointer to a string.
	OUT:      
	GLOBALS:   	lpTknData - long pointer to the command structure
					
	RETURNS:  
********************************************************************/
void FAR PASCAL AddTknParm (WORD cParmNum, MAC_VALUE_TYPE eType,
							WORD wFlags, PARAMETER Param)
{
	LPVOID lpParam;
	int iLen;

	lpTknData->DataBlock[cParmNum].eType = eType;
	lpTknData->DataBlock[cParmNum].wFlags = wFlags;
			
	switch(eType)
	{
		case eParmStringWord: 
		case eParmStringVariable:
			if(Param == NULL)
			   lpTknData->DataBlock[cParmNum].uData.lpvPtr = Param;
			else
			{
				iLen= lpfnwwstrlen((FPWUBYTE)Param)*2;
				lpParam= AllocPtr(iLen, GHND);
				memcpy(lpParam, Param, iLen);
				lpTknData->DataBlock[cParmNum].uData.lpvPtr = lpParam;
			}
			break;
		
		case eParmWPFname:
		case eParmStringAnsi:
		case eParmStringLabel:
		case eParmStringOem:
			if(Param == NULL)
			   lpTknData->DataBlock[cParmNum].uData.lpvPtr = Param;
			else
			{
				iLen= lstrlen((LPSTR)Param) + 1;
				lpParam= AllocPtr(iLen, GHND);
				lstrcpy((LPSTR)lpParam, (LPSTR)Param);
				lpTknData->DataBlock[cParmNum].uData.lpvPtr = lpParam;
			}
			break;

		default:
			lpTknData->DataBlock[cParmNum].uData.lpvPtr = Param;
	}
}/* End AddTknParm */ 







/*FUNCTION***********************************************************
	;SendTkn
	DESCRIPTION:  Sends the PerfectScript command to the PerfectOffice
	application's link window.	This function is used in conjunction 
	with InitTkn() and AddTknParm().
	
	NOTE:  You must call FreeTkn for each command sent using SendTkn;

    IN:			wTknID - 	ID of the PerfectScript command (see 
							appname.TXT file for command IDs).
	OUT:      
	GLOBALS:   	lpTknData - long pointer to the command's structure
				lpMacRetVal - long pointer to the command's return information
				aAppAtom - PerfectOffice application's atom.
				hAppLnkWnd - PerfectOffice application's Link Window;
					
	RETURNS:    The result of the SendMessage call to the application.
********************************************************************/
DWORD FAR PASCAL SendTkn (MAC_TOKENID wTknID)
{
	TPH_RETURNVAL 	TknData;
	LPTPH_RETURNVAL lpTPHData;
	DWORD			dwRV;

	/* Fill out global PerfectScript command's structure */
	lpTknData->eCommand		= (MAC_CMD_TYPE)0;
	lpTknData->Version			= 0L;
	lpTknData->atomRequestor 	= aMyAppAtom;
	lpTknData->atomApp			= aAppAtom;
	lpTknData->dwMacroID		= 0L;
	lpTknData->wReserved		= 0;
	lpTknData->wTokenID 		= wTknID;
	lpTknData->dwFlags			= 0L;
	lpTknData->dwReserved		= 0L;
		
	
	/*File out ReturnVal Structure */
	TknData.lpTokenData = lpTknData;
	TknData.lplpmacRetVal =  &lpMacRetVal;

	lpTPHData = &TknData;
	dwRV = SendMessage (hAppLnkWnd, WPLM_EXECUTE_TOKEN, 0, (LPARAM)lpTPHData);

	return dwRV;
}/* End SendTkn */ 




/*FUNCTION***********************************************************
	;FreeTkn
	DESCRIPTION:  Sends a message back to the PerfectOffice application 
	informing it to free the command's return information it allocated 
	when SendTkn() was called.
	
	IN:
	OUT:      
	GLOBALS:   	lpMacRetVal - Return value for the command.
					
	RETURNS:    Pointer to the memory, otherwise NULL.
********************************************************************/
void FAR PASCAL FreeTkn()
{
	int i;

	for(i= 0; i < (int)lpTknData->cParam; i++)
	{
		switch(lpTknData->DataBlock[i].eType)
		{
			case eParmStringWord: 
			case eParmStringVariable:
			case eParmWPFname:
			case eParmStringAnsi:
			case eParmStringLabel:
			case eParmStringOem:
				if(lpTknData->DataBlock[i].uData.lpvPtr != NULL)
					FreePtr(lpTknData->DataBlock[i].uData.lpvPtr);
				break;
		}
	}
	
	SendMessage(hAppLnkWnd, WPLM_FREE_MEM, 0, (LPARAM)lpMacRetVal);
	FreePtr (lpTknData);
	lpMacRetVal= NULL;
}/* End FreeTkn */


/*FUNCTION***********************************************************
	;AllocPtr
	DESCRIPTION:  Allocate global memory and return the pointer.
	
	IN:	        nSize - Size to allocate
				wFlags - Allocation flags.
	OUT:      
	GLOBALS:   	
					
	RETURNS:    Pointer to the memory, otherwise NULL.
********************************************************************/
LPVOID FAR PASCAL AllocPtr (int nSize, WORD wFlags)
{
	HGLOBAL hMem;
	LPVOID lpvPtr;
	
	if ((hMem = GlobalAlloc (wFlags, nSize)) != NULL)
	{
		if ((lpvPtr = GlobalLock (hMem)) != NULL)
		{
			return lpvPtr;
		}
		else
		{
			GlobalFree (hMem);
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}/* End AllocPtr */ 





/*FUNCTION***********************************************************
	;FreePtr
	DESCRIPTION:  Free the memory allocated previously by AllocPtr.
	
	IN:	        lpvPtr - Pointer to the memory
	OUT:      
	GLOBALS:   	
					
	RETURNS:    
********************************************************************/
void FAR PASCAL FreePtr (LPVOID lpvPtr)
{          
	HGLOBAL hMem;

	
	if (( hMem = GlobalHandle((LPCVOID)lpvPtr)) != NULL)
	{
		if (!(GlobalUnlock (hMem)))
		{
			GlobalFree (hMem);
		}
	}

}/* End FreePtr */ 






/*FUNCTION***********************************************************
	;CreateTheta
	DESCRIPTION:  Creates a dynatheta with the given paramters.  
	This function is provided for those developers wanting to create
	menu items in an application. This function only created the 
	menu information, it does not add it to the menu.  To add it to
	a menu: 
	1)  Watch and trap the menu command being sent by the application in
	the TPHHandleTokenValReturn function
	2)  Use the menu theta ID returned by this function and one 
	of Shared Code's Menu functions to add the menu item.  See the
	Menus chapter in the Shared code manual.
	3)  Return DLL_HAN_NOT_HANDLED in the TPHHandleTokenValReturn function
	
	IN:	        szThetaName - DynaTheta unique name
				aAtomApp - 	Application's atom Name from Compatability()
							function. 
				szMenuTxt - Text for the menu item.
				szBBarTxt - Button Text.
				szPromptTxt - Prompt Text. 
				hBitmap - Handle of button bitmap.  Can be set to NULL.
				wpMenuGroup - Menu Group only applies to users who will
						be manually adding you menu item.  These groups
						start at 0 for File, and go on up.
				bOverwrite - FALSE, will not create the Dynatheta if it
				             already exists.  True, always recreate theta.
				
	OUT:      
	GLOBALS:   	
					
	RETURNS:    The ID for the new theta.
********************************************************************/
DTHETAID FAR PASCAL CreateTheta (LPSTR szThetaName,
								ATOM aAtomApp,
								LPSTR szMenuTxt,
								LPSTR szBBarTxt,
								LPSTR szPromptTxt,
								LPSTR szBitmap,
								WORD wpMenuGroup,
								BOOL bOverwrite)
{
	WZ	ThetaName[MAX_TEXT_LEN];
	WZ	ThetaMenuText[MAX_TEXT_LEN];
	WZ	ThetaBBarText[MAX_TEXT_LEN];
	WZ	ThetaPromptText[MAX_TEXT_LEN];
	DTHETAID dThetaID;
	WMEMOBJECT wmoDynaTheta;
	HBITMAP hBitmap;
	hBitmap = 0;

	
	lpfnW6azTowz((unsigned char *)szThetaName, (unsigned short *)ThetaName);

	/* check to see if theta exists */
	if(!bOverwrite)
	{
		dThetaID = lpfnWpidDynaThetaListGetTempID (aAtomApp, ThetaName);

		if (PID_ISDYNATHETA(dThetaID))
		{
			return dThetaID;
		}
	}

	/* Create new dynatheta */
	else
	{
		if (szMenuTxt != NULL)
		{
			lpfnW6azTowz ((LPAZ)szMenuTxt, (LPWZ)ThetaMenuText);
		}
		if (szBBarTxt != NULL)
		{
			lpfnW6azTowz ((LPAZ)szBBarTxt, (LPWZ)ThetaBBarText);
		}
		if (szPromptTxt != NULL)
		{
			lpfnW6azTowz ((LPAZ)szPromptTxt, (LPWZ)ThetaPromptText);
		}
		if (szBitmap != NULL)
		{
			hBitmap = LoadBitmap(hInst, szBitmap);
		}

		
		/* Create dynatheta */
		if (!(wmoDynaTheta = lpfnWpidThetaCreate ((LPWZ)ThetaName,
					(WORD)0, (WORD)0, ThetaMenuText, ThetaBBarText,
					ThetaPromptText, 0, 0, wpMenuGroup, hBitmap,
					0, NULL, 0, NULL, 0)))
		{
			return DTHETAID_NULL;
		}

		lpfnWpidDynaThetaAdd (aAtomApp, wmoDynaTheta);

		if ((dThetaID = lpfnWpidDynaThetaListGetTempID (aAtomApp, ThetaName)) == DTHETAID_NULL)
		{
			return DTHETAID_NULL;
		}

		lpfnWpidThetaDestroy (wmoDynaTheta);
		
		return dThetaID;
	}

return DTHETAID_NULL;
}/* End CreateTheta */

/*FUNCTION***********************************************************
	;SetSharedCodeFuncPtrs
	DESCRIPTION:  Loads shared code DLLs, and gets the addresses of the
	functions used in this WOAPI template file.	 This function is used
	with FreeSharedCode().
	
	IN:	        
	OUT:      
	GLOBALS:   	Shared Code Dll handles.
				Function pointers.
					
	RETURNS:  TRUE, if shared code was successfully loaded, otherwise FALSE
********************************************************************/
BOOL FAR PASCAL SetSharedCodeFuncPtrs()
{
	hSCDll = LoadLibrary("shwin70.dll");
	if( hSCDll != NULL )
	{
		lpfnWpidThetaCreate = (WPIDTHETACREATE)GetProcAddress(hSCDll, "WpidThetaCreate");
		lpfnWpidDynaThetaAdd = (WPIDDYNATHETAADD)GetProcAddress(hSCDll, "WpidDynaThetaAdd");
		lpfnWpidDynaThetaListGetTempID = (WPIDDYNATHETALISTGETTEMPID)GetProcAddress(hSCDll, "WpidDynaThetaListGetTempID");
		lpfnWpidThetaDestroy = (WPIDTHETADESTROY)GetProcAddress(hSCDll, "WpidThetaDestroy");
		lpfnWpidMenuItemInsert = (WPIDMENUITEMINSERT)GetProcAddress(hSCDll, "WpidMenuItemInsert");
		lpfnWpidMenuItemAppend = (WPIDMENUITEMAPPEND)GetProcAddress(hSCDll, "WpidMenuItemAppend");
		lpfnWpidMenuCreatePopup = (WPIDMENUCREATEPOPUP)GetProcAddress(hSCDll, "WpidMenuCreatePopup");
		lpfnW6wzToaz = (W6WZTOAZ)GetProcAddress(hSCDll, "W6wzToaz");
		lpfnW6azTowz = (W6AZTOWZ)GetProcAddress(hSCDll, "W6azTowz");
		lpfnwwstrlen = (WWSTRLEN)GetProcAddress(hSCDll, "wwstrlen");

		if((lpfnWpidThetaCreate == NULL) ||
			(lpfnWpidDynaThetaAdd  == NULL) ||
			(lpfnWpidDynaThetaListGetTempID  == NULL) ||
			(lpfnWpidThetaDestroy  == NULL) ||
			(lpfnWpidMenuItemInsert  == NULL) ||
			(lpfnWpidMenuItemAppend  == NULL) ||
			(lpfnWpidMenuCreatePopup  == NULL) ||
			(lpfnW6wzToaz  == NULL) ||
			(lpfnW6azTowz  == NULL) || 
			(lpfnwwstrlen == NULL))
		{
			return FALSE;
		}		
	}
	else
	{
		return FALSE;
	}


	return TRUE;
}/* End SetSharedCodeFuncPtrs */


/*FUNCTION***********************************************************
	;FreeSharedCode
	DESCRIPTION:  Frees shared code DLL handles loaded by the
	SetSharedCodeFuncPtrs() function.
	
	IN:	        
	OUT:      
	GLOBALS:   	Shared Code Dll handles.
					
	RETURNS:  
********************************************************************/
VOID FAR PASCAL FreeSharedCode()
{
	
	if( hSCDll != NULL )
		FreeLibrary(hSCDll);
}/* End FreeSharedCode */


/*FUNCTION***********************************************************
	Initialization Function - required
	Called by Windows
********************************************************************/
DLLEXPORT BOOL WINAPI DllMain (
				HINSTANCE 		hInstance,
				DWORD			fdwReason,
				LPVOID			lpReserved )
{
	
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
			//------------------------------------------------------------
			// during process attach, determine if this is the first instance
			// of this dll.  If it is, set up shared memory to be used to
			// communicate with other instances of the dll.  Set up TLS memory.
			// This process is left as an exercise for the dll writer.
			//------------------------------------------------------------
			
			//------------------------------------------------------------
			// Save the instance handle for use later.
			hInst = hInstance;
			
			if(!SetSharedCodeFuncPtrs())
			{
				return FALSE;
			}
			break;

		case DLL_PROCESS_DETACH:
			//------------------------------------------------------------
			// Do any cleaning up that needs to done before going down.

			FreeSharedCode();
			break;

		case DLL_THREAD_ATTACH:
			//------------------------------------------------------------
			// during thread attach, determine if this is the first instance
			// of this dll.  If it is, set up shared memory to be used to
			// communicate with other instances of the dll.  Set up TLS memory.
			// This process is left as an exercise for the dll writer.
			break;

		case DLL_THREAD_DETACH:
			//------------------------------------------------------------
			// Do any cleaning up that needs to done before going down.
			break;

	} //switch

	return TRUE;
} // end DllMain


