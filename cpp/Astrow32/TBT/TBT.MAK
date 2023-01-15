# Microsoft Visual C++ generated build script - Do not modify

PROJ = TBT
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
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
FIRSTCPP = ATEXTEDT.CPP
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /Gy /W3 /Gf /Zi /AL /Gx- /Od /D "Z_NP"="1" /D "_WINTBT_"="1" /D "_DEBUG" /FR /GA /Fd"TBT.PDB" /GEd
CFLAGS_R_WEXE = /nologo /Gs /G2 /Gy /W3 /Gf /AL /Gx- /O2 /D "Z_NP"="1" /D "_WINTBT_"="1" /D "NDEBUG" /FR /GA /GEd
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /FARCALL /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO /MAP /SEG:512
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /MAP /SEG:512
LIBS_D_WEXE = oldnames libw llibcew ..\tbtutil\tbtcvtut.lib commdlg.lib toolhelp
LIBS_R_WEXE = oldnames libw llibcew ..\tbtutil\tbtcvtut.lib commdlg.lib toolhelp
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = TBT.DEF
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
SBRS = ATEXTEDT.SBR \
		CMDTAIL.SBR \
		CONVERT.SBR \
		DOSCMD.SBR \
		ENDETAB.SBR \
		ERRORS.SBR \
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
		PCH.SBR \
		REPRTEDT.SBR \
		RTEXTEDT.SBR \
		RULES.SBR \
		SYMBOL.SBR \
		TBFRMDLG.SBR \
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
		WINCMD.SBR \
		ACOMBBOX.SBR \
		CHARCONS.SBR \
		DLGCTR.SBR \
		FIELDRNG.SBR \
		INIFILE.SBR \
		MAKENAME.SBR \
		MENUUTL.SBR \
		ZYIELD.SBR \
		MSG.SBR


ATEXTEDT_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\inc\fieldrng.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\tbt\symbol.hpp \
	d:\wpro\tbt\textbloc.hpp \
	d:\wpro\tbt\reprtedt.hpp \
	d:\wpro\tbt\rtextedt.hpp \
	d:\wpro\tbt\atextedt.hpp \
	d:\wpro\inc\helpid.h


CMDTAIL_DEP = d:\zapp\zapp.hpp \
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
	d:\zapp\zapph\mdi.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\tbt\tdirec.hpp \
	d:\wpro\tbt\tbtoptn.hpp \
	d:\wpro\inc\paths.hpp \
	d:\wpro\tbt\tbtframe.hpp \
	d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\errors.fns \
	d:\wpro\tbt\make.h


CONVERT_DEP = d:\zapp\zapp.hpp \
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
	d:\zapp\zapph\mdi.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\tbt\tbtoptn.hpp \
	d:\wpro\inc\tbtutil.h \
	d:\wpro\inc\msg.hpp


DOSCMD_DEP = d:\zapp\zapp.hpp \
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


ENDETAB_DEP = d:\zapp\zapp.hpp \
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
	d:\zapp\zapph\formdlg.hpp


ERRORS_DEP = d:\wpro\inc\errors.fns \
	d:\wpro\tbt\charcons.h


FILEARY_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\tbt\tdirec.hpp \
	d:\wpro\tbt\fileary.hpp \
	d:\wpro\inc\errors.fns


HELPCMD_DEP = d:\zapp\zapp.hpp \
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
	d:\zapp\zapph\mdi.hpp \
	d:\wpro\tbt\tbtframe.hpp \
	d:\wpro\inc\paths.hpp \
	d:\wpro\inc\acombbox.hpp


MAIN_DEP = d:\zapp\zapp.hpp \
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
	d:\zapp\zapph\mdi.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\tbt\fileary.hpp \
	d:\wpro\tbt\tdirec.hpp \
	d:\wpro\tbt\tbtoptn.hpp \
	d:\wpro\tbt\tbtframe.hpp \
	d:\wpro\inc\title.hpp \
	d:\wpro\inc\inifile.hpp


