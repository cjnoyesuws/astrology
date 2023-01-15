# Microsoft Visual C++ generated build script - Do not modify

PROJ = TBT
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG 
R_RCDEFINES = /dNDEBUG 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\WPRO\TBT\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = PCH.CPP     
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Gf /Zi /AL /Od /D "Z_NP"="1" /D "_DEBUG" /FR /GA /Fd"TBT.PDB" /D "_WINTBT_"
CFLAGS_R_WEXE = /nologo /G2 /W3 /Gf /AL /O1 /D "Z_NP"="1" /D "NDEBUG" /FR /GA /D "_WINTBT_"
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /SEG:500 /ALIGN:16 /ONERROR:NOEXE /CO /MAP  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /SEG:500 /ALIGN:16 /ONERROR:NOEXE /MAP  
LIBS_D_WEXE = ..\tbtutil\tbtcvtut ..\astrengn oldnames libw llibcew commdlg.lib toolhelp.lib 
LIBS_R_WEXE = ..\tbtutil\tbtcvtut ..\astrengn oldnames libw llibcew commdlg.lib toolhelp.lib 
RCFLAGS = /nologo 
RESFLAGS = /nologo 
RUNFLAGS = 
DEFFILE = TBT.DEF
OBJS_EXT = 
LIBS_EXT = F:\ZAPP\LIB\ZAPPC7.LIB 
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
SBRS = PCH.SBR \
		ATEXTEDT.SBR \
		CMDTAIL.SBR \
		CONVERT.SBR \
		DOSCMD.SBR \
		ENDETAB.SBR \
		FILEARY.SBR \
		HELPCMD.SBR \
		MAIN.SBR \
		MAKE.SBR \
		MAKEMAIN.SBR \
		MKCHECK.SBR \
		MKDEL.SBR \
		MKIFPROC.SBR \
		MKINPUT.SBR \
		MKMACRO.SBR \
		MKREADER.SBR \
		OPTCMD.SBR \
		REPRTEDT.SBR \
		RTEXTEDT.SBR \
		RULES.SBR \
		SYMBOL.SBR \
		TBTFRAME.SBR \
		TBTOPTN.SBR \
		TBTTITLE.SBR \
		TDIREC.SBR \
		TEXTBARY.SBR \
		TEXTBLOC.SBR \
		TEXTEDIT.SBR \
		TEXTTYPE.SBR \
		TEXTXREF.SBR \
		TFILECMD.SBR \
		TFILELST.SBR \
		TSETPATH.SBR \
		WINCMD.SBR


PCH_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp


ATEXTEDT_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\inc\fieldrng.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\tbt\symbol.hpp \
	d:\wpro\tbt\textbloc.hpp \
	d:\wpro\tbt\reprtedt.hpp \
	d:\wpro\tbt\rtextedt.hpp \
	d:\wpro\tbt\atextedt.hpp


CMDTAIL_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	f:\zapp\zapph\mdi.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\tbt\tdirec.hpp \
	d:\wpro\tbt\tbtoptn.hpp \
	d:\wpro\inc\paths.hpp \
	d:\wpro\tbt\tbtframe.hpp \
	d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\errors.fns \
	d:\wpro\tbt\make.h


CONVERT_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	f:\zapp\zapph\mdi.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\tbt\tbtoptn.hpp \
	d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\msg.hpp


DOSCMD_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\inc\tbtutil.h


ENDETAB_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp


FILEARY_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\tbt\tdirec.hpp \
	d:\wpro\tbt\fileary.hpp \
	d:\wpro\inc\errors.fns


HELPCMD_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	f:\zapp\zapph\mdi.hpp \
	d:\wpro\tbt\tbtframe.hpp \
	d:\wpro\inc\paths.hpp \
	d:\wpro\inc\acombbox.hpp


MAIN_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	f:\zapp\zapph\mdi.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\tbt\fileary.hpp \
	d:\wpro\tbt\tdirec.hpp \
	d:\wpro\tbt\tbtoptn.hpp \
	d:\wpro\tbt\tbtframe.hpp \
	d:\wpro\inc\title.hpp


MAKE_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\inc\tbtutil.h \
	d:\wpro\tbt\make.h


