section .text
	global _ft_strdup
extern _ft_strlen
extern _ft_strcpy
extern _malloc

_ft_strdup:
	cmp		rdi, 0
	jle		error
	push	rdi
	call	_ft_strlen
	inc		rax
	mov		rdi, rax
	call	_malloc
	cmp		rax, 0
	jle		error
	pop		rdi
	mov		rsi, rdi
	mov		rdi, rax
	call	_ft_strcpy
	ret

error:
	mov 	rax, 0
	ret