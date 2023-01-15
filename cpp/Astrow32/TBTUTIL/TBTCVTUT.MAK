# Microsoft Visual C++ generated build script - Do not modify

PROJ = TBTCVTUT
DEBUG = 0
PROGTYPE = 1
CALLER = TBTUTTST
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\WPRO\TBTUTIL\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = 3DBLDTXT.CPP
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /Gy /W3 /Gf /Zi /ALw /Gx- /YX"pch.cpp" /Od /D "_DEBUG" /D "BSR" /FR /GD /GEe /Fd"TBTCVTUT.PDB"   /Fp"TBTCVTUT.PCH" /GEd
CFLAGS_R_WDLL = /nologo /G2 /Gy /W3 /Gf /ALw /YX"pch.cpp" /O2 /Ob1 /D "NDEBUG" /D "BSR" /FR /GD /GEe /Fp"TBTCVTUT.PCH"
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /SEG:700 /ALIGN:16 /ONERROR:NOEXE /CO /MAP /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = oldnames libw ldllcew commdlg.lib
LIBS_R_WDLL = oldnames libw ldllcew commdlg.lib
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = TBTCVTUT.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WDLL)
LFLAGS = $(LFLAGS_D_WDLL)
LIBS = $(LIBS_D_WDLL)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WDLL)
LFLAGS = $(LFLAGS_R_WDLL)
LIBS = $(LIBS_R_WDLL)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = 3DBLDTXT.SBR \
		AMITOAST.SBR \
		ARRAY.SBR \
		ASCTOAST.SBR \
		AST2AMI.SBR \
		AST2ASC.SBR \
		AST2RTF.SBR \
		AST2WP4.SBR \
		AST2WP5.SBR \
		AST2WS.SBR \
		ASTTODOC.SBR \
		BUILDRPT.SBR \
		BUILDTXT.SBR \
		COMPRESS.SBR \
		EXECER.SBR \
		LIBMAIN.SBR \
		LOGTEXT.SBR \
		MKBSR.SBR \
		MKRBSR.SBR \
		MKSTRB.SBR \
		MSWTOAST.SBR \
		RTFTOAST.SBR \
		STRTABLE.SBR \
		STRX.SBR \
		TEXTWRAP.SBR \
		WORDS.SBR \
		WP4TOAST.SBR \
		WP5TOAST.SBR \
		WPINTL.SBR \
		WSTOAST.SBR \
		PCH.SBR \
		ERRORS.SBR \
		CHARCONS.SBR \
		AST2WP6.SBR \
		WP6TOAST.SBR


3DBLDTXT_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp \
	d:\wpro\inc\array.hpp


AMITOAST_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


ARRAY_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp \
	d:\wpro\inc\array.hpp


ASCTOAST_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


AST2AMI_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


AST2ASC_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


AST2RTF_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


AST2WP4_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


AST2WP5_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


AST2WS_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


ASTTODOC_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


BUILDRPT_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


BUILDTXT_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp \
	d:\wpro\inc\array.hpp


COMPRESS_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


EXECER_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


LIBMAIN_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


LOGTEXT_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


MKBSR_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


MKRBSR_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


MKSTRB_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp \
	d:\wpro\inc\strtab.h


MSWTOAST_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


RTFTOAST_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp \
	d:\wpro\inc\rtf.h


STRTABLE_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp \
	d:\wpro\inc\strtab.h


STRX_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


TEXTWRAP_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


WORDS_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


WP4TOAST_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


WP5TOAST_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\wp5.h


WPINTL_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


WSTOAST_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


PCH_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


ERRORS_DEP = d:\wpro\inc\errors.fns \
	d:\wpro\tbt\charcons.h


CHARCONS_DEP = d:\wpro\tbt\charcons.h


AST2WP6_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\builder.hpp


WP6TOAST_DEP = d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\wp5.h


all:	$(PROJ).DLL $(PROJ).BSC