MAKEMAIN_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\inc\tbtutil.h \
	d:\wpro\tbt\make.h


MKCHECK_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\inc\tbtutil.h \
	d:\wpro\tbt\make.h


MKDEL_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\tbt\make.h


MKIFPROC_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\inc\tbtutil.h \
	d:\wpro\tbt\make.h


MKINPUT_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\inc\tbtutil.h \
	d:\wpro\tbt\make.h


MKMACRO_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\inc\tbtutil.h \
	d:\wpro\tbt\make.h


MKREADER_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\inc\tbtutil.h \
	d:\wpro\tbt\make.h


OPTCMD_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	f:\zapp\zapph\mdi.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\inc\paths.hpp \
	d:\wpro\inc\charcons.h \
	d:\wpro\tbt\tbtframe.hpp \
	d:\wpro\tbt\tdirec.hpp \
	d:\wpro\tbt\tbtoptn.hpp


REPRTEDT_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\inc\fieldrng.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\tbt\symbol.hpp \
	d:\wpro\tbt\textbloc.hpp \
	d:\wpro\tbt\reprtedt.hpp \
	d:\wpro\inc\msg.hpp \
	d:\wpro\tbt\tbtoptn.hpp


RTEXTEDT_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\inc\fieldrng.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\tbt\symbol.hpp \
	d:\wpro\tbt\textbloc.hpp \
	d:\wpro\tbt\reprtedt.hpp \
	d:\wpro\tbt\rtextedt.hpp


RULES_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\inc\tbtutil.h \
	d:\wpro\tbt\make.h


SYMBOL_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\tbt\symbol.hpp \
	d:\wpro\inc\errors.fns


TBTFRAME_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	f:\zapp\zapph\mdi.hpp \
	d:\wpro\tbt\tbtframe.hpp \
	d:\wpro\inc\title.hpp \
	d:\wpro\inc\paths.hpp


TBTOPTN_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\inc\dialogs.h \
	d:\wpro\inc\helpid.h \
	d:\wpro\inc\attrib.h \
	d:\wpro\inc\inifile.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\tbt\tbtoptn.hpp \
	d:\wpro\inc\basedcs.h


TBTTITLE_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\inc\inifile.hpp \
	d:\wpro\inc\basedcs.h \
	d:\wpro\inc\title.hpp \
	d:\wpro\inc\paths.hpp


TDIREC_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\inc\dialogs.h \
	d:\wpro\inc\helpid.h \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\tbt\tdirec.hpp \
	d:\wpro\inc\basedcs.h \
	d:\wpro\inc\inifile.hpp \
	d:\wpro\inc\acombbox.hpp


TEXTBARY_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\tbt\symbol.hpp \
	d:\wpro\tbt\textbloc.hpp \
	d:\wpro\inc\errors.fns


TEXTBLOC_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\tbt\symbol.hpp \
	d:\wpro\tbt\textbloc.hpp \
	d:\wpro\inc\errors.fns


TEXTEDIT_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	f:\zapp\zapph\mdi.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\inc\paths.hpp \
	d:\wpro\tbt\textedit.hpp \
	d:\wpro\inc\astromn.h \
	d:\wpro\inc\errors.fns \
	d:\wpro\inc\menuutl.hpp \
	d:\wpro\tbt\tbtoptn.hpp


TEXTTYPE_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\tbt\textbloc.h \
	d:\wpro\inc\errors.fns


TEXTXREF_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\tbt\symbol.hpp \
	d:\wpro\tbt\textbloc.hpp


TFILECMD_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	f:\zapp\zapph\mdi.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\inc\fieldrng.hpp \
	d:\wpro\inc\paths.hpp \
	d:\wpro\tbt\symbol.hpp \
	d:\wpro\tbt\textbloc.hpp \
	d:\wpro\tbt\fileary.hpp \
	d:\wpro\tbt\tfilelst.hpp \
	d:\wpro\tbt\reprtedt.hpp \
	d:\wpro\tbt\rtextedt.hpp \
	d:\wpro\tbt\atextedt.hpp \
	d:\wpro\tbt\textedit.hpp \
	d:\wpro\tbt\tbtoptn.hpp \
	d:\wpro\tbt\tbtframe.hpp


