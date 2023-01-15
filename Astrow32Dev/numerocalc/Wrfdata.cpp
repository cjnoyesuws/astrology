#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "chartinf.h"
#include "name.h"
#include "namegraf.h"
#include "numbr.h"
#include "errors.fns"

FILE_ID file_info;


void DllExport SetFileInfo( FILE_ID *p )
{
file_info = *p;
}


int fdata_write( FILE *stream, unsigned short type )
{
 int r;

 fwrite( &chart_info_data, sizeof( CHART_INFO ), 1, stream );
 file_info.birth = sizeof(FILE_ID);
 file_info.data = ftell( stream );
 r = fwrite( &type, sizeof( unsigned short ), 2, stream );
 if ( type == PERSON_FILE || type == NUMERIC_FILE ) {
    r += fwrite( &date_numbers, sizeof(NUMBERS), 1, stream ); 
    r += fwrite( &name_numbers, sizeof(NAME_NUMB_GROUP ), 1, stream );
    }
 else     
    r += fwrite( &name_graphs, sizeof(NAMEGRF_GRP ), 1, stream );
 file_info.text = ftell(stream);
 return( r );
}


void file_info_write( FILE *stream )
{
 fseek( stream, 0L, SEEK_SET );
 fwrite(&file_info, sizeof(FILE_ID), 1, stream );
}
