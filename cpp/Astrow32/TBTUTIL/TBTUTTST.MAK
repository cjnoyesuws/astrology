# Microsoft Visual C++ generated build script - Do not modify

PROJ = TBTUTTST
DEBUG = 1
PROGTYPE = 0
CALLER = 
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
FIRSTCPP = TBTUTTST.CPP
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Gf /Zi /AL /Od /D "Z_NP"="1" /D "_DEBUG" /FR /GA /Fd"TBTUTTST.PDB"
CFLAGS_R_WEXE = /nologo /G2 /Gy /W3 /Gf /AL /Gx- /O1 /D "Z_NP"="1" /D "NDEBUG" /FR /GA 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = oldnames libw llibcew tbtcvtut commdlg.lib 
LIBS_R_WEXE = oldnames libw llibcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = TBTUTTST.DEF
OBJS_EXT = 
LIBS_EXT = ..\..\ZAPP\LIB\ZAPPC7.LIB 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = TBTUTTST.SBR


ZAPPC7_DEP = 

TBTUTTST_DEP = d:\zapp\zapp.hpp \
	d:\zapp\zapph\presys.hpp \
	d:\zapp\zapph\defs.hpp \
	d:\zapp\zapph\enumdef.hpp \
	d:\zapp\zapph\assert.hpp \
	d:\zapp\zapph\memmgr.hpp \
	d:\zapp\zapph\darray.hpp \
	d:\zapp\zapph\persist.hpp \
	d:\zapp\zapph\llink.hpp \
	d:\zapp\zapph\zslist.hpp \
	d:\zapp\zapph\string.hpp \
	d:\zapp\zapph\general.hpp \
	d:\zapp\zapph\general.inl \
	d:\zapp\zapph\events.hpp \
	d:\zapp\zapph\events.inl \
	d:\zapp\zapph\sizer.hpp \
	d:\zapp\zapph\sizer.inl \
	d:\zapp\zapph\device.hpp \
	d:\zapp\zapph\display.hpp \
	d:\zapp\zapph\display.inl \
	d:\zapp\zapph\text.hpp \
	d:\zapp\zapph\dialog.hpp \
	d:\zapp\zapph\control.hpp \
	d:\zapp\zapph\control.inl \
	d:\zapp\zapph\zapp.inl \
	d:\zapp\zapph\clip.hpp \
	d:\zapp\zapph\comdlg.hpp \
	d:\zapp\zapph\editor.hpp \
	d:\zapp\zapph\scroller.hpp \
	d:\zapp\zapph\formdlg.hpp \
	d:\wpro\inc\tbtutil.h


TBTUTTST_RCDEP = d:\wpro\tbtutil\icon1.ico


all:	$(PROJ).EXE $(PROJ).BSC

TBTUTTST.OBJ:	TBTUTTST.CPP $(TBTUTTST_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c TBTUTTST.CPP

TBTUTTST.RES:	TBTUTTST.RC $(TBTUTTST_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r TBTUTTST.RC


$(PROJ).EXE::	TBTUTTST.RES

$(PROJ).EXE::	TBTUTTST.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
TBTUTTST.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
d:\zapp\lib\+
d:\vicwin\+
D:\msvc\lib\+
D:\msvc\mfc\lib\+
..\..\ZAPP\LIB\ZAPPC7.LIB+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) TBTUTTST.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	TBTUTTST.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) TBTUTTST.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
