# Makefile for creating3
# Chi-Sheng Shih
# 2016-09-08
#
# Useful commands
ECHO = echo

# Commands for assemble compiler
ASM = nasm
DD = dd

# Source files
SOURCE = HelloWorld2017.asm
BIN = $(patsubst %.asm,%.bin,$(SOURCE))
IMG = $(patsubst %.asm,%.img,$(SOURCE))
# .PHONY: clean
all:
	@$(ECHO) "Source file is $(SOURCE)"
	@$(ECHO) "Binary file is $(BIN)"
	@$(ECHO) "Image file is $(IMG)"
	@$(ECHO) "--------------------------------------------------------------"
	@$(ECHO) "Creating binary files"
	@$(ECHO) "--------------------------------------------------------------"
	$(ASM) -f bin -o $(BIN) $(SOURCE)
	@$(ECHO) "--------------------------------------------------------------"
	@$(ECHO) "Creating disk image file."
	@$(ECHO) "--------------------------------------------------------------"
	$(DD) if=$(BIN) of=$(IMG)

clean:
	@$(ECHO) "--------------------------------------------------------------"
	@$(ECHO) "Clean all temporary files"
	@$(ECHO) "--------------------------------------------------------------"
	rm -rf $(BIN) $(IMG)
