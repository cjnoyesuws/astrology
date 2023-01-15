/*************************************************************************
|									 |
|   MAIN.C							29.04.89 |
|   MAKE Utility:  main program 					 |
|									 |
*************************************************************************/

#define 	VV		"1.60"

#include "stdafx.h"
#include	<io.h>
#include	<direct.h>
#include	<errno.h>
#include	<stdlib.h>
#include	<signal.h>
#include	<stdarg.h>
#include        "tbtutil.h"
#include        "make.h"

char * myname;				/* Name of this program */
char * makefile;			/* The make file  */

bool domake = TRUE;			/* Go through the motions option  */
bool ignore = FALSE;			/* Ignore exit status option  */
bool silent = FALSE;			/* Silent option  */
bool print = FALSE;			/* Print debuging information  */
bool rules = TRUE;			/* Use inbuilt rules  */
bool dotouch = FALSE;			/* Touch files instead of making  */
bool quest = FALSE;			/* Question up-to-dateness of file  */
bool display = FALSE;			/* Display times */
uchar macrotype = '\0';                 /* Environment, Command-line, etc */
CATCHBUF j;

FILE * ifile[4] = {0,0,0,0};		/* input files */
int fln[4]	= {
    0,0,0,0};				/* input file line numbers */
char fname[4][80] =
{
    "",
    "",
    "",
    ""
};					/* input file names */
int nestlvl	= 0;			/* nesting level */
char ifmessage	= '#';                  /* 'if' statement lead-in */

void usage(void)
{
    LogPrintf("Usage: %s [-f makefile] [-deinpqrst] [macro=val ...] [target(s) ...]\n", myname);
    Throw(j,1);
}

void _cdecl fatal(char *msg, ...)
{
 char buf[100];

    va_list params;
    va_start(params,msg);
    sprintf(buf, "MAKE: %s", makefile);
    valert_box_ext(buf, MB_ICONSTOP, msg, params);
    Throw(j,1);
}

int  make_main(int argc, char **argv)
{
    register char * p;			/*  For argument processing  */
    int estat	    = 0;		/*  For question  */
    register struct name * np;
    int i;
    char * makeflags;
    int egiven	    = 0;

    if ( (i = Catch( j )) > 0 )
       return( i );
    myname = "make";

    makeflags = getenv("MAKEFLAGS");
    if (makeflags)
	argv[0] = makeflags;
    else
	argv[0] = "";

    while (argc > 0)
    {
	if (**argv == '\0')             /* empty makeflags */
	{
	    argc--;			/*  One less to process  */
	    argv++;
	}
	else if (**argv == '-')
	{
	    argc--;			/*  One less to process  */
	    p = *argv++;		/*  Now processing this one  */

	    while (*++p != '\0')
	    {
		switch(*p)
		{
		case 'd':               /*  debug with timestamps */
		    display++;
		    break;
		case 'e':               /*  Enviroment macros prevail */
		    egiven++;
		    break;
		case 'f':               /*  Alternate file name  */
		    if (*(argv-1) == makeflags)
			break;
		    if (argc-- <= 0)
			usage();
		    makefile = *argv++;
		    break;
		case 'n':               /*  Pretend mode  */
		    domake = FALSE;
		    break;
		case 'i':               /*  Ignore fault mode  */
		    ignore = TRUE;
		    break;
		case 's':               /*  Silent about commands  */
		    silent = TRUE;
		    break;
		case 'p':
		    if (*(argv-1) != makeflags)
			print = TRUE;
		    break;
		case 'r':
		    rules = FALSE;
		    break;
		case 't':
		    dotouch = TRUE;
		    break;
		case 'q':
		    quest = TRUE;
		    break;
		}
	    }
	}
	else if ((p = strchr(*argv, '=')) != NULL)
	{
	    char c;

	    c = *p;
	    *p = '\0';
	    macrotype = M_PERM; 	/* doing command-line macros */
	    setmacro(*argv, p+1);
	    macrotype = '\0';
	    *p = c;

	    argv++;
	    argc--;
	}
	else break;
    }

    if (!makefile) 		/*  If no file, then use default */
    {
	strncpy(fname[0],DEFN1,80);
	if ((ifile[0] = fopen(fname[0], "r")) == (FILE *)0)
	{
	    fatal("Unable to open file %s", fname[0]);
	}
    }
    else
    {
	if ((ifile[0] = fopen(makefile, "r")) == (FILE *)0)
	    fatal("Unable to open file %s", makefile);
	strncpy(fname[0],makefile,80);
    }
    setmacro("MAKEFILE",fname[0]);
    if (egiven)
	markmacros();			/* make env macros perm */
    if (rules)
	makerules();			/* use builtin rules */
    setmacro("\\","\\");
    setmacro("HOME",getcwd((char *)0,64));
#ifdef		DOLLAR
    setmacro("$", "\244");              /* special high bit set */
#else
    setmacro("$", "$");
#endif
    setmacro("MAKE",myname);
    setmacro("-", LIFNAME);

    input();				/*  Input all the gunga  */
    lineno = 0; 			/*  Any calls to error now print no line number */
    ifmessage = '%';                    /*  if statement lead-in now '%' */

    np = newname(".SILENT");
    if (np->n_flag & N_TARG)
	silent = TRUE;

    np = newname(".IGNORE");
    if (np->n_flag & N_TARG)
	ignore = TRUE;

    p = str1;
    *p++ = '-';
    if (egiven)
	*p++ = 'e';
    if (ignore)
	*p++ = 'i';
    if (!domake)
	*p++ = 'n';
    if (quest)
	*p++ = 'q';
    if (!rules)
	*p++ = 'r';
    if (silent)
	*p++ = 's';
    if (dotouch)
	*p++ = 't';
    if (p == (str1+1))
	p = str1;
    *p = '\0';
    setmacro("+MAKEFLAGS",str1);

    if (print)
	prt();				/*  Print out structures  */
    precious();
    if (!domake)
	silent = FALSE;
    if (!firstname)
	fatal("No targets found to build");
    circh();				/*  Check circles in target definitions  */

    if (!argc)
	estat = make(firstname, 0);
    else while (argc--)
	estat |= make(newname(*argv++), 0);

    if (quest)
	return(1);
    else return(0);
 return( 0 );
}

void cleanupmake()
{
 extern int iftable[], iflevel;
 killname( &namehead, 0 );
 namehead.n_next = NULL;
 namehead.n_name = NULL;
 namehead.n_line = NULL;
 firstname = NULL;
 lineno = 0;
 memset(ifile, 0, 4 * sizeof( FILE *) );
 memset(fln, 0, 8 );
 memset(fname, 0, 320 );
 memset(str1, 0, LZ );
 memset(str2, 0, LZ );
 nestlvl = 0;
 iflevel = 0;
 memset(iftable, 0, 20 );
 killmacros();
}
