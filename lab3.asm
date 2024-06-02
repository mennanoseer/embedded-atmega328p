;
; AssemblerApplication2.asm
;
; Created: 3/5/2024 10:48:14 AM
; Author : MENNA
;


/*
start:
	LDI R20, HIGH(RAMEND)
	OUT SPH, R20
	LDI R20,LOW(RAMEND)
	OUT SPL, R20

    LDI R20, $15 ; Stack Pointer: 0x08FF
	LDI R21, $14 ; Stack Pointer: 0x08FF
	LDI R22, $33 ; Stack Pointer: 0x08FF
	LDI R23, $45 ; Stack Pointer: 0x08FF
	LDI R24, $45 ; Stack Pointer: 0x08FF

	PUSH R20 ; Stack Pointer AFTER: 0x08FE
	PUSH R21 ; Stack Pointer AFTER: 0x08FD
	PUSH R22 ; Stack Pointer AFTER: 0x08FC
	PUSH R23 ; Stack Pointer AFTER: 0x08FB
	PUSH R24 ; Stack Pointer AFTER: 0x08FA

*/
	LDI R20, HIGH(0x01FF)
	OUT SPH, R20
	LDI R20,LOW(0x01FF)
	OUT SPL, R20 

	LDI R21, $13
	STS 0x1FF, R21

	LDI R22, $14
	STS 0x200, R22

	LDI R23, $15
	STS 0x201, R23

	LDI R24, $16
	STS 0x202, R24

	LDI R25, $17
	STS 0x203, R25

	LDI R26, $18
	STS 0x204, R26

	POP R20
	POP R21
	POP R22
	POP R23
	POP R24
