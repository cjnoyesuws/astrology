// testopen.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
    ShellExecute( NULL, "open", "http://www.cjnoyessw.com", NULL, NULL, SW_SHOW );
	return 0;
}



