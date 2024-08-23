sw $31, -4($30)
lis $4
.word 4
sub $30, $30, $4
lis $4
.word readWord
lis $5
.word printHex

jalr $4
add $29, $0, $3 ;
add $10, $0, $3 ;
sw $29, -4($30)
lis $4
.word 4
sub $30, $30, $4
lis $4
.word readWord
jalr $4
jalr $4 ; now this holds the address of the endmodel; 
lis $6
.word 0x0000000c
lis $7
.word 4
sub $13, $3, $6 ; this holds the endmodle minus 12

jalr $4
sub $8, $3, $6 ; end code minus 12
add $12, $8, $0 ; this holds the end code address minus 12
div $8, $7
mflo $8 ; now register 8 holds the numbers of lines we need to read in
add $9, $8, $0 


lis $2
.word 1
loop: 
beq $8, $0, callFooter
sub $8, $8, $2 ; decrease 8 
jalr $4
sw $3, 0($29)
add $29, $29, $7
add $1, $3, $0
jalr $5
beq $0, $0, loop

callFooter:
add $12, $12, $6 ; end of the code
add $13, $13, $6 ; end of the file
lis $21
.word 0x01
lis $22
.word 0x05
lis $23
.word 0x11
beq $0, $0, footer 

footer: 
slt $17, $12, $13 
beq $17, $0, callSecondLoop
jalr $4
beq $3, $21, relocation
beq $3, $22, skip
beq $3, $23, ESR

skip: 
jalr $4
jalr $4 
add $12, $12, $7
add $12, $12, $7
add $12, $12, $7
beq $0, $0, footer

ESR: 
lis $1
.word 0x000EBB0B
beq $0, $0, end

relocation:
jalr $4
add $29, $3, $10 ; add the relocation value
sub $29, $29, $6 ; subract 12
lw $15, 0($29) ; load the word from this new address 
add $15, $15, $10 ; add alpha to this value
sub $15, $15, $6 ; subract 12
sw $15, 0($29) ; store this word back at location we got it from
; increment $12 by 8
add $12, $12, $7
add $12, $12, $7
beq $0, $0, footer


callSecondLoop:
lis $25
.word 0x00
sw $30, 0($25)
;add $11, $11, $7
jalr $10
lw $30, 0($25) 
lis $2
.word 1
lis $29
.word 4
add $30, $30, $29
lw $29, -4($30)
add $8, $9, $0
beq $0, $0, SecondLoop

SecondLoop: 
beq $8, $0, end
sub $8, $8, $2 ; decrease 8 
lw $1, 0($29)
add $29, $29, $7
jalr $5
beq $0, $0, SecondLoop

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
