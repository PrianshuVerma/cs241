; $1 holds address of start of array
; $2 holds number of elements in array

lis $4
.word 4 ; this is used to skip to element of the array

lis $3
.word 0 ; this keeps track of the current element we're at 

lis $7
.word 1 ; this is used to increment current element

lis $10
.word 0xFFFF000c

lis $9
.word 64 ; convert dec to letters

lis $11
.word 32

loop:
  slt $5, $3, $2
  beq $5, $0, end ; if $5 = 0 then we hit all elements and we end program
; now we output current letter and increment $3

  lw $8, 0($1) ; output 
  add $3, $3, $7 ; move to next element of array
  add $1, $1, $4 ; move to next adress
  
  beq $8, $0, 2 ; skip the next two instructions if $8 is 0
  add $8, $8, $9 
  sw $8, 0($10) ; outputs letter in register 

  bne $8, $0, 1 ; skip next intruction if $8 is not 0
  sw $11, 0($10)

  beq $0, $0, loop ; always return to loop

end:
  jr $31
