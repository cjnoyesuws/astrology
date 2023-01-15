/*************************************************************************
|									 |
|   MAKE.H                                                      29.04.89 |
|   MAKE Utility:  header file						 |
|									 |
*************************************************************************/
#ifndef MDOS
#ifndef MOS2
#define MDOS
#endif
#endif

#define uchar	    unsigned char
#define bool	    uchar
#ifndef _MAKEDECLONLY_
#undef  TRUE
#define TRUE	    (1)
#undef  FALSE
#define FALSE	    (0)
#undef  ERROR
#define ERROR	    (-1)
#define DEFN1	    "makefile"              /*  Default names  */
#define LIFNAME     "TEMP_LIF.TMP"
#define LZ	    (1024)		    /*	Line size  */
#define DOLLAR	    1			    /* special dollar processing */

#define PXNORMAL 0	    /* normal exit() arg */
#define PXERROR  1	    /* error exit() arg */



struct name
{
    struct name *	    n_next;	    /* Next in the list of names */
    char *		    n_name;	    /* Called */
    struct line *	    n_line;	    /* Dependencies */
    unsigned long	    n_time;	    /* Modify time of this name */
    uchar		    n_flag;	    /* Info about the name */
};

#define N_MARK		    0x01	    /* For cycle check */
#define N_DONE		    0x02	    /* Name looked at */
#define N_TARG		    0x04	    /* Name is a target */
#define N_PREC		    0x08	    /* Target is precious */
#define N_DYND		    0x10	    /* Name was made by dyndep */
#define N_DOUBLE	    0x20	    /* Double colon */

struct	line
{
    struct line *	    l_next;	    /* Next line (for ::) */
    struct depend *	    l_dep;	    /* Dependents for this line */
    struct cmd *	    l_cmd;	    /* Commands for this line */
};

struct	depend
{
    struct depend *	    d_next;	    /* Next dependent */
    struct name *	    d_name;	    /* Name of dependent */
};

struct	cmd
{
    struct cmd *	    c_next;	    /* Next command line */
    struct lif *	    c_lif;	    /* LIF lines for this command */
    char *		    c_cmd;	    /* Command line */
};

struct	lif
{
    struct lif *	    f_next;	    /* Next LIF line */
    char *		    f_lif;	    /* LIF line */
};

struct	macro
{
    struct macro *	    m_next;	    /* Next variable */
    char *		    m_name;	    /* Called ... */
    char *		    m_val;	    /* Its value */
    char *		    m_sub;	    /* Temp subst value */
    uchar		    m_flag;	    /* Infinite loop check */
};
#define M_DEFAULT	    0x00	    /* when not one of the following */
#define M_LOOPCHK	    0x01	    /* For loop check */
#define M_ENV		    0x02	    /* ex-environment macro */
#define M_PERM		    0x04	    /* not resetable */

extern char *		myname;
extern struct name	namehead;
extern struct macro *	macrohead;
extern struct name *	firstname;
extern bool		silent;
extern bool		ignore;
extern bool		rules;
extern bool		dotouch;
extern bool		quest;
extern bool		domake;
extern bool		display;
extern char		dollarbuf[];
extern char		str1[];
extern char		str2[];
extern int		lineno;
extern uchar		macrotype;
extern unsigned char	makeos2;
extern char *makefile;

extern FILE *		ifile[4];
extern int		fln[4];
extern char		fname[4][80];
extern int		nestlvl;
extern CATCHBUF j;
#endif
extern	void		check(struct name *np);
extern	void		checklif(struct cmd *cp);
extern	void		circh(void);
extern	void		cleardynflag(struct name *np);
extern	void		docmds1(struct name *np,struct line *lp);
extern	void		docmds(struct name *np);
extern	void		dodisp(char *name,long t);
extern	void		doexp(char * *to,char *from,int *len,char *buf);
extern	char *		dollar(char *);
extern	void		dosetcmd(char *p);
extern	int		dosh(char *p,int shell);
extern	int		dos_internal(char *s);
extern	bool		dyndep(struct name *np);
extern	void  _cdecl	error(char *msg,...);
extern	void		expand(char *str);
extern	void		ifeoc(void);
extern	void		ifeof(void);
extern	int		ifproc(char *s,int n);
extern	void		input(void);
extern	int		istrue(char *s);
extern	void  _cdecl	fatal(char *msg, ...);
extern	bool		getline(char *str);
extern	struct macro *	getmp(char *name);
extern	char *		gettok(char * *ptr);
extern	void		killlif(void);
extern  int  _cdecl    make_main(int argc,char * *argv);
extern	int		make(struct name *np,int level);
extern	void		make1(struct name *np,struct line *lp,struct depend *qdp);
extern	void		makelif(struct cmd *cp);
extern	void		makerules(void);
extern	void		markmacros(void);
extern	void	      * memcalloc(int amnt,char *errmsg);
extern	void		modtime(struct name *np);
extern	struct name *	newname(char *name);
extern	struct depend * newdep(struct name *np,struct depend *dp);
extern	struct cmd *	newcmd(char *str,struct cmd *cp,struct cmd * *crp);
extern	struct lif *	newlif(char *str,struct lif *lp);
extern	void		newline(struct name *np,struct depend *dp,struct cmd *cp,int flag);
extern	void		precious(void);
extern	void		prt(void);
extern	char *		pstrstr(char *, char *);
extern	void		setdmacros(struct name *np,struct depend *qdp);
extern	struct macro *	setmacro(char *name,char *val);
extern	char *		suffix(char *name);
extern	void		touch(struct name *np);
extern  void            usage(void);
extern  int             doDosCmd( char *fnc, char *p1, char *p2 );
extern  int             win_System( char *p );
extern  void            killcmd( struct  cmd *cp );
extern  void            killdepend(struct depend * pd );
extern  void            killline(struct line *lp);
extern  void            killname(struct name *np, int del);
extern  void            killmacros();
extern  void            killlif(struct lif * lp);
extern  void            cleanupmake(void);
extern  int 			checkDllFunc(char *fnc);