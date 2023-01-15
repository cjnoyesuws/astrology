#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "fieldrng.hpp"
#include <stdlib.h>
#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )
#include "resstr.hpp"


int zNumFieldRng::checkData()
{
 char buf[100];
 zMessage *m;

 int v;

 v = atoi( text() );
 if ( v >= _low && v <= _hi )
    return( 1 );
 else {
    sprintf( buf, CResStr(_ERR_OUTOFRG)/*"Out of Range! Entry Must be within %d and %d"*/,
          _low, _hi  );
    m = new zMessage( this, buf, "Error!" );
    delete m;
    setFocus();
    return( 0 );
    }
}


