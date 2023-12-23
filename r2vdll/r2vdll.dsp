# Microsoft Developer Studio Project File - Name="r2vdll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=r2vdll - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "r2vdll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "r2vdll.mak" CFG="r2vdll - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "r2vdll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "r2vdll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "r2vdll - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /MD /W3 /GX /O2 /I "..\sources\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL_LIB" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "NDEBUG"
# ADD RSC /l 0x410 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /profile /machine:I386

!ELSEIF  "$(CFG)" == "r2vdll - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /MDd /W3 /Gm /GX /ZI /Od /I "..\sources\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL_LIB" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "_DEBUG"
# ADD RSC /l 0x410 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /profile /debug /machine:I386

!ENDIF 

# Begin Target

# Name "r2vdll - Win32 Release"
# Name "r2vdll - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\sources\ras2vec\bmputil.c
# End Source File
# Begin Source File

SOURCE=..\sources\dll_files\dll_main.c
# End Source File
# Begin Source File

SOURCE=..\sources\ras2vec\filescan.c
# End Source File
# Begin Source File

SOURCE=..\sources\ras2vec\flushpoly.c
# End Source File
# Begin Source File

SOURCE=..\sources\ras2vec\himage.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Lladd.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Llappnd.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Llchdata.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Llclear.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Llcreate.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Llcrfill.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Lldelete.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Lldesf.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Llempty.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Llgcnt.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Llgdata.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Llget.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Llgetusd.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Llgetusdaddr.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Llpurge.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Llrearrg.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Llsdata.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Llsearch.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Llset.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\llsetdat.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Llskdel.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Llstype.c
# End Source File
# Begin Source File

SOURCE=..\sources\dbll_list\Llusdadd.c
# End Source File
# Begin Source File

SOURCE=..\sources\ras2vec\log.c
# End Source File
# Begin Source File

SOURCE=..\sources\dll_files\r2vdll.def
# End Source File
# Begin Source File

SOURCE=..\sources\ras2vec\thinner.c
# End Source File
# Begin Source File

SOURCE=..\sources\ras2vec\tree.c
# End Source File
# Begin Source File

SOURCE=..\sources\ras2vec\util.c
# End Source File
# Begin Source File

SOURCE=..\sources\ras2vec\vectorize.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\sources\include\bmputil.h
# End Source File
# Begin Source File

SOURCE=..\sources\include\dbll_list.h
# End Source File
# Begin Source File

SOURCE=..\sources\include\filescan.h
# End Source File
# Begin Source File

SOURCE=..\sources\include\flushpoly.h
# End Source File
# Begin Source File

SOURCE=..\sources\include\himage.h
# End Source File
# Begin Source File

SOURCE=..\sources\include\log.h
# End Source File
# Begin Source File

SOURCE=..\sources\include\r2vdll.h
# End Source File
# Begin Source File

SOURCE=..\sources\include\ras2vec.h
# End Source File
# Begin Source File

SOURCE=..\sources\include\thinner.h
# End Source File
# Begin Source File

SOURCE=..\sources\include\tree.h
# End Source File
# Begin Source File

SOURCE=..\sources\include\util.h
# End Source File
# Begin Source File

SOURCE=..\sources\include\vectorize.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
