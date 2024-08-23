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


print:

; first store register 2-12 in stack 


sw $1, -4($30)
sw $2, -8($30)
sw $3, -12($30)
sw $4, -16($30)
sw $5, -20($30)
sw $6, -24($30)
sw $7, -28($30)
sw $8, -32($30)
sw $9, -36($30)
sw $10, -40($30)
sw $11, -44($30)
sw $12, -48($30)
lis $2
.word 48
sub $30, $30, $2

lis $2
.word 10 ; used to divide $1

lis $3
.word 4 ; used to increment stack in memory

lis $5
.word 0 ; used to keep track of size of stack

lis $6 
.word 1 ; used to increment $5

lis $8
.word 0xFFFF000c

lis $9
.word 48

; check if our number is negative
slt $11, $0, $1 ; $11 will be 0 if our number is negative

bne $1, $0, 1 ; if $1 is 0 then we want to make $11 1
add $11, $0, $6

bne $11, $0, push ; skip to push intructions if $11 is zero
lis $12
.word -1
mult $12, $1
mflo $1
lis $12
.word 45 ; lets us output negative sign after
push:

  slt $4, $1, $2 ; $4 is 1 if our number is less then 10
  ;this means we will end the push this last num and move to pull 
  beq $4, $0, 4 ; if $4 is 0 we skip to else by skipping 4 intructions
  sw $1, -4($30)
  sub $30, $30, $3
  add $5, $5, $6
  beq $0, $0, pull

  ; else we divide, push the remainder and loop
  div $1, $2 
  mflo $1 ; put the updated number back in $1
  mfhi $7 ; put the remainder in $7
  add $5, $5, $6

  sw $7, -4($30) ; storing word in
  sub $30, $30, $3 ; update the stack
  
  beq $0, $0, push


pull:

  bne $11, $0, 2
  add $11, $0, $6
  sw $12, 0($8)

  slt $4, $0, $5 ; if 4 is 0 then we skip to end
  beq $4, $0, end

  sub $5, $5, $6 ; decrease number of items left on stack

  add $30, $30, $3
  lw $10, -4($30) 
  add $10, $10, $9
  sw $10, 0($8) 
  beq $0, $0, pull

end:

  lis $10
  .word 10
  sw $10, 0($8)
  lis $2
  .word 48
  add $30, $30, $2
lw $1, -4($30)
lw $2, -8($30)
lw $3, -12($30)
lw $4, -16($30)
lw $5, -20($30)
lw $6, -24($30)
lw $7, -28($30)
lw $8, -32($30)
lw $9, -36($30)
lw $10, -40($30)
lw $11, -44($30)
lw $12, -48($30)
  jr $31 
