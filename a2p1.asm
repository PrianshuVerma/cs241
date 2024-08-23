add $3, $1, $0 ; set register 3 to value of 1 initially 
slt $4, $1, $2 ; 4 = 0 if $1 > $2 #### 4 = 1 if $1 < $2
beq $4, $0, 1 ; if $4 is 0 than $1 > $2 and we skip the intruction 
add $3, $2, $0 ; 
jr $31
