# Nmake uses carets to escape special characters
!MESSAGE NMAKE -f TestComAtlps.mk

CPP=cl.exe

OUTDIR=..\Bin

INTDIR=..\Obj

OBJDIR = ..\Obj

INCLUDE = /I.\idl /I . /I "C:\Program Files\Microsoft SDK\Include"

CLAGS =/c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL

LINK32_OBJS= \
	"$(INTDIR)\TestComAtl_p.obj" \
	"$(INTDIR)\dlldata.obj" \
	"$(INTDIR)\TestComAtl_i.obj"

LINK32_FLAGS=/dll /entry:DllMain kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib

DEF_FILE = TestComAtlps.def 

"$(OUTDIR)\tets.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
	$(LINK32) @<<
	$(LINK32_FLAGS) $(LINK32_OBJS)
<<

ALL : "$(OUTDIR)\TestComAtlps.dll"

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CLAGS) $< 
<<

SOURCE=.\dlldata.c

"$(INTDIR)\dlldata.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\idl\TestComAtl_i.c

"$(INTDIR)\TestComAtl_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\TestComAtl_p.c

"$(INTDIR)\TestComAtl_p.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)

#TestComAtlps.dll: dlldata.obj TestComAtl_p.obj TestComAtl_i.obj
#	link /dll /out:TestComAtlps.dll /def:TestComAtlps.def /entry:DllMain dlldata.obj TestComAtl_p.obj TestComAtl_i.obj \
#		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \


#.c.obj:
#	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
#		$<


clean:
	@del TestComAtlps.dll
	@del TestComAtlps.lib
	@del TestComAtlps.exp
	@del dlldata.obj
	@del TestComAtl_p.obj
	@del TestComAtl_i.obj

"$(OUTDIR)" :
	if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"


