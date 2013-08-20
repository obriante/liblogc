dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.57)
AC_INIT([liblogc], [1.1.1], [orazio.briante@hotmail.it], )
AC_CONFIG_SRCDIR(configure.ac)

AC_CANONICAL_SYSTEM

LOGC_MAJOR_VERSION=$(echo $PACKAGE_VERSION | cut -d. -f1)
LOGC_MINOR_VERSION=$(echo $PACKAGE_VERSION | cut -d. -f2)
LOGC_MICRO_VERSION=$(echo $PACKAGE_VERSION | cut -d. -f3)
LOGC_EXTRA_VERSION=$(echo $PACKAGE_VERSION | cut -d. -f4)

LOGC_VERSION=$LOGC_MAJOR_VERSION.$LOGC_MINOR_VERSION.$LOGC_MICRO_VERSION${SNAPSHOT:+.$SNAPSHOT}

LT_LOGC_VERSION=1.1.0

AC_SUBST(LOGC_MAJOR_VERSION)
AC_SUBST(LOGC_MINOR_VERSION)
AC_SUBST(LOGC_MICRO_VERSION)
AC_SUBST(LT_VERSION)
AC_SUBST(LOGC_VERSION)

AC_PROG_CC
AC_PROG_CXX
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([no])])

dnl Initialize automake
AM_INIT_AUTOMAKE()

dnl this allows us specify individual liking flags for each target
AM_PROG_CC_C_O 

dnl Doxygen
DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(ON)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(ON)
DX_PS_FEATURE(OFF)
DX_INIT_DOXYGEN([$PACKAGE_NAME],[liblogc.doxyfile],[doc])

AC_CONFIG_SUBDIRS( liblogc )
	liblogc_CFLAGS="-I\$(top_srcdir)/include"
	liblogc_LIBS="\$(top_builddir)/src/liblogc.a"
AC_SUBST(liblogc_CFLAGS)
AC_SUBST(liblogc_LIBS)

AC_PROG_RANLIB

AC_CONFIG_FILES(
Makefile
src/Makefile
include/Makefile
include/logc/Makefile
tests/Makefile
tests/simplelog/Makefile
tests/multilog/Makefile
tests/logqueue/Makefile
)
AC_OUTPUT