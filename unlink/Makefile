.PHONY: clean all

# Makefile for creating unlink
# Shin-Yan
# 2023/1/16
#
# Useful command
ECHO = echo
ROOT = ..
LIBAPUE = $(ROOT)/lib/libapue.a

PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

SOURCE =  $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SOURCE))
all: $(PROGS) 
	@$(ECHO) "Source files are $(SOURCE)"
	@$(ECHO) "Program files are $(PROGS)"
	@$(ECHO) "--------------------------------------------------------------"
	@$(ECHO) "Creating program files"
	@$(ECHO) "--------------------------------------------------------------"

%: %.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	@$(ECHO) "--------------------------------------------------------------"
	@$(ECHO) "Clean all object files"
	@$(ECHO) "--------------------------------------------------------------"
	rm -rf $(PROGS)

include $(ROOT)/Make.libapue.inc
