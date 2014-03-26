	.file	"bmi.c"
	.section	.rodata
.LC0:
	.string	"Your bmi index is: %lf\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$48, %esp
	call	height
	fstpl	24(%esp)
	call	weight
	fstpl	32(%esp)
	fldl	24(%esp)
	fadd	%st(0), %st
	fldl	32(%esp)
	fdivp	%st, %st(1)
	fstpl	40(%esp)
	fldl	40(%esp)
	fstpl	4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.8.1-10ubuntu9) 4.8.1"
	.section	.note.GNU-stack,"",@progbits
