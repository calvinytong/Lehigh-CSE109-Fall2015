;CSE 109
;Calvin Tong
;cyt219
;hw 3
;tokenize a string


SYS_EXIT equ 1
SYS_WRITE equ 4
STDOUT equ 1

section .text
  global main

main:
  mov ecx, MSG            ; load initial pointer

itrstr:
  cmp byte[ecx], 0        ; compare it to the 0 byte to see if we are done
  jz done                 ; jump to the end if we are at the end of the string
  cmp byte[ecx], 0x20     ; check if we have a space
  jz printlnlbl           ; jump to printlnlbl
  call writeout           ; write the char out, skipped if its a space
  inc ecx                 ; increment the pointer stored in ecx
  jmp itrstr              ; jump back to the top of the loop

printlnlbl: 
  mov [ecx], byte 0xA     ; move the new line character to ecx as the character to print
  call writeout           ; print the space
top:
  inc ecx                 ; increment the pointer
  cmp byte[ecx], 0x20     ; check if space is there
  jz top                  ; if it is a space then inc pointer and check if space again 
  jmp itrstr             ; jump back to the loop @the next not space char

done:
  mov ecx, NL            
  call writeout           ; write out final new line
  mov eax,SYS_EXIT        ; call sys exit
  int 0x80

writeout:
  mov eax, SYS_WRITE      ; syscall number for sys_write
  mov ebx, STDOUT         ; print to stdout
  mov edx, 1              ; write 1 char at a time
  int 0x80                ; call the kernal
  ret

segment .data
  MSG db "this   is   a  string with tokens hi hi hi", 0x0 ; string to write out
  NL db 0xA
