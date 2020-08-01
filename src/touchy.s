			AREA touchy, CODE
			EXPORT asm_entry
			
			; ------------------
FIO0DIR 	EQU		0x3FFFC000
FIO0PIN 	EQU		0x3FFFC014
FIO0SET		EQU		0x3FFFC018
FIO0CLR		EQU		0x3FFFC01C

m10			EQU 	0x00000400		;11th bit for pin 10
			; ------------------

asm_entry    
			ldr r0, =FIO0DIR		; Setup GPIO as required
			mov r1, #0x00000000
			str r1, [r0]			
			
touchy_loop
			ldr r0, =FIO0PIN		; Read P0.10
			ldr r1, [r0]			; Branch to left_switch_pushed if input is high
			ands r0, r1, #m10	
			bne left_switch_pushed
			; cmp ~= subs
			b	touchy_loop	

left_switch_pushed					; does nothing yet
			nop
			b	left_switch_pushed
			
			END
