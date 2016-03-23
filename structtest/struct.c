#include<stdio.h>
#include<string.h>
#pragma pack(1)
typedef struct _st1
{
	int a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
}st1;
typedef struct _st2
{
	st1 sta;
	st1 stb;
	st1 stc;
	st1 std;
}st2;

#pragma pack()

int main(int argc,char** argv)
{
	st2 sttest;
	int i;
	memset(&sttest,0,sizeof(sttest));
	for(i=0;i<sizeof(sttest);i++)
	{
		((unsigned char*)&sttest)[i]=i;
	}
	
	printf("sizeof(st1)=%d\n",sizeof(st1));
	printf("sizeof(st2)=%d\n",sizeof(st2));
	printf("sttest.sta=%p\n",&sttest.sta);
	printf("sttest.sta=%x\n",sttest.sta);
	printf("sttest.sta.a=%x\n",sttest.sta.a);
	printf("sttest.sta.b=%x\n",sttest.sta.b);
	printf("sttest.sta.c=%x\n",sttest.sta.c);
	printf("&sttest.sta.a=%x\n",&sttest.sta.a);
	printf("&sttest.sta.b=%x\n",&sttest.sta.b);
	printf("&sttest.sta.c=%x\n",&sttest.sta.c);
	

	return 0;
}
/*
C:\temp_training\prog>a.exe
sizeof(st1)=7
sizeof(st2)=28
sttest.sta=00000000001DF7E0
sttest.sta=1df7d0
sttest.sta.a=3020100
sttest.sta.b=4
sttest.sta.c=5
&sttest.sta.a=1df7e0
&sttest.sta.b=1df7e4
&sttest.sta.c=1df7e5
*/