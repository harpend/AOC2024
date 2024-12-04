%include "linux64.inc"

section .data
	filename db "input4.txt",0

section .bss
	char resb 1
	counter resq 1
section .text
	global _start

_start:
	mov rax, SYS_OPEN
	mov rdi, filename
	mov rsi, O_RDONLY
	mov rdx, 0
	syscall

	mov rbx, rax
	xor rax, rax
	mov [counter], rax
_loop:
	jmp _matchX
	jmp _loop

_end:
	call _printCounter
	mov rax, SYS_CLOSE
	mov rdi, rbx
	syscall

	mov rax, 60
	xor rdi, rdi
	syscall

_readChar:
	mov rdi, rbx
	mov rax, SYS_READ
	mov rsi, char
	mov rdx, 1
	syscall
	ret

_printChar:
	mov rax, SYS_WRITE
	mov rdi, 1
	mov rsi, char
	mov rdx, 1
	syscall
	ret

_printCounter:
	mov rax, [counter]
	xor rbx, rbx
	mov rcx, 10

_printDigit:
	xor rdx, rdx
	div rcx
	add dl, '0'
	push rdx
	inc rbx
	test rax, rax
	jnz _printDigit

_printStack:
	pop rax
	mov [char], al
	call _printChar
	dec rbx
	jnz _printStack
	ret

_matchX:
	call _readChar
	cmp rax, 0
	je _end

	mov al, byte [char]
_checkX:
	cmp al, 'X'
	jne _loop

_matchM:
	call _readChar
	cmp rax, 0
	je _end

	mov al, byte [char]
	cmp al, 'M'
	jne _checkX

_matchA:
	call _readChar
	cmp rax, 0
	je _end

	mov al, byte [char]
	cmp al, 'A'
	jne _checkX

_matchS:
	call _readChar
	cmp rax, 0
	je _end

	mov al, byte [char]
	cmp rax, 'S'
	jne _checkX

_increment:
	mov rax, [counter]
	inc rax
	mov [counter], rax
	jmp _loop

