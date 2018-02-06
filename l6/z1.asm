
	org $1000
start	equ *
	lda <text
	sta $80
	lda >text
	sta $81
	ldy #1
	lda #%10101001
	jsr phex

	lda <text
	ldx >text
	jsr $ff80
	brk

phex	pha
	jsr pxdig
	pla
	lsr @ ; przesunięcie bitowe w prawo
	lsr @
	lsr @
	lsr @
pxdig	and #%00001111
	ora #'0'
	cmp #'9'+1 ; porównanie aku. z wartoscia
	bcc pr
	clc
	adc #'a'-'9'-1
pr	sta ($80),y
	dey
	rts

text	equ *
	dta b(0),b(0)
	dta b(10) ; '\n'
	dta b(0)

	org $2E0 
	dta a(start) ; instrukcja między nawiasami rozpocznie program

