#include "batch.hpp"
#include "inifile.hpp"

void ArgType::read( FILE *stream )
{
 char buf[300];

 fgets( buf, 299, stream );
 processVars(buf);
}


void ArgType::read( char *buf )
{
 processVars(buf);
}


void ArgType::processVars( char *buf )
{
 int vn;
 char c;
 char *p=buf, *v;

 if ( (v = strchr( buf, '%' ) ) == NULL ) {
    data = buf;
    }
 data = "";
 do {
    if ( *(v+1)='%' ) {
       v++;
       *v = '\0';
       data &= p;
       *v = '%';
       v++;
       }
    else {
       *v = '\0';
       data &= p;
       *v = '%';
       v++;
       if ( isalpha(*v)) {
	  c = toupper( *v );
	  vn = c - 'A';
	  }
       else
	  vn = atoi(v);
       if ( vn > 0 && vn < 10 ) {
	  data &= get(vn).get();
	  }
       else {
	  alert_box( ERROR, "Illegal Variable Number %d", vn );
	  return;
	  }
       v++;
       v++;
       }
    p = v;
    v = strchr( p, '%' );
    } while ( v != NULL );
  data &= p;
  if ( ( v = strchr( (char *)data, '%' ) != NULL ) {
     if ( *(v+2) == '%' ) {
	zString t = data;
	processVars( (char *)t );
	}
     }
}

Vars::saveToIni()
{
 char buf[10];

 for ( i = 0; i < 10; i++ ) {
     sprintf( buf, "Arg%d", i );
     WritePrivateProfileString( "BatchVars", buf, (char *)get(i).get(), 199, APPNAME );
     }
}

Vars::getFromIni()
{
 ArgType a;
 char buf[10];
 char buf2[200];

 for ( i = 0; i < 10; i++ ) {
     sprintf( buf, "Arg%d", i );
     GetPrivateProfileString( "BatchVars", buf, "", buf2, 199, APPNAME );
     a.read(buf2);
     set(i,a);
     }
}




