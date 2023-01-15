
TestDBps.dll: dlldata.obj TestDB_p.obj TestDB_i.obj
	link /dll /out:TestDBps.dll /def:TestDBps.def /entry:DllMain dlldata.obj TestDB_p.obj TestDB_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \
.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0500 /DREGISTER_PROXY_DLL \
		$<
# _WIN32_WINNT=0x0500 is for Win2000, change it to 0x0400 for NT4 or Win95 with DCOM

clean:
	@del TestDBps.dll
	@del TestDBps.lib
	@del TestDBps.exp
	@del dlldata.obj
	@del TestDB_p.obj
	@del TestDB_i.obj
