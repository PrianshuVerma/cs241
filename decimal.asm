lis $1
.word 0xffff0004
lis $2
.word 0xffff000c
lis $3
.word 0
lis $4
.word 1 ; increment bytes using this

lis $5
.word 0 ; store word here

lis $6
.word 10 ; mult by 10 from here

lis $7
.word 0x0000000a ; termination key

lis $8 
.word 0x0000002d ; - sign 

lis $9
.word 0 ; 0 means postive and 1 means negative 

lis $10 
.word -1 

lis $12
.word 0x00000030

load: 
lw $11, 0($1)
beq $11, $7, end ; end on termination key
bne $11, $8, 2
add $9, $9, $4
beq $0, $0, load ; if negative sign then change $9 and start loop again
; if we're here then it is a number
sub $11, $11, $12
mult $5, $6
mflo $5
add $5, $5, $11
add $3, $3, $4 ; increment bytes
beq $0,$0, load

end:
beq $9, $0, 2
mult $5, $10
mflo $5
sw $5, 0($2)
jr $31
