#include<stdio.h>
#include<windows.h>
//typedef unsigned
#define SIGNATURE_16(A, B)        ((A) | (B << 8))
#define SIGNATURE_32(A, B, C, D)  (SIGNATURE_16 (A, B) | (SIGNATURE_16 (C, D) << 16))
#define Sig2Int(a,b,c,d) ((((UINTN)a)<<24) + (((UINTN)b)<<16) + (((UINTN)c)<<8) + ((d)))

void main()
{
	UINT32 aval=0;
	aval=SIGNATURE_32('c','n','f','g');
	printf("test\n");
}