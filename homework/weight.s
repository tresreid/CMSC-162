	.file	"weight.c"
	.section	.rodata
	.align 4
.LC0:
	.string	"Please input your weight(kg): "
.LC1:
	.string	"%lf"
	.text
	.globl	weight
	.type	weight, @function
weight:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	$.LC0, (%esp)
	call	printf
	leal	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC1, (%esp)
	call	__isoc99_scanf
	fldl	-16(%ebp)
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	weight, .-weight
	.ident	"GCC: (Ubuntu/Linaro 4.8.1-10ubuntu9) 4.8.1"
	.section	.note.GNU-stack,"",@progbits
