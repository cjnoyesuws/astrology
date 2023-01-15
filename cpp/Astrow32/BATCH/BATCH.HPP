

struct ArgType {
      zString data;
      int get() { return( (int) atoi( (char *)data ) ); }
      zString &get() { return( data.buf ); }
      void set( char *buf ) { data = buf; }
      int read( FILE *stream );
      int read( char *buf );
      }

class Vars {
ArgType array[10];
public:
      Vars() {}
      ~Vars() {}
      ArgType &get(int i) { assert(i>0 && i < 10 ); return(array[i]); }
      set( int i, ArgType &a ) { assert(i>0 && i < 10 ); array[i] = a; }
      saveToIni();
      getFromIni();
      }

#define _MAIN_ 0
#define _TEXT_ 1
#define _GRAP_ 2

typedef struct CMD {
	char name[20];
	int cmd_base;
	int list;
	int args;
	int (*setup)(ArgType *ar, CMD *cm, zEvent *e);
	CommandProc exec;
	int (*proc)( FILE *stream, CMD *cm );
	int (*cmd)( ArgType *arg, CMD *cm );
	} CMD;

class BatchCommand {
CMD *cmdf;
zEvent e;
ArgType ar;
public:
      BatchCommand(CMD *pC) {cmdf=pC;}
      BatchCommand() {}
      int getList() { return list; }
      int hasArgs() { return args; }
      int CommandBase() { return cmd_base };
      int hasSetup() { return(cmdf->setup!=NULL); }
      int hasProc() { return(cmdf->proc!=NULL); }
      int hasExec() { return(cmdf->exec!=NULL); }
      int hasCmd() { return(cmdf->cmd!=NULL); }
      int doSetup() { return( cmdf->setup(&ar, cmdf, &e) ); }
      int doCommand() { return( cmdf->cmd(&ar, cmdf) ); }
      int doProc(FILE *stream) { return( cmdf->cmd(stream, cmdf) ); }
      int doExec(zWindow *w) { return( w->(*cmdf->setup)(&ar, cmdf, &e) );  }
      };

extern char *parseStr( char *sbuf, char *fmt, char *del, char *var  );
extern char *parseInt( char *sbuf, char *fmt, char *del int *var );
extern char *parsef( char *sbuf, char *fmt, char *del, ... );
