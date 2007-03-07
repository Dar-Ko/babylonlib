
TAPITestps.dll: dlldata.obj TAPITest_p.obj TAPITest_i.obj
	link /dll /out:TAPITestps.dll /def:TAPITestps.def /entry:DllMain dlldata.obj TAPITest_p.obj TAPITest_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del TAPITestps.dll
	@del TAPITestps.lib
	@del TAPITestps.exp
	@del dlldata.obj
	@del TAPITest_p.obj
	@del TAPITest_i.obj