MAKE_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\tbtutil.h \
	d:\wpro\tbt\make.h


MAKEMAIN_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\tbtutil.h \
	d:\wpro\tbt\make.h


MKCHECK_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\tbtutil.h \
	d:\wpro\tbt\make.h


MKDEL_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\tbt\make.h


MKIFPROC_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\tbtutil.h \
	d:\wpro\tbt\make.h


MKINPUT_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\tbtutil.h \
	d:\wpro\tbt\make.h


MKMACRO_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\tbtutil.h \
	d:\wpro\tbt\make.h


MKREADER_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\tbtutil.h \
	d:\wpro\tbt\make.h


OPTCMD_DEP = d:\zapp\zapp.hpp \
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
	d:\zapp\zapph\mdi.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\inc\paths.hpp \
	d:\wpro\tbt\charcons.h \
	d:\wpro\tbt\tbtframe.hpp \
	d:\wpro\tbt\tdirec.hpp \
	d:\wpro\tbt\tbtoptn.hpp \
	d:\wpro\tbt\fileary.hpp \
	d:\wpro\tbt\tfilelst.hpp \
	d:\wpro\inc\tbtutil.h


PCH_DEP = d:\zapp\zapp.hpp \
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
	d:\zapp\zapph\formdlg.hpp


REPRTEDT_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\inc\fieldrng.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\tbt\symbol.hpp \
	d:\wpro\tbt\textbloc.hpp \
	d:\wpro\tbt\reprtedt.hpp \
	d:\wpro\inc\msg.hpp \
	d:\wpro\tbt\tbtoptn.hpp \
	d:\wpro\inc\errors.fns \
	d:\wpro\inc\helpid.h


RTEXTEDT_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\inc\fieldrng.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\tbt\symbol.hpp \
	d:\wpro\tbt\textbloc.hpp \
	d:\wpro\tbt\reprtedt.hpp \
	d:\wpro\tbt\rtextedt.hpp \
	d:\wpro\inc\helpid.h


RULES_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\tbtutil.h \
	d:\wpro\tbt\make.h


SYMBOL_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\tbt\symbol.hpp \
	d:\wpro\inc\errors.fns


TBFRMDLG_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\inc\paths.hpp


TBTFRAME_DEP = d:\zapp\zapp.hpp \
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
	d:\zapp\zapph\mdi.hpp \
	d:\wpro\tbt\tbtframe.hpp \
	d:\wpro\inc\title.hpp \
	d:\wpro\inc\paths.hpp \
	d:\wpro\inc\menuutl.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\tbt\tbtoptn.hpp


TBTOPTN_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\dialogs.h \
	d:\wpro\inc\helpid.h \
	d:\wpro\inc\attrib.h \
	d:\wpro\inc\inifile.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\tbt\tbtoptn.hpp \
	d:\wpro\inc\basedcs.h


TBTTITLE_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\inc\inifile.hpp \
	d:\wpro\inc\basedcs.h \
	d:\wpro\inc\title.hpp \
	d:\wpro\inc\paths.hpp


TDIREC_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\dialogs.h \
	d:\wpro\inc\helpid.h \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\tbt\tdirec.hpp \
	d:\wpro\inc\basedcs.h \
	d:\wpro\inc\inifile.hpp \
	d:\wpro\inc\acombbox.hpp


TEXTBARY_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\tbt\symbol.hpp \
	d:\wpro\tbt\textbloc.hpp \
	d:\wpro\inc\errors.fns


TEXTBLOC_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\tbt\symbol.hpp \
	d:\wpro\tbt\textbloc.hpp \
	d:\wpro\inc\errors.fns \
	d:\wpro\inc\tbtutil.h


