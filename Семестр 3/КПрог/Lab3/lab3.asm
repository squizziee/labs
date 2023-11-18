	ORG $8000
	LDX #$8200
	LDAA #$00
	LDAB #$00
	STAA $21
	STAB $22
	JMP LOOP
LOOP:	
	CMPX #$82ff
	BEQ END
	LDAA #$00
	STAA $8400
	LDAA 0,X
	STAA $8401
	LDD $8400
	LDY $21
	JSR ADD_16X16
	INX
	JMP LOOP
ADD_16X16:
	STD $1
 	STY $3
 	LDAA $2
 	LDAB $4
 	ABA
 	STAA $22
 	LDAA #0
 	ADCA #0 
 	STAA $21
 	LDAA $1
 	LDAB $3
 	ABA
 	PSHA
 	LDAA #0
 	ADCA #0
 	STAA $20
 	PULA
 	LDAB $21
 	ABA
 	STAA $21
	LDY $21
	RTS
END:	
	BRA *