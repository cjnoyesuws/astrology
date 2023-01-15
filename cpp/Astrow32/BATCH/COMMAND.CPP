#include "batch.hpp"

int setup_command_arg(arg_type *ar, struct CMD *cm, zEvent *e)
{
 e->Msg = cm->cmd_base + ar->get();
 switch( cm->list ) {
       case _MAIN_ :
	     e->who = (HWND)*app->rootWindow();
	    break;
       case _TEXT_ :
	    e->who = (HWND)*pTextFrame;
	    break;
       case _GRAP_ :
	    e->who = (HWND)*pGraphFrame;
	    break;
       default:
	    break;
       }
 e->lParam=0;
}

int setup_command_nilarg(arg_type *ar, struct CMD *cm, zEvent *e)
{
 e->Msg = cm->cmd_base;
 switch( cm->list ) {
       case _MAIN_ :
	     e->who = (HWND)*app->rootWindow();
	    break;
       case _TEXT_ :
	    e->who = (HWND)*pTextFrame;
	    break;
       case _GRAP_ :
	    e->who = (HWND)*pGraphFrame;
	    break;
       default:
	    break;
       }
 e->lParam=0;
}


