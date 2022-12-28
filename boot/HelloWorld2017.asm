[BITS 16]	; We start with 16 bits bootable program
[ORG 0x7C00]	; The program starts at 0x7C00

main:
	mov si,msg	; mov the msg to be printed to SI register 
	jmp printstr	; Jump to the function to print the string

printstr:
	lodsb		; Copy the byte pointed by DS:SI
	or al, al  	; Set ZF to zero if we reach end of the string
	jz hang		; Jump to hang the terminate printstr
	mov ah, 0x0e	; Mov the instruction code to ah
	int 10h		; Generate an interrupt to trigger video services, specified in AH
	jmp printstr	; Jump to the stat of printstr to print next character
	
hang:
	jmp hang

	msg db "Hello to the class of SP 2017!!", 0	

end:
	times 510 - ($ - $$) db 0 ; 512 bytes -2 bytes (0xAA55) fill the space with zero
	dw 0xAA55	; bootable program
