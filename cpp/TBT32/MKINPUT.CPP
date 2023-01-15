/*************************************************************************
|									 |
|   INPUT.C							14.03.89 |
|   MAKE Utility:  parse a makefile					 |
|									 |
*************************************************************************/

#include "stdafx.h"
#include	<stdlib.h>
#include	<ctype.h>
#include        "tbtutil.h"
#include        "make.h"

struct name namehead;
struct name * firstname;
char blank8[]	= "        ";           /* 8 space == tab */
char str1[LZ];				/* general store */
char str2[LZ];

/*****	intern a name - return a pointer to the name struct */

struct name *newname(char *name)
{
    struct name * rp;
    struct name * rrp;
    char * cp;
    register int i;
    register char * q;

    static char namerr[] = {
	"Cannot allocate memory for name"};

    for
    (rp = namehead.n_next, rrp = &namehead;
    rp;
    rp = rp->n_next, rrp = rrp->n_next)
    {
	i = 0;
	q = rp->n_name;
	while (name[i] == *(q+i))
	    if (name[i++] == '\0')
		return rp;
    }
    rp=(struct name *)memcalloc(sizeof(struct name),namerr);
/*  following zeroed out in memcalloc
 *  rp->n_line = (struct line *)0;
 *  rp->n_time = (long)0;
 *  rp->n_flag = 0;
 *  rp->n_next = (struct name *)0;
*/
    rrp->n_next = rp;
    cp = (char *) memcalloc(strlen(name)+1,namerr);
    strcpy(cp, name);
    rp->n_name = cp;

    return rp;
}


/*****	add a dependant to the end of the supplied list of dependants */
/*****	return the new head pointer for that list */

struct depend *newdep(struct name * np,struct depend * dp)
{
    register struct depend *rp = NULL;
    register struct depend *rrp = NULL;
    static char deperr[] = {
	"Cannot allocate memory for dependant"};

    rp = (struct depend *)memcalloc(sizeof(struct depend),deperr);
/*  zeroed out in memcalloc
 *  rp->d_next = (struct depend *)0;
 */
    rp->d_name = np;

    if (dp == (struct depend *)0)
	return rp;

    for (rrp = dp; rrp->d_next; rrp = rrp->d_next)
	;

    rrp->d_next = rp;
    return dp;
}


/*****	add a command to the end of the supplied list of commands */
/*****	return the new head pointer for that list, and save the */
/*****	actual command structure created in case lif lines are found */

struct cmd *newcmd(char * str,struct cmd * cp,struct cmd * * crp)
{
    register struct cmd * rp;
    register struct cmd * rrp;
    register char * rcp;
    static char comerr[] = {
	"Cannot allocate memory for command"};

    if (NULL != (rcp = strrchr(str, '\n')))
	*rcp = '\0';                    /* lose newline  */
    while (isspace(*str))
	str++;

    if (*str == '\0')                   /* if nothing left, then exit */
    {
	*crp = (struct cmd *)0;
	return cp;
    }

    rp = (struct cmd *)memcalloc(sizeof(struct cmd),comerr);
/*
 *   zeroed out in memcalloc()
 *   rp->c_next = (struct cmd *)0;
 *   rp->c_lif = (struct lif *)0;
 */
    rcp = (char _far *)memcalloc(strlen(str)+1,comerr);
    strcpy(rcp, str);
    rp->c_cmd = rcp;
    *crp = rp;

    if (cp == (struct cmd *)0)
	return rp;

    for (rrp = cp; rrp->c_next; rrp = rrp->c_next)
	;

    rrp->c_next = rp;
    return cp;
}

/*****	add a lif line to the end of the supplied list of lif lines */
/*****	return the new head pointer for that list */

struct lif *newlif(char *str,struct lif * lp)
{
    register struct lif * rp;
    register struct lif * rrp;
    register char * rlp;
    static char liferr[] = "Cannot allocate memory for local input file";

    if (NULL != (rlp = strrchr(str, '\n')))
	*rlp = '\0';                    /* lose newline */

    if (*str == '\0')
	return lp;			/* if nothing left, then exit */

