;; To Solve the "Guru Problem"
;; compile:
;; nasm -f elf64 semaphore.asm
;; nasm -f elf64 threads-x86_64.s 
;; link:
;; ld semaphore.o threads-x86_64.o
;; execute:
;; ./a.out

global _start
;; Imported from 
;; https://github.com/skeeto/pure-linux-threads-demo/blob/master/threads-x86_64.s 
;; make it global there!
extern thread_create
extern puts

section .data
	; Semaphores are defined and initialized here
	; All are Binary Semaphores
	s0 : db 0x01
	s1 : db 0x00
	s2 : db 0x00
	str : db "0",0

section .text

_start: 
	mov rdi,t0
	call thread_create
	mov rdi,t1
	call thread_create
	mov rdi,t2
	call thread_create
	call exit

sWait:
	; sWait(byte* sem: rdi)
	.l1:
	cmp byte [rdi],0x00
	je .l1 ; wait
	mov byte [rdi],0x00
	ret

sSignal:
	; sSignal(byte* sem: rdi)
	mov byte [rdi],0x01
	ret

t0: 
	.l0:
	mov rdi,s0
	call sWait
	mov rdi,str
	call puts
	mov rdi,s1
	call sSignal
	mov rdi,s2
	call sSignal
	jmp .l0
t1:
	mov rdi,s1
	call sWait
	mov rdi,s0
	call sSignal
t2:
	mov rdi,s2
	call sWait
	mov rdi,s0
	call sSignal
exit:
	mov rdi, 0
	mov rax, 60
	syscall
	
