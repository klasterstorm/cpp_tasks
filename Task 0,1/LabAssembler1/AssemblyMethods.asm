.686
.MODEL FLAT, C
.STACK
.DATA

movsqcpy PROC
	;mov copy_size, %rax
	;mov (%rax), %rax
	;mov $8, %rbx
	;xor %rdx, %rdx
	;div %rbx
	;mov %rax, %rcx
	;mov $copy_source, %esi
	;mov $copy_destination, %edi
	;cld
	;rep movsb
	;retn
movsqcpy ENDP

END