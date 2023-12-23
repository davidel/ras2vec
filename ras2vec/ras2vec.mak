# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103
# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=r2vlib - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to r2vlib - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ras2vec - Win32 Release" && "$(CFG)" !=\
 "ras2vec - Win32 Debug" && "$(CFG)" != "dbll_list - Win32 Release" && "$(CFG)"\
 != "dbll_list - Win32 Debug" && "$(CFG)" != "r2vlib - Win32 Release" &&\
 "$(CFG)" != "r2vlib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "ras2vec.mak" CFG="r2vlib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ras2vec - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ras2vec - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "dbll_list - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "dbll_list - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "r2vlib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "r2vlib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "r2vlib - Win32 Debug"

!IF  "$(CFG)" == "ras2vec - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "r2vlib - Win32 Release" "dbll_list - Win32 Release"\
 "$(OUTDIR)\ras2vec.exe"

CLEAN : 
	-@erase "$(INTDIR)\ras2vec.obj"
	-@erase "$(OUTDIR)\ras2vec.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /Zp1 /W3 /GX /O2 /I "\projects\ras2vec\sources\include" /D "NDEBUG" /D "_CONSOLE" /D "WIN32" /YX /c
CPP_PROJ=/nologo /Zp1 /ML /W3 /GX /O2 /I "\projects\ras2vec\sources\include" /D\
 "NDEBUG" /D "_CONSOLE" /D "WIN32" /Fp"$(INTDIR)/ras2vec.pch" /YX\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x410 /d "NDEBUG"
# ADD RSC /l 0x410 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ras2vec.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib \projects\ras2vec\lib\tiff.lib /nologo /subsystem:console /profile /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib \projects\ras2vec\lib\tiff.lib /nologo /subsystem:console /profile\
 /machine:I386 /out:"$(OUTDIR)/ras2vec.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ras2vec.obj" \
	".\dbll_list\Release\dbll_list.lib" \
	".\r2vlib\Release\r2vlib.lib"

"$(OUTDIR)\ras2vec.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ras2vec - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "r2vlib - Win32 Debug" "dbll_list - Win32 Debug" "$(OUTDIR)\ras2vec.exe"

CLEAN : 
	-@erase "$(INTDIR)\ras2vec.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\ras2vec.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /Zp1 /ML /W3 /Gm /GX /Zi /Od /I "\projects\ras2vec\sources\include" /D "_DEBUG" /D "_CONSOLE" /D "WIN32" /YX /c
CPP_PROJ=/nologo /Zp1 /ML /W3 /Gm /GX /Zi /Od /I\
 "\projects\ras2vec\sources\include" /D "_DEBUG" /D "_CONSOLE" /D "WIN32"\
 /Fp"$(INTDIR)/ras2vec.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x410 /d "_DEBUG"
# ADD RSC /l 0x410 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ras2vec.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib \projects\ras2vec\lib\tiff.lib /nologo /subsystem:console /profile /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib \projects\ras2vec\lib\tiff.lib /nologo /subsystem:console /profile\
 /debug /machine:I386 /out:"$(OUTDIR)/ras2vec.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ras2vec.obj" \
	".\dbll_list\Debug\dbll_list.lib" \
	".\r2vlib\Debug\r2vlib.lib"

"$(OUTDIR)\ras2vec.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dbll_list - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "dbll_list\Release"
# PROP BASE Intermediate_Dir "dbll_list\Release"
# PROP BASE Target_Dir "dbll_list"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "dbll_list\Release"
# PROP Intermediate_Dir "dbll_list\Release"
# PROP Target_Dir "dbll_list"
OUTDIR=.\dbll_list\Release
INTDIR=.\dbll_list\Release

ALL : "$(OUTDIR)\dbll_list.lib"

