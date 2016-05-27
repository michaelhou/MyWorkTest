//to use filename.asm in 32bit project,we also have to select the file's properity and choose Microsoft Macro Assembler option.
#include<stdio.h>
#include <xmmintrin.h>
extern "C" __int64 MichaelTestProc1( __int64 );
//extern "C"  __int64 __cdecl MichaelCPUID( __int32  EAX,__int32  EBX,__int32 ECX,__int32 EDX,__int32 app1,__int32 app2);
extern "C"  __int64  MichaelCPUID( __int32  EAX,__int32  EBX,__int32 ECX,__int32 EDX,__int32 app1,__int32 app2);

//__int64 __stdcall MichaelTestProc1(__int64 avak,__int32 ECX,__int32 EDX,__int32 app1,__int32 app2)//it's the callee's responsibility to clear the stack ;ret 24
__int64 __cdecl MichaelTestProc1(__int64 avak,__int32 ECX,__int32 EDX,__int32 app1,__int32 app2)//the caller clear the stack;ret 0
{
	long long s=0;
//	for(long long i=1;i<1000000000;i++)s+=i;
	for(long long i=1;i<101;i++)s+=i;
	return s;
}
int main( int argc, char* argv[] )
{
    __int64 value = 123456789;
	__m128  am128val={1.0,2.0,3.0,4.0};
	__int64 result = value;
//	__asm int 3;//embeded assembly only support in win32 project
	result=sizeof(value);
	result=sizeof(am128val);
    printf( "%lli\n", result );
	MichaelCPUID(1,2,3,4,5,6);//verified that use push stack in 32bit.
 
    return 0;
}