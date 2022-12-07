
.org $4000

add_Loop: 
	adc #1            ;   test
	bcs sub_Loop       
	sta 0             
	jmp add_Loop       

sub_Loop:
	sbc #1          
	sta 0         
	beq add_Loop      
	jmp sub_Loop       

jump_location:
	.dw $4025 

irq:
	.org $fffd
	jmp (jump_location)

	.org $4025
	inc 2
	rti