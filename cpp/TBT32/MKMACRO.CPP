/*************************************************************************
|									 |
|   MACRO.C							14.03.89 |
|   MAKE Utility:  macro control functions				 |
|									 |
*************************************************************************/

#include "stdafx.h"
#include	<stdlib.h>
#include        "tbtutil.h"
#include        "make.h"

void killmacros()
{
 struct macro *pm = macrohead, *tmp = NULL;
 do {
    if ( pm != NULL ) {
       tmp = pm->m_next;
       delete pm->m_sub;
       delete pm->m_val;
       delete pm->m_name;
       delete pm;
       if ( tmp != NULL )
          pm = tmp;
       }   
    } while ( tmp != NULL );
 macrohead = NULL;
}

/*****	do not include <ctypes.h> */

struct macro * macrohead;

/*****	get macro, do substitutions */

struct macro *getmp(char *name)
{
    register struct macro * rp;
    char * p;
    char * q;
    char * qq;
    char * qqq;
    char * sub1     = NULL;
    char * sub2     = NULL;
    char * a;

    if(0 != (p = strchr(name,':')))
    {
	sub1 = p+1;
	*p = '\0';
	sub2 = strchr(sub1,'=');
	if (sub2) *sub2++ = '\0';
	else sub2 = "";
    }

    for (rp = macrohead; rp; rp = rp->m_next)
	if (strcmp(name, rp->m_name) == 0)
	{
	    rp->m_sub = NULL;
	    if (sub1)
	    {
		a = (char _far *)memcalloc(LZ,"No memory for macro substitution");
		p = a;
		q = rp->m_val;
		while (NULL != (qq = strstr(q,sub1)))
		{
		    for (qqq = q; qqq < qq;)
			 *p++ = *qqq++;
		    q = qq + strlen(sub1);
		    qqq = sub2;
		    while (*qqq)
			 *p++ = *qqq++;
		}
		if (q != rp->m_val)
		{
		    strcpy(p,q);
		    rp->m_sub = a;
		}
		else
		    delete (char *)a;
	    }
	    return rp;
	}
    return (struct macro *)0;
}

/*****	Do the dirty work for expand */

void doexp(char **to, char *from,int* len,char * buf)
{
    register char * rp;
    register char * p;
    register char * q;
    register struct macro * mp;

    rp = from;
    p = *to;
    while (*rp)
    {
	if (*rp != '$')
	{
	    *p++ = *rp++;
	    (*len)--;
	}
	else
	{
	    q = buf;
	    if (*++rp == '{')
		while (*++rp && *rp != '}')
		    *q++ = *rp;
	    else if (*rp == '(')
		while (*++rp && *rp != ')')
		    *q++ = *rp;
	    else if (!*rp)
	    {
		*p++ = '$';
		break;
	    }
	    else
		*q++ = *rp;
	    *q = '\0';
	    if (*rp)
		rp++;
	    if (0 ==(mp = getmp(buf)))
		mp = setmacro(buf, "");
	    if (mp->m_flag & M_LOOPCHK)
		fatal("Macro %s cannot be expanded: infinite recursion", mp->m_name);
	    mp->m_flag = M_LOOPCHK;
	    *to = p;
	    if (mp->m_sub)
	    {
		doexp(to, mp->m_sub, len, buf);
		delete (char *)mp->m_sub;
		mp->m_sub=NULL;
	    }
	    else
		doexp(to, mp->m_val, len, buf);
	    p = *to;
	    mp->m_flag &= ~M_LOOPCHK;
	}
	if (*len <= 0)
	    error("Macro expansion too long");
    }
    *p = '\0';
    *to = p;
}

/*****	expand any macros in str */

void expand(char *str)
{
    static char a[LZ];
    static char b[LZ];
    char * p	    = str;
    int len	    = LZ-1;

    doexp(&p, strcpy(a,str), &len, b);
}


/*****	mark all M_ENV macros as permanent (M_PERM) */

void markmacros()
{
    register struct macro * rp;

    for (rp = macrohead; rp; rp = rp->m_next)
    {
	if (rp->m_flag & M_ENV)
	    rp->m_flag |= M_PERM;
    }
}

/*****	set macro value */

struct macro *setmacro(char *name, char* val)
{
    register struct macro * rp;
    register char * cp;
    register int i,j;
    static char buf[LZ];
    static char macerr[] = {
	"Cannot allocate memory for macro"};

    if (*name == '+')
    {
	name++;
	if ( (strlen(name) + strlen(val)) < 126)
	{
	    for (i = 0, j = 0; name[j]; ) buf[i++] = (char)(toupper(*(name+(j++))));
	    buf[i++] = '=';
	    for (j = 0; *(val+j); ) buf[i++] = *(val+(j++));
	    buf[i++] = '\0';
	    expand(buf);
	    }
    }

    /*****  replace macro definition if it exists  */
    /*****  don't let macros derived from external env. be replaced if -e given */

    for (rp = macrohead; rp; rp = rp->m_next)
	if (strcmp(name, rp->m_name) == 0)
	{
	    if (rp->m_flag & M_PERM)
		return rp;
	    delete (char *)rp->m_val;            /*  Free space from old  */
	    break;
	}

    if (!rp)				/*  If not defined, allocate space for new  */
    {
	rp = (struct macro *)memcalloc(sizeof (struct macro),macerr);
/*
 *	zeroed out in memcalloc
 *	 rp->m_sub = NULL;
 */
	rp->m_next = macrohead;
	macrohead = rp;
	cp  = (char _far *)memcalloc(strlen(name)+1,macerr);
	rp->m_name=strcpy(cp, name);
    }

    cp = (char _far *)memcalloc(strlen(val)+1,macerr);
    rp->m_val = strcpy(cp, val);	/*  Copy in new value  */
    rp->m_flag = macrotype;

    return rp;
}
