#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include "charcons.h"
#include "astro.h"
#include "useri.h"
#include "errors.fns"
#include "paths.hpp"
#include "coverdat.hpp"
#include "inifile.hpp"


#define CVPGID "CPG1WPRO2"

/* save the structure to a file */

int CoverPageData::save( char *fName, int fld )
{
 static char  fmt1[] = "%s\n%d, %d, \"%s\"\n";
 static char  fmt2[] = "%s\n%s\n%s\n";
 char buf[100];
 FILE *stream;

 if ( strrchr( fName, '\\' ) == NULL )
    strcpy( buf, set_path( fName, fld ) );
 else
    strcpy( buf, fName );
 if ( ( stream = fopen( buf, "wt" ) ) == NULL ) {
    do_error( buf );
    return( 0 );
    }
 AfxGetApp()->WriteProfileString( Cover_SEC, "Astrologer", astName );
 fprintf( stream, fmt1, CVPGID, image, font, file );
 fprintf( stream, fmt2, title, 	name, comments );
 fclose( stream );
 return( 1 );
}

/* Load the structure from a file */

int CoverPageData::load( char *fName, int fld )
{
 char dummy;
 CString b;
 char buf[350];
 FILE *stream;
 static char fmt1[] = "%d, %d, \"%149[^\"]\"";
// static char BCS er1[] = ;

 if ( strrchr( fName, '\\' ) == NULL )
    strcpy( buf, set_path( fName, fld ) );
 else
    strcpy( buf, fName );
 if ( ( stream = fopen( buf, "rt" ) ) == NULL ) {
    do_error( buf );
    ok = 0;
    return( 0 );
    }
 fscanf( stream, "%s", buf );
 if ( strcmp( buf, CVPGID ) ) {
    alert_box( ERROR1, "Not a Cover Page File!"  );
    fclose( stream );
    ok = 0;
    return( 0 );
    }
 buf[0] = '\0';
 astName = AfxGetApp()->GetProfileString( Cover_SEC, "Astrologer", "" );
 fscanf( stream, fmt1, &image, &font, buf );
 dummy = fgetc(stream);
 if ( dummy == '\"' )
    fgetc(stream);
 file = buf;
 buf[0] = '\0';
 fgets( buf, 149, stream );
 buf[strlen(buf)-1] = '\0';
 title = buf;
 buf[0] = '\0';
 fgets( buf, 149, stream );
 buf[strlen(buf)-1] = '\0';
 name = buf;
 comments = "";
 do {		
    buf[0] = '\0';
    if ( fgets( buf, 349, stream ) != NULL )
       comments += buf;
    } while ( !feof( stream ) );
 if ( comments[comments.GetLength()-1] == '\n' )
    comments.SetAt(comments.GetLength()-1,(TCHAR)'\0');
 
 fclose( stream );
 ok = 1;
 return( 1 );
}

/* fill the structure with default values */

int CoverPageData::create( XPFILE_DB *ptr )
{
 static char fmt1[] = "ASTRO %s REPORT";
 char buf[100];
 CString b;
 
 name = ptr->name;
 comments = ptr->comment;
 sprintf( buf, long_types[ptr->type] );
 strupr(buf);
 title = buf;
 b = AfxGetApp()->GetProfileString( Cover_SEC, "StdGraphic", "" );
 if ( b.GetLength() ) {
    image = USER_BMP;
    file = b;
    }
 else {
    image = AfxGetApp()->GetProfileInt( Cover_SEC, "defImage", 0 );
    font = AfxGetApp()->GetProfileInt( Cover_SEC, "defFont", 0 );
    image = 0;
    font = 0;
    file = "";
    }
 astName = AfxGetApp()->GetProfileString( Cover_SEC, "Astrologer", "" );
 ok = 1;
 return( 1 );
}

/* Creates an ASTRO format file for conversion to text */

CString *CoverPageData::toAstFile()
{
 char buf[250];
 FILE *stream;

 GetTempFileName( 0, "ASTW", 0, buf );
 tempName = buf;   
 if ( ( stream = fopen( tempName, "wt" ) ) == NULL ) {
    do_error( (char *)(LPCTSTR)tempName );
    return( NULL );
    }
 fprintf( stream, "\n\n\n[%s]\n\n", title );
 fprintf( stream, "Name: {%s}\n\n", name );
 fprintf( stream, "Comments: %s\n\n\n", comments );
 fprintf( stream, "Astrologer: {%s}\n\n\n", astName );
 fprintf( stream, "Produced by \x80""ASTRO--The Program For Astrological Analysis\x80" );
 fprintf( stream, "(C) 1986-1999 by Christopher J. Noyes\n\n" );
 fclose( stream );
 return( &tempName );
}


/* deletes the file created by CoverPageData::toAstFile() */

int CoverPageData::deleteTemp()
{
 return( unlink( tempName ) );
}
