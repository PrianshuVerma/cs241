sw $31, -4($30)
lis $4
.word 4
sub $30, $30, $4
lis $4
.word readWord
lis $5
.word printHex

jalr $4
jalr $4 ; now this holds the address of the endcode; 
lis $6
.word 0x0000000c
lis $7
.word 4
sub $8, $3, $6 ; end code minus 12
div $8, $7
mflo $8 ; now register 8 holds the numbers of lines we need to read in
jalr $4 ; get rid of the endModule shit as well 

lis $2
.word 1
loop: 
beq $8, $0, end
sub $8, $8, $2 ; decrease 8 
jalr $4
add $1, $3, $0
jalr $5
beq $0, $0, loop

end:
lis $4
.word 4
add $30, $30, $4
lw $31, -4($30)
jr $31


readWord:
sw $1,  -4($30)
sw $2,  -8($30)
sw $4, -12($30)
sw $5, -16($30)
sw $6, -20($30)
sw $7, -24($30)
sw $8, -28($30)
lis $8
.word 28
sub $30, $30, $8
lis $4
.word 0x01000000
lis $3
.word 0x00010000
lis $2
.word 0x00000100
lis $1
.word 0xffff0004
lw $8, 0($1)
lw $7, 0($1)
lw $6, 0($1)
lw $5, 0($1)
multu $8, $4
mflo $8
multu $7, $3
mflo $7
multu $6, $2
mflo $6
add $4, $8, $7
add $3, $6, $5
add $3, $4, $3
lis $8
.word 28
add $30, $30, $8
lw $1,  -4($30)
lw $2,  -8($30)
lw $4, -12($30)
lw $5, -16($30)
lw $6, -20($30)
lw $7, -24($30)
lw $8, -28($30)
jr $31

printHex:
sw $1,  -4($30)
sw $2,  -8($30)
sw $3, -12($30)
sw $4, -16($30)
sw $5, -20($30)
sw $6, -24($30)
sw $7, -28($30)
sw $8, -32($30)
lis $8
.word 32
sub $30, $30, $8
lis $2
.word 0x10000000
lis $3
.word 0x10
lis $4
.word 0x30
lis $6
.word 10
lis $7
.word 7  
lis $8
.word 0xffff000c
PHloop:
divu $1, $2
mflo $1
slt $5, $1, $6 
bne $5, $0, PHskip
        add $1, $1, $7
PHskip: add $1, $1, $4 
sw $1, 0($8)
mfhi $1
divu $2, $3
mflo $2
bne $2, $0, PHloop
sw $6, 0($8)
lis $8
.word 32
add $30, $30, $8
lw $1,  -4($30)
lw $2,  -8($30)
lw $3, -12($30)
lw $4, -16($30)
lw $5, -20($30)
lw $6, -24($30)
lw $7, -28($30)
lw $8, -32($30)
jr $31