TEXTEDIT_DEP = d:\zapp\zapp.hpp \
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
	d:\zapp\zapph\mdi.hpp \
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\inc\paths.hpp \
	d:\wpro\tbt\textedit.hpp \
	d:\wpro\inc\astromn.h \
	d:\wpro\inc\errors.fns \
	d:\wpro\inc\menuutl.hpp \
	d:\wpro\tbt\tbtoptn.hpp \
	d:\wpro\tbt\tbtframe.hpp \
	d:\wpro\inc\helpid.h \
	d:\wpro\inc\tbtutil.h


TEXTTYPE_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\tbt\textbloc.h \
	d:\wpro\inc\errors.fns


TEXTXREF_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\tbt\symbol.hpp \
	d:\wpro\tbt\textbloc.hpp


TFILECMD_DEP = d:\zapp\zapp.hpp \
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
	d:\zapp\zapph\mdi.hpp \
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
	d:\wpro\tbt\tbtframe.hpp \
	d:\wpro\inc\errors.fns


TFILELST_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\tbt\fileary.hpp \
	d:\wpro\tbt\tfilelst.hpp \
	d:\wpro\inc\inifile.hpp \
	d:\wpro\inc\errors.fns \
	d:\wpro\inc\helpid.h


TSETPATH_DEP = d:\zapp\zapp.hpp \
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
	d:\zapp\zapph\mdi.hpp \
	d:\wpro\inc\asfrmdlg.hpp \
	d:\wpro\tbt\tdirec.hpp \
	d:\wpro\inc\paths.hpp


WINCMD_DEP = d:\zapp\zapp.hpp \
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
	d:\zapp\zapph\mdi.hpp \
	d:\wpro\inc\paths.hpp \
	d:\wpro\tbt\charcons.h \
	d:\wpro\tbt\tbtframe.hpp


ACOMBBOX_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\acombbox.hpp \
	d:\wpro\inc\errors.fns


CHARCONS_DEP = 

DLGCTR_DEP = d:\zapp\zapp.hpp \
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
	d:\zapp\zapph\mdi.hpp


FIELDRNG_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\fieldrng.hpp \
	d:\wpro\inc\resstr.hpp \
	d:\wpro\inc\resstrid.h


INIFILE_DEP = d:\wpro\inc\inifile.hpp


MAKENAME_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\paths.hpp


MENUUTL_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\basedcs.h \
	d:\wpro\inc\menuutl.hpp


ZYIELD_DEP = d:\zapp\zapp.hpp \
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
	d:\zapp\zapph\formdlg.hpp


MSG_DEP = d:\zapp\zapp.hpp \
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
	d:\wpro\inc\msg.hpp \
	d:\wpro\inc\acombbox.hpp


TBT_RCDEP = d:\wpro\tbt\tbt.ico \
	d:\wpro\tbt\text.ico \
	d:\wpro\tbt\tbtwin.bmp


ZAPPC7_DEP = 

all:	$(PROJ).EXE $(PROJ).BSC

