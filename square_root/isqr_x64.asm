[bits 64]

[section .text]
[global isqrasm]
      
isqrasm:
		mov rbx, rcx
		bsr rcx, rbx
		sar rcx,1
		inc rcx
		xor rax,rax
		xor rdi,rdi

	iloop1:
		btr rax,rcx     ;----------Main Loop---------
	iloop:
		dec rcx
		js  end
		mov rdx,rax
		bts rax,rcx
		add rdx,rax
		shl rdx,cl
		add rdx,rdi
		cmp rdx,rbx
		ja  iloop1
		mov rdi,rdx
		jb  iloop        ;--------------------
		
	end:
		RET              ;result is in rax, __cdecl cleans up

; Microsoft Visual Studio Community 2015 / The Netwide Assembler
; this file -> properties -> 
;  platform: x64
; this file -> properties -> custom build tool ->
;  command line:  C:\Users\vs\AppData\Local\NASM\nasm.exe -f win64 "%(FullPath)" -o "$(OutDir)%(Filename).obj"
;  outputs:       $(OutDir)%(Filename).obj
