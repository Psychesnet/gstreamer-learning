export PKG_CONFIG_PATH="/usr/local/Cellar/libffi/3.2.1/lib/pkgconfig"
PKG_PACKAGES=gstreamer-1.0
PKG_CFLAGS=$(shell pkg-config --cflags $(PKG_PACKAGES))
PKG_LIBS=$(shell pkg-config --libs $(PKG_PACKAGES))

TARGETS = main
SRCS = main.cpp

PREFIX = $(PJ_PREFIX)
CROSS_COMPILE = $(PJ_TARGET)-

CFLAGS    = $(PLATFORM_CFLAGS) -Wall -W $(PKG_CFLAGS)
CXXFLAGS  = $(CFLAGS)
CPPFLAGS  = $(PLATFORM_CPPFLAGS)
LDFLAGS   = $(PLATFORM_LDFLAGS) $(PKG_LIBS)
LOADLIBES = $(PLATFORM_LOADLIBES)
LDLIBS    = $(PLATFORM_LDLIBS)

CC        = $(CROSS_COMPILE)g++
CPP       = $(CROSS_COMPILE)gcc -E
CXX       = $(CROSS_COMPILE)g++
AS        = $(CROSS_COMPILE)as
AR        = $(CROSS_COMPILE)ar
LD        = $(CROSS_COMPILE)ld
NM        = $(CROSS_COMPILE)nm
OBJCOPY   = $(CROSS_COMPILE)objcopy
OBJDUMP   = $(CROSS_COMPILE)objdump
RANLIB    = $(CROSS_COMPILE)ranlib
READELF   = $(CROSS_COMPILE)readelf
SIZE      = $(CROSS_COMPILE)size
STRINGS   = $(CROSS_COMPILE)strings
STRIP     = $(CROSS_COMPILE)strip


.PHONY: all clean
all: $(TARGETS)
clean:
	rm -f *.o *.d *~
	rm -f $(TARGETS)

install: $(TARGETS)
