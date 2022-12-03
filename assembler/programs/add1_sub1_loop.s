
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

.db 232
.db 232, 23, 322
.tx "Hello"
.dw 256

.org $4000

add_Loop: 
	adc #1            ;   test
	bcs sub_Loop       
	sta zero             
	jmp add_Loop       

sub_Loop:
	sbc #constant          
	sta zero         
	beq add_Loop      
	jmp sub_Loop        

irq:
	.org $fffd
	jmp $4018
	.org $4018
	iNc 2
	RTI
	adc 23+a,X