ATEXTEDT.OBJ:	ATEXTEDT.CPP $(ATEXTEDT_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c ATEXTEDT.CPP

CMDTAIL.OBJ:	CMDTAIL.CPP $(CMDTAIL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CMDTAIL.CPP

CONVERT.OBJ:	CONVERT.CPP $(CONVERT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CONVERT.CPP

DOSCMD.OBJ:	DOSCMD.CPP $(DOSCMD_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DOSCMD.CPP

ENDETAB.OBJ:	ENDETAB.CPP $(ENDETAB_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ENDETAB.CPP

ERRORS.OBJ:	ERRORS.CPP $(ERRORS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ERRORS.CPP

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

PCH.OBJ:	PCH.CPP $(PCH_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PCH.CPP

REPRTEDT.OBJ:	REPRTEDT.CPP $(REPRTEDT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c REPRTEDT.CPP

RTEXTEDT.OBJ:	RTEXTEDT.CPP $(RTEXTEDT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RTEXTEDT.CPP

RULES.OBJ:	RULES.CPP $(RULES_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RULES.CPP

SYMBOL.OBJ:	SYMBOL.CPP $(SYMBOL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SYMBOL.CPP

TBFRMDLG.OBJ:	TBFRMDLG.CPP $(TBFRMDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TBFRMDLG.CPP

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

ACOMBBOX.OBJ:	..\DLG\ACOMBBOX.CPP $(ACOMBBOX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\DLG\ACOMBBOX.CPP

CHARCONS.OBJ:	..\UIUTL\CHARCONS.CPP $(CHARCONS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\UIUTL\CHARCONS.CPP

DLGCTR.OBJ:	..\DLG\DLGCTR.CPP $(DLGCTR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\DLG\DLGCTR.CPP

FIELDRNG.OBJ:	..\DLG\FIELDRNG.CPP $(FIELDRNG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\DLG\FIELDRNG.CPP

INIFILE.OBJ:	..\UIUTL\INIFILE.CPP $(INIFILE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\UIUTL\INIFILE.CPP

MAKENAME.OBJ:	..\UIUTL\MAKENAME.CPP $(MAKENAME_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\UIUTL\MAKENAME.CPP

MENUUTL.OBJ:	..\UIUTL\MENUUTL.CPP $(MENUUTL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\UIUTL\MENUUTL.CPP

ZYIELD.OBJ:	..\UIUTL\ZYIELD.CPP $(ZYIELD_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\UIUTL\ZYIELD.CPP

MSG.OBJ:	..\UIUTL\MSG.CPP $(MSG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\UIUTL\MSG.CPP

TBT.RES:	TBT.RC $(TBT_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r TBT.RC


$(PROJ).EXE::	TBT.RES

$(PROJ).EXE::	ATEXTEDT.OBJ CMDTAIL.OBJ CONVERT.OBJ DOSCMD.OBJ ENDETAB.OBJ ERRORS.OBJ \
	FILEARY.OBJ HELPCMD.OBJ MAIN.OBJ MAKE.OBJ MAKEMAIN.OBJ MKCHECK.OBJ MKDEL.OBJ MKIFPROC.OBJ \
	MKINPUT.OBJ MKMACRO.OBJ MKREADER.OBJ OPTCMD.OBJ PCH.OBJ REPRTEDT.OBJ RTEXTEDT.OBJ \
	RULES.OBJ SYMBOL.OBJ TBFRMDLG.OBJ TBTFRAME.OBJ TBTOPTN.OBJ TBTTITLE.OBJ TDIREC.OBJ \
	TEXTBARY.OBJ TEXTBLOC.OBJ TEXTEDIT.OBJ TEXTTYPE.OBJ TEXTXREF.OBJ TFILECMD.OBJ TFILELST.OBJ \
	TSETPATH.OBJ WINCMD.OBJ ACOMBBOX.OBJ CHARCONS.OBJ DLGCTR.OBJ FIELDRNG.OBJ INIFILE.OBJ \
	MAKENAME.OBJ MENUUTL.OBJ ZYIELD.OBJ MSG.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
ATEXTEDT.OBJ +
CMDTAIL.OBJ +
CONVERT.OBJ +
DOSCMD.OBJ +
ENDETAB.OBJ +
ERRORS.OBJ +
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
PCH.OBJ +
REPRTEDT.OBJ +
RTEXTEDT.OBJ +
RULES.OBJ +
SYMBOL.OBJ +
TBFRMDLG.OBJ +
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
ACOMBBOX.OBJ +
CHARCONS.OBJ +
DLGCTR.OBJ +
FIELDRNG.OBJ +
INIFILE.OBJ +
MAKENAME.OBJ +
MENUUTL.OBJ +
ZYIELD.OBJ +
MSG.OBJ +
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
	$(RC) $(RESFLAGS) TBT.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	TBT.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) TBT.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
