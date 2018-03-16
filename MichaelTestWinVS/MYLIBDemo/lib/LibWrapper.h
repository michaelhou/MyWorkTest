#pragma once
/*
description: 
dynamic wrapper for sys and static lib.

todo:
we should add version and compatibility check later.

demo usage:
	UINT8 portval=0;
	int retval=0;
	retval=MYLIBRead_Io_Byte(0x80,&portval);

	printf("read 80 port value=%02x\n",portval);

	for(int i=0;i<=0xff;i++){
		retval=MYLIBRead_Io_Byte(i,&portval);
		printf("%02X ",portval);
		if((i&0x0f)==0x0f)
			printf("\n");
	}
*/
#include<stdio.h>
#include<Windows.h>


typedef int  (*pMYLIBinitialize)();
typedef int  (*pMYLIBDeInitialize)();
typedef int   (*pMYLIBRead_Io_Byte)(unsigned short port,unsigned char * value);
typedef int  (*pMYLIBRead_Io_Word)(unsigned short port,unsigned short * value);
typedef int  (*pMYLIBRead_Io_Dword)(unsigned short port,unsigned int * value);


typedef int  (*pMYLIBWrite_Io_Byte)(unsigned short port,unsigned char value);
typedef int  (*pMYLIBWrite_Io_Word)(unsigned short port,unsigned short  value);
typedef int  (*pMYLIBWrite_Io_Dword)(unsigned short port,unsigned int  value);



typedef int  (*pMYLIBRead_Mem_Byte)(unsigned long long address,unsigned char * value);
typedef int  (*pMYLIBRead_Mem_Word)(unsigned long long address,unsigned short * value);
typedef int  (*pMYLIBRead_Mem_Dword)(unsigned long long address,unsigned int * value);
typedef int  (*pMYLIBWrite_Mem_Byte)(unsigned long long address,unsigned char  value);
typedef int  (*pMYLIBWrite_Mem_Word)(unsigned long long address,unsigned short  value);
typedef int  (*pMYLIBWrite_Mem_Dword)(unsigned long long address,unsigned int  value);
typedef int  (*pMYLIBGetVariable)(const wchar_t * tname ,const wchar_t * tguid,int * length,byte ** outvalue );
typedef int  (*pMYLIBSetVariable)(const wchar_t * tname ,const wchar_t * tguid,int  length,byte * invalue );


typedef int  (*pMYLIBDump_PhysMem)(unsigned long address,unsigned char * data,unsigned long size);
typedef int  (*pMYLIBRead_PCI_Dword_Sync)(unsigned long dPCIAddress,PDWORD pdValue);
typedef int  (*pMYLIBWrite_PCI_Dword_Sync)(unsigned long dPCIAddress,PDWORD pdValue);





extern pMYLIBinitialize MYLIBinitialize;
extern pMYLIBDeInitialize MYLIBDeInitialize;

extern pMYLIBRead_Io_Byte MYLIBRead_Io_Byte;
extern pMYLIBRead_Io_Word MYLIBRead_Io_Word;
extern pMYLIBRead_Io_Dword MYLIBRead_Io_Dword;
extern pMYLIBWrite_Io_Byte MYLIBWrite_Io_Byte;
extern pMYLIBWrite_Io_Word MYLIBWrite_Io_Word;
extern pMYLIBWrite_Io_Dword MYLIBWrite_Io_Dword;
extern pMYLIBRead_Mem_Byte MYLIBRead_Mem_Byte;
extern pMYLIBRead_Mem_Word MYLIBRead_Mem_Word;
extern pMYLIBRead_Mem_Dword MYLIBRead_Mem_Dword;
extern pMYLIBWrite_Mem_Byte MYLIBWrite_Mem_Byte;
extern pMYLIBWrite_Mem_Word MYLIBWrite_Mem_Word;
extern pMYLIBWrite_Mem_Dword MYLIBWrite_Mem_Dword;
extern pMYLIBGetVariable MYLIBGetVariable;
extern pMYLIBSetVariable MYLIBSetVariable;
extern pMYLIBDump_PhysMem MYLIBDump_PhysMem;
extern pMYLIBRead_PCI_Dword_Sync MYLIBRead_PCI_Dword_Sync;
extern pMYLIBWrite_PCI_Dword_Sync MYLIBWrite_PCI_Dword_Sync;

extern int debugInfoFlag;
extern int MYLIBInitialize(void * parg);
extern int MYLIBFinalize(void * parg);

