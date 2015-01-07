section .text
	global _start

_start:
	; print name
	mov edx, 11
	mov ecx, name
	mov ebx, 1
	mov eax, 4
	int 0x80
	
	; print new line
	mov edx, 1
	mov ecx, newline
	mov ebx, 1
	mov eax, 4
	int 0x80

	; print address of name
	mov edx, 5
	mov ecx, [name]
	mov ebx, 1
	mov eax, 4
	int 0x80

	; print new line
	mov edx, 1
	mov ecx, [address]
	mov ebx, 1
	mov eax, 4
	int 0x80

	; exit
	mov eax, 1
	int 0x80

section .data
	name db "Hello, Joe" 
	newline db 0xa
	address db 0x1