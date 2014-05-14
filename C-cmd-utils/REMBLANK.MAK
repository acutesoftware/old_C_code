ORIGIN = PWB
ORIGIN_VER = 2.1.49
PROJ = REMBLANK
PROJFILE = REMBLANK.MAK
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
CFLAGS_G  = /W4 /G2 /BATCH
CFLAGS_D  = /f /Od /Zi
CFLAGS_R  = /f- /Ob0 /Od /Ol /Og /Oe /Oi /Gs
CXX  = cl
CXXFLAGS_G  = /W4 /BATCH
CXXFLAGS_D  = /f /Od /Zi
CXXFLAGS_R  = /f- /Ot /Ol /Og /Oe /Oi /Gs
MAPFILE_D  = NUL
MAPFILE_R  = NUL
LFLAGS_G  = /NOI /NOE /TINY /BATCH /ONERROR:NOEXE
LFLAGS_D  = /CO /FAR
LFLAGS_R  = /FAR /NOPACKC
LINKER	= link
ILINK  = ilink
LRF  = echo > NUL
ILFLAGS  = /a /e
RT_OBJS  = crtcom.lib
NMFLAGS  = /M

FILES  = REMBLANK.C
OBJS  = REMBLANK.obj
SBRS  = REMBLANK.sbr

all: $(PROJ).com

.SUFFIXES:
.SUFFIXES: .obj .sbr .c
.SUFFIXES: .obj .sbr .c

REMBLANK.obj : REMBLANK.C
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /FoREMBLANK.obj REMBLANK.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /FoREMBLANK.obj REMBLANK.C
<<
!ENDIF

REMBLANK.sbr : REMBLANK.C
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_D) /FRREMBLANK.sbr REMBLANK.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/Zs $(CFLAGS_G)
$(CFLAGS_R) /FRREMBLANK.sbr REMBLANK.C
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
