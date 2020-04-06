#### Civilization 4 SDK Makefile 1.0 ####
####  Copyright 2010 Danny Daemonic  ####
#########################################

####  Revised by zahlen  ####

#### Paths ####
INSTALLDIR=$(CIV4DLL_COMPILER_PORTABLE_DIR)
TOOLKIT=$(INSTALLDIR)\Microsoft Visual C++ Toolkit 2003
PSDK = $(INSTALLDIR)\Microsoft Platform SDK

#### Tools ####
CC="$(TOOLKIT)\bin\cl.exe"
CPP="$(TOOLKIT)\bin\cl.exe"
LD="$(TOOLKIT)\bin\link.exe"
RC="$(PSDK)\bin\rc.exe"
## Uncomment to build dependencies using fastdep
#FD="$(MAKEDIR)\bin\fastdep.exe"

GLOBAL_CFLAGS =
GLOBAL_LDFLAGS =
GLOBAL_LIBS = /LIBPATH:"$(TOOLKIT)/lib" /LIBPATH:"$(PSDK)/Lib"
GLOBAL_INCS = /I"$(TOOLKIT)/include" /I"$(PSDK)/Include" /I"$(PSDK)/Include/mfc"
GLOBAL_RES_INCS = /I"$(PSDK)/Include" /I"$(PSDK)/Include/mfc"

#### EXCLUDE ####
## Uncomment to block CvTextScreen (accidentally included by Firaxis)
EXCLUDE=CvTextScreens

#### Civ4 ####
#CIVINSTALL=C:\Program Files\Firaxis Games\Sid Meier's Civilization 4\Beyond the Sword
#GLOBALBOOST = $(CIVINSTALL)\CvGameCoreDLL\Boost-1.32.0
#GLOBALPYTHON = $(CIVINSTALL)\CvGameCoreDLL\Python24
GLOBALBOOST = $(INSTALLDIR)\CvGameCoreDLL\Boost-1.32.0
GLOBALPYTHON = $(INSTALLDIR)\CvGameCoreDLL\Python24

#### MOD Info ####
## Uncomment to have newly compiled dlls copied to your mod's Assets directory
OUTPUT = $(INSTALLDIR)\dll
Debug_MOD_CFLAGS =
Release_MOD_CFLAGS =
Final_Release_MOD_CFLAGS =
MOD_LDFLAGS =
MOD_INCS =
MOD_LIBS =

#### Civilization 4 (Japanese Version) ####
## Uncomment to define the macros for Japanese version
#CYBERFRONT = 1

#### Rise of Mankind - A new dawn ####
## Uncomment to define the macros for ROM-AND
#ROM_AND = 1
!IFDEF ROM_AND
Debug_MOD_CFLAGS = /D_MOD_SENTRY /D_MOD_FRACTRADE /D_MOD_GOVWORKERS /DQC_MASTERY_VICTORY /DLOG_AI /D_MOD_GWARM /D_MOD_SHAM_SPOILER /DFP_PROFILE_ENABLE /DC2C_BUILD /DUSE_INTERNAL_PROFILER /DSCALE_CITY_LIMITS
Release_MOD_CFLAGS = /D_MOD_SENTRY /D_MOD_FRACTRADE /D_MOD_GOVWORKERS /DQC_MASTERY_VICTORY /D_MOD_GWARM /D_MOD_SHAM_SPOILER /DC2C_BUILD /DSCALE_CITY_LIMITS
Final_Release_MOD_CFLAGS = /D_MOD_SENTRY /D_MOD_FRACTRADE /D_MOD_GOVWORKERS /DQC_MASTERY_VICTORY /DLOG_AI /DFP_PROFILE_ENABLE /D_MOD_GWARM /D_MOD_SHAM_SPOILER /DC2C_BUILD /DUSE_INTERNAL_PROFILER /DSCALE_CITY_LIMITS
MOD_LDFLAGS = /TLBID:1
MOD_INCS = 
MOD_LIBS = thread.obj exceptions.obj condition.obj xtime.obj mutex.obj once.obj recursive_mutex.obj read_write_mutex.obj tss_hooks.obj
!ENDIF

