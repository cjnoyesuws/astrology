/*************************************************************************
|									 |
|   MAKE.C							25.04.89 |
|   MAKE Utility:  do the actual making 				 |
|									 |
*************************************************************************/
#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include	<fcntl.h>
#include	<io.h>
#include	<sys\types.h>
#include	<sys\stat.h>
#include	<process.h>
#include	<dos.h>
#include	<errno.h>
#include	<ctype.h>
#include	<stdlib.h>
#include	<time.h>
#if             !defined(__ZTC__) && !defined(__TSC__)
#include	<sys\utime.h>
#endif
#include        "tbtutil.h"

#include        "make.h"
#ifdef _WINTBT_
#define         ARGN            12
#else
#define         ARGN            64
#endif

static int lifmade = 0;
static char lifname[128] = "";



#ifdef		MDOS
#define 	_TESTINTERNAL		/* number of internal commands to test for */
#endif
#ifdef		MOS2
#define 	_TESTINTERNAL		/* number of internal commands to test for */
#endif

/* Dos internal commands, augment list if reqd */
#ifdef		_TESTINTERNAL
static char * reallyinternal[] =
{
    "CD",
    "CHDIR",
    "DEL",
    "ERASE",
    "MD",
    "MKDIR",
    "RD",
    "REN",
    "RENAME",
    "RMDIR",
    "COPY"
};

static char * internal[] =
{
    "CD",
    "CHDIR",
    "COPY",                             /* keep in alphabetic sequence */
    "DEL",
    "ECHO",
    "ERASE",
    "FOR",
    "IF",
    "MD",
    "MKDIR",
    "PAUSE",
    "RD",
    "REM",
    "REN",
    "RENAME",
    "RMDIR",
    "TYPE",
};

#define         TESTINTERNAL    (sizeof(internal)/sizeof(char *))
#define         TESTINTERNALR    (sizeof(reallyinternal)/sizeof(char *))
#else
#define 	TESTINTERNAL	0
#endif

/*****	remove special $ markers */

char dollarbuf[LZ];

char * dollar(char *p)
{
    register char * q = dollarbuf;
    strcpy(q,p);
#ifdef		DOLLAR
    while (0 != (q=strchr(q,0244)))
	*q++ = '$';
#endif
    return dollarbuf;
}


/****	test for common DOS and OS/2 internal commands, true if found */

#ifdef		_TESTINTERNAL

int dos_internal(char *s)
{
    register int i;
    char * p;
    char * q;
    char **in       = internal;
    while ((*s == ' ') && (*s != '\0'))
	s++;
    for (i = TESTINTERNAL; i--;)
    {
	p = s;
	q = *in++;
	while ( (*p != ' ') && ( (*p & 0x5f) == *q ))
	    p++,q++;
	if ((*p == ' ') && (*q == '\0'))
	    return 1;
    }
    return 0;
}

int really_internal(char *s)
{
    register int i;
    char * p;
    char * q;
    char **in       = reallyinternal;
    while ((*s == ' ') && (*s != '\0'))
	s++;
    for (i = TESTINTERNALR; i--;)
    {
	p = s;
	q = *in++;
	while ( (*p != ' ') && ( (*p & 0x5f) == *q ))
	    p++,q++;
	if ((*p == ' ') && (*q == '\0'))
	    return 1;
    }
    return 0;
}



#endif

/*****	do the command */

