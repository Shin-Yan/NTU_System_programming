# Makefile for creating syncio
# Shin-Yan
# 2022/12/28
#
# Useful command
CC = gcc
ECHO = echo
SOURCE = bufferIO.c

BIN = $(patsubst %.c,%,$(SOURCE))
all:
	@$(ECHO) "Source file is $(SOURCE)"
	@$(ECHO) "Binary file is $(BIN)"
	@$(ECHO) "--------------------------------------------------------------"
	@$(ECHO) "Creating binary files"
	@$(ECHO) "--------------------------------------------------------------"
	$(CC) -o $(BIN) $(SOURCE)

clean:
	@$(ECHO) "--------------------------------------------------------------"
	@$(ECHO) "Clean all temporary files"
	@$(ECHO) "--------------------------------------------------------------"
	rm -rf $(BIN)