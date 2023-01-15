// reg.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <string.h>
#include <stdio.h>

char urlbuf[512];
char goodchars[]={"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890@.*_-"};

char * encode( char *src )
{
static char buf[100];
 char *d=buf, *s=src;

while ( *s != '\0' )
{
	if ( *s==' ' ) {
		*d++ = '+';
		s++;
	}
    else if ( strchr(goodchars,*s) != NULL )
		*d++ = *s++;
	else {
		sprintf( d, "%%%02x", (int) *s++ );
		d+= 3;	
	}

}
*d++='\0';
return( buf );

}

/*
[Reg]
Name=%NAME%
Reg=%REG%
Company=%COMPANY%
Email=%EMAIL%
Version=%VERSION%


  */


void buildurl(LPSTR cmdline)
{
 char buf[80], buf2[40], buf3[40], buf4[40], buf5[40];

 sscanf(cmdline, "N=\"%39[^\"]\" O=\"%39[^\"]\" E=\"%39[^\"]\" V=\"%39[^\"]\"", buf2, buf3, buf4, buf5 );
 strcpy( urlbuf, "http://www.cjnoyessw.com/reg.php?NAME=" );
 //GetPrivateProfileString( "Reg", "Name", "", buf, 79, "Astrow.ini" );
 strcat( urlbuf, encode(buf2) );
 strcat( urlbuf, "&COMPANY=" );
 //GetPrivateProfileString( "Reg", "Company", "", buf, 79, "Astrow.ini" );
 strcat( urlbuf, encode(buf3) );
 strcat( urlbuf, "&EMAIL=" );
 //GetPrivateProfileString( "Reg", "Email", "", buf, 79, "Astrow.ini" );
 strcat( urlbuf, encode(buf4) );
 strcat( urlbuf, "&REG=" );
 //GetPrivateProfileString( "Reg", "Reg", "", buf, 79, "Astrow.ini" );
 strcat( urlbuf, encode(buf5) );
 strcat( urlbuf, "&VERSION=" );
 //GetPrivateProfileString( "Reg", "Version", "", buf, 79, "Astrow.ini" );
 strcat( urlbuf, encode("2.25") );
 
}



int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
    buildurl(lpCmdLine);
	ShellExecute( NULL, "open", urlbuf, NULL, NULL, SW_SHOW );
	return 0;
}



