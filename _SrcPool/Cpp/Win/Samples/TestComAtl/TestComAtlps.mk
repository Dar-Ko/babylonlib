
TestComAtlps.dll: dlldata.obj TestComAtl_p.obj TestComAtl_i.obj
	link /dll /out:TestComAtlps.dll /def:TestComAtlps.def /entry:DllMain dlldata.obj TestComAtl_p.obj TestComAtl_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del TestComAtlps.dll
	@del TestComAtlps.lib
	@del TestComAtlps.exp
	@del dlldata.obj
	@del TestComAtl_p.obj
	@del TestComAtl_i.obj
