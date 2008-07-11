
netembryoincludedir = $(top_srcdir)/include

noinst_LTLIBRARIES = libwsocket.la

libwsocket_la_LDFLAGS = 

libwsocket_la_SOURCES =		multicast.c \
				socket.c \
				sock_ntop_host.c \
				get_info.c \
				Sock.c \
				$(top_srcdir)/include/ssl.h \
				$(top_srcdir)/include/wsocket-internal.h

if ENABLE_SSL
libwsocket_la_SOURCES += ssl.c
endif

INCLUDES = -I$(netembryoincludedir) -I$(top_srcdir)
