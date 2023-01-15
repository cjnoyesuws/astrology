#include "batch.hpp"

void eat_line( FILE *stream )
{
 while ( fgetc( stream ) != '\n' );
 return;
}


int blnicmp( const void *p1, const void *p2 )
{
 int l1 = strlen(p1), l2 = strlen(p2), l;

 if ( l1 > l2 )
    l = l2;
 else
    l = l1;
 return( strnicmp( (char *)p1, (char *)p2, l ) );
}


int do_batch_line( FILE *stream )
{
 static char BCS msg[] = {"Illegal Command: %s!" };
 CMD *cmdf;
 int n;
 char buf[25], erbuf[50];
 ArgType arg;
 zEvent e;

 fscanf( stream, "%s", buf );
 n = NCMD;
 cmdf =(struct CMD *) bsearch( buf, cmds, n, sizeof( struct CMD ), blnicmp );
 if ( cmdf == NULL ) {
    sprintf( erbuf, (char _far *)msg, buf );
    alert_box( ERROR2, erbuf );
    eat_line( stream );
    return( 1 );
    }
 else if ( cmdf->proc != NULL ) {
    return( return( cmdf->proc( stream, cmdf ) );
    }
 if ( cmdf->hasArg() )
    arg.read(stream);
 else
    arg.set("");
 if ( cmdf->cmd != NULL ) {
    cmdf->cmd( &arg, cmdf );
    }
 if ( cmdf->setup != NULL )
    cmdf->setup( &arg, cmdf, &e );
 if ( cmdf->exec != NULL ) {
    switch( cmdf->list ) {
       case _MAIN_ :
	    return( app->rootWindow()->*(cmdf->exec)( (zCommandEvt *) &e ) );
	    break;
       case _TEXT_ :
	    return( pTextFrame->*(cmdf->exec)( (zCommandEvt *) &e ) );
	    break;
       case _GRAP_ :
	    return( pGraphFrame->*(cmdf->exec)( (zCommandEvt *) &e ) );
	    break;
       default:
	    break;
       }
 return( 0 );
}

int do_batch_line( char *rdbuf )
{
 static char BCS msg[] = {"Illegal Command: %s!" };
 CMD *cmdf;
 int n;
 char buf[25], erbuf[50];
 char *p;
 ArgType arg;
 zEvent e;

 p = strchr( rdbuf, ' ' );
 if ( p != NULL ) {
    *p = '\0';
    strcpy( buf, rdbuf );
    rdbuf = p+1;
    }
 n = NCMD;
 cmdf =(struct CMD *) bsearch( buf, cmds, n, sizeof( struct CMD ), blnicmp );
 if ( cmdf == NULL ) {
    sprintf( erbuf, (char _far *)msg, buf );
    alert_box( ERROR2, erbuf );
    return( 1 );
    }
 if ( cmdf->hasArg() )
    arg.read(rdbuf);
 else
    arg.set("");
 if ( cmdf->cmd != NULL ) {
    cmdf->cmd( &arg, cmdf );
    }
 if ( cmdf->setup != NULL )
    cmdf->setup( &arg, cmdf, &e );
 if ( cmdf->exec != NULL ) {
    switch( cmdf->list ) {
       case _MAIN_ :
	    return( app->rootWindow()->*(cmdf->exec)( (zCommandEvt *) &e ) );
	    break;
       case _TEXT_ :
	    return( pTextFrame->*(cmdf->exec)( (zCommandEvt *) &e ) );
	    break;
       case _GRAP_ :
	    return( pGraphFrame->*(cmdf->exec)( (zCommandEvt *) &e ) );
	    break;
       default:
	    break;
       }

 else if ( cmdf->proc == NULL && cmdf->exec != NULL ) {
    return( cmdf->exec() );
    }
 else if ( cmdf->proc != NULL )
    return( cmdf->proc( , cmdf ) );
 return( 0 );
}



int do_batch( char *batch_file )
{
 char buf[150];
 int c = 0, ret = 0;
 FILE *stream;

 if ( ( stream = _fsopen( batch_file, "rt", SH_DENYWR ) ) == NULL ) {
    do_error( batch_file );
    return( 1 );
    }
 do {
 c = fgetc( stream );
 switch( c ) {
       case '#' :  /* comment line */
	    fgets( buf, 149, stream );
	    break;
       case ' '  :
       case '\n' :
       case '\t' :
       case EOF  :
	    break;
       default :
	    ungetc( c, stream );
	    ret = do_batch_line( stream );
	    break;
       }
 } while ( !ret && c != EOF && !ferror( stream ) );
 if ( ferror( stream ) ) {
    do_error( batch_file );
    ret = 1;
    }
 else
    ret = 0;
 fclose( stream );
 return( ret );
}

