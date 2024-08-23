lis $3
.word 1
bne $1, $2, 2 ; skip next 3 if $1 != $2
bne $1, $0, 1; skip next 2 if $1 == $0
beq $0, $0, end ; skip to end with $3 = 1
lis $3
.word 0
beq $1, $0, end ; skip to end if $1 is zero

divu $2, $1
mfhi $4
lis $3
.word 1
beq $4, $0, 1
add $3, $0, $0
end:
jr $31

