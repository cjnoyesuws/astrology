
typedef int (CALLBACK *LOGPROC)(LPVOID, LPCSTR);
typedef void (CALLBACK *YIELDPROC)(int);

extern void FAR setHinstance( HINSTANCE h );
extern void SetYieldProc(YIELDPROC data);

extern int FAR getFunctionRet();
extern int FAR execFunction(char *lib, char *func, char *p1=NULL, char *p2=NULL,
    char *p3=NULL, char *p4=NULL, char *p5=NULL, char *p6=NULL,
    char *p7=NULL, char *p8=NULL  );
extern void SetupLogProc(LOGPROC proc);
extern void FAR SetupLog(LPVOID data);
extern int FAR LogOutput( LPCSTR text );
extern int FAR LogPrintf(LPCSTR fmt, ...  );
extern int FAR LogPutc(char c);
extern int alert_box(char *title, char *fmt, ... );
extern int alert_box_ext(char *title, UINT flags, LPCSTR fmt, ... );
extern VOID do_mem_error(int fatal);
extern VOID do_error( char *file );
extern int valert_box_ext( LPCSTR title, UINT options, LPCSTR fmt, va_list marker );
extern VOID dllYield();
extern void getConvertTextSettings( int &src, int &edit, int &dst, int &cvt );

#define _OEM_T_  0
#define _SRC_T_  1
#define _EDT_T_  2
#define _DST_T_  3
#define _CVT_T_  4
#define _ANS_T_  5
#define _INI_T_  -1
extern void doConvertText( char *buf, int stype, int dtype, int dst=-1 );



#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )
