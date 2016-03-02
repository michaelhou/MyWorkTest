#include<stdio.h>
#include<stdlib.h>
#include<ATSZLIB.h>

int main()
{
	LoadATSZIoDriver();
	WORD temp=0;
	Read_Mem_Word(0xfffffff0, &temp);
	printf("%x\n",temp);
	getchar();

	RemoveNTDriver();
	return 0;
}