	ORG $8000
METHOD_1:
	LDAA #%00001010
	STAA $10
	LDX #$10
	BSET 0,X,#%01101010
METHOD_2:
	LDAA #%00001010
	STAA $10
	LDAB #%01101010
	ORAB #%10101010
	STAB $10
METHOD_3:
	LDAA #%0000101
	STAA $10
	SEC
	ADCA #$00
	STAA $10
	ROLA
	SEC
	ADCA #$00
	STAA $10
	ROL $10
	ROL $10
	ROL $10
	ROL $10
	ROL $10