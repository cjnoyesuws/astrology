#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#include "paths.hpp"
#include "charcons.h"
#include "tbtframe.hpp"
#include "resource.h"

int TbtAppFrame::windCmd(zCommandEvt* Ev) {
	switch ((unsigned int)Ev->cmd()) {
	case ID_WINDOWS_ARRANGE:
		arrangeIcons();
		break;
	case ID_WINDOWS_CASCADE:
		cascade();
		break;
	case ID_WINDOWS_TILE:
		tile();
		break;
	case ID_FILES_EXIT:
	     kill((zEvent *)Ev);
	     app->quit();
	     break;
	default:
		return 0;
	}
 return 1;
}
