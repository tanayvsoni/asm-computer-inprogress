; Adds 1 untill 255 and than subtracts 1 down to 0 in a loop

add_Loop: 
    out 
    add const
    jc sub_Loop
    jmp add_Loop

sub_Loop:
    sub const
    out
    jz add_Loop
    jmp sub_Loop

const: 1



