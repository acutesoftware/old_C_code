ORIGIN = PWB
ORIGIN_VER = 2.1.49
PROJ = FINDAT
PROJFILE = FINDAT.MAK
DEBUG = 0

BSCMAKE  = bscmake
SBRPACK  = sbrpack
NMAKEBSC1  = set
NMAKEBSC2  = nmake
PBTDEPEND  = $(PROJ).com
PREP  = prep
PROFILE  = profile
PLIST  = plist
PROFSET  = set
PROFNMAKE  = nmake
CC  = cl
CFLAGS_G  = /W4 /BATCH
CFLAGS_D  = /f- /Od /Zi
CFLAGS_R  = /f- /Ot /Ol /Og /Oe /Oi
CXX  = cl
CXXFLAGS_G  = /W2 /BATCH
CXXFLAGS_D  = /f /Zi /Od
CXXFLAGS_R  = /f- /Ot /Oi /Ol /Oe /Og /Gs
MAPFILE_D  = NUL
MAPFILE_R  = NUL
LFLAGS_G  = /NOI /TINY /NOE /BATCH /ONERROR:NOEXE
LFLAGS_D  = /CO /FAR
LFLAGS_R  = /FAR
LINKER	= link
ILINK  = ilink
LRF  = echo > NUL
ILFLAGS  = /a /e
RT_OBJS  = crtcom.lib

FILES  = FINDAT.C
OBJS  = FINDAT.obj
SBRS  = FINDAT.sbr

all: $(PROJ).com

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .obj .sbr .c

FINDAT.obj : FINDAT.C
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoFINDAT.obj FINDAT.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoFINDAT.obj FINDAT.C
<<
!ENDIF

FINDAT.sbr : FINDAT.C
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRFINDAT.sbr FINDAT.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRFINDAT.sbr FINDAT.C
<<
!ENDIF


$(PROJ).bsc : $(SBRS)
	$(BSCMAKE) @<<
$(BRFLAGS) $(SBRS)
<<

$(PROJ).pbt : 
	$(PROFSET) MAKEFLAGS=
	$(PROFNMAKE) $(NMFLAGS) -f $(PROJFILE) $(PBTDEPEND)
	$(PREP) /P $(PBTDEPEND) /OT $(PROJ).pbt

$(PROJ).com : $(OBJS)
!IF $(DEBUG)
	$(LRF) @<<$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_D)
$(LIBS: = +^
) +
$(LLIBS_G: = +^
) +
$(LLIBS_D: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_D);
<<
!ELSE
	$(LRF) @<<$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_R)
$(LIBS: = +^
) +
$(LLIBS_G: = +^
) +
$(LLIBS_R: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_R);
<<
!ENDIF
	$(LINKER) @$(PROJ).lrf


.c.obj :
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo$@ $<
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo$@ $<
<<
!ENDIF

.c.sbr :
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FR$@ $<
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FR$@ $<
<<
!ENDIF


run: $(PROJ).com
	$(PROJ).com $(RUNFLAGS)

debug: $(PROJ).com
	CV $(CVFLAGS) $(PROJ).com $(RUNFLAGS)
