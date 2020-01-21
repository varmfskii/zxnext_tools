	GLOBAL _main
	defc screen=$4000
	defc next_sel=$243b
	defc next_ctl=$253b
	defc spr_sel=$303b
	defc spr_ctl=$57
	defc spr_pat=$5b
	defc sprx=screen
	defc spry=screen+$0100
	org $c000
_main:
	;; sprite 0
	ld bc,spr_sel
	xor a
	out (c),a
	;; write pattern
	ld bc,spr_pat 
	ld hl,circle
	otir
	;; move sprite layer to top 
	ld bc,next_sel
	ld a,$15
	out (c),a
	inc b
	in a,(c)
	ld d,a
	and $1c
	srl a
	srl a
	ld hl,table
	add a,l
	ld l,a
	ld e,(hl)
	ld a,d
	and a,$80
	or a,e
	;; ld a,$03
	out (c),a
	;; set position to 0
	ld de,$0000
	ei
inc:				; move sprite and increment
	call draw
	inc de
	ld a,d
	cp $01
	jp nz,inc
	ld a,e
	cp $30
	jp nz,inc
dec:				; move sprite and decrement
	call draw
	dec de
	ld a,d
	cp $00 
	jp nz,dec
	ld a,e
	cp $00
	jp nz,dec
	jp inc
draw:
	xor a
	ld bc,spr_sel
	out (c),a
	ld c,spr_ctl
	out (c),e
	ld a,$78
	out (c),a
	out (c),d
	ld a,$80
	out (c),a
	halt
	ret
circle:	
	defb $e3,$e3,$e3,$e3,$e3,$e0,$e0,$e0,$e0,$e0,$e0,$e3,$e3,$e3,$e3,$e3
	defb $e3,$e3,$e3,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e3,$e3,$e3
	defb $e3,$e3,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e3,$e3
	defb $e3,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e3
	defb $e3,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e3
	defb $e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0
	defb $e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0
	defb $e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0
	defb $e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0
	defb $e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0
	defb $e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0
	defb $e3,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e3
	defb $e3,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e3
	defb $e3,$e3,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e3,$e3
	defb $e3,$e3,$e3,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e0,$e3,$e3,$e3
	defb $e3,$e3,$e3,$e3,$e3,$e0,$e0,$e0,$e0,$e0,$e0,$e3,$e3,$e3,$e3,$e3
circle_end:	
	defs ((circle_end+$07)&$fff8)-circle_end ; align to 8 byte boundry
table:
	defb $03,$03,$0b,$03,$0b,$0b,$1b,$1f
