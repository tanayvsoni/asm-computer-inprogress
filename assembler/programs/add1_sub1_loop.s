
;test2

a = 1
a = 12;

b = 23;

c= 4;

d = 2;


e = d+c;

f = e+1


;how are your


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

irq:
	.org $fffd
	jmp $4018
	.org $4018
	inc 2
	rti