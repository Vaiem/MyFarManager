.code
	
MakeSum proc

	mov eax, ecx
	add eax, edx

	ret

MakeSum endp


;void DrawConsole(CHAR_INFO* buffer_screen,Pos pos,int lenght,CHAR_INFO infoChar)

DrawConsole proc

	push rax
	push rcx
	push rdi

	mov rdi, rcx
	mov eax, r9d

	mov rcx, r8

	rep stosd 

	pop rdi
	pop rcx
	pop rax

	ret

DrawConsole endp


end