CLEAN : 
	-@erase "$(INTDIR)\Lladd.obj"
	-@erase "$(INTDIR)\Llappnd.obj"
	-@erase "$(INTDIR)\Llchdata.obj"
	-@erase "$(INTDIR)\Llclear.obj"
	-@erase "$(INTDIR)\Llcreate.obj"
	-@erase "$(INTDIR)\Llcrfill.obj"
	-@erase "$(INTDIR)\Lldelete.obj"
	-@erase "$(INTDIR)\Lldesf.obj"
	-@erase "$(INTDIR)\Llempty.obj"
	-@erase "$(INTDIR)\Llgcnt.obj"
	-@erase "$(INTDIR)\Llgdata.obj"
	-@erase "$(INTDIR)\Llget.obj"
	-@erase "$(INTDIR)\Llgetusd.obj"
	-@erase "$(INTDIR)\Llgetusdaddr.obj"
	-@erase "$(INTDIR)\Llpurge.obj"
	-@erase "$(INTDIR)\Llrearrg.obj"
	-@erase "$(INTDIR)\Llsdata.obj"
	-@erase "$(INTDIR)\Llsearch.obj"
	-@erase "$(INTDIR)\Llset.obj"
	-@erase "$(INTDIR)\llsetdat.obj"
	-@erase "$(INTDIR)\Llskdel.obj"
	-@erase "$(INTDIR)\Llstype.obj"
	-@erase "$(INTDIR)\Llusdadd.obj"
	-@erase "$(OUTDIR)\dbll_list.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /W3 /GX /O2 /I "\projects\ras2vec\include" /I "\projects\ras2vec\sources\include" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /Zp1 /ML /W3 /GX /O2 /I "\projects\ras2vec\include" /I\
 "\projects\ras2vec\sources\include" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D\
 "_CONSOLE" /Fp"$(INTDIR)/dbll_list.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\dbll_list\Release/
CPP_SBRS=.\.

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/dbll_list.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/dbll_list.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Lladd.obj" \
	"$(INTDIR)\Llappnd.obj" \
	"$(INTDIR)\Llchdata.obj" \
	"$(INTDIR)\Llclear.obj" \
	"$(INTDIR)\Llcreate.obj" \
	"$(INTDIR)\Llcrfill.obj" \
	"$(INTDIR)\Lldelete.obj" \
	"$(INTDIR)\Lldesf.obj" \
	"$(INTDIR)\Llempty.obj" \
	"$(INTDIR)\Llgcnt.obj" \
	"$(INTDIR)\Llgdata.obj" \
	"$(INTDIR)\Llget.obj" \
	"$(INTDIR)\Llgetusd.obj" \
	"$(INTDIR)\Llgetusdaddr.obj" \
	"$(INTDIR)\Llpurge.obj" \
	"$(INTDIR)\Llrearrg.obj" \
	"$(INTDIR)\Llsdata.obj" \
	"$(INTDIR)\Llsearch.obj" \
	"$(INTDIR)\Llset.obj" \
	"$(INTDIR)\llsetdat.obj" \
	"$(INTDIR)\Llskdel.obj" \
	"$(INTDIR)\Llstype.obj" \
	"$(INTDIR)\Llusdadd.obj"

"$(OUTDIR)\dbll_list.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dbll_list - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "dbll_list\Debug"
# PROP BASE Intermediate_Dir "dbll_list\Debug"
# PROP BASE Target_Dir "dbll_list"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "dbll_list\Debug"
# PROP Intermediate_Dir "dbll_list\Debug"
# PROP Target_Dir "dbll_list"
OUTDIR=.\dbll_list\Debug
INTDIR=.\dbll_list\Debug

ALL : "$(OUTDIR)\dbll_list.lib"

