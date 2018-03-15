.586p
.model  flat
ASSUME FS:NOTHING
.code
 
MultiplyBy10  PROC
 
    shl           ecx, 1
    mov           EAX, ECX
    shl           ECX, 2
    add           EAX, ECX
	cpuid 
    ret
 
MultiplyBy10  ENDP

MichaelCPUID  PROC   C
 mov eax,1
	cpuid 
    ret
 
MichaelCPUID  ENDP
END