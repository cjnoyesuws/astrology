// setdate.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <time.h>
#include <stdio.h>
#include <string.h>

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
    char dbuf[20], *pstr, rbuf[20];
	char pthbuf[200];
	int m, d, y;
	LONG lbuf;
	_strdate(dbuf);
	sscanf( dbuf, "%d/%d/%d", &m, &d, &y );
	sprintf( dbuf, "AsT%d$%d@%dRoW", d+100, y+1000, m+500 );
	HKEY hkSub;
	DWORD dwDisposition;
	pstr = lpCmdLine;
	strcpy( pthbuf, "Software\\Christopher J. Noyes Software" );
	if ( !strcmpi( pstr, "ASTROW" ) || !strlen(pstr) )
		strcat( pthbuf, "\\Astro For Windows\\");
	else if (!strcmpi(pstr,"NUMEROW") )
		strcat( pthbuf, "\\Numerow For Windows\\");
	else if ( !strcmpi(pstr, "BIO") )
		strcat( pthbuf, "\\Biorythms\\");
	strcat( pthbuf, "Shareware");
	RegOpenKey(HKEY_CURRENT_USER, pthbuf,&hkSub);
	if ( hkSub != NULL ) {
	  rbuf[0] = '\0';
	  RegQueryValue(hkSub,"Key", rbuf, &lbuf);
	  if ( !strlen(rbuf) ) {
	    RegSetValueEx(hkSub,"Key",0,REG_SZ,(const BYTE *)dbuf,strlen(dbuf));
	  }
	}
	else {
	   RegCreateKeyEx(HKEY_CURRENT_USER, pthbuf, 0, 0, 0,
              KEY_READ | KEY_WRITE, NULL, &hkSub, &dwDisposition);
	   RegSetValueEx(hkSub,"Key",0,REG_SZ,(const BYTE *)dbuf,strlen(dbuf));
	}
	RegCloseKey(hkSub);
	//WritePrivateProfileString( "Shareware", "Key", dbuf, "ASTROW.INI" );
	return 0;
}



