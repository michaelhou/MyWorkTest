#include<stdio.h>
extern "C" __int64 MultiplyBy10( __int64 );
extern "C" __int64 MichaelCal1( __int64,__int64,__int64 );
extern "C" __int64 MichaelCPUID( __int32  EAX,__int32  EBX,__int32 ECX,__int32 EDX);
 
int main( int argc, char* argv[] )
{
    __int64 value = 123456789;

    __int64 result = MultiplyBy10( value );
//__int64 result = value;
//	__asm int 3;//only support in win32 project
    printf( "%lli\n", result );
	MichaelCPUID(1,2,3,4);
	value=MichaelCal1(10,2,255);
 
    return 0;
}