.org $4000

ldx #0

print:
    lda message,X
    beq stop
    inx 
    out
    jmp print

stop:
    hlt

message:
    .tx "I love Shannon"
    .db 0

interrupt:
    inc 0
    rti

.org $fffd
irq:
    jmp interrupt


