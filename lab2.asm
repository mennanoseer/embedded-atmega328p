;
; AssemblerApplication1.asm
;
; Created: 2/27/2024 11:02:45 AM
; Author : MENNA
;

; Question 1:
/*
start:
    ldi r17,0b00000001
	out DDRB,r17
	ldi r18,0b00000001
	out DDRD,r18
	ldi r19,0b00000001
	out PORTB,r19
	in r16,PORTB
	out PORTD,r16
Loop:
	rjmp Loop
*/
	
; Question 2:
/*
	LDI R20, $27
	LDI R21, $15
	SUB R20, R21

	LDI R20, $20
	LDI R21, $15
	SUB R20, R21 ; the half carry falg to 1 (H)

	LDI R24, 95
	LDI R25, 95
	SUB R24, R25 ; Reset H falg and set Z (zero) falg

	LDI R22, 50
	LDI R23, 70
	SUB R22, R23 ; Reset Z flag, and set each of H, S (Sign bit),N (Negative flag), and C (Carry flag)
L1: RJMP L1
*/

;Question 3:
/*
LDI R20, $15
LDI R21, $1
LDI R22, $26
LDI R23, $30

COM R20 ; set S, N, and C flags. R20 = 0xEA
COM R21 ; no falgs are setted. R21 = 0xFE
COM R22 ; no falgs are setted. R22 = 0xD9
COM R23 ; no falgs are setted. R22 = 0xCF
*/

;Question 4:
	LDI R20, $92
	LDI R21, $23
	LDI R22, $66
	LDI R23, $87
	LDI R24, $F5

	ADD R20, R21 ; set falgs: S, N.
	ADD R20, R22 ; set falg: C. Reset: S, N
	ADD R20, R23 ; set flags:  H, S, N. Reset: C
	ADD R20, R24 ; set flag: C. Reset: H