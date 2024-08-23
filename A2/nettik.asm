lis $1
.word 0xffff0004
lis $2
.word 0xffff000c
lis $3
.word 0
lis $4
.word 1 ; increment bytes using this
lis $7
.word 4 ; increment array using this
; register 8 will be used to store the values as an array
lis $10
.word 0
read:
lw $5,0($1)
slt $6,$5, $0
bne $6,$0, write
;check if value is -1, if it is then stop it
; now lets work on moving this into an array
sw $5, -4($30)
lis $5
.word 4
sub $30, $30, $5 ; put each character in the $30 stack
add $3,$3, $4
beq $0, $0, read

write: 
slt $9, $10, $3
beq $9, $0, end
lw $8, 0($30)
sw $8, 0($2)
add $30, $30, $7
add $10, $10, $4
beq $0, $0, write

end:
jr $31