TFILELST_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\tbt\fileary.hpp \
	d:\wpro\tbt\tfilelst.hpp \
	d:\wpro\inc\inifile.hpp \
	d:\wpro\inc\errors.fns


TSETPATH_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	f:\zapp\zapph\mdi.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\tbt\tdirec.hpp \
	d:\wpro\inc\paths.hpp


WINCMD_DEP = f:\zapp\zapp.hpp \
	f:\zapp\zapph\presys.hpp \
	f:\zapp\zapph\defs.hpp \
	f:\zapp\zapph\enumdef.hpp \
	f:\zapp\zapph\assert.hpp \
	f:\zapp\zapph\memmgr.hpp \
	f:\zapp\zapph\darray.hpp \
	f:\zapp\zapph\persist.hpp \
	f:\zapp\zapph\llink.hpp \
	f:\zapp\zapph\zslist.hpp \
	f:\zapp\zapph\string.hpp \
	f:\zapp\zapph\general.hpp \
	f:\zapp\zapph\general.inl \
	f:\zapp\zapph\events.hpp \
	f:\zapp\zapph\events.inl \
	f:\zapp\zapph\sizer.hpp \
	f:\zapp\zapph\sizer.inl \
	f:\zapp\zapph\device.hpp \
	f:\zapp\zapph\display.hpp \
	f:\zapp\zapph\display.inl \
	f:\zapp\zapph\text.hpp \
	f:\zapp\zapph\dialog.hpp \
	f:\zapp\zapph\control.hpp \
	f:\zapp\zapph\control.inl \
	f:\zapp\zapph\zapp.inl \
	f:\zapp\zapph\clip.hpp \
	f:\zapp\zapph\comdlg.hpp \
	f:\zapp\zapph\editor.hpp \
	f:\zapp\zapph\scroller.hpp \
	f:\zapp\zapph\formdlg.hpp \
	f:\zapp\zapph\mdi.hpp \
	d:\wpro\inc\paths.hpp \
	d:\wpro\inc\charcons.h \
	d:\wpro\tbt\tbtframe.hpp


ZAPPC7_DEP = 

all:	$(PROJ).EXE $(PROJ).BSC

