section .text
	global _main
_main:
	mov edx,len
	mov ecx,msg
	mov ebx,1
	mov eax,4
	int 0x80
	mov eax,1
	int 0x80
section .data
msg db 'Hello, joe!', 0xa
len equ $ - msg
