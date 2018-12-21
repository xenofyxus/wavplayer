  # vectors.S
  # This file written 2015 by Axel Isaksson
  # Modified 2015 by F Lundevall
  # For copyright and licensing, see file COPYING

.macro movi reg, val
	lui \reg, %hi(\val)
	ori \reg, \reg, %lo(\val)
.endm

.macro STUB num
	.align 4
	.section .vector_new_\num,"ax",@progbits
	.global __vector_\num
	__vector_\num:
		movi $k0, _isr_primary_install
		lw $k0, \num * 4($k0)
		jr $k0
.endm

.align 4
.global __use_isr_install
__use_isr_install:
STUB 0
STUB 1
STUB 2
STUB 3
STUB 4
STUB 5
STUB 6
STUB 7

STUB 8
STUB 9
STUB 10
STUB 11
STUB 12
STUB 13
STUB 14
STUB 15

STUB 16
STUB 17
STUB 18
STUB 19
STUB 20
STUB 21
STUB 22
STUB 23

STUB 24
STUB 25
STUB 26
STUB 27
STUB 28
STUB 29
STUB 30
STUB 31

STUB 32
STUB 33
STUB 34
STUB 35
STUB 36
STUB 37
STUB 38
STUB 39

STUB 40
STUB 41
STUB 42
STUB 43
STUB 44
STUB 45
STUB 46
STUB 47

STUB 48
STUB 49
STUB 50
STUB 51
STUB 52
STUB 53
STUB 54
STUB 55

STUB 56
STUB 57
STUB 58
STUB 59
STUB 60
STUB 61
STUB 62
STUB 63

.text

.align 4
.global _isr_primary_install
_isr_primary_install:
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline

.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline

.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline

.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline

.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline

.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline

.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline

.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline
.word _isr_trampoline

# Interrupts are handled here
.align 4
.set noreorder
.global _isr_trampoline
_isr_trampoline:	
	# this is an interrupt service routine

	# tell the assembler not to use $1 right now
	.set noat

	# save all caller-save registers, and also ra
	addi	$sp, $sp,-72
	sw		$ra, 0($sp)
	sw		$at, 4($sp)
	sw		$v0, 8($sp)
	sw		$v1, 12($sp)
	sw		$a0, 16($sp)
	sw		$a1, 20($sp)
	sw		$a2, 24($sp)
	sw		$a3, 28($sp)
	sw		$t0, 32($sp)
	sw		$t1, 36($sp)
	sw		$t2, 40($sp)
	sw		$t3, 44($sp)
	sw		$t4, 48($sp)
	sw		$t5, 52($sp)
	sw		$t6, 56($sp)
	sw		$t7, 60($sp)
	sw		$t8, 64($sp)
	sw		$t9, 68($sp)

	# call user's handler
	jal ISR
	nop

	# restore saved registers
	lw		$t9, 68($sp)
	lw		$t8, 64($sp)
	lw		$t7, 60($sp)
	lw		$t6, 56($sp)
	lw		$t5, 52($sp)
	lw		$t4, 48($sp)
	lw		$t3, 44($sp)
	lw		$t2, 40($sp)
	lw		$t1, 36($sp)
	lw		$t0, 32($sp)
	lw		$a3, 28($sp)
	lw		$a2, 24($sp)
	lw		$a1, 20($sp)
	lw		$a0, 16($sp)
	lw		$v1, 12($sp)
	lw		$v0, 8($sp)
	lw		$at, 4($sp)
	lw		$ra, 0($sp)
	addi	$sp, $sp, 72

	.set at
	# now the assembler is allowed to use $1 again

	# standard epilogue follows
	eret
	nop


# Exceptions are handled here (trap, syscall, etc)
.section .gen_handler,"ax",@progbits
.set noreorder
.ent _gen_exception
_gen_exception:
	mfc0 $k0, $14, 0
	addi $k0, $k0, 4
	mtc0 $k0, $14, 0
	eret
	nop

.end _gen_exception
