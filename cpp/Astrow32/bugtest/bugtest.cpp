// bugtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>

extern char *buffer;
int main(int argc, char* argv[])

{
    strcpy( buffer, "test" );
	return 0;
}
