  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,2
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #
.globl hexasc
hexasc:
	andi $v0,$a0,0xf    # save the 4 least significant bits 
	addi $v0,$v0,0x30   # turn into ASCII, 0x30 = 48, ascci 48 = 1, 49 = 2...
	slti  $v1, $v0, 0x39 #check if v0 is less than 9, if is v1 = 1 else v1 = 0
	beq $v1,1,L2     # check if v1 = 1 if so go directly to L2
	addi $v0,$v0,7      #else add additional 7 for 'A'-'F'
L2:
	jr $ra 
	
.globl delay
delay: 
	jr $ra
	nop
	
.globl time2string
time2string:
            PUSH ($s0)
            PUSH ($s1)
            PUSH ($ra)

            add $s0, $a0, 0
            add $s1, $a1, 0
            
            addi $t1, $s1, 0xf000
            srl  $a1, $s1, 12 
            jal hexasc
            sb $v0, 0($s0)
            
            addi $t1, $s1, 0x0f00
            srl  $a1, $s1, 8 
            jal hexasc
            sb $v0, 1($s0)
            
            li $t0, 0x3A
            sb $t0, 2($s0)

            addi $t1, $s1, 0x00f0
            srl  $a1, $s1, 4
            jal hexasc
            sb $v0, 3($s0)
            
            addi $t1, $s1, 0xf000
            srl  $a1, $s1, 12 
            jal hexasc
            sb $v0, 4($s0)                          

            li  $t1, 0x00           
            sb  $t1, 5($s0)

            POP ($ra)
        POP ($s1)
        POP ($s0)   
        jr   $ra  
	

