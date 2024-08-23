lis $4 
.word 0
lis $3
.word 0
lis $20 ; used to multiply by 4
.word 4
lis $21 ; used to add 1 
.word 1
lis $22
.word -1
lis $23
.word 0xffff000c
lis $24
.word 0x00000030

children:

sw $31, -4($30)
sw $6, -8($30)
sw $7, -12($30)
sw $8, -16($30)
sw $9, -20($30)
lis $31
.word 20
sub $30, $30, $31

lis $3
.word 1
lis $8
.word 0
lis $9
.word 0

; large assumption is that when $4 comes in it is a valid node 


add $6, $4, $21 ; load number of left child into $6
mult $6, $20
mflo $6
add $6, $6, $1
lw $6, 0($6)

add $7, $4, $21 ; load number of right child into $7 
add $7, $7, $21
mult $7, $20
mflo $7
add $7, $7, $1
lw $7, 0($7)

add $25,$6, $24
sw $25, 0($24)
add $25, $7, $24
sw $25, 0($24)

bne $6, $22, 2 ; base case if both left and right child are absent
bne $7, $22, 1
beq $6, $7, end 

add $8, $3, $0 ; hold # of childer in left and right counter
add $9, $3, $0

beq $6, $22, 5 ; skip left child if not there 
add $4, $6, $0
lis $10
.word children
jalr $10
add $8, $3, $8

beq $7, $22, 5 ; traversing right child
add $4, $7, $0
lis $10
.word children
jalr $10
add $9, $3, $9

slt $11, $8, $9
bne $11, $0, 1
add $3, $8, $0
beq $11, $0, 1
add $3, $9, $0

beq $0,$0, end

end: 
lis $31
.word 20
add $30, $30, $31
lw $31, -4($30)
lw $6, -8($30)
lw $7, -12($30)
lw $8, -16($30)
lw $9, -20($30)
jr $31