int dosh(char *p,int shell)
{

    int argc;
    char * argv[ARGN];
    char c;
    char * q;
    char token[64];
    register int i;
    char * mode;
    int ret;
    int r0,r1,r2;

    p = dollar(p);
    if (shell <= 1)
       return win_System(p);


#ifdef		_TESTINTERNAL		/* must be DOS or OS/2 */

    r0 = r1 = r2 = 0;			/* clear redirection switches */
    if ((q = strstr(p,"<")) != (char *)0)
    {
	i = 0;
	*q++ = ' ';
	while (*q == ' ')
	    q++;
	while (!isspace(*q) && (*q != '\0') && (i < 63))
	{
	    token[i++] = *q;
	    *q++ = ' ';
	}
	token[i] = '\0';
	if (0 == freopen(token,"r",stdin))
	    return 999;
	r0 = 1;
    }
    if ((q = strstr(p,"2>")) != (char *)0)
    {
	i = 0;
	mode = "w";
	*q++ = ' ';
	*q++ = ' ';
	if (*q == '>')
	{
	    mode = "a";
	    *q++ = ' ';
	}
	while (*q == ' ')
	    q++;
	while (!isspace(*q) && (*q != '\0') && (i < 63))
	{
	    token[i++] = *q;
	    *q++ = ' ';
	}
	token[i] = '\0';
	if (0 == freopen(token,mode,stderr))
	    return 999;
	r2 = 1;
    }
    if ((q = strstr(p,">")) != (char *)0)
    {
	i = 0;
	mode = "w";
	*q++ = ' ';
	if (*q == '>')
	{
	    mode = "a";
	    *q++ = ' ';
	}
	while (*q == ' ')
	    q++;
	while (!isspace(*q) && (*q != '\0') && (i < 63))
	{
	    token[i++] = *q;
	    *q++ = ' ';
	}
	token[i] = '\0';
	if (0 == freopen(token,mode,stdout))
	    return 999;
	r1 = 1;
    }
#endif

    for (argc = 0; argc < ARGN-1; argc++) argv[argc] = 0;
    for (argc = 0; argc < ARGN-1; )
    {
	while(isspace(*p))
	    p++;
	if (*p == '\0')
	    break;
	argv[argc++] = p;
	while ((*p != '\0') && (! isspace(*p)))
	    p++;
	c = *p;
	*p++ = '\0';
	if (c == '\0')
	    break;
    }
    if ( shell == 3 || checkDllFunc( argv[0] ) ) {
       ret = !execFunction(argv[0], argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8] );
       }
    else if ( shell == 2 )
       ret = doDosCmd( argv[0], argv[1], argv[2] );
#ifdef          _TESTINTERNAL           /* must be DOS or OS/2 */

    if (r0)
	freopen("CON","r",stdin);
    if (r1)
	freopen("CON","w",stdout);
    if (r2)
	freopen("CON","w",stderr);

#endif
    return ret;
}

/*****	create the local input file */

void makelif(struct cmd * cp)
{
    FILE * lifile;
    struct lif * lp;
    struct macro * mp;
    char * p	    = lifname;
    char * q;
    static char * ermsg = {
	"Unable to write local input file"};

    lifmade = 0;
    if ( cp->c_lif == (struct lif *)0 )
	return;
    if (NULL != (mp = getmp("-")))
    {
	if (mp->m_sub)
	{
	    strncpy(lifname,mp->m_sub,127);
	    delete (char *)mp->m_sub;
	}
	else
	    strncpy(lifname,mp->m_val,127);
    }
    else
	lifname[0] = '\0';
    while (*p == ' ')
	p++;
    strcpy(lifname,dollar(lifname));
    if (*p == '\0')
	strcpy(lifname,LIFNAME);
    if ( (lifile = fopen(lifname,"w")) == NULL)
	fatal(ermsg);
    for (lp = cp->c_lif; lp; lp = lp->f_next)
    {
	strcpy(str2, lp->f_lif);
	expand(str2);
	while (NULL != (q = strstr(str2,"\\n")))
	{
	    *q++ = '\n';
	    while (*++q) *(q-1) = *q;
	    *--q = '\0';
	}
	if (fputs( dollar(str2), lifile) == EOF)
	    fatal(ermsg);
	if (fputs("\n", lifile) == EOF)
	    fatal(ermsg);
    }
    if (fclose(lifile) == EOF)
	fatal(ermsg);
    lifmade = 1;
}

/*****	kill the local input file */

void killlif()
{
 if (lifmade)
    unlink(lifname);
 }

void killlif(struct lif * lp)
{
 struct lif * temp = NULL;

 if (lp == NULL)
    return;
 do {
    temp = lp->f_next;
    delete lp->f_lif;
    delete lp;
    if ( temp != NULL )
       lp = temp;
    } while ( temp != NULL );
}

