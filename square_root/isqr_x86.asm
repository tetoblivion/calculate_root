[bits 32]

[section .text]
[global _isqrasm]
       
_isqrasm:
		mov ebx, [ESP+4]
		bsr ecx, ebx
		sar ecx,1
		inc ecx
		xor eax,eax
		xor edi,edi

	iloop1:
		btr eax,ecx     ;----------Main Loop---------
	iloop:
		dec ecx
		js  end
		mov edx,eax
		bts eax,ecx
		add edx,eax
		shl edx,cl
		add edx,edi
		cmp edx,ebx
		ja  iloop1
		mov edi,edx
		jb  iloop        ;--------------------
		
	end:
		RET              ;result is in eax, __cdecl cleans up

; Microsoft Visual Studio Community 2015 / The Netwide Assembler
; this file -> properties -> 
;  platform: win32
; this file -> properties -> custom build tool ->
;  command line:  C:\Users\vs\AppData\Local\NASM\nasm.exe -f win32 "%(FullPath)" -o "$(OutDir)%(Filename).obj"
;  outputs:       $(OutDir)%(Filename).obj
