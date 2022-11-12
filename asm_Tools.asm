.code
	
MakeSum proc

	mov eax, ecx
	add eax, edx

	ret

MakeSum endp


;void DrawConsole(CHAR_INFO* buffer_screen,Pos pos,CHAR_INFO infoChar)

DrawConsoleHorizontal proc


; Параметры:
;rax - free
; RCX - screen_buffer
; RDX - pos
; R8 - infoChar
; Возврат: RAX
 

	push rax
	push rbx
	push rcx
	push rdi

	;addres_offset = (pos.Y_Pos * pos.Screen_Width + pos.X_Pos) * 4
	
	mov rax,rdx
	shr rax,16
	mov rbx,rdx
	shr rbx,32
	movzx rax, ax
	movzx rbx, bx
	imul rax, rbx
	mov bx,dx
	movzx rbx,bx
	add rax, rbx
	shl rax, 2

	add rcx,rax

	;output
	mov rdi, rcx
	mov eax, r8d


	mov rcx,rdx
	shr rcx,48

	rep stosd 

	pop rdi
	pop rcx
	pop rbx
	pop rax

	ret

DrawConsoleHorizontal endp


end