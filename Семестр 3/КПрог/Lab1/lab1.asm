	org $8000	; start of program in memory
START:
	LDX #$1234	; set X to $1234
	STX $9000
	LDAA $9000
	STAA $9002
	LDX $9001
	
	
