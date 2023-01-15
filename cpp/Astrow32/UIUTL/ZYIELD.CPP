#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")

extern HWND hMDIclient;
extern HWND activeDialog;
#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )

void zYield( int dp )
{
 MSG msg;

 if ( dp ) {
    if ( app->tasks()->busy() )
       app->tasks()->poll();
    }
 if ( PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) ) {
    GetMessage(&msg,NULL,0,0);
    if (msg.message==WM_QUIT)
       app->quit();
    if (activeDialog!=0) {
       if (IsWindow(activeDialog)) {
	  if (IsDialogMessage(activeDialog,&msg)) {
	     zYield(dp);
	     return;
	     }
	  }
       }
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    }
}

void zYield()
{
 zYield( 1 );
}

