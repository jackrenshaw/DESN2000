				AREA feature_3, CODE
				EXPORT SWI_Handler
				
				IMPORT calc_speed
				IMPORT gpio_simulate_speed
				IMPORT smooth_speed
				IMPORT deadmans_switch
				IMPORT stopping_distance

swi_num_funcs	EQU 6
FIO3DIR			EQU 0x3FFFC060
FIO3PIN 		EQU 0x3FFFC074
FIO3SET			EQU 0X3FFFC078
FIO3CLR			EQU 0X3FFFC07C
MAX_SPEED 		EQU 50
				
SWI_Handler
				
				ldr ip, [lr, #-4]
				bic ip, ip, #0xFF000000
				cmp ip, #swi_num_funcs
				
				ldrlo pc, [pc, ip, lsl#2]
				
				b swi_outofrange

swi_jump_table
				DCD swi_0
				DCD swi_1
				DCD swi_2
				DCD swi_3
				DCD swi_4

				
swi_0
				;Check current speed
				
				bl gpio_simulate_speed ;returns the current speed of tram
	
				ldr r4, =current_speed
				ldr r5, [r4]
				str r0,[r5]				;store cuyrrent speed into data log
				
				b swi_exit
				
swi_1 
				;Check average speed
				
				bl smooth_speed			; returns average speed of tram
				ldr r4, =average_speed
				ldr r5, [r4]
				str r0, [r5]			;store average speed into data logs
				
				b swi_exit
				
swi_2		 
				;Turn on red LED if max speed exceeded
				
				bl gpio_simulate_speed ;returns the current speed of tram
				
				mov r4, MAX_SPEED
				cmp r0, r4
				bgt red_led				;if current speed > max speed, turn on leds
red_led			
				ldr r5, =FIO3DIR
				mov r6, #0x90000 ;set red leds as outputs
				str r6, [r5]
				
				ldr r5, =FIO3SET
				mov r6, #0x90000 ; turn on red leds
				str r6, [r5]
				
				b swi_exit
				
swi_3			
				;Check if dead mans switch is applied
				
				bl deadmans_switch	;returns 1 if deadmans is applied, 0 if not 
				
				ldr r4, =deadmans
				ldr r5, [r4]
				str r0, [r5] 		; store into data log 		
				
				
swi_4
				;Find stopping distance
				
				bl gpio_simulate_speed ;returns the current speed of the tram
				mov r1, #1		; brake=1
				
				stmfd sp!, {r0-r1, lr}
				bl stopping_distance	;returns the stopping distnace
				ldr r4, =stop_distance
				ldr r5, [r4]
				ldr r0, [r5] 			;store stopping sistance
				
swi_outofrange 	
				mov r0, #0 
				b swi_exit
				
swi_exit		
				movs pc, lr
				
				
				AREA tram_data_log, DATA				
current_speed	SPACE 48
average_speed	SPACE 48
deadmans		SPACE 48
stop_distance	SPACE 48

;extra space is available for future data 

				END	