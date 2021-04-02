section .text
	global _ft_strlen

_ft_strlen:
	mov rax, 0
	jmp check

more:
	inc rax;

check: 
	cmp BYTE [rdi, rax], 0
	jne more
	ret