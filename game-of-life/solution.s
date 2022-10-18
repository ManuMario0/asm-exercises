	.text
	.globl step
// the idea is to put the next value in the second bit of the value in the table, so that we can store its next state as well as its current state (which is used in further computation)
step:
	pushq	%rbp
	movq	$0, %rcx
	movq	$0, %r8
	movq	%rdx, %r9
	callq	parse
	movq	%r9, %r8
	subq	%rdx, %r8
	movq	$0, %rcx
	callq	shift
	popq	%rbp
	ret

parse:
	jmp	alive

parse.adder:
	incq	%r9
	incq	%r8
	cmpq	%r8, %rsi
	jg	parse
	movq	$0, %r8
	incq	%rcx
	cmpq	%rcx, %rdi
	jg	parse
	ret

alive:
	// we now loop around two indexes, r10 and r11
	movq	$-1, %r10
	movq	$-1, %r11
	movq	$0, %r12
alive.L1:
	cmpq	$1, %r10
	jg	alive.continue
	movq	%r10, %rax
	addq	%rcx, %rax
	cmpq	$0, %rax
	jl	alive.L1.adder
	cmpq	%rdi, %rax
	jge	alive.continue
alive.L2:
	cmpq	$1, %r11
	jg	alive.L1.adder
	movq	%r11, %rax
	addq	%r8, %rax
	cmpq	$0, %rax
	jl	alive.L2.adder
	cmpq	%rsi, %rax
	jge	alive.L1.adder
	
	// compute the y location
	movq	%r10, %r13
	addq	%rcx, %r13
	
	// compute the x location
	movq	%r11, %r14
	addq	%r8, %r14

	// compute the location in table
	movq	%r13, %rax
	imulq	%rdi, %rax
	addq	%r14, %rax

	addq	%rdx, %rax
	movsbl	(%rax), %eax
	and	$1, %eax
	cmpl	$0, %eax
	je	alive.L2.adder
	incq	%r12
	jmp	alive.L2.adder

alive.continue:
	cmpb	$0, (%r9)
	jne	liv
	cmpq	$3, %r12
	jne	parse.adder
	
	movsbl	(%r9), %eax
	orl	$2, %eax
	movb	%al, (%r9)
	jmp	parse.adder

liv:
	addq	$-1, %r12
	cmpq	$1, %r12
	jle	parse.adder
	cmpq	$3, %r12
	jg	parse.adder
	movb	$3, (%r9)
	//movsbl	(%r9), %eax
	//orl	$2, %eax
	//movb	%al, (%r9)
	jmp	parse.adder

alive.L1.adder:
	incq	%r10
	movq	$-1, %r11
	jmp	alive.L1

alive.L2.adder:
	incq	%r11
	jmp	alive.L2

shift:
	cmpq	%rcx, %r8
	je	end
	movq	%rcx, %rax
	addq	%rdx, %rax
	shrb	(%rax)
	incq	%rcx
	jmp	shift

end:
	ret
