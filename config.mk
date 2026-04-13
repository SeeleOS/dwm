# dwm version
VERSION = 6.8

# Customize below to fit your system

# paths
BINDIR ?= ${PREFIX}/programs
PREFIX ?= /
MANPREFIX = ${PREFIX}/share/man

PKG_CONFIG ?= pkg-config

# Xinerama, comment if you don't want it
XINERAMALIBS ?= $(shell ${PKG_CONFIG} --libs xinerama)
XINERAMAFLAGS ?= -DXINERAMA

# freetype
FREETYPELIBS ?= $(shell ${PKG_CONFIG} --libs fontconfig xft freetype2)
FREETYPEINC ?= $(shell ${PKG_CONFIG} --cflags fontconfig xft freetype2)
# OpenBSD (uncomment)
#FREETYPEINC = ${X11INC}/freetype2
#MANPREFIX = ${PREFIX}/man

# includes and libs
INCS ?= $(shell ${PKG_CONFIG} --cflags x11 xinerama xft fontconfig freetype2)
LIBS ?= $(shell ${PKG_CONFIG} --libs --static x11 xinerama xft fontconfig freetype2) -lXrender -lImlib2 -lXext -lintl -liconv

# flags
CPPFLAGS += -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700L -DVERSION=\"${VERSION}\" ${XINERAMAFLAGS}
#CFLAGS   = -g -std=c99 -pedantic -Wall -O0 ${INCS} ${CPPFLAGS}
CFLAGS += -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os ${INCS}
LDFLAGS += ${LIBS}

# Solaris
#CFLAGS = -fast ${INCS} -DVERSION=\"${VERSION}\"
#LDFLAGS = ${LIBS}

# compiler and linker
CC ?= cc