/*****	do the %set command */

void dosetcmd(char *p)
{
    char * q;
    char * pp;

    while (isspace(*p))
	p++;				/* find first target */

    pp = p;
    while (((q = strchr(p, '=')) != (char *)0) &&
    (p != q) && (q[-1] == '\\'))        /*  Find value */
    {
	register char * a;

	a = q - 1;			/* del \ chr; move rest back */
	p = q;
	while(0 != (*a++ = *q++)) ;
    }

    if (q != (char *)0)
    {
	register char * a;

	*q++ = '\0';                    /* separate name and val */
	while (isspace(*q))
	    q++;
	if ((a = gettok(&pp)) == (char *)0)
	    error("Macro definition without macro name");
	setmacro(a, q);
    }
}

/*****	do a set of commands to make a target */

void docmds1(struct name * np,struct line * lp)
{
    bool ssilent;
    bool signore;
    bool sdomake;
    int estat;
    register char * q;
    register char * p;
    int shell;
    register struct cmd * cp;
    int specialhash;

    for (cp = lp->l_cmd; cp; cp = cp->c_next)
    {
	shell = 0;
	ssilent = silent;
	signore = ignore;
	sdomake = domake;
	strcpy(str1, cp->c_cmd);
	specialhash = 0;
	if(*str1 == '%')
	{
	    if (!strncmp(str1,"%ifn",4))
		specialhash = 2;
	    else if (!strncmp(str1,"%if",3))
		specialhash = 1;
	    else if (!strncmp(str1,"%else",5))
		specialhash = 3;
	    else if (!strncmp(str1,"%endif",6))
		specialhash = 4;
	    else if (!strncmp(str1,"%set",4))
		specialhash = 5;
	    else if (!strncmp(str1,"%exit",5))
		specialhash = 6;
	    else specialhash = 0;
	}
	if (ifproc(str1,specialhash))
	    continue;
	if (specialhash == 6)
	   Throw(j,atoi(str1+5));
	if (specialhash == 5)
	{
	    dosetcmd(str1+4);
	    continue;
	}

	if (strstr(str1,"$(MAKE)"))
	    sdomake = TRUE;
	expand(str1);
	q = str1;
	while ((*q == '@') || (*q == '-') || (*q == '+') || (*q == '\\') || (*q == '!')|| (*q == '^'))
	{
	    if (*q == '@')
		ssilent = TRUE; 	/* specific silent */
	    else if (*q == '-')
		signore = TRUE; 	/* specific ignore */
	    else if (*q == '^')
		shell = 3;              /* specific internal funcs */
	    else if (*q == '!')
		shell = 2;              /* specific internal funcs */
	    else if (*q == '+')
		shell = 1;              /* specific shell */

	    else			/* must be \ */
	    {
		q++;			/* skip past \ */
		if ((*q == '@') || (*q == '-') || (*q == '+') || (*q == '!')|| (*q == '^'))
		    break;
		else			/* \ is a real char */
		{
		    q--;		/* make it start command */
		    break;		/* no more specials */
		}
	    }
	    q++;			/* skip past special char */
	}
#ifdef		_TESTINTERNAL
	if ( checkDllFunc( q ) )
	    shell = 3;
	else if ( really_internal(q) )
	    shell = 2;
	else if ( dos_internal(q) )
	    shell = 1;
	
#endif

	if (!ssilent)
	   LogPrintf("    ");

	for (p = q; *p; p++)
	{
	    if (*p == '\n' && p[1] != '\0')
	    {
		*p = ' ';
		if (!ssilent)
		   LogPrintf("\\\n", stdout);
	    }
	    else if (!ssilent)
	    {
#ifdef		DOLLAR
		if ((*p & 0xff) == 0244)
		    LogPutc('$');
		else
#endif
		    LogPutc(*p);
	    }
	}
	if (!ssilent)
	    LogPutc('\n');

	if (sdomake)
	{				/*  Get the shell to execute it  */
	    makelif(cp);
	    estat = dosh(q, shell);
	    killlif();
	    killlif(cp->c_lif);
	    cp->c_lif=NULL;
#ifdef      MDOS
	    bdos(0xb,0,0);		/* check control break */
#endif
	    if (estat != 0)
	    {
		if (shell)
		{
#ifdef		MOS2
		    if (makeos2 & signore)
			LogPrintf("(Ignored)\n",stdout);
		    else
#endif
			fatal("Couldn't execute shell");
		}
		else
		{
		    if (estat == 4)
			LogPrintf("%s: Interrupted", myname);
		    else if (estat == -1)
			LogPrintf("%s: Couldn't execute command",myname);
		    else if (estat == 999)
			LogPrintf("%s: Redirection error",myname);
		    else LogPrintf("%s: Error return %d", myname, estat);
		    if (signore)
			LogPrintf(" (Ignored)\n", stdout);
		    else
		    {
			LogPutc('\n');
			if (!(np->n_flag & N_PREC))
			    if (unlink(dollar(np->n_name)) == 0)
				LogPrintf("%s: '%s' removed\n", myname, dollarbuf);
			Throw(j, estat);
		    }
		}
	    }
	}
    }
    ifeoc();				/* check for unterminated if in cmds */
}

