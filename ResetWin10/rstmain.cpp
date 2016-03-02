#include<stdio.h>
#include<stdlib.h>
#include<ATSZLIB.h>

int main()
{
	LoadATSZIoDriver();
	WORD temp=0;
	BYTE PortVal=0x06;
	Read_Mem_Word(0xfffffff0, &temp);
	printf("%x\n",temp);
	Write_Io_Byte(0xcf9,&PortVal);
	getchar();

	RemoveNTDriver();
	return 0;
}