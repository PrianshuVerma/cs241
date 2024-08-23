
stirling: 

sw $31, -4($30)
sw $1, -8($30)
sw $2, -12($30)
sw $4, -16($30)
sw $11, -20($30)
lis$31
.word 20
sub $30, $30, $31

lis $11
.word 1

lis $3
.word 0
; base case of $1 and $2 = 0

bne $1, $2, 4 ; skip these tree instructions if both are not the same
bne $1, $0, 3 ; if $1 not 0 then skip 2 instructions 
lis $3
.word 1
beq $0, $0, end 

; base case of $1 or $2 is 0
beq $1, $2, 2 ;if these two are the same then we skip this case
beq $1, $0, end
beq $2, $0, end

; now we do the recursion 
sub $1, $1, $11
lis $3
.word stirling
jalr $3

; multiply 
mult $1, $3
mflo $4 ; store answer in register 4 for now
sub $2, $2, $11
lis $3
.word stirling
jalr $3

add $3, $3, $4 ; add value from last call and register 4 and store  

end:
lis $31
.word 20
add $30, $30, $31
lw $31, -4($30)
lw $1, -8($30)
lw $2, -12($30)
lw $4, -16($30)
lw $11, -20($30)
jr $31 
