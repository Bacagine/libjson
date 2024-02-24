# 
# Makefile
# 
# Makefile for the project libjson
# 
# This is the a Makefile to my personal JSON C library
#
# Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
#
# Date: 2024-02-24
#

TARGET     = libjson.so
SRCDIR     = src
INCDIR     = include
OBJDIR     = obj
LIBDIR     = lib
BINDIR     = bin
TESTDIR    = tests
SRC        = $(wildcard $(SRCDIR)/*.c)
OBJS       = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
LIB        = $(LIBDIR)/$(TARGET)
LDFLAGS    = -L $(LIBDIR)
LDLIBS     = -lm -pthread
CFLAGS     = -I $(INCDIR) -Wall -Wextra
DEBUGFLAGS = -g -O0 -DDEBUG
CC         = gcc

ifdef DEBUG_COMPILATION
	CFLAGS += $(DEBUGFLAGS) 
	LDFLAGS += $(DEBUGFLAGS)
else
	CFLAGS += -O3
endif

all: distclean $(OBJDIR) $(LIBDIR) $(LIB)
	
$(LIB): $(OBJS)
	$(CC) -shared -o $@ $(OBJS) $(CFLAGS) $(LDLIBS)

$(BINDIR):
	mkdir $@
$(LIBDIR):
	mkdir $@
$(OBJDIR):
	mkdir $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -fPIC -c $< -o $@ $(CFLAGS) $(LDLIBS)

clean:
	rm -rvf $(OBJDIR)

install: all
	./install.sh

uninstall:
	./uninstall.sh

test: all $(BINDIR)
	$(CC) -o $(BINDIR)/test_json $(TESTDIR)/test_json.c  $(CFLAGS) $(LDFLAGS) -ljson
	
distclean: clean
	rm -rvf $(LIBDIR)
	rm -rvf $(BINDIR)
	
.PHONY: all clean debug install uninstall test check dist distclean