/***** do commands to make a target */

void docmds(struct name * np)
{
    struct name * dft;
    register struct line * rp;
    struct line * lp;
    bool hascmds = FALSE;

    for
    (
    rp = np->n_line;
    rp;
    rp = rp->l_next
    )
	if (rp->l_cmd)
	    hascmds = TRUE;

    if (!hascmds)
    {
	dft = newname(".DEFAULT");
	if (dft->n_flag & N_TARG)
	    np->n_line = dft->n_line;
    }

    for (lp = np->n_line; lp; lp = lp->l_next)
	docmds1(np,lp);
}


/*****	get the modification time of a file	     ********/
/*****	if the file doesn't exist, it's modtime is set to 0 */

void modtime(struct name * np)
{
    struct stat info;
    int fd;

    if ((fd = open(dollar(np->n_name), 0)) < 0)
	np->n_time = 0L;
    else
    {
	if (fstat(fd, &info) < 0)
	    fatal("Unable to get modification time for file %s; error code %02x", dollarbuf, errno);
	else
	    np->n_time = info.st_mtime;

	close(fd);
    }
}


/***** update the mod time of a file to now */


void touch(struct name * np)
{
    int fd;				/* used as error switch and for fileno */
    if (!domake || !silent)
       LogPrintf("    touch %s\n", dollar(np->n_name));
    if (domake)
    {
	if(-1 == access(dollarbuf,fd=0))
	{
	    if (0 <= (fd=creat(dollarbuf ,S_IWRITE)))
		fd=close(fd);
	}
	else
	    if (fd || _utime(dollarbuf ,(struct _utimbuf *)0))
	    {
		if (errno != ENOENT)
		    fatal("Unable to update modification time for file %s; error code %02x",
		    dollarbuf,errno);
		else
		    LogPrintf("%s: '%s' modification time not updated, file not found\n",
		    myname, dollarbuf);
	    }
    }
}


/*****	set $< and $* for the first dependancy name */
/*****	set $? to list of out-of-date dependency names */

void setdmacros(struct name * np,struct depend * qdp)
{
    char * p;
    char * q;
    char * suff;
    register struct depend *dp;
    register struct line * lp;
    int found	    = 0;
    int slen;
    for (lp = np->n_line; lp; lp = lp->l_next)
	for (dp = lp->l_dep; dp; dp = dp->d_next)
	{
	    if ( (!found) || (dp->d_name->n_flag & N_DYND) )
	    {
		q = dp->d_name->n_name;
		setmacro("<",q);
		p = str1;
		suff = suffix(q);
		while (q < suff) *p++ = *q++;
		*p = '\0';
		setmacro("*",str1);
		if (found)
		    return;
		found++;
	    }
	}

    strcpy(str1, "");
    for (dp = qdp; dp; dp = qdp)
    {
	slen=strlen(str1);
	if ((slen + strlen(dp->d_name->n_name) + 2) > LZ)
	    fatal("$? macro is too long");
	if (slen)
	    strcat(str1, " ");
	strcat(str1, dp->d_name->n_name);
	qdp = dp->d_next;
	delete (char *)dp;
    }
    setmacro("?", str1);
}

