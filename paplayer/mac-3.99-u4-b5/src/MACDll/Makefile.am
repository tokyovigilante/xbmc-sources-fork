AUTOMAKE_OPTIONS = gnu

SUBDIRS =

lib_LTLIBRARIES = libmacdll.la

INCLUDES = -I$(top_srcdir)/src/Shared -I$(top_srcdir)/src/MACLib

libmacdll_la_LIBADD = $(shared_ldadd) $(asm_ldadd)
libmacdll_la_LDFLAGS = \
	-export-dynamic \
	-version-info 2:0:0

libmacdll_la_SOURCES = \
	MACDll.cpp 

pkginclude_HEADERS = \
	MACDll.h