#### You shouldn't need to modify anything beyond this point ####
#################################################################

DEBUG_DIR=Debug
RELEASE_DIR=Release
FINAL_RELEASE_DIR=Final_Release

#### Target Files ####
TARGET=CvGameCoreDLL

Debug_BIN = $(DEBUG_DIR)\$(TARGET).dll
Release_BIN = $(RELEASE_DIR)\$(TARGET).dll
Final_Release_BIN=$(FINAL_RELEASE_DIR)\$(TARGET).dll

!IF [IF NOT EXIST $(TARGET).rc EXIT 1] == 0
Debug_RESOURCE = $(DEBUG_DIR)\$(TARGET).res
Release_RESOURCE = $(RELEASE_DIR)\$(TARGET).res
Final_Release_RESOURCE = $(FINAL_RELEASE_DIR)\$(TARGET).res
!ENDIF

Debug_STATICLIB = $(DEBUG_DIR)\$(TARGET).lib
Release_STATICLIB = $(RELEASE_DIR)\$(TARGET).lib
Final_Release_STATICLIB = $(FINAL_RELEASE_DIR)\$(TARGET).lib

Debug_LIBDEF = $(DEBUG_DIR)\$(TARGET).def
Release_LIBDEF = $(RELEASE_DIR)\$(TARGET).def
Final_Release_LIBDEF=$(FINAL_RELEASE_DIR)\$(TARGET).def

Debug_PDB = $(DEBUG_DIR)\$(TARGET).pdb
Release_PDB = $(RELEASE_DIR)\$(TARGET).pdb
Final_Release_PDB = $(FINAL_RELEASE_DIR)\$(TARGET).pdb

Debug_OTHER = $(DEBUG_DIR)\$(TARGET).exp $(DEBUG_DIR)\$(TARGET).ilk
Release_OTHER = $(RELEASE_DIR)\$(TARGET).exp
Final_Release_OTHER = $(FINAL_RELEASE_DIR)\$(TARGET).exp

PCH = CvGameCoreDLL.h
!IFDEF PCH
Debug_PCH = $(DEBUG_DIR)\$(PCH:h=pch)
Release_PCH = $(RELEASE_DIR)\$(PCH:h=pch)
Final_Release_PCH = $(FINAL_RELEASE_DIR)\$(PCH:h=pch)
!ENDIF

#### CFLAGS ####
## Targets compiler flags
# /EHsc   catches C++ exceptions only and tells the compiler to assume that extern C functions never throw a C++ exception
# /Gd     Use the __cdecl calling convention (x86 only). 
# /GR     enable run-time type information (RTTI)
# /G7     optimize for Pentium 4 and above
# /MD     multithreaded normal DLL with MSVCRT.dll
# /MDd    multithreaded debug DLL with MSVCRTD.dll
# /O2     optimize for speed (equal to /Og /Oi /Ot /Oy /Ob2 /Gs /GF /Gy)
# /Od     disables optimization
# /RTC    enables run-time error checking
# /W3     warning level 3
# /Zi     generates complete debugging information

PROJECT_CFLAGS = /EHsc /Gd /GR /G7 /W3 /DWIN32 /D_WINDOWS /D_USRDLL /DCVGAMECOREDLL_EXPORTS /Yu"$(PCH)"
!IFDEF CYBERFRONT
PROJECT_CFLAGS = $(PROJECT_CFLAGS) /DCYBERFRONT
!ENDIF
#Debug_SAFE_CFLAGS = $(GLOBAL_CFLAGS) $(PROJECT_CFLAGS) /MDd /Od /RTC1 /D_DEBUG /Fp"$(Debug_PCH)" /Fd"$(Debug_PDB)" $(Debug_MOD_CFLAGS)
Debug_CFLAGS = $(GLOBAL_CFLAGS) $(PROJECT_CFLAGS) /Zi /MDd /Od /RTC1 /D_DEBUG /Fp"$(Debug_PCH)" /Fd"$(Debug_PDB)" $(Debug_MOD_CFLAGS)
Release_CFLAGS = $(GLOBAL_CFLAGS) $(PROJECT_CFLAGS) /MD /O2 /DNDEBUG /DFINAL_RELEASE /Fp"$(Release_PCH)" /Fd"$(Release_PDB)" $(Release_MOD_CFLAGS)
Final_Release_CFLAGS = $(GLOBAL_CFLAGS) $(PROJECT_CFLAGS) /MD /O2 /DNDEBUG /DFINAL_RELEASE /Fp"$(Final_Release_PCH)" /Fd"$(Final_Release_PDB)" $(Final_Release_MOD_CFLAGS)

