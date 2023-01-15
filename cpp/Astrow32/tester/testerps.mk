
testerps.dll: dlldata.obj tester_p.obj tester_i.obj
	link /dll /out:testerps.dll /def:testerps.def /entry:DllMain dlldata.obj tester_p.obj tester_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del testerps.dll
	@del testerps.lib
	@del testerps.exp
	@del dlldata.obj
	@del tester_p.obj
	@del tester_i.obj
