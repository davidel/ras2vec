# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=R2VDLL - WIN32 DEBUG
!MESSAGE No configuration specified.  Defaulting to R2VDLL - WIN32 DEBUG.
!ENDIF 

!IF "$(CFG)" != "r2vdll - Win32 Release" && "$(CFG)" != "r2vdll - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "r2vdll.mak" CFG="R2VDLL - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "r2vdll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "r2vdll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "r2vdll - Win32 Release"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "r2vdll - Win32 Release"

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

ALL : "$(OUTDIR)\r2vdll.dll"

CLEAN : 
	-@erase "$(INTDIR)\bmputil.obj"
	-@erase "$(INTDIR)\dll_main.obj"
	-@erase "$(INTDIR)\filescan.obj"
	-@erase "$(INTDIR)\flushpoly.obj"
	-@erase "$(INTDIR)\himage.obj"
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
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\thinner.obj"
	-@erase "$(INTDIR)\tree.obj"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vectorize.obj"
	-@erase "$(OUTDIR)\r2vdll.dll"
	-@erase "$(OUTDIR)\r2vdll.exp"
	-@erase "$(OUTDIR)\r2vdll.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /MT /W3 /GX /O2 /I "\projects\ras2vec\sources\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL_LIB" /D "MULTITHREAD" /YX /c
CPP_PROJ=/nologo /Zp1 /MT /W3 /GX /O2 /I "\projects\ras2vec\sources\include" /D\
 "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL_LIB" /D "MULTITHREAD"\
 /Fp"$(INTDIR)/r2vdll.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x410 /d "NDEBUG"
# ADD RSC /l 0x410 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/r2vdll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /profile /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /profile /machine:I386\
 /out:"$(OUTDIR)/r2vdll.dll" /implib:"$(OUTDIR)/r2vdll.lib" 
LINK32_OBJS= \
	"$(INTDIR)\bmputil.obj" \
	"$(INTDIR)\dll_main.obj" \
	"$(INTDIR)\filescan.obj" \
	"$(INTDIR)\flushpoly.obj" \
	"$(INTDIR)\himage.obj" \
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
	"$(INTDIR)\Llusdadd.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\thinner.obj" \
	"$(INTDIR)\tree.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\vectorize.obj"

"$(OUTDIR)\r2vdll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "r2vdll - Win32 Debug"

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

ALL : "$(OUTDIR)\r2vdll.dll"

CLEAN : 
	-@erase "$(INTDIR)\bmputil.obj"
	-@erase "$(INTDIR)\dll_main.obj"
	-@erase "$(INTDIR)\filescan.obj"
	-@erase "$(INTDIR)\flushpoly.obj"
	-@erase "$(INTDIR)\himage.obj"
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
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\thinner.obj"
	-@erase "$(INTDIR)\tree.obj"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\vectorize.obj"
	-@erase "$(OUTDIR)\r2vdll.dll"
	-@erase "$(OUTDIR)\r2vdll.exp"
	-@erase "$(OUTDIR)\r2vdll.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /MT /W3 /Gm /GX /Zi /Od /I "\projects\ras2vec\sources\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL_LIB" /D "MULTITHREAD" /YX /c
CPP_PROJ=/nologo /Zp1 /MT /W3 /Gm /GX /Zi /Od /I\
 "\projects\ras2vec\sources\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "DLL_LIB" /D "MULTITHREAD" /Fp"$(INTDIR)/r2vdll.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x410 /d "_DEBUG"
# ADD RSC /l 0x410 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/r2vdll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /profile /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /profile /debug /machine:I386\
 /out:"$(OUTDIR)/r2vdll.dll" /implib:"$(OUTDIR)/r2vdll.lib" 
LINK32_OBJS= \
	"$(INTDIR)\bmputil.obj" \
	"$(INTDIR)\dll_main.obj" \
	"$(INTDIR)\filescan.obj" \
	"$(INTDIR)\flushpoly.obj" \
	"$(INTDIR)\himage.obj" \
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
	"$(INTDIR)\Llusdadd.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\thinner.obj" \
	"$(INTDIR)\tree.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\vectorize.obj"

"$(OUTDIR)\r2vdll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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

################################################################################
# Begin Target

# Name "r2vdll - Win32 Release"
# Name "r2vdll - Win32 Debug"

!IF  "$(CFG)" == "r2vdll - Win32 Release"

!ELSEIF  "$(CFG)" == "r2vdll - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=\projects\ras2vec\sources\dll_files\dll_main.c
DEP_CPP_DLL_M=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	"\projects\ras2vec\sources\include\filescan.h"\
	"\projects\ras2vec\sources\include\flushpoly.h"\
	"\projects\ras2vec\sources\include\himage.h"\
	"\projects\ras2vec\sources\include\log.h"\
	"\projects\ras2vec\sources\include\ras2vec.h"\
	"\projects\ras2vec\sources\include\thinner.h"\
	"\projects\ras2vec\sources\include\tree.h"\
	"\projects\ras2vec\sources\include\vectorize.h"\
	

"$(INTDIR)\dll_main.obj" : $(SOURCE) $(DEP_CPP_DLL_M) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
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

!IF  "$(CFG)" == "r2vdll - Win32 Release"

DEP_CPP_BMPUT=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	"\projects\ras2vec\sources\include\ras2vec.h"\
	
NODEP_CPP_BMPUT=\
	"..\sources\ras2vec\ras2vec.h"\
	

"$(INTDIR)\bmputil.obj" : $(SOURCE) $(DEP_CPP_BMPUT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "r2vdll - Win32 Debug"

DEP_CPP_BMPUT=\
	"\projects\ras2vec\sources\include\dbll_list.h"\
	"\projects\ras2vec\sources\include\ras2vec.h"\
	

"$(INTDIR)\bmputil.obj" : $(SOURCE) $(DEP_CPP_BMPUT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
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
# End Project
################################################################################