#### LDFLAGS ####
## Targets linker flags
# /DEBUG              creates debugging information
# /INCREMENTAL        controls incremental linking
# /LARGEADDRESSAWARE  tells the compiler that the application supports addresses larger than two gigabytes
# /OPT:REF            eliminates functions and/or data that are never referenced
# /OPT:ICF            perform identical COMDAT folding
# /SUBSYSTEM          specify Subsystem

PROJECT_LDFLAGS = /DLL /NOLOGO /SUBSYSTEM:WINDOWS /LARGEADDRESSAWARE $(MOD_LDFLAGS)
Debug_LDFLAGS = $(GLOBAL_LDFLAGS) $(PROJECT_LDFLAGS) /INCREMENTAL /DEBUG /NODEFAULTLIB:msvcprtd.lib /IMPLIB:"$(Debug_STATICLIB)" /PDB:"$(Debug_PDB)"
Release_LDFLAGS = $(GLOBAL_LDFLAGS) $(PROJECT_LDFLAGS) /INCREMENTAL:NO /DEBUG /OPT:REF /OPT:ICF /IMPLIB:"$(Release_STATICLIB)" /PDB:"$(Release_PDB)"
Final_Release_LDFLAGS = $(GLOBAL_LDFLAGS) $(PROJECT_LDFLAGS) /INCREMENTAL:NO /DEBUG /OPT:REF /OPT:ICF /IMPLIB:"$(Final_Release_LIBDEF)" /PDB:"$(Final_Release_PDB)"

#### INCLUDES ####
PROJECT_INCS = /I"$(GLOBALBOOST)/include" /I"$(GLOBALPYTHON)/include"
Debug_INCS = $(GLOBAL_INCS) $(PROJECT_INCS) $(MOD_INCS)
Release_INCS = $(GLOBAL_INCS) $(PROJECT_INCS) $(MOD_INCS)
Final_Release_INCS = $(GLOBAL_INCS) $(PROJECT_INCS) $(MOD_INCS)

#### LIBS ####
PROJECT_LIBS = winmm.lib user32.lib psapi.lib /LIBPATH:"$(GLOBALPYTHON)/libs" /LIBPATH:"$(GLOBALBOOST)/libs/" boost_python-vc71-mt-1_32.lib
Debug_LIBS = $(GLOBAL_LIBS) $(PROJECT_LIBS) $(MOD_LIBS) msvcprt.lib #/NODEFAULTLIB:msvcprtd.lib
Release_LIBS = $(GLOBAL_LIBS) $(PROJECT_LIBS) $(MOD_LIBS)
Final_Release_LIBS = $(GLOBAL_LIBS) $(PROJECT_LIBS) $(MOD_LIBS)

#### Objects ####
Debug_LINKOBJS=$(Debug_OBJS)
Release_LINKOBJS=$(Release_OBJS)
Final_Release_LINKOBJS=$(Final_Release_OBJS)

