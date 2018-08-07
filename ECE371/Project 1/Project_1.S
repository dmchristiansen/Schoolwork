@ Daniel Christiansen
@ ECE 371
@ Design Project 1
@ Fahrenheit to Celsius conversion

.text
.global _start
_start:
.equ	ARRAY_SIZE, 16				@ Set array size to 16 (makes it easier to change)
		MOV R1, #ARRAY_SIZE			@ Use R3 as index value/array size
		LDR R2, =FAHRENHEIT_TEMPS	@ Load pointer to FAHRENHEIT_TEMPS array
		LDR R3, =CELSIUS_TEMPS		@ Load pointer to CELSIUS_TEMPS array
		LDR R4, =FAHRENHEIT_AVE		@ Load pointer to Fahrenheit Average
		LDR R5, =CELSIUS_AVE		@ Load pointer to Clesius Average
		BL CONVERT					@ Jump to convert procedure
		MOV R0, R2					@ Load pointer to Fahrenheit array to pass to procedure
		BL AVERAGE					@ Jump to average procedure for Fahrenheit
		STRB R0, [R4]				@ Store Fahrenheit average
		MOV R0, R3					@ Load pointer to Celsius array to pass to procedure
		BL AVERAGE					@ Jump to average procedure for Celsius
		STRB R0, [R5]				@ Store Celsius average
		NOP

CONVERT:							@ Conversion procedure
		STMFD R13!, {R1-R5, R14}	@ Push registers to stack (even though we don't really need one...)
CONV_ARRAY_LOOP:					@ Temperature conversion loop
		LDRB R4, [R2], #1			@ Load entry in FAHRENHEIT_TEMPS into R4, increment by 1
		MOV R0, #0					@ Load COUNT into R0
		SUBS R4, R4, #32			@ Subtract 32 from FAHR value
		MOV R5, #5
		MUL R4, R4, R5				@ Multiply FAHR value by 5
		BPL	CONV_POS				@ Jump to 'CONV_POS' if FAHR value is positive
		MOV R6, #-1					@ Set inrementing register to -1
		MOV R7, #0
		SUB R4, R7, R4				@ R4 = -R4
		B CONV_SUB_LOOP				@ Jump to beginning of subtraction loop
CONV_POS:							@ ...if FAHR value is positive
		MOV R6, #1					@ Set incrementing register to 1
CONV_SUB_LOOP:						@ Repeated subtraction loop
		CMP R4, #9					@ Compare FAHR value to 9
		BMI CONV_ROUND				@ Jump to 'CONV_ROUND' if FAHR < 9
		SUBS R4, #9					@ Subtract 9 from FAHR value
		ADD R0, R6					@ Add increment register to count register
		B CONV_SUB_LOOP				@ Jump to top of subtraction loop
CONV_ROUND:
		CMP R4, #5					@ Compare FAHR value to 5
		BMI CONV_STORE				@ Jump to 'CONV_STORE' if FAHR < 5
		ADD R0, R6					@ Round up if FAHR > 4
CONV_STORE:
		STRB R0, [R3], #1			@ Store Celcius value in array, increment pointer by 1
		SUBS R1, #1					@ Decrement index value
		BNE CONV_ARRAY_LOOP			@ Jump to top of conversion loop if index > 0
		LDMFD R13!, {R1-R5, PC}		@ Pop registers off stack, return from conversion procedure

AVERAGE:							@ Array averaging procedure
		STMFD R13!, {R1-R5, R14}	@ Push registers to stack
		MOV R2, #0					@ Set Array Total to zero
		MOV R3, R1					@ Copy R1 to R3
AVE_ADD_LOOP:						@ Cycle through array, totaling values
		SUBS R1, #1					@ Decrement index variable
		LDRSB R6, [R0], #1			@ Load array element into R6, increment array pointer
		ADDPL R2, R2, R6			@ Add R6 to R2 if index >= 0
		BNE AVE_ADD_LOOP			@ Jump to top of loop if index > 0
		MOV R0, #0					@ Clear R0 for use as quotient/return value
		CMP R2, #0					@ Test if array total > 0
		BPL AVE_POS					@ Jump to 'AVE_POS' if total is positive
		MOV R5, #0
		SUB R2, R5, R2				@ R2 = -R2
		MOV R4, #-1					@ Incrementing value = -1
		B AVE_SUB_LOOP
AVE_POS:							@ If if array total is positive
		MOV R4, #1					@ Incrementing value = 1
AVE_SUB_LOOP:						@ Loop for repeated subtraction
		CMP R2, R3					@ Compare array total to Array Size
		BMI AVE_ROUND				@ Jump to 'AVE_ROUND' if R2 < R3
		SUBS R2, R3					@ Subtract Array Size from Array Total
		ADD R0, R4					@ Add increment value to Quotient
		B AVE_SUB_LOOP				@ Jump to top of subtraction loop
AVE_ROUND:
		AND R8, R3, #1				@ Grab LSB of Array Size
		LSR R3, R3, #1				@ Divide Array Size by 2
		ADD R3, R8					@ Add 1 if R3 was odd...
		CMP R2, R3					@ Test if Remaining Total > Array Size / 2, +1 if it was odd
		BMI AVE_RETURN				@ Jump to 'AVE_RETURN' if Remainder < Array Size / 2 (+1 if it was odd)
		ADD R0, R4					@ Round up
AVE_RETURN:
		LDMFD R13!, {R1-R5, PC}		@ Pop registers off stack, return from average procedure

PROG_END:
		NOP

.data

FAHRENHEIT_TEMPS:	.byte 0x00, 0x02, 0x04, 0x10	@ 0, 2, 4, 16
F2:					.byte 0x1D, 0x1F, 0x20, 0x21	@ 29, 31, 32, 33
F3:					.byte 0x2C, 0x32, 0x3E, 0x49	@ 44, 50, 62, 73
F4:					.byte 0x54, 0x5F, 0x6A, 0x7D	@ 84, 95, 106, 125

CELSIUS_TEMPS:		.byte 0x00, 0x00, 0x00, 0x00
C2:					.byte 0x00, 0x00, 0x00, 0x00
C3:					.byte 0x00, 0x00, 0x00, 0x00
C4:					.byte 0x00, 0x00, 0x00, 0x00

FAHRENHEIT_AVE:		.byte 0x00

CELSIUS_AVE:		.byte 0x00

STACK:				.rept 256
					.byte 0x00
					.endr

.end
