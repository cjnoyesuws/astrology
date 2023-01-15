/*************************************************************************
|									 |
|   READER.C							05.12.88 |
|   MAKE Utility:  read in the makefile 				 |
|									 |
*************************************************************************/

#include "stdafx.h"
#include	<stdlib.h>
#include	<ctype.h>
#include	<stdarg.h>
#include        "tbtutil.h"
#include        "make.h"

int lineno;

static char * detabfgets(char *,int ,FILE *);

/*****	syntax error handler - print message, with line number, and exit */

void _cdecl error(char *msg, ...)
{
 char buf[100];
 va_list params;

 va_start(params,msg);
 sprintf(buf, "MAKE: %s", makefile);
 valert_box_ext(buf, MB_ICONSTOP, msg, params);
 Throw(j,1);
}

/*****	read a line */

/*************************************************************************
|									 |
|   Read a line into the supplied string of length LZ.	Remove		 |
|   comments, ignore blank lines. Deal with quoted (\) #, and		 |
|   quoted newlines.  If EOF return TRUE.				 |
|									 |
*************************************************************************/

bool getline(char *str)
{
    register char * p;
    char * q;
    char * a;
    int pos	    = 0;
    FILE * fd;
    FILE * incf;
    int specialhash;

    if (nestlvl < 0)
	return TRUE;			/* EOF */

    for (;;)
    {
	fd = ifile[nestlvl];
	if (detabfgets(str+pos, LZ-pos, fd) == (char *)0)
	{
	    fclose(fd);
	    if (nestlvl == 0)
	    {
		nestlvl--;
		ifeof();
		return TRUE;
	    }
	    fln[nestlvl] = 0;
	    nestlvl--;
	    continue;
	}
	lineno = ++fln[nestlvl];

	if ((p = strchr(str+pos, '\n')) == (char *)0)
	    error("Input line is too long");

	if (p[-1] == '\\')
	{
	    p[-1] = '\n';
	    pos = p - str;
	    continue;
	}
	specialhash = 0;
	if(*str == '#' )                /* starts with # */
	{
	    if(*(str+1) == 'i')         /* could  be #i */
	    {
		if (!memcmp(str,"#ifn",4))
		    specialhash = 2;
		else if (!memcmp(str,"#if",3))
		    specialhash = 1;
		else if (!memcmp(str,"#include",8))
		    specialhash = 5;
	    }
	    else			/* or it could be #e */
	    if(*(str+1) == 'e')
	    {
		if (!memcmp(str,"#else",5))
		    specialhash = 3;
		else if (!memcmp(str,"#endif",6))
		    specialhash = 4;
	    }
	}
	p = str + (specialhash != 0);
	while (((q = strchr(p, '#')) != (char *)0) &&
	(p != q) && (q[-1] == '\\'))
	{
	    a = q - 1;			/*  Del \ chr; move rest back  */
	    p = q;
	    while (0 != (*a++ = *q++))
		;
	}

	if (q != (char *)0)
	{
	    while ( (q != str) && (isspace(q[-1])) )
		q--;
	    q[0] = '\n';
	    q[1] = '\0';
	}

	if (ifproc(str,specialhash))
	{
	    pos = 0;
	    continue;
	}

	if (specialhash == 5)
	{
	    q = str + 8;
	    while (isspace(q[0]))
		q++;
	    if (nestlvl >= 3)
		fatal("Include files nested too deeply");
	    a = q + strlen(q) - 1;
	    if (*a == '\n')
		*a = '\0';
	    expand(q);
	    incf = fopen(dollar(q),"r");
	    if (incf == (FILE *)0)
		fatal("Unable to open include file %s",dollarbuf);
	    ifile[++nestlvl] = incf;
	    strncpy(fname[nestlvl],q,80);
	    continue;
	}

	p = str;
	while (isspace(*p))		/*  Checking for blank	*/
	    p++;

	if (*p != '\0')
	    return FALSE;
	pos = 0;
    }
}

/*****	get token */

/*************************************************************************
|									 |
|   Get a word from the current line, surounded by white space. 	 |
|   return a pointer to it. String returned has no white spaces 	 |
|   in it.								 |
|									 |
*************************************************************************/

char *gettok(char **ptr)
{
    register char * p;
    register char * q;
    for(p=*ptr;isspace(*p);p++) ;
    *ptr = q = p;
    if (*p == '\0')
	return NULL;			/* nothing after spaces  */
    while ((*q != '\0') && (!isspace(*q)))
	q++;				/* find word end */
    *(q++) = '\0';                      /* terminate it  */
    *ptr=q;
    return(p);
}

/*
 * detabfgets()
 * read makefile, detab it, as msdos editors tab to next
 * column
 */

static char *detabfgets(char *str,int len,FILE *fd)
{
    char *cp;
    register int cc;
    int inpcol,inptab;
    inpcol=inptab=0;
    cp=str;
    while(inpcol<len)
    {
	if('\t' == (cc=fgetc(fd)))
	{
	    inpcol += (inptab=1+((~inpcol)&7));
	    if(inpcol<len)
		while(0<inptab--)
		    *str++ =' ';
	    continue;
	}

	if((cc == EOF))
	{
	    *str++ ='\0';
	    return (char *)0;
	}
	inpcol++;			/* logical position in the input line */
	*str++=(char)cc;
	if( cc == '\n' )
	     break;
    }
    *str='\0';
    return cp;
}
