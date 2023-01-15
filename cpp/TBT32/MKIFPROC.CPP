/*************************************************************************
|									 |
|   IFPROC.C							05.12.88 |
|   MAKE Utility:  process conditionals 				 |
|									 |
*************************************************************************/

#include "stdafx.h"
#include	<stdlib.h>
#include	<ctype.h>
#include        "tbtutil.h"
#include        "make.h"
#define 	MAXIF		10

int iftable[MAXIF+1] = {
    0};
int iflevel	= 0;
extern char ifmessage;

#define 	NORMAL		0	/* No conditionals in force */
#define 	OKCOND		1	/* Processing lines, waiting for else or endif */
#define 	SKIP		2	/* Skipping lines, waiting for else or endif */
#define 	HADELSE 	4	/* Had else, must be waiting for endif */

/*****	check clean eof */

void ifeof()
{
    if (iflevel == 1)
	fatal("End of file - expected #endif");
    if (iflevel > 1)
	fatal("End of file - expected %d #endif's",iflevel);
}

/*****	check clean end of commands */

void ifeoc()
{
    if (iflevel == 1)
	fatal("End of command set - expected %%endif");
    if (iflevel > 1)
	fatal("End of command set - expected %d %%endif's",iflevel);
}

/*****	check each line, return true if to be ignored */

int ifproc(char * s,int n)
{
    register int i;

    switch (n)
    {
    case 1:				/* IF */
    case 2:				/* IFN */
	if (iflevel >= (MAXIF))
	    error("%cif and %cifn statements nested too deeply",
	    ifmessage,ifmessage);
	s += 4;
	while (isspace(*s))
	    s++;
	i = istrue(s);
	if (n == 2)
	    i = !i;
	iftable[++iflevel] = 2 - i;
	return 1;
    case 3:				/* ELSE */
	i = iftable[iflevel];
	if ((i == NORMAL) || (i & HADELSE))
	    error("%celse without %cif",ifmessage,ifmessage);
	if (i & OKCOND)
	    i = SKIP | HADELSE;
	else i = OKCOND | HADELSE;
	iftable[iflevel] = i;
	return 1;
    case 4:
	if (iftable[iflevel])
	{
	    iftable[iflevel] = NORMAL;
	    iflevel--;
	    return 1;
	}
	error("%cendif without %cif",ifmessage,ifmessage);
    default:
	return (iftable[iflevel] & SKIP); /* true if skipping */
    }
}

/*****	check whether if statement is true */

int istrue(char *s)
{
    char * p;				/*  General  */
    char * q;				/*  General  */
    struct macro * mp;
    int r;

    p = s;

    while (((q = strchr(p, '=')) != (char *)0) &&
    (p != q) && (q[-1] == '\\'))        /*  Find value */
    {
	register char * a;
	a = q - 1;			/*  Del \ chr; move rest back  */
	p = q;
	while(0!=(*a++ = *q++))
	    ;
    }
    if (q != (char *)0)
    {
	register char * a;

	*q++ = '\0';                    /*  Separate name and val  */
	while (isspace(*q))
	    q++;
	if (NULL!=(p = strrchr(q, '\n')))
	    *p = '\0';
	p = s;
	if ((a = gettok(&p)) == (char *)0)
	    error("Bad conditional on %cif statement",ifmessage);
	expand(q);
	if (0!= (mp = getmp(a)))
	{
	    if (mp->m_sub)
	    {
		r = strcmp(q,mp->m_sub);
		delete (char *) mp->m_sub;
	    mp->m_sub=NULL;
	    }
	    else
	    r = strcmp(q,mp->m_val);
	}
	else
	    r = strcmp(q,"");
	return (r == 0);
    }
    error("No conditional on %cif statement",ifmessage);
return( 0 );
}
