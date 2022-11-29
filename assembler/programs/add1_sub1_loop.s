
;test2

/*

asjdkashjsadhfks

*/

a = 23

a = 433

b = $a

e = a
c = %10+a

zero =0

constant = 1

;how are your


.org $4000

add_Loop: 
	adc #constant            ;   test
	bcs sub_Loop       
	sta zero             
	jmp add_Loop       

sub_Loop:
	sbc #1            
	sta zero         
	beq add_Loop      
	jmp sub_Loop        

irq:
	.org $fffd
	jmp $4018
	.org $4018
	iNc 2
	RTI
	adc (23),X