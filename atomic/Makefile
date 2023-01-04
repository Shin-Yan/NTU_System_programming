.PHONY: clean all

# Makefile for creating file_FD
# Shin-Yan
# 2023/1/4
#
# Useful command
CC = gcc
ECHO = echo
CFLAGS = -Wall

SOURCE =  $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SOURCE))
all: $(PROGS)
	@$(ECHO) "Source files are $(SOURCE)"
	@$(ECHO) "Program files are $(PROGS)"
	@$(ECHO) "--------------------------------------------------------------"
	@$(ECHO) "Creating program files"
	@$(ECHO) "--------------------------------------------------------------"

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	@$(ECHO) "--------------------------------------------------------------"
	@$(ECHO) "Clean all object files"
	@$(ECHO) "--------------------------------------------------------------"
	rm -rf $(PROGS)