PCH.OBJ:	PCH.CPP $(PCH_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c PCH.CPP

ATEXTEDT.OBJ:	ATEXTEDT.CPP $(ATEXTEDT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ATEXTEDT.CPP

CMDTAIL.OBJ:	CMDTAIL.CPP $(CMDTAIL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CMDTAIL.CPP

CONVERT.OBJ:	CONVERT.CPP $(CONVERT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CONVERT.CPP

DOSCMD.OBJ:	DOSCMD.CPP $(DOSCMD_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DOSCMD.CPP

ENDETAB.OBJ:	ENDETAB.CPP $(ENDETAB_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ENDETAB.CPP

FILEARY.OBJ:	FILEARY.CPP $(FILEARY_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c FILEARY.CPP

HELPCMD.OBJ:	HELPCMD.CPP $(HELPCMD_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c HELPCMD.CPP

MAIN.OBJ:	MAIN.CPP $(MAIN_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAIN.CPP

MAKE.OBJ:	MAKE.CPP $(MAKE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAKE.CPP

MAKEMAIN.OBJ:	MAKEMAIN.CPP $(MAKEMAIN_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAKEMAIN.CPP

MKCHECK.OBJ:	MKCHECK.CPP $(MKCHECK_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MKCHECK.CPP

MKDEL.OBJ:	MKDEL.CPP $(MKDEL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MKDEL.CPP

MKIFPROC.OBJ:	MKIFPROC.CPP $(MKIFPROC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MKIFPROC.CPP

MKINPUT.OBJ:	MKINPUT.CPP $(MKINPUT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MKINPUT.CPP

MKMACRO.OBJ:	MKMACRO.CPP $(MKMACRO_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MKMACRO.CPP

MKREADER.OBJ:	MKREADER.CPP $(MKREADER_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MKREADER.CPP

OPTCMD.OBJ:	OPTCMD.CPP $(OPTCMD_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c OPTCMD.CPP

REPRTEDT.OBJ:	REPRTEDT.CPP $(REPRTEDT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c REPRTEDT.CPP

RTEXTEDT.OBJ:	RTEXTEDT.CPP $(RTEXTEDT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RTEXTEDT.CPP

RULES.OBJ:	RULES.CPP $(RULES_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RULES.CPP

SYMBOL.OBJ:	SYMBOL.CPP $(SYMBOL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SYMBOL.CPP

TBTFRAME.OBJ:	TBTFRAME.CPP $(TBTFRAME_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TBTFRAME.CPP

TBTOPTN.OBJ:	TBTOPTN.CPP $(TBTOPTN_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TBTOPTN.CPP

TBTTITLE.OBJ:	TBTTITLE.CPP $(TBTTITLE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TBTTITLE.CPP

TDIREC.OBJ:	TDIREC.CPP $(TDIREC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TDIREC.CPP

TEXTBARY.OBJ:	TEXTBARY.CPP $(TEXTBARY_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TEXTBARY.CPP

TEXTBLOC.OBJ:	TEXTBLOC.CPP $(TEXTBLOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TEXTBLOC.CPP

TEXTEDIT.OBJ:	TEXTEDIT.CPP $(TEXTEDIT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TEXTEDIT.CPP

TEXTTYPE.OBJ:	TEXTTYPE.CPP $(TEXTTYPE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TEXTTYPE.CPP

TEXTXREF.OBJ:	TEXTXREF.CPP $(TEXTXREF_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TEXTXREF.CPP

TFILECMD.OBJ:	TFILECMD.CPP $(TFILECMD_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TFILECMD.CPP

TFILELST.OBJ:	TFILELST.CPP $(TFILELST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TFILELST.CPP

TSETPATH.OBJ:	TSETPATH.CPP $(TSETPATH_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TSETPATH.CPP

WINCMD.OBJ:	WINCMD.CPP $(WINCMD_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c WINCMD.CPP


$(PROJ).EXE::	PCH.OBJ ATEXTEDT.OBJ CMDTAIL.OBJ CONVERT.OBJ DOSCMD.OBJ ENDETAB.OBJ \
	FILEARY.OBJ HELPCMD.OBJ MAIN.OBJ MAKE.OBJ MAKEMAIN.OBJ MKCHECK.OBJ MKDEL.OBJ MKIFPROC.OBJ \
	MKINPUT.OBJ MKMACRO.OBJ MKREADER.OBJ OPTCMD.OBJ REPRTEDT.OBJ RTEXTEDT.OBJ RULES.OBJ \
	SYMBOL.OBJ TBTFRAME.OBJ TBTOPTN.OBJ TBTTITLE.OBJ TDIREC.OBJ TEXTBARY.OBJ TEXTBLOC.OBJ \
	TEXTEDIT.OBJ TEXTTYPE.OBJ TEXTXREF.OBJ TFILECMD.OBJ TFILELST.OBJ TSETPATH.OBJ WINCMD.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
PCH.OBJ +
ATEXTEDT.OBJ +
CMDTAIL.OBJ +
CONVERT.OBJ +
DOSCMD.OBJ +
ENDETAB.OBJ +
FILEARY.OBJ +
HELPCMD.OBJ +
MAIN.OBJ +
MAKE.OBJ +
MAKEMAIN.OBJ +
MKCHECK.OBJ +
MKDEL.OBJ +
MKIFPROC.OBJ +
MKINPUT.OBJ +
MKMACRO.OBJ +
MKREADER.OBJ +
OPTCMD.OBJ +
REPRTEDT.OBJ +
RTEXTEDT.OBJ +
RULES.OBJ +
SYMBOL.OBJ +
TBTFRAME.OBJ +
TBTOPTN.OBJ +
TBTTITLE.OBJ +
TDIREC.OBJ +
TEXTBARY.OBJ +
TEXTBLOC.OBJ +
TEXTEDIT.OBJ +
TEXTTYPE.OBJ +
TEXTXREF.OBJ +
TFILECMD.OBJ +
TFILELST.OBJ +
TSETPATH.OBJ +
WINCMD.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
d:\msvc\lib\+
e:\msvc\mfc\lib\+
f:\zapp\lib\+
F:\ZAPP\LIB\ZAPPC7.LIB+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) $@


run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
