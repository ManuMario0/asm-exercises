	.text
	.globl order

// We will do that recusivly !
order:
	pushq	%rbp
	movq	%rdi, %rsi
	movq	8(%rdi), %r10
	movq	16(%rdi), %r11
	movq	$0, 8(%rdi)
	movq	$0, 16(%rdi)
	movq	%r10, %rdi
	call	find
	movq	%r11, %rdi
	call	find
	movq	%rsi, %rax
	popq	%rbp
	ret

find:
	cmpq	$0, %rdi
	je	end
	pushq	%rdi
	movq	8(%rdi), %rdi
	call	find
	popq	%rdi
	pushq	%rdi
	movq	16(%rdi), %rdi
	call	find
	popq	%rdi
	movq	$0, 8(%rdi)
	movq	$0, 16(%rdi)
	call	add_element
end:
	ret

add_element:
	movq	(%rdi), %rax
	cmpq	%rax, (%rsi)
	jl	right
	cmpq	$0, 8(%rsi)
	je	replace_left
	pushq	%rsi
	movq	8(%rsi), %rsi
	call	add_element
	popq	%rsi
	ret

replace_left:
	movq	%rdi, 8(%rsi)
	ret

right:
	cmpq	$0, 16(%rsi)
	je	replace_right
	pushq	%rsi
	movq	16(%rsi), %rsi
	call	add_element
	popq	%rsi
	ret

replace_right:
	movq	%rdi, 16(%rsi)
	ret
