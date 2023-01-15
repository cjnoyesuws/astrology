//
//	Copyright (c) 1991, 1993 Inmark Development Corp.
//	All rights reserved.
//
#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )

#include "zapp.hpp"
#include "resource.h"
#include "tbtutil.h"

typedef struct TEST {
   int argc;
   zString func;
   zString p1;
   zString p2;
   zString p3;
   zString p4;
   zString p5;
   zString p6;
   zString p7;
   zString p8;
   } TEST;

class testApp : public zAppFrame {
	zTextPane* out;
public:
	testApp(char * title);
	virtual int command(zCommandEvt *);
	~testApp() { delete out; }
};

class testForm : public zFormDialog {
public:
	testForm(zWindow *, TEST *);
};

TEST data;

testForm::testForm(zWindow *p, TEST *t) : zFormDialog(p, zResId(IDD_DIALOG1)) {
	new zStringEdit(this, IDC_EDIT1, &t->func, "X(20)");
	new zStringEdit(this, IDC_EDIT2, &t->p1, "X(75)", FLD_NOTREQUIRED);
	new zStringEdit(this, IDC_EDIT3, &t->p2, "X(75)", FLD_NOTREQUIRED);
	new zStringEdit(this, IDC_EDIT4, &t->p3, "X(75)", FLD_NOTREQUIRED);
	new zStringEdit(this, IDC_EDIT5, &t->p4, "X(75)", FLD_NOTREQUIRED);
	new zStringEdit(this, IDC_EDIT6, &t->p5, "X(75)", FLD_NOTREQUIRED);
	new zStringEdit(this, IDC_EDIT7, &t->p6, "X(75)", FLD_NOTREQUIRED);
	new zStringEdit(this, IDC_EDIT8, &t->p7, "X(75)", FLD_NOTREQUIRED);
	new zStringEdit(this, IDC_EDIT9, &t->p8, "X(75)", FLD_NOTREQUIRED);
	show();
	modal();
}


void _pascal _export _loadds zYield( int i )
{
}


int _pascal _export _loadds logFunc( LPVOID data, LPCSTR text )
{
 zTextPane *p = (zTextPane *)data;
 if ( data = NULL )
    return( 0 );
 p->put((char *)text);
 zYield(1);
 zYield(1);
 return( 1 );
}


testApp::testApp(char * title):zAppFrame(0,new zSizer,zSTDFRAME,title) {
	out = new zTextPane(this,new zSizeWithParent);
	out->show();
	menu(new zMenu(this));
	menu()->addStr(ID_TEST, "&Test");
	menu()->update();
}

testApp::command(zCommandEvt *e) {
	if (e->cmd() == ID_TEST) {
		testForm* form = new testForm(this, &data );
		SetupLog(out);
		SetupLogProc((LOGPROC)logFunc);
		SetYieldProc((YIELDPROC)zYield);
		/*hLib = LoadLibrary("TBTCVTUT.DLL");
		setHinstance( hLib ); */
		if (form->completed()){
		   if ( data.p8.length() == 0 )
		      data.argc = 7;
		   if ( data.p7.length() == 0 )
		      data.argc = 6;
		   if ( data.p6.length() == 0 )
		      data.argc = 5;
		   if ( data.p5.length() == 0 )
		      data.argc = 4;
		   if ( data.p4.length() == 0 )
		      data.argc = 3;
		   if ( data.p3.length() == 0 )
		      data.argc = 2;
		   if ( data.p2.length() == 0 )
		      data.argc = 1;
		   if ( data.p1.length() == 0 )
		      data.argc = 0;
		   switch( data.argc ) {
		      case 0 :
			   execFunction( data.func, data.func );
			   break;
		      case 1 :
			   execFunction( data.func, data.func, data.p1 );
			   break;
		      case 2 :
			   execFunction( data.func, data.func, data.p1, data.p2 );
			   break;
		      case 3 :
			   execFunction( data.func, data.func, data.p1, data.p2, data.p3 );
			   break;
		      case 4 :
			   execFunction( data.func, data.func, data.p1, data.p2,
				   data.p3, data.p4 );
			   break;
		      case 5 :
			   execFunction( data.func, data.func, data.p1, data.p2,
				   data.p3, data.p4, data.p5 );
			   break;
		      case 6 :
			   execFunction( data.func, data.func, data.p1, data.p2,
				   data.p3, data.p4, data.p5, data.p6 );
			   break;
			   case 7 :
			   execFunction( data.func, data.func, data.p1, data.p2,
				   data.p3, data.p4, data.p5, data.p6, data.p7 );
			   break;
			   case 8 :
			   execFunction( data.func, data.func, data.p1, data.p2,
				   data.p3, data.p4, data.p5, data.p6, data.p7, data.p8 );
			   break;
		      default :
			   break;
		      }
		/* FreeLibrary(hLib); */
		out->printf( "\n\nFunction Returns %d\n\n", getFunctionRet() );
		} else out->printf("\n\nForm not completed.\n");
		delete form;
	}
	return 1;
}

void zApp::main() {
	testApp *p=new testApp("TBT Dll Tester");
	p->show();
	go();
	delete p;
}