#### Auto SOURCES/OBJS ####
!IFNDEF CLEAN
!IF [ECHO SOURCES= \> sources.mk] == 0 && \
    [FOR %i IN (*.cpp) DO @ECHO. "%i" \>> sources.mk] == 0 && \
    [ECHO.>> sources.mk] == 0 && \
    [ECHO Debug_OBJS= \>> sources.mk] == 0 && \
    [FOR /F "delims=." %i IN ('dir /b *.cpp') DO @ECHO. $(DEBUG_DIR)\%i.obj \>> sources.mk] == 0 && \
    [ECHO.>> sources.mk] == 0 && \
    [ECHO Release_OBJS= \>> sources.mk] == 0 && \
    [FOR /F "delims=." %i IN ('dir /b *.cpp') DO @ECHO. $(RELEASE_DIR)\%i.obj \>> sources.mk] == 0 && \
    [ECHO.>> sources.mk] == 0  && \
    [ECHO Final_Release_OBJS= \>> sources.mk] == 0 && \
    [FOR /F "delims=." %i IN ('dir /b *.cpp') DO @ECHO. $(FINAL_RELEASE_DIR)\%i.obj \>> sources.mk] == 0 && \
    [ECHO.>> sources.mk] == 0
!INCLUDE sources.mk
!IF [DEL sources.mk]
!ENDIF
!ENDIF
!ENDIF

#### Targets ####
#################

.PHONY: all clean Debug_clean Release_clean Final_Release_clean Debug Release Final_Release

all: Debug Final_Release Release

clean: Debug_clean Release_clean Final_Release_clean

Debug_clean:
	@FOR %i IN ($(Debug_BIN) $(Debug_STATICLIB) $(Debug_LIBDEF) \
		$(DEBUG_DIR)\*.obj $(DEBUG_DIR)\*.@ $(Debug_RESOURCE) \
		$(Debug_PCH) $(Debug_PDB) $(Debug_OTHER)) DO @IF EXIST "%i" DEL "%i"

Release_clean:
	@FOR %i IN ($(Release_BIN) $(Release_STATICLIB) $(Release_LIBDEF) \
		$(RELEASE_DIR)\*.obj $(RELEASE_DIR)\*.@ $(Release_RESOURCE) \
		$(Release_PCH) $(Release_PDB) $(Release_OTHER)) DO @IF EXIST "%i" DEL "%i"
		
Final_Release_clean:
	@FOR %i IN ($(Final_Release_BIN) $(Final_Release_STATICLIB) $(Final_Release_LIBDEF) \
		$(FINAL_RELEASE_DIR)\*.obj $(FINAL_RELEASE_DIR)\*.@ $(Final_Release_RESOURCE) \
		$(Final_Release_PCH) $(Final_Release_PDB) $(Final_Release_OTHER)) DO @IF EXIST "%i" DEL "%i"

Debug: Debug_DIR Debug_unfinished $(Debug_PCH) $(Debug_BIN)
!IFDEF OUTPUT
	-COPY "$(Debug_BIN)" "$(OUTPUT)\."
!ENDIF

Release: Release_DIR Release_unfinished $(Release_PCH) $(Release_BIN)
!IFDEF OUTPUT
	-COPY "$(Release_BIN)" "$(OUTPUT)\."
!ENDIF

Final_Release: Final_Release_DIR Final_Release_unfinished $(Final_Release_PCH) $(Final_Release_BIN)
!IFDEF OUTPUT
	-COPY "$(Final_Release_BIN)" "$(OUTPUT)\."
!ENDIF

Debug_DIR:
	-@IF NOT EXIST "$(DEBUG_DIR)\." MKDIR "$(DEBUG_DIR)"

Release_DIR:
	-@IF NOT EXIST "$(RELEASE_DIR)\." MKDIR "$(RELEASE_DIR)"
	
Final_Release_DIR:
	-@IF NOT EXIST "$(FINAL_RELEASE_DIR)\." MKDIR "$(FINAL_RELEASE_DIR)"

Debug_unfinished:
	@ECHO.>$(DEBUG_DIR)\unfinished.@
	@FOR /F "delims=@" %i IN ('dir /b $(DEBUG_DIR)\*.@') DO \
		@IF EXIST "$(DEBUG_DIR)\%i" DEL "$(DEBUG_DIR)\%i"
	@FOR /F %i IN ('dir /b $(DEBUG_DIR)\*.@') DO \
		@IF EXIST "$(DEBUG_DIR)\%i" DEL "$(DEBUG_DIR)\%i"

