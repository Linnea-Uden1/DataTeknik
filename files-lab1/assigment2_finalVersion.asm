.text

.globl main
main: 
	li $a0, 10
	
	jal hexasc
	move $a0, $v0
	li $v0, 11
	syscall 
	
	li $v0, 10
	syscall 
	
	
.globl hexasc
hexasc:
	andi $v0,$a0,0xf    # save the 4 least significant bits 
	addi $v0,$v0,0x30   # turn into ASCII, 0x30 = 48, ascci 48 = 1, 49 = 2...
	slti  $v1, $v0, 0x39 #check if v0 is less than 9, if is v1 = 1 else v1 = 0
	beq $v1,1,L2     # check if v1 = 1 if so go directly to L2
	addi $v0,$v0,7      #else add additional 7 for 'A'-'F'
L2:
	jr $ra 

	
