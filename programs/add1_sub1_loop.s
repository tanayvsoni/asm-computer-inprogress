.org $4000

add_Loop:
	adc #1              ; 3 steps
	bcs sub_Loop        ; 3 steps / 5 steps
	sta 0               ; 3 steps
	jmp add_Loop        ; 5 steps

sub_Loop:
	sbc #1              ; 3 steps
	sta 0               ; 3 steps
    beq add_Loop        ; 3 steps / 5 steps
	jmp sub_Loop        ; 5 steps