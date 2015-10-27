SYS_EXIT equ 1
SYS_READ equ 3
SYS_WRITE equ 4
STDIN equ 0
STDOUT equ 1

segment .bss
char resb 1

section .text
	global main
main:
	mov ecx, str           ; load initial pointer

itrstr:
  cmp byte[ecx], 0       ; compare it to the 0 byte to see if we are done
  jz done                ; jump to the end if we are at the end of the string
  cmp byte[ecx], 0x20    ; check if we have a space
  jz printlnlbl          ; jump to printlnlbl
  call writeout          ; write the char out, skipped if its a space
retprintln:
  inc ecx                 ; increment the pointer stored in ecx
  jmp itrstr              ; jump back to the top of the loop

printlnlbl:
  push ecx                ; push the pointer value back in ecx
  mov ecx, 0xA            ; move the new line character to ecx as the character to print
  call writeout           ; jump back to the loop to write things out
  pop ecx                 ; pop the value back
  jmp retprintln          ; jump back to the loop after the other call to write out

done:
  mov eax,SYS_EXIT
	int 0x80

writeout:
  mov eax, SYS_WRITE      ; syscall number for sys_write
  mov ebx, STDOUT         ; print to stdout
  mov edx, 1              ; write 1 char at a time
  int 0x80                ; call the kernal
  ret

segment .data
	 str db ’this is a string with tokens’, 0x0
