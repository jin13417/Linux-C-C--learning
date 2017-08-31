	.file	"hello.c"
	.section	.rodata
.LC0:
	.string	"hello world\n"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	movl	$20, 28(%esp)
	movl	$.LC0, (%esp)
	call	puts
	movl	$0, %eax
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.4.4-14ubuntu5.1) 4.4.5"
	.section	.note.GNU-stack,"",@progbits
