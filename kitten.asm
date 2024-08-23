lis $1
.word 0xffff0004
lis $2
.word 0xffff000c
lis $3
.word 0
lis $4
.word 1 ; increment bytes using this

read:
lw $5,0($1)
slt $6,$5, $0
bne $6,$0, end
;check if value is -1, if it is then stop it
sw $5,0($2)
add $3,$3, $4
beq $0, $0, read

end:
jr $31
