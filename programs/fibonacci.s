; Displays all fibonacci numbers until 233 and than resets

ldi 1
sta x
ldi 0
sta y
out
lda x
add y
sta x
out
lda y
add x
jc 0
jmp 3

.org 14
    x:0
    y:0