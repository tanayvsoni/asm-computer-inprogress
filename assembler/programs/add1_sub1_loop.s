.org $4000
;test2

;how are your

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

irq:
	.org $fffd
	jmp $4018
	.org $4018
	inc 2
	rti