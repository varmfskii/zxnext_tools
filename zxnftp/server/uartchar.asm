	GLOBAL _uartchar

;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
defc _TX	=	0x133b
defc _RX	=	0x143b

;--------------------------------------------------------
; code
;--------------------------------------------------------
	
	SECTION code_compiler
	
;---------------------------------
; Function uartchar
; ---------------------------------

_uartchar:
loop0:	
	ld bc,_TX
	in a,(c)
	bit 0,a 		; UART_DATA
	jr Z,loop0
	inc b
	in a,(c)
	ld l, a
	ret
	
	SECTION IGNORE
