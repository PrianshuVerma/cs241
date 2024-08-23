sw $31, -4($30)
sw $3, -8($30)
sw $4, -12($30)
sw $5, -16($30)
sw $6, -20($30)
sw $7, -24($30)
lis $31
.word -24
add $30, $30, $31

lis $3
.word 0
lis $4
.word 1
lis $5
.word 4
lis $7
.word print

arrayloop:

  slt $6, $3, $2
  beq $6, $0, endprogram

  add $3, $3, $4 ; increment current element
  sw $1, -4($30) ; store address in stack
  sub $30, $30, $5

  lw $1, 0($1)
  jalr $7

  add $30, $30, $5
  lw $1, -4($30) ; put array address back in $1
  
  add $1, $1, $5 ; increment address of array

  beq $0, $0, arrayloop

endprogram:

lis $31
.word 24
add $30, $30, $31
lw $31, -4($30)
lw $3, -8($30)
lw $4, -12($30)
lw $5, -16($30)
lw $6, -20($30)
lw $7, -24($30)
jr $31
