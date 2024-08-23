lis $4
.word 4
lis $5 ; track of what element we're on
.word 0
lis $6
.word 1
lis $10
.word 0xffff000c
;lis $20
;.word compare

start:
; preserve $1 and $2 
sw $1, -4($30)
sw $2, -8($30)
lis $8
.word 8
sub $30, $30, $8 

sub $2, $2, $6
slt $7, $5, $2 ; $7 is equal to 1 if we want to continue
bne $7, $6, end

mult $5, $4
mflo $8
add $8, $8, $1

lw $2,4($8)
lw $1,0($8)

; call compare/ output here to test
sw $31, -4($30)
lis $31
.word 4
sub $30, $30, $31
lis $20
.word compare
jalr $20
lis $31
.word 4
add $30,$30, $31
lw $31, -4($30)
beq $3, $0, end
; check value of 3, if zero then we end

;lis $13
;.word 48
;add $1,$1,$13
;add $2, $2, $13
;sw $1,0($10)
;sw $2,0($10)

;else restore values of $1,$2, and increment $5 to the next element
lis $1
.word 8
add $30, $30, $1
lw $1, -4($30)
lw $2, -8($30)
add $5, $5, $6
beq $0,$0, start


end:
;restore $1 and $2 here as well
lis $1
.word 8
add $30, $30, $1
lw $1, -4($30)
lw $2, -8($30)
jr $31

