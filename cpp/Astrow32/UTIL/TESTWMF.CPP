#include "stdafx.h"
#include <stdio.h>

#pragma pack(1)
typedef struct WMFHead {
    WORD  mtType;     
	WORD  mtHeaderSize;     
	WORD  mtVersion;     
	DWORD mtSize; 
    WORD  mtNoObjects;     
	DWORD mtMaxRecord;     
	WORD  mtNoParameters;
 	} WMFHead;

typedef struct WMFItem {
	long size;
	int  code;
	} WMFItem;


#pragma pack()
char buffer[1000];


void main(int argc, char **argv)
{
 WMFHead head;
 WMFItem it;
 FILE *stream;

 stream = fopen( argv[1], "rb" );
 fread( &head, sizeof(WMFHead), 1, stream );
 do {
    fread( &it, 6, 1, stream );
    fread( buffer, (it.size*2)-6, 1, stream );
    printf( "Type %hx, Size %d\n", it.code, it.size);
    } while( !feof( stream ) );
 fclose( stream );
}