Release_unfinished:
	@ECHO.>$(RELEASE_DIR)\unfinished.@
	@FOR /F "delims=@" %i IN ('dir /b $(RELEASE_DIR)\*.@') DO \
		@IF EXIST "$(RELEASE_DIR)\%i" DEL "$(RELEASE_DIR)\%i"
	@FOR /F %i IN ('dir /b $(RELEASE_DIR)\*.@') DO \
		@IF EXIST "$(RELEASE_DIR)\%i" DEL "$(RELEASE_DIR)\%i"
		
Final_Release_unfinished:
	@ECHO.>$(FINAL_RELEASE_DIR)\unfinished.@
	@FOR /F "delims=@" %i IN ('dir /b $(FINAL_RELEASE_DIR)\*.@') DO \
		@IF EXIST "$(FINAL_RELEASE_DIR)\%i" DEL "$(FINAL_RELEASE_DIR)\%i"
	@FOR /F %i IN ('dir /b $(FINAL_RELEASE_DIR)\*.@') DO \
		@IF EXIST "$(FINAL_RELEASE_DIR)\%i" DEL "$(FINAL_RELEASE_DIR)\%i"

$(Debug_BIN): $(Debug_LINKOBJS) $(Debug_RESOURCE)
	@$(LD) /out:$(Debug_BIN) $(Debug_LDFLAGS) $(Debug_LIBS) $(Debug_LINKOBJS) $(Debug_RESOURCE)

$(Release_BIN): $(Release_LINKOBJS) $(Release_RESOURCE)
	@$(LD) /out:$(Release_BIN) $(Release_LDFLAGS) $(Release_LIBS) $(Release_LINKOBJS) $(Release_RESOURCE)
	
$(Final_Release_BIN): $(Final_Release_LINKOBJS) $(Final_Release_RESOURCE)
	@$(LD) /out:$(Final_Release_BIN) $(Final_Release_LDFLAGS) $(Final_Release_LIBS) $(Final_Release_LINKOBJS) $(Final_Release_RESOURCE)

.cpp{$(DEBUG_DIR)}.obj:
	@ECHO.>"$*.obj.@"
	@$(CPP) /nologo $(Debug_CFLAGS) $(Debug_INCS) /Fo$*.obj /c $<
	@DEL "$*.obj.@"

.cpp{$(RELEASE_DIR)}.obj:
	@ECHO.>"$*.obj.@"
	@$(CPP) /nologo $(Release_CFLAGS) $(Release_INCS) /Fo$*.obj /c $<
	@DEL "$*.obj.@"
	
.cpp{$(FINAL_RELEASE_DIR)}.obj:
	@ECHO.>"$*.obj.@"
	@$(CPP) /nologo $(Final_Release_CFLAGS) $(Final_Release_INCS) /Fo$*.obj /c $<
	@DEL "$*.obj.@"

!IFDEF PCH
$(Debug_PCH) $(DEBUG_DIR)\_precompile.obj:
	@ECHO.>"$(Debug_PCH).@"
	@ECHO.>"$(DEBUG_DIR)\_precompile.obj.@"
	@$(CPP) /nologo $(Debug_CFLAGS) $(Debug_INCS) /Yc"$(PCH)" /Fo"$(DEBUG_DIR)\_precompile.obj" /c _precompile.cpp
	@DEL "$(Debug_PCH).@"
	@DEL "$(DEBUG_DIR)\_precompile.obj.@"

$(Release_PCH) $(RELEASE_DIR)\_precompile.obj:
	@ECHO.>"$(Release_PCH).@"
	@ECHO.>"$(RELEASE_DIR)\_precompile.obj.@"
	@$(CPP) /nologo $(Release_CFLAGS) $(Release_INCS) /Yc"$(PCH)" /Fo"$(RELEASE_DIR)\_precompile.obj" /c _precompile.cpp
	@DEL "$(Release_PCH).@"
	@DEL "$(RELEASE_DIR)\_precompile.obj.@"
	
