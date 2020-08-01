			AREA blinky, CODE
			EXPORT delay
			
count		EQU 0x257AD0	;should take about 200ms to count to

			;Function: delay
			;Takes about 200ms to complete
delay		mov r0, #0
			ldr r1, =count
			
delay_loop	add r0, r0, #1
			cmp r0, r1
			bne delay_loop
			
			mov pc, lr
			
			END