    rp = (struct lif *)memcalloc(sizeof(struct lif),liferr);
/*
 *  zeroed out in memcalloc()
 *   rp->f_next = (struct lif *)0;
 */
    rlp = (char _far *)memcalloc(strlen(str)+1,liferr);
    strcpy(rlp, str);
    rp->f_lif = rlp;

    if (lp == (struct lif *)0)
	return rp;
    for (rrp = lp; rrp->f_next; rrp = rrp->f_next)
	;

    rrp->f_next = rp;
    return lp;
}


/*****	add a new 'line' of stuff to a target */
/*****	check to see if commands already exist for the target */

void newline(struct name * np,struct depend * dp,struct cmd * cp,int flag)
{
    bool hascmds = FALSE;		/*  Target has commands  */
    register struct line * rp = NULL;
    register struct line * rrp = NULL;
    static char linerr[] = "Cannot allocate memory for line";

    if ( (!dp && !cp && !strcmp(np->n_name,".SUFFIXES")))
    {
	for (rp = np->n_line; rp; rp = rrp)
	{
	    rrp = rp->l_next;
	    delete (char *)rp;
	}
	np->n_line = (struct line *)0;
	np->n_flag &= ~N_TARG;
	return;
    }

    for
    ( rp = np->n_line, rrp = (struct line *)0; rp;
                   rrp = rp, rp = rp->l_next ) {
	if (rp->l_cmd)
	    hascmds = TRUE;
    }
    /*****  handle the implicit rules redefinition case */

    if (hascmds && cp && !(np->n_flag & N_DOUBLE)) {
	if (np->n_name[0] == '.' && dp == (struct depend *)0)
	{
	    np->n_line->l_cmd = cp;
	    return;
	}
	else
	    error("Multiple sets of commands for target %s", np->n_name);
        }
    if (np->n_flag & N_TARG)
	if (!(np->n_flag & N_DOUBLE) != !flag) /* like xor */
	    error("Inconsistent rules for target %s", np->n_name);

    rp = (struct line *)memcalloc(sizeof (struct line),linerr);
/*
 *  zeroed out in memcalloc()
 *  rp->l_next = (struct line *)0;
 */
    rp->l_dep = dp;
    rp->l_cmd = cp;

    if (rrp)
	rrp->l_next = rp;
    else
	np->n_line = rp;

    np->n_flag |= N_TARG;

    if (flag)
	np->n_flag |= N_DOUBLE;
}

/*****	check for the presence of a local input file */

void checklif(struct cmd * cp)
{
    register struct lif * lp;

    lp = (struct lif *)0;
    if (strstr(str2,"$-"))              /* lif follows */
    {
	for (;;)
	{
	    if (getline(str2))
		fatal("Unterminated local input file");
	    if (str2[0] == '<')
		break;
	    lp = newlif(&str2[0],lp);
	}
    }
    if (cp)
	cp->c_lif = lp;
}

/* expand $* in dependencies, by creating a new dep for each */

void expast(struct name * np)
{
    register struct depend *dp = NULL;
    register struct line * lp = NULL;
    struct name * nnp;
    struct depend * * dpp = NULL;
    char * p;
    char * q;
    char * r;
    char * rr;
    char * suff;
    char expb[64];
    static char experr[] = {
	"Unable to expand $*"};

    for (lp = np->n_line; lp; lp = lp->l_next)
    {
	for (dp = lp->l_dep; dp; dp = dp->d_next)
	{
	    rr = (char *)0;
	    p = r = dp->d_name->n_name;
	    while (*p)
	    {
		if ( ((*p & 0xff) == 0244) && ((*(p + 1) & 0xff) == 0244) )
		{
		    rr = p;
		    break;
		}
		p++;
	    }
	    if (rr != (char *)0)
	    {
		q = np->n_name; 	/* get target name */
		if ((strlen(q) + strlen(r)) > 60)
		    fatal(experr);
		p = expb;
		while (r < rr) *p++ = *r++;
		suff = suffix(q);
		while (q < suff) *p++ = *q++;
		r += 2; 		/* skip special marker */
		while (*r) *p++ = *r++;
		*p = '\0';
		nnp = newname(expb);	/* make a new dependent */
		for (dpp = &(lp->l_dep); *dpp; dpp = &((*dpp)->d_next))
		{
		    if (*dpp == dp)
		    {
			*dpp = (struct depend *)memcalloc(sizeof(struct depend),experr);
			(*dpp)->d_next = dp->d_next;
			(*dpp)->d_name = nnp;
		    }
		}
	    }
	}
    }
}

