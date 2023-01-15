#include "stdafx.h"
#include "make.h"


void killcmd( struct  cmd *cp )
{
 struct  cmd *tmp = NULL;

 do {
    tmp = cp->c_next;
    if ( cp->c_cmd != NULL )
       delete cp->c_cmd;
    if ( cp->c_lif != NULL ) {
       killlif(cp->c_lif);
       cp->c_lif = NULL;
       }
    delete cp;
    if ( tmp != NULL )
       cp = tmp;
    } while ( tmp != NULL );
}

void killdepend(struct depend * pd )
{
 struct depend * tmp = NULL;
 do {
    tmp = pd->d_next;
    //if ( pd->d_name != NULL )
    //  killname( pd->d_name, 1 );
    delete pd;
    if ( tmp != NULL )
       pd = tmp;
    } while( tmp != NULL );

}

void killline(struct line *lp)
{
 struct line * tmp = NULL;

 do {
    tmp = lp->l_next;
    if ( lp->l_dep != NULL )
       killdepend( lp->l_dep );
    if ( lp->l_cmd != NULL )
       killcmd( lp->l_cmd );
    delete lp;
    if ( tmp != NULL )
       lp = tmp;
    } while( tmp != NULL );
}


void killname(struct name *np, int del)
{
 struct name * tmp = NULL;

 do {
    tmp = np->n_next;
    if ( np->n_line != NULL )
       killline( np->n_line );
    if ( np->n_name != NULL )
       delete np->n_name;
    if ( del )
       delete np;
    if ( tmp != NULL )
       np = tmp;
    } while( tmp != NULL );
}
