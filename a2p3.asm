;$1 holds the start of array address in memory
;$2 holds the number of elemnts

lis $4
.word 4 ; this is used to skip to the next element

lis $5
.word 1 ; holds current element of array, starts at 1 since non-empty array

lis $6
.word 1 ; using this to increment $5 by 1
 
lw $3, 0($1)
loop: 
  slt $8, $5, $2 
  beq $8, $0, end ; if $8 = 0 than we have hit all elements so end programs
; else increment and see if we have a new max
  
  add $5, $5, $6 ; increment current element 
  add $1, $1, $4 ; increment address of current element
  lw $9, 0($1) ; load next element in $9
  slt $8, $3, $9 ; check if max < new element
  beq $8, $0, 1 ; skip the next intruction if the value is zero
  add $3, $9, $0 ; if new > max then we update the value 
  beq $0, $0, loop ; always return to loop

end: 
  jr $31 ; this label will be used to end the loop 