/*****	parse input from the makefile, and construct a tree structure of it */

void input()
{
    char * p;				/*  General  */
    char * q;
    struct name * np = NULL;
    struct depend * dp = NULL;
    struct cmd * cp = NULL;
    struct cmd * crp = NULL;
    bool dbl;

    if (getline(str1))
	return; 			/* read the first line */
    setmacro("*","\244\244");           /* special marker for $* */

    for(;;)
    {
	if (isspace(*str1) || 0 == memcmp(str1,blank8,8))/* rules without targets */
	    error("Command found with no target/dependancy line");

	p = str1;
	while (isspace(*p))
	    p++;			/* find first target */

	while (((q = strchr(p, '=')) != (char *)0) &&
	(p != q) && (q[-1] == '\\'))    /*  Find value */
	{
	    register char * a;

	    a = q - 1;			/* del \ chr; move rest back */
	    p = q;
	    while(0 != (*a++ = *q++))
		;
	}

	if (q != (char *)0)
	{
	    register char * a;

	    *q++ = '\0';                /* separate name and val */
	    while (isspace(*q))
		q++;
	    if (NULL != (p = strrchr(q, '\n')))
		  *p = '\0';
	    p = str1;
	    if ((a = gettok(&p)) == (char *)0)
		error("Macro definition without macro name");
	    setmacro(a, q);
	    if (getline(str1))
		return;
	    continue;
	}

	expand(str1);
	p = str1;

	while (( (q = strchr(p, ':'))  != (char *)0) &&
	(p != q) && (q[-1] == '\\'))    /*  Find dependents  */
	{
	    register char * a;

	    a = q - 1;			/* del \ chr; move rest back */
	    p = q;
	    while(0 != (*a++ = *q++))
		;
	}
    if ( q = str1+1 )
	   q = strchr(q+1, ':');
	if (q == (char *)0)
	    error("Cannot find any targets");
    *q++ = '\0';                    /* separate targets and dependents */

	if (*q == ':')                  /* double colon */
	{
	    dbl = 1;
	    q++;
	}
	else
	    dbl = 0;

	for (dp = (struct depend *)0; ((p = gettok(&q)) != (char *)0);)

	{				/* get list of dep's */
	    np = newname(p);		/* intern name */
	    dp = newdep(np, dp);	/* add to dep list */
	}

	*((q = str1) + strlen(str1) + 1) = '\0'; /* two nulls for gettok */
	cp = (struct cmd *)0;
	if (getline(str2) == FALSE)	/* get commands */
	{

	    while (isspace(*str2) || 0 == memcmp(str2,blank8,8))
	    {
		cp = newcmd(&str2[0], cp, &crp);
		checklif(crp);
		if (getline(str2))
		    break;
	    }
	}

	while ((p = gettok(&q)) != (char *)0) /* get list of targ's */
	{
	    np = newname(p);		/* intern name */
	    newline(np, dp, cp, dbl);
	    expast(np); 		/* expand $* in dep */
	    if (!firstname && p[0] != '.')
		firstname = np;
	}

	if (nestlvl < 0)
	    return;			/* eof? */
	strcpy(str1, str2);
    }
}
/*
 *  get memory and zero out area obtained
 *  if unable to do so, exit with message
 *  all requests are for some positive memory amnt
 */
void *memcalloc(int amnt,char *errmsg)
{
    void *r;

    r = new char[amnt];
    if ( r == NULL ) {
       do_mem_error( 0 );
       Throw(j, 1);
       }
    memset( r, 0, amnt );
    return r;
}
