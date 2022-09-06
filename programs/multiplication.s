;
; Multiply two numbers using a loop (Ben Eater's design)
;

loop:	
	lda prod
	add x
	sta prod
	lda y
	sub one
	jz end
	sta y
	jmp loop

end:    
	lda prod
	out
	hlt

one: 	 1
x:	 	15
y:	 	17
prod:	 0