CLEAN : 
	-@erase "$(INTDIR)\Lladd.obj"
	-@erase "$(INTDIR)\Llappnd.obj"
	-@erase "$(INTDIR)\Llchdata.obj"
	-@erase "$(INTDIR)\Llclear.obj"
	-@erase "$(INTDIR)\Llcreate.obj"
	-@erase "$(INTDIR)\Llcrfill.obj"
	-@erase "$(INTDIR)\Lldelete.obj"
	-@erase "$(INTDIR)\Lldesf.obj"
	-@erase "$(INTDIR)\Llempty.obj"
	-@erase "$(INTDIR)\Llgcnt.obj"
	-@erase "$(INTDIR)\Llgdata.obj"
	-@erase "$(INTDIR)\Llget.obj"
	-@erase "$(INTDIR)\Llgetusd.obj"
	-@erase "$(INTDIR)\Llgetusdaddr.obj"
	-@erase "$(INTDIR)\Llpurge.obj"
	-@erase "$(INTDIR)\Llrearrg.obj"
	-@erase "$(INTDIR)\Llsdata.obj"
	-@erase "$(INTDIR)\Llsearch.obj"
	-@erase "$(INTDIR)\Llset.obj"
	-@erase "$(INTDIR)\llsetdat.obj"
	-@erase "$(INTDIR)\Llskdel.obj"
	-@erase "$(INTDIR)\Llstype.obj"
	-@erase "$(INTDIR)\Llusdadd.obj"
	-@erase "$(OUTDIR)\dbll_list.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /ML /W3 /GX /Z7 /Od /I "\projects\ras2vec\include" /I "\projects\ras2vec\sources\include" /D "_DEBUG" /D "_WINDOWS" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /Zp1 /ML /W3 /GX /Z7 /Od /I "\projects\ras2vec\include" /I\
 "\projects\ras2vec\sources\include" /D "_DEBUG" /D "_WINDOWS" /D "WIN32" /D\
 "_CONSOLE" /Fp"$(INTDIR)/dbll_list.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\dbll_list\Debug/
CPP_SBRS=.\.

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/dbll_list.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/dbll_list.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Lladd.obj" \
	"$(INTDIR)\Llappnd.obj" \
	"$(INTDIR)\Llchdata.obj" \
	"$(INTDIR)\Llclear.obj" \
	"$(INTDIR)\Llcreate.obj" \
	"$(INTDIR)\Llcrfill.obj" \
	"$(INTDIR)\Lldelete.obj" \
	"$(INTDIR)\Lldesf.obj" \
	"$(INTDIR)\Llempty.obj" \
	"$(INTDIR)\Llgcnt.obj" \
	"$(INTDIR)\Llgdata.obj" \
	"$(INTDIR)\Llget.obj" \
	"$(INTDIR)\Llgetusd.obj" \
	"$(INTDIR)\Llgetusdaddr.obj" \
	"$(INTDIR)\Llpurge.obj" \
	"$(INTDIR)\Llrearrg.obj" \
	"$(INTDIR)\Llsdata.obj" \
	"$(INTDIR)\Llsearch.obj" \
	"$(INTDIR)\Llset.obj" \
	"$(INTDIR)\llsetdat.obj" \
	"$(INTDIR)\Llskdel.obj" \
	"$(INTDIR)\Llstype.obj" \
	"$(INTDIR)\Llusdadd.obj"

"$(OUTDIR)\dbll_list.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "r2vlib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "r2vlib\Release"
# PROP BASE Intermediate_Dir "r2vlib\Release"
# PROP BASE Target_Dir "r2vlib"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "r2vlib\Release"
# PROP Intermediate_Dir "r2vlib\Release"
# PROP Target_Dir "r2vlib"
OUTDIR=.\r2vlib\Release
INTDIR=.\r2vlib\Release

ALL : "$(OUTDIR)\r2vlib.lib"

CLEAN : 
	-@erase "$(INTDIR)\bmputil.obj"
	-@erase "$(INTDIR)\filescan.obj"
	-@erase "$(INTDIR)\flushpoly.obj"
	-@erase "$(INTDIR)\himage.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\thinner.obj"
	-@erase "$(INTDIR)\tree.obj"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vectorize.obj"
	-@erase "$(OUTDIR)\r2vlib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /W3 /GX /O2 /I "\projects\ras2vec\include" /I "\projects\ras2vec\sources\include" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /Zp1 /ML /W3 /GX /O2 /I "\projects\ras2vec\include" /I\
 "\projects\ras2vec\sources\include" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D\
 "_CONSOLE" /Fp"$(INTDIR)/r2vlib.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\r2vlib\Release/
CPP_SBRS=.\.

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/r2vlib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/r2vlib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\bmputil.obj" \
	"$(INTDIR)\filescan.obj" \
	"$(INTDIR)\flushpoly.obj" \
	"$(INTDIR)\himage.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\thinner.obj" \
	"$(INTDIR)\tree.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\vectorize.obj"