$(Final_Release_PCH) $(FINAL_RELEASE_DIR)\_precompile.obj:
	@ECHO.>"$(Final_Release_PCH).@"
	@ECHO.>"$(FINAL_RELEASE_DIR)\_precompile.obj.@"
	@$(CPP) /nologo $(Final_Release_CFLAGS) $(Final_Release_INCS) /Yc"$(PCH)" /Fo"$(FINAL_RELEASE_DIR)\_precompile.obj" /c _precompile.cpp
	@DEL "$(Final_Release_PCH).@"
	@DEL "$(FINAL_RELEASE_DIR)\_precompile.obj.@"

!ENDIF

.rc{$(DEBUG_DIR)}.res:
	@ECHO.>"$*.res.@"
	@$(RC) /Fo$@ $(Debug_INCS) $(GLOBAL_RES_INCS) $<
	@DEL "$*.res.@"

.rc{$(RELEASE_DIR)}.res:
	@ECHO.>"$*.res.@"
	@$(RC) /Fo$@ $(Release_INCS) $(GLOBAL_RES_INCS) $<
	@DEL "$*.res.@"
	
.rc{$(FINAL_RELEASE_DIR)}.res:
	@ECHO.>"$*.res.@"
	@$(RC) /Fo$@ $(Final_Release_INCS) $(GLOBAL_RES_INCS) $<
	@DEL "$*.res.@"

!IFDEF EXCLUDE

$(DEBUG_DIR)\$(EXCLUDE).obj: $(EXCLUDE).cpp
	@ECHO.>"$*.obj.@"
	@ECHO.>"$*-dummy.cpp"
	@ECHO [EXCLUDE start]
	@$(CPP) /nologo $(Debug_CFLAGS) $(Debug_INCS) /Y- /Fo$@ /c "$*-dummy.cpp"
	@ECHO [EXCLUDE end]
	@DEL "$*-dummy.cpp"
	@DEL "$*.obj.@"

$(RELEASE_DIR)\$(EXCLUDE).obj: $(EXCLUDE).cpp
	@ECHO.>"$*.obj.@"
	@ECHO.>"$*-dummy.cpp"
	@ECHO [EXCLUDE start]
	@$(CPP) /nologo $(Release_CFLAGS) $(Release_INCS) /Y- /Fo$@ /c "$*-dummy.cpp"
	@ECHO [EXCLUDE end]
	@DEL "$*-dummy.cpp"
	@DEL "$*.obj.@"
	
$(FINAL_RELEASE_DIR)\$(EXCLUDE).obj: $(EXCLUDE).cpp
	@ECHO.>"$*.obj.@"
	@ECHO.>"$*-dummy.cpp"
	@ECHO [EXCLUDE start]
	@$(CPP) /nologo $(Final_Release_CFLAGS) $(Final_Release_INCS) /Y- /Fo$@ /c "$*-dummy.cpp"
	@ECHO [EXCLUDE end]
	@DEL "$*-dummy.cpp"
	@DEL "$*.obj.@"

!ENDIF

!IFDEF FD

!IF [IF NOT EXIST $(FD) EXIT 1] == 0
!IF [$(FD) --objectextension=pch -q -O $(DEBUG_DIR) $(TARGET).cpp > depends] != 0 || \
    [$(FD) --objectextension=obj -q -O $(DEBUG_DIR) $(SOURCES) >> depends] != 0 || \
    [$(FD) --objectextension=pch -q -O $(RELEASE_DIR) $(TARGET).cpp >> depends] != 0 || \
    [$(FD) --objectextension=obj -q -O $(RELEASE_DIR) $(SOURCES) >> depends] != 0 || \
    [$(FD) --objectextension=pch -q -O $(FINAL_RELEASE_DIR) $(TARGET).cpp >> depends] != 0 || \
    [$(FD) --objectextension=obj -q -O $(FINAL_RELEASE_DIR) $(SOURCES) >> depends] != 0
!MESSAGE Error running fastdep.
!ENDIF
!ELSE
!IF [ECHO "fastdep.exe" NOT FOUND! && \
     ECHO Please edit Makefile to reflect the correct path of fastdep. && \
     ECHO. ]
!ENDIF
!ENDIF

!ENDIF

!IF EXIST(depends)
!INCLUDE depends
!ENDIF