3DBLDTXT.OBJ:	3DBLDTXT.CPP $(3DBLDTXT_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c 3DBLDTXT.CPP

AMITOAST.OBJ:	AMITOAST.CPP $(AMITOAST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c AMITOAST.CPP

ARRAY.OBJ:	ARRAY.CPP $(ARRAY_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ARRAY.CPP

ASCTOAST.OBJ:	ASCTOAST.CPP $(ASCTOAST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ASCTOAST.CPP

AST2AMI.OBJ:	AST2AMI.CPP $(AST2AMI_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c AST2AMI.CPP

AST2ASC.OBJ:	AST2ASC.CPP $(AST2ASC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c AST2ASC.CPP

AST2RTF.OBJ:	AST2RTF.CPP $(AST2RTF_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c AST2RTF.CPP

AST2WP4.OBJ:	AST2WP4.CPP $(AST2WP4_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c AST2WP4.CPP

AST2WP5.OBJ:	AST2WP5.CPP $(AST2WP5_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c AST2WP5.CPP

AST2WS.OBJ:	AST2WS.CPP $(AST2WS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c AST2WS.CPP

ASTTODOC.OBJ:	ASTTODOC.CPP $(ASTTODOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ASTTODOC.CPP

BUILDRPT.OBJ:	BUILDRPT.CPP $(BUILDRPT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c BUILDRPT.CPP

BUILDTXT.OBJ:	BUILDTXT.CPP $(BUILDTXT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c BUILDTXT.CPP

COMPRESS.OBJ:	COMPRESS.CPP $(COMPRESS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c COMPRESS.CPP

EXECER.OBJ:	EXECER.CPP $(EXECER_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EXECER.CPP

LIBMAIN.OBJ:	LIBMAIN.CPP $(LIBMAIN_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c LIBMAIN.CPP

LOGTEXT.OBJ:	LOGTEXT.CPP $(LOGTEXT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c LOGTEXT.CPP

MKBSR.OBJ:	MKBSR.CPP $(MKBSR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MKBSR.CPP

MKRBSR.OBJ:	MKRBSR.CPP $(MKRBSR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MKRBSR.CPP

MKSTRB.OBJ:	MKSTRB.CPP $(MKSTRB_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MKSTRB.CPP

MSWTOAST.OBJ:	MSWTOAST.CPP $(MSWTOAST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MSWTOAST.CPP

RTFTOAST.OBJ:	RTFTOAST.CPP $(RTFTOAST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RTFTOAST.CPP

STRTABLE.OBJ:	STRTABLE.CPP $(STRTABLE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STRTABLE.CPP

STRX.OBJ:	STRX.CPP $(STRX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STRX.CPP

TEXTWRAP.OBJ:	TEXTWRAP.CPP $(TEXTWRAP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TEXTWRAP.CPP

WORDS.OBJ:	WORDS.CPP $(WORDS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c WORDS.CPP

WP4TOAST.OBJ:	WP4TOAST.CPP $(WP4TOAST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c WP4TOAST.CPP

WP5TOAST.OBJ:	WP5TOAST.CPP $(WP5TOAST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c WP5TOAST.CPP

WPINTL.OBJ:	WPINTL.CPP $(WPINTL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c WPINTL.CPP

WSTOAST.OBJ:	WSTOAST.CPP $(WSTOAST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c WSTOAST.CPP

PCH.OBJ:	PCH.CPP $(PCH_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PCH.CPP

ERRORS.OBJ:	..\TBT\ERRORS.CPP $(ERRORS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\TBT\ERRORS.CPP

CHARCONS.OBJ:	..\TBT\CHARCONS.CPP $(CHARCONS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\TBT\CHARCONS.CPP

AST2WP6.OBJ:	AST2WP6.CPP $(AST2WP6_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c AST2WP6.CPP

WP6TOAST.OBJ:	WP6TOAST.CPP $(WP6TOAST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c WP6TOAST.CPP


$(PROJ).DLL::	3DBLDTXT.OBJ AMITOAST.OBJ ARRAY.OBJ ASCTOAST.OBJ AST2AMI.OBJ AST2ASC.OBJ \
	AST2RTF.OBJ AST2WP4.OBJ AST2WP5.OBJ AST2WS.OBJ ASTTODOC.OBJ BUILDRPT.OBJ BUILDTXT.OBJ \
	COMPRESS.OBJ EXECER.OBJ LIBMAIN.OBJ LOGTEXT.OBJ MKBSR.OBJ MKRBSR.OBJ MKSTRB.OBJ MSWTOAST.OBJ \
	RTFTOAST.OBJ STRTABLE.OBJ STRX.OBJ TEXTWRAP.OBJ WORDS.OBJ WP4TOAST.OBJ WP5TOAST.OBJ \
	WPINTL.OBJ WSTOAST.OBJ PCH.OBJ ERRORS.OBJ CHARCONS.OBJ AST2WP6.OBJ WP6TOAST.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
3DBLDTXT.OBJ +
AMITOAST.OBJ +
ARRAY.OBJ +
ASCTOAST.OBJ +
AST2AMI.OBJ +
AST2ASC.OBJ +
AST2RTF.OBJ +
AST2WP4.OBJ +
AST2WP5.OBJ +
AST2WS.OBJ +
ASTTODOC.OBJ +
BUILDRPT.OBJ +
BUILDTXT.OBJ +
COMPRESS.OBJ +
EXECER.OBJ +
LIBMAIN.OBJ +
LOGTEXT.OBJ +
MKBSR.OBJ +
MKRBSR.OBJ +
MKSTRB.OBJ +
MSWTOAST.OBJ +
RTFTOAST.OBJ +
STRTABLE.OBJ +
STRX.OBJ +
TEXTWRAP.OBJ +
WORDS.OBJ +
WP4TOAST.OBJ +
WP5TOAST.OBJ +
WPINTL.OBJ +
WSTOAST.OBJ +
PCH.OBJ +
ERRORS.OBJ +
CHARCONS.OBJ +
AST2WP6.OBJ +
WP6TOAST.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
d:\zapp\lib\+
d:\vicwin\+
D:\msvc\lib\+
D:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) $@
	implib /nowep $(PROJ).LIB $(PROJ).DLL


run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
