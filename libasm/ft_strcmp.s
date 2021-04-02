global _ft_strcmp

section .text

_ft_strcmp:
	mov		rax, 0
	mov		rdx, 0
	mov		rbx, 0

loop:
	mov		dl, BYTE[rdi + rax]
	sub		dl, BYTE[rsi + rax]
	cmp		dl, 0
	jnz		exit
	cmp		BYTE[rdi + rax], 0
	jz		exit
	inc		rax
	jmp		loop

exit:
	mov		dl, BYTE[rdi + rax]
	mov		bl, BYTE[rsi + rax]
	sub		rdx, rbx
	mov		rax, rdx
	ret
