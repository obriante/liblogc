noinst_PROGRAMS=logTest

logTest_SOURCES= \
logTest.c

logTest_LDADD= \
@liblogc_LIBS@


if DEBUG

AM_CFLAGS = -g3 -O0 \
@liblogc_CFLAGS@

else

AM_CFLAGS = -O2 \
@liblogc_CFLAGS@

endif
