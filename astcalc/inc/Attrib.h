
#if (!defined(ATTRIB))
#define ATTRIB 1

#define ATTRIB_LEN 45

typedef struct FIL_ATTRIB {
	CString bold_on;
	CString bold_off;
	CString uscore_on;
	CString uscore_off;
	CString head_on;
	CString head_off;
	} FIL_ATTRIB;

extern FIL_ATTRIB global_attribs;

#define S_NORM       '\x1b'
#define S_BOLD       '\x1f'
#define S_ULIN       '\x01'

/* printer string constants are in charcons.c */

#define F_BOLD_ON    "[BOLD]"
#define F_BOLD_OFF   "[X-BOLD]"
#define F_SCOR_ON    "[USCORE]"
#define F_SCOR_OFF   "[X-USCORE]"
#define F_HEAD_ON    "[HEAD]"
#define F_HEAD_OFF   "[X-HEAD]"


#define BOLD_ON_C    '{'
#define BOLD_OFF_C   '}'
#define SCOR_ON_C    '<'
#define SCOR_OFF_C   '>'
#define HEAD_ON_C    '['
#define HEAD_OFF_C   ']'


#define F_SOFTCR     '\1'
#define F_HARDCR     '\2'
#define F_STARTUL    '\3'
#define F_ENDUL      '\4'
#define F_STARTBD    '\5'
#define F_ENDBD      '\6'
#define F_STARTHD    '\7'
#define F_ENDHD      '\10'
#define F_TAB        '\11'
#define F_BINARY     '\13'
#endif
