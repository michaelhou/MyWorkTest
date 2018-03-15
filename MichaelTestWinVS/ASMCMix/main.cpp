#include<stdio.h>
#include <xmmintrin.h>
extern "C" __int64 MichaelTestProc1( __int64 );
extern "C" __int64 MultiplyBy10( __int64 );
extern "C" __int64 MultiplyBy10( __int64 );
extern "C" __int64 MichaelCal1( __int64,__int64,__int64 );
extern "C"  __int64 __cdecl MichaelCPUID( __int32  EAX,__int32  EBX,__int32 ECX,__int32 EDX,__int32 app1,__int32 app2);

__int64 MichaelTestProc1(__int64 avak)
{
	long long s=0;
//	for(long long i=1;i<1000000000;i++)s+=i;//RCX+3
	for(long long i=1;i<101;i++)s+=i;//RXC+4
	return s;
}
int main( int argc, char* argv[] )
{
    __int64 value = 123456789;
	__m128  am128val={1.0,2.0,3.0,4.0};
    __int64 result = MultiplyBy10( value );
//__int64 result = value;
//	__asm int 3;//only support in win32 project
	result=sizeof(am128val);
    printf( "%lli\n", result );
	//MichaelCPUID(1,2,3,4);
	MichaelCPUID(1,2,3,4,5,6);
	value=MichaelCal1(10,2,255);
 
    return 0;
}