#include "stdafx.h"
#include        "tbtutil.h"
#include        "make.h"

/*************************************************************************
|									 |
|   RULES.C							14.03.89 |
|   MAKE Utility:  control of implicit suffix rules			 |
|									 |
*************************************************************************/
/*****	return a pointer to the suffix of a name */

char *suffix(char * name)
{
    register int i;
    int l;
    l = strlen(name);
    for (i = l - 1; i >= 0; i--)
    {
	if (name[i] == '.')
	    return name + i;
    }
    return name + l - 1;
}


/*****	dynamic dependency */

/*************************************************************************
|									 |
|   This routine applies the suffix rules to try and find a source and	 |
|   a set of rules for a missing target.  If found, np is made into a	 |
|   target with the implicit source name and rules.  Returns TRUE if np  |
|   was made into a target.						 |
|									 |
*************************************************************************/

bool dyndep(struct name * np)
{
    register char * p;
    register char * q;
    register char * suff;		/*  Old suffix	*/
    register char * basename;		/*  Name without suffix  */
    struct name * op;			/*  New dependent  */
    struct name * sp;			/*  Suffix  */
    struct line * lp;
    struct depend * dp;
    char * newsuff;

    p = str1;
    q = np->n_name;
    suff = suffix(q);
    while (q < suff)
	*p++ = *q++;
    *p = '\0';
    basename = strcpy(str2,str1);

    if (!((sp = newname(".SUFFIXES"))->n_flag & N_TARG))
	return FALSE;

    for (lp = sp->n_line; lp; lp = lp->l_next)
	for (dp = lp->l_dep; dp; dp = dp->d_next)
	{
	    newsuff = dp->d_name->n_name;
	    if (strlen(suff)+strlen(newsuff)+1 >= LZ)
		fatal("Inference rule too long");
	    p = str1;
	    q = newsuff;
	    while (0!=(*p++ = *q++))
		;
	    p--;
	    q = suff;
	    while (0!=(*p++ = *q++))
		;
	    sp = newname(str1);
	    if (sp->n_flag & N_TARG)
	    {
		p = str1;
		q = basename;
		if (strlen(basename) + strlen(newsuff)+1 >= LZ)
		    fatal("Inferred name too long");
		while (0!= (*p++ = *q++))
		    ;
		p--;
		q = newsuff;
		while (0!= (*p++ = *q++))
		    ;
		if ((np->n_line) &&
		(strstr(q=np->n_line->l_dep->d_name->n_name,str1)))
		    op=newname(q);
		else
		    op = newname(str1);
		if (!op->n_time)
		    modtime(op);
		if ((op->n_time) || (op->n_flag & N_TARG))
		{
		    dp = newdep(op, 0);
		    newline(np, dp, sp->n_line->l_cmd,0);
		    op->n_flag |= N_DYND;
		    return TRUE;
		}
	    }
	}
    return FALSE;
}


static void makearule(char *str1,char *str2);

/***** make the default rules */

void makerules()
{
    struct depend * dp=NULL;
    struct name * np;

    np = newname(".SUFFIXES");
    newline(np, dp, 0, 0);
}

static void makearule(char *str1,char *str2)
{
    struct cmd * cp;
    struct cmd * rcp;
    struct name*  np;

    cp=newcmd(str1,0,&rcp);
    np=newname(str2);
    newline(np, 0, cp, 0);
}