"$(OUTDIR)\r2vlib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "r2vlib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "r2vlib\Debug"
# PROP BASE Intermediate_Dir "r2vlib\Debug"
# PROP BASE Target_Dir "r2vlib"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "r2vlib\Debug"
# PROP Intermediate_Dir "r2vlib\Debug"
# PROP Target_Dir "r2vlib"
OUTDIR=.\r2vlib\Debug
INTDIR=.\r2vlib\Debug

ALL : "$(OUTDIR)\r2vlib.lib"

CLEAN : 
	-@erase "$(INTDIR)\bmputil.obj"
	-@erase "$(INTDIR)\filescan.obj"
	-@erase "$(INTDIR)\flushpoly.obj"
	-@erase "$(INTDIR)\himage.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\thinner.obj"
	-@erase "$(INTDIR)\tree.obj"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vectorize.obj"
	-@erase "$(OUTDIR)\r2vlib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /ML /W3 /GX /Z7 /Od /I "\projects\ras2vec\include" /I "\projects\ras2vec\sources\include" /D "_DEBUG" /D "_WINDOWS" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /Zp1 /ML /W3 /GX /Z7 /Od /I "\projects\ras2vec\include" /I\
 "\projects\ras2vec\sources\include" /D "_DEBUG" /D "_WINDOWS" /D "WIN32" /D\
 "_CONSOLE" /Fp"$(INTDIR)/r2vlib.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\r2vlib\Debug/
CPP_SBRS=.\.

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/r2vlib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/r2vlib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\bmputil.obj" \
	"$(INTDIR)\filescan.obj" \
	"$(INTDIR)\flushpoly.obj" \
	"$(INTDIR)\himage.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\thinner.obj" \
	"$(INTDIR)\tree.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\vectorize.obj"

"$(OUTDIR)\r2vlib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "ras2vec - Win32 Release"
# Name "ras2vec - Win32 Debug"

!IF  "$(CFG)" == "ras2vec - Win32 Release"

!ELSEIF  "$(CFG)" == "ras2vec - Win32 Debug"

!ENDIF 

################################################################################
# Begin Project Dependency

# Project_Dep_Name "dbll_list"

!IF  "$(CFG)" == "ras2vec - Win32 Release"

"dbll_list - Win32 Release" : 
   $(MAKE) /$(MAKEFLAGS) /F ".\ras2vec.mak" CFG="dbll_list - Win32 Release" 

!ELSEIF  "$(CFG)" == "ras2vec - Win32 Debug"

"dbll_list - Win32 Debug" : 
   $(MAKE) /$(MAKEFLAGS) /F ".\ras2vec.mak" CFG="dbll_list - Win32 Debug" 

!ENDIF 

# End Project Dependency
################################################################################
# Begin Project Dependency

# Project_Dep_Name "r2vlib"

!IF  "$(CFG)" == "ras2vec - Win32 Release"

"r2vlib - Win32 Release" : 
   $(MAKE) /$(MAKEFLAGS) /F ".\ras2vec.mak" CFG="r2vlib - Win32 Release" 

!ELSEIF  "$(CFG)" == "ras2vec - Win32 Debug"

"r2vlib - Win32 Debug" : 
   $(MAKE) /$(MAKEFLAGS) /F ".\ras2vec.mak" CFG="r2vlib - Win32 Debug" 

!ENDIF 

# End Project Dependency
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\exe_test\ras2vec.c

!IF  "$(CFG)" == "ras2vec - Win32 Release"

DEP_CPP_RAS2V=\
	"..\sources\include\tiff.h"\
	"\projects\ras2vec\sources\include\bmputil.h"\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	"\projects\ras2vec\sources\include\filescan.h"\
	"\projects\ras2vec\sources\include\himage.h"\
	"\projects\ras2vec\sources\include\log.h"\
	"\projects\ras2vec\sources\include\ras2vec.h"\
	"\projects\ras2vec\sources\include\thinner.h"\
	"\projects\ras2vec\sources\include\tiffext.h"\
	"\projects\ras2vec\sources\include\tiffio.h"\
	"\projects\ras2vec\sources\include\vectorize.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	{$(INCLUDE)}"\sys\types.h"\
	

"$(INTDIR)\ras2vec.obj" : $(SOURCE) $(DEP_CPP_RAS2V) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ras2vec - Win32 Debug"

