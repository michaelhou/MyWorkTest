.code
 
MultiplyBy10  PROC
 
    shl           RCX, 1
    mov           RAX, RCX
    shl           RCX, 2
    add           RAX, RCX
	cpuid 
    ret
 
MultiplyBy10  ENDP

MichaelCal1  PROC
 
    sub           RCX, RDX
    add           RCX, rax
	mov			  rax,rcx
;	cpuid 
    ret
 
MichaelCal1  ENDP

MichaelCPUID  PROC
 mov eax,1
	cpuid 
    ret
 
MichaelCPUID  ENDP

END