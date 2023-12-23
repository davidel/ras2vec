# Microsoft Developer Studio Project File - Name="dbll_list" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=dbll_list - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dbll_list.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dbll_list.mak" CFG="dbll_list - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dbll_list - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "dbll_list - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dbll_list - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir "."
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir "."
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /W3 /GX /O2 /I "..\..\sources\include" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_CONSOLE" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "dbll_list - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir "."
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir "."
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /W3 /GX /Z7 /Od /I "..\..\sources\include" /D "_DEBUG" /D "_WINDOWS" /D "WIN32" /D "_CONSOLE" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "dbll_list - Win32 Release"
# Name "dbll_list - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\..\sources\dbll_list\Lladd.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\Llappnd.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\Llchdata.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\Llclear.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\Llcreate.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\Llcrfill.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\Lldelete.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\Lldesf.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\Llempty.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\Llgcnt.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\Llgdata.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\Llget.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\Llgetusd.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\Llgetusdaddr.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\Llpurge.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\Llrearrg.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\Llsdata.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\Llsearch.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\Llset.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\llsetdat.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\Llskdel.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\Llstype.c
# End Source File
# Begin Source File

SOURCE=..\..\sources\dbll_list\Llusdadd.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
