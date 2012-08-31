noinst_LIBRARIES = liblogc.a

liblogc_a_SOURCES = \
logc.c

liblogc_a_LIBADD =

if DEBUG

AM_CFLAGS = -g3 -O0 \
	-DDEBUG \
	@liblogc_CFLAGS@

else

AM_CFLAGS = -O2 \
	@liblogc_CFLAGS@

endif