/*****	clear the dynamic dep flag for all deps of this target */
/*****	(in case this dep is used again for another target) */

void cleardynflag(struct name * np)
{
    register struct depend *dp;
    register struct line * lp;

    for (lp = np->n_line; lp; lp = lp->l_next)
	for (dp = lp->l_dep; dp; dp = dp->d_next)
	    dp->d_name->n_flag &= ~N_DYND;
}

/*****	display the timestamp */


void dodisp(char *name,const unsigned long t)
{
    if (t < 10)
       LogPrintf("... %s Timestamp %ld\n",name,t);
    else
       LogPrintf("... %s Timestamp %s\n",name,ctime(&t));
}

/*****	make one thing */

void make1(struct name * np,struct line * lp,struct depend * qdp)
{
 char *p;
 char buf[125];

    if (dotouch)
	touch(np);
    else
    {
	setmacro("@", np->n_name);      /* NOTE: *not* dollar() */
	strcpy( buf, np->n_name);
	p = strchr( buf, '.' );
	if ( p != NULL )
	   *p = '\0';
	p = strrchr( buf, '\\' );
	if ( p != NULL )
	   setmacro("&", p+1);
	else
	   setmacro("&", buf);
	setdmacros(np,qdp);
	if (lp)
	    docmds1(np, lp);		/* lp set if doing a :: rule */
	else docmds(np);
    }
}

/*****	recursive routine to make a target */

int make(struct name * np,int level)
{
    register struct depend *dp;
    register struct line * lp;
    long dtime	    = 1;
    register struct depend *qdp;
    int didsomething = 0;
    dollar(np->n_name); 		/* build dollarbuf */
    if (np->n_flag & N_DONE)
    {
	if ( display )
	    dodisp(dollarbuf,np->n_time);
	return 0;
    }

    if (!np->n_time)
	modtime(np);			/*  Gets modtime of this file  */

    if ( display )
	dodisp(dollarbuf,np->n_time);

    for (lp = np->n_line; lp; lp = lp->l_next)
	if (lp->l_cmd)
	    break;
    if (!lp)
	dyndep(np);

    if (!(np->n_flag & N_TARG) && np->n_time == 0L)
	fatal("Don't know how to make %s", dollarbuf);

    for (qdp = (struct depend *)0, lp = np->n_line; lp; lp = lp->l_next)
    {
	for (dp = lp->l_dep; dp; dp = dp->d_next)
	{
	    make(dp->d_name, level+1);
#ifdef		DEBUG
	    LogPrintf("%s, %lx, %s, %lx\n",
	    np->n_name,np->n_time, dp->d_name->n_name, dp->d_name->n_time);
#endif
	    if (np->n_time < dp->d_name->n_time)
		qdp = newdep(dp->d_name, qdp);
	    if (dtime < dp->d_name->n_time)
		dtime = dp->d_name->n_time;
	}
	if (!quest && (np->n_flag & N_DOUBLE) && (np->n_time < dtime))
	{
	    make1(np, lp, qdp); 	/* free()'s qdp */
	    dtime = 1;
	    qdp = (struct depend *)0;
	    didsomething++;
	}
    }

    np->n_flag |= N_DONE;

    if (quest)
    {
	long t;
	t = np->n_time;
	time(&np->n_time);
	cleardynflag(np);
	return t < dtime;
    }
    else if (np->n_time < dtime && !(np->n_flag & N_DOUBLE))
    {
	make1(np, (struct line *)0, qdp);
	time(&np->n_time);
    }
    else if (level == 0 && !didsomething)
	LogPrintf("%s: '%s' is up to date\n", myname, dollarbuf);
    cleardynflag(np);
    return 0;
}
