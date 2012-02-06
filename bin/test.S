.global _start

_start:

	push	len
	push	msg
	push	$1
	mov		$16, %eax
	call	_syscall

	add		$12, %esp

	push	$0
	mov		$2, %eax
	call	_syscall

_syscall:
	int $0x40 
	ret

msg:
.asciz "Hello, world!\n"

len:
.byte  14