DEP_CPP_RAS2V=\
	"..\sources\include\tiff.h"\
	"\projects\ras2vec\sources\include\bmputil.h"\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	"\projects\ras2vec\sources\include\filescan.h"\
	"\projects\ras2vec\sources\include\himage.h"\
	"\projects\ras2vec\sources\include\log.h"\
	"\projects\ras2vec\sources\include\ras2vec.h"\
	"\projects\ras2vec\sources\include\thinner.h"\
	"\projects\ras2vec\sources\include\tiffext.h"\
	"\projects\ras2vec\sources\include\tiffio.h"\
	"\projects\ras2vec\sources\include\vectorize.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	{$(INCLUDE)}"\sys\types.h"\
	

"$(INTDIR)\ras2vec.obj" : $(SOURCE) $(DEP_CPP_RAS2V) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
# End Target
################################################################################
# Begin Target

# Name "dbll_list - Win32 Release"
# Name "dbll_list - Win32 Debug"

!IF  "$(CFG)" == "dbll_list - Win32 Release"

!ELSEIF  "$(CFG)" == "dbll_list - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Llusdadd.c
DEP_CPP_LLUSD=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Llusdadd.obj" : $(SOURCE) $(DEP_CPP_LLUSD) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Llappnd.c
DEP_CPP_LLAPP=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Llappnd.obj" : $(SOURCE) $(DEP_CPP_LLAPP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Llchdata.c
DEP_CPP_LLCHD=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Llchdata.obj" : $(SOURCE) $(DEP_CPP_LLCHD) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Llclear.c
DEP_CPP_LLCLE=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Llclear.obj" : $(SOURCE) $(DEP_CPP_LLCLE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Llcreate.c
DEP_CPP_LLCRE=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Llcreate.obj" : $(SOURCE) $(DEP_CPP_LLCRE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Llcrfill.c
DEP_CPP_LLCRF=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Llcrfill.obj" : $(SOURCE) $(DEP_CPP_LLCRF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Lldelete.c
DEP_CPP_LLDEL=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Lldelete.obj" : $(SOURCE) $(DEP_CPP_LLDEL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Lldesf.c
DEP_CPP_LLDES=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Lldesf.obj" : $(SOURCE) $(DEP_CPP_LLDES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Llempty.c
DEP_CPP_LLEMP=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Llempty.obj" : $(SOURCE) $(DEP_CPP_LLEMP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Llgcnt.c
DEP_CPP_LLGCN=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Llgcnt.obj" : $(SOURCE) $(DEP_CPP_LLGCN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Llgdata.c
DEP_CPP_LLGDA=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Llgdata.obj" : $(SOURCE) $(DEP_CPP_LLGDA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Llget.c
DEP_CPP_LLGET=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Llget.obj" : $(SOURCE) $(DEP_CPP_LLGET) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Llgetusd.c
DEP_CPP_LLGETU=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Llgetusd.obj" : $(SOURCE) $(DEP_CPP_LLGETU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Llgetusdaddr.c
DEP_CPP_LLGETUS=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Llgetusdaddr.obj" : $(SOURCE) $(DEP_CPP_LLGETUS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Llpurge.c
DEP_CPP_LLPUR=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Llpurge.obj" : $(SOURCE) $(DEP_CPP_LLPUR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Llrearrg.c
DEP_CPP_LLREA=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Llrearrg.obj" : $(SOURCE) $(DEP_CPP_LLREA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Llsdata.c
DEP_CPP_LLSDA=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Llsdata.obj" : $(SOURCE) $(DEP_CPP_LLSDA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Llsearch.c
DEP_CPP_LLSEA=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Llsearch.obj" : $(SOURCE) $(DEP_CPP_LLSEA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Llset.c
DEP_CPP_LLSET=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Llset.obj" : $(SOURCE) $(DEP_CPP_LLSET) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\llsetdat.c
DEP_CPP_LLSETD=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\llsetdat.obj" : $(SOURCE) $(DEP_CPP_LLSETD) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Llskdel.c
DEP_CPP_LLSKD=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Llskdel.obj" : $(SOURCE) $(DEP_CPP_LLSKD) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Llstype.c
DEP_CPP_LLSTY=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Llstype.obj" : $(SOURCE) $(DEP_CPP_LLSTY) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dbll_list\Lladd.c
DEP_CPP_LLADD=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	

"$(INTDIR)\Lladd.obj" : $(SOURCE) $(DEP_CPP_LLADD) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
################################################################################
# Begin Target

# Name "r2vlib - Win32 Release"
# Name "r2vlib - Win32 Debug"

!IF  "$(CFG)" == "r2vlib - Win32 Release"

!ELSEIF  "$(CFG)" == "r2vlib - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\ras2vec\vectorize.c
DEP_CPP_VECTO=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	"\projects\ras2vec\sources\include\filescan.h"\
	"\projects\ras2vec\sources\include\flushpoly.h"\
	"\projects\ras2vec\sources\include\himage.h"\
	"\projects\ras2vec\sources\include\log.h"\
	"\projects\ras2vec\sources\include\ras2vec.h"\
	"\projects\ras2vec\sources\include\thinner.h"\
	"\projects\ras2vec\sources\include\tree.h"\
	"\projects\ras2vec\sources\include\vectorize.h"\
	

"$(INTDIR)\vectorize.obj" : $(SOURCE) $(DEP_CPP_VECTO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\ras2vec\filescan.c
DEP_CPP_FILES=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	"\projects\ras2vec\sources\include\filescan.h"\
	"\projects\ras2vec\sources\include\flushpoly.h"\
	"\projects\ras2vec\sources\include\himage.h"\
	"\projects\ras2vec\sources\include\log.h"\
	"\projects\ras2vec\sources\include\ras2vec.h"\
	"\projects\ras2vec\sources\include\thinner.h"\
	

"$(INTDIR)\filescan.obj" : $(SOURCE) $(DEP_CPP_FILES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\ras2vec\flushpoly.c
DEP_CPP_FLUSH=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	"\projects\ras2vec\sources\include\flushpoly.h"\
	"\projects\ras2vec\sources\include\log.h"\
	"\projects\ras2vec\sources\include\ras2vec.h"\
	

"$(INTDIR)\flushpoly.obj" : $(SOURCE) $(DEP_CPP_FLUSH) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\ras2vec\himage.c
DEP_CPP_HIMAG=\
	"\projects\ras2vec\sources\include\himage.h"\
	"\projects\ras2vec\sources\include\ras2vec.h"\
	

"$(INTDIR)\himage.obj" : $(SOURCE) $(DEP_CPP_HIMAG) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\ras2vec\log.c
DEP_CPP_LOG_C=\
	"\projects\ras2vec\sources\include\log.h"\
	"\projects\ras2vec\sources\include\ras2vec.h"\
	

"$(INTDIR)\log.obj" : $(SOURCE) $(DEP_CPP_LOG_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\ras2vec\thinner.c
DEP_CPP_THINN=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	"\projects\ras2vec\sources\include\himage.h"\
	"\projects\ras2vec\sources\include\log.h"\
	"\projects\ras2vec\sources\include\ras2vec.h"\
	"\projects\ras2vec\sources\include\thinner.h"\
	

"$(INTDIR)\thinner.obj" : $(SOURCE) $(DEP_CPP_THINN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\ras2vec\tree.c
DEP_CPP_TREE_=\
	"\projects\ras2vec\sources\include\tree.h"\
	

"$(INTDIR)\tree.obj" : $(SOURCE) $(DEP_CPP_TREE_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\ras2vec\util.c
DEP_CPP_UTIL_=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	"\projects\ras2vec\sources\include\flushpoly.h"\
	"\projects\ras2vec\sources\include\himage.h"\
	"\projects\ras2vec\sources\include\log.h"\
	"\projects\ras2vec\sources\include\ras2vec.h"\
	"\projects\ras2vec\sources\include\thinner.h"\
	

"$(INTDIR)\util.obj" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\ras2vec\bmputil.c
DEP_CPP_BMPUT=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	"\projects\ras2vec\sources\include\ras2vec.h"\
	

"$(INTDIR)\bmputil.obj" : $(SOURCE) $(DEP_CPP_BMPUT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
