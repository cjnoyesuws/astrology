#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "grpoped.hpp"
#include "errors.fns"
#include "basedcs.h"
#include "resstr.hpp"

extern int decompress( char *inbuf, char **outbuf, int in_size, int *out_size );
extern int centerDialog( zFrameWin *fw );
// zPercentSizer(ZGRAV_CENTER,33,33,pPar->sizer()

GrPopView::GrPopView(zFrameWin *pPar, char *file) :
	     zPopupFrame(pPar,new zSizer(150,150,325,200),zSTDFRAME,CResStr(_GRP_GRPOPED)/*"You Clicked On..."*/)
{
 strcpy( name, file );
 edit = new zEditBox(this,new zSizeWithParent,zSCROLLV|ES_WANTRETURN|ES_READONLY, "", 101 );
 edit->setStoreAddr(&buf);
 load();
 centerDialog(this);
 edit->show();
 deleteOnClose(TRUE);
}


int GrPopView::load()
{
 unsigned int len, nlen;
 FILE *stream;
 char *bf, *p;

 if ( (stream = fopen(name, "rb")) == NULL ) {
    do_error(name);
    return( 0 );
    }
 len = (int)filelength(fileno(stream));
 char *rb = new char[len+2];
 if (rb == NULL) {
    do_mem_error(0);
    fclose( stream );
    return( 0 );
    }
 if ( (len = fread(rb, 1, len, stream)) < len ) {
    do_error( name );
    fclose( stream );
    return( 0 );
    }
 nlen = len * 2;
 buf.reSize(nlen);
 bf = (char *)buf;
 decompress( rb, (char **)&bf, len, &nlen );
 delete rb;
 fclose( stream );
 edit->setToDefault();
 edit->hasChanged( 0 );
 return( 1 );
}


