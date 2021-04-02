global _ft_strcpy

section .text

_ft_strcpy: ;rdi - first rsi - second
	mov		rax, 0

loop:
	cmp		BYTE[rsi + rax], 0
	jz		fin
	mov		dl, BYTE[rsi + rax]
	mov		BYTE[rdi + rax], dl
	inc		rax
	jmp		loop

fin:
	mov		BYTE[rdi + rax], 0
	mov		rax, rdi
	ret