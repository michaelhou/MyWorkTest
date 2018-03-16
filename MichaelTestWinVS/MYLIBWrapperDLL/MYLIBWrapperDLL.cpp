/*
for x64 build  we should select
`Use Unicode Character Set` and `Multi-threaded (/MT)`
*/
#include"m.h"
//#include<MYLIB.h>
#include<stdio.h>
#include<stdlib.h>
#define MIC_PERFORMANCE_PROFILE 0
extern  BOOL _stdcall LoadMYLIBIoDriver();
int  MYLIBInitialize()
{
	BOOL retval=FALSE;
	retval=LoadMYIoDriver();
	if(retval)
	{
		return 0;
	}

	return -1;
}
int MYLIBDeInitialize()
{
	 CloseMYIoDriver();
	 return 0;
}
int MYLIBRead_Io_Byte(unsigned short port,unsigned char * value)
{
	BYTE abyte=0;
	BOOL retval=FALSE;
	retval=Read_Io_Byte(port,&abyte);
	if(retval)*value =abyte;
	return retval;
}
int MYLIBRead_Io_Word(unsigned short port,unsigned short * value)
{
	WORD abytes=0;
	BOOL retval=FALSE;
	retval=Read_Io_Word(port,&abytes);
	if(retval)*value =abytes;
	return retval;
}
int MYLIBRead_Io_Dword(unsigned short port,unsigned int * value)
{
	DWORD abytes=0;
	BOOL retval=FALSE;
	retval=Read_Io_Dword(port,&abytes);
	if(retval)*value =abytes;
	return retval;
}

int MYLIBWrite_Io_Byte(unsigned short port,unsigned char value)
{
	BYTE abyte=value;
	BOOL retval=FALSE;
	retval=Write_Io_Byte(port,&abyte);
	return retval;
}
int MYLIBWrite_Io_Word(unsigned short port,unsigned short  value)
{
	WORD abyte=value;
	BOOL retval=FALSE;
	retval=Write_Io_Word(port,&abyte);
	return retval;
}
int MYLIBWrite_Io_Dword(unsigned short port,unsigned int  value)
{
	DWORD abyte=value;
	BOOL retval=FALSE;
	retval=Write_Io_Dword(port,&abyte);
	return retval;
}



int MYLIBRead_Mem_Byte(unsigned long long address,unsigned char * value)
{
	BYTE abyte=0;
	BOOL retval=FALSE;
	retval=Read_Mem_Byte(address,&abyte);
	if(retval)*value =abyte;
	return retval;
}
int MYLIBRead_Mem_Word(unsigned long long address,unsigned short * value)
{
	WORD abytes=0;
	BOOL retval=FALSE;
	retval=Read_Mem_Word(address,&abytes);
	if(retval)*value =abytes;
	return retval;
}
int MYLIBRead_Mem_Dword(unsigned long long address,unsigned int * value)
{
	DWORD abytes=0;
	BOOL retval=FALSE;
	retval=Read_Mem_Dword(address,&abytes);
	if(retval)*value =abytes;
	return retval;
}
int MYLIBWrite_Mem_Byte(unsigned long long address,unsigned char  value)
{
	BOOL retval=FALSE;
	retval=Write_Mem_Byte(address,value);
	return retval;
}
int MYLIBWrite_Mem_Word(unsigned long long address,unsigned short  value)
{
	BOOL retval=FALSE;
	retval=Write_Mem_Word(address,value);
	return retval;
}
int MYLIBWrite_Mem_Dword(unsigned long long address,unsigned int  value)
{
	BOOL retval=FALSE;
	retval=Write_Mem_Dword(address,value);
	return retval;
}

int ObtainPrivileges(LPCTSTR privilege) {
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    BOOL res;
    DWORD error;
    // Obtain required privileges
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        printf("OpenProcessToken failed!\n");
        //PrintError(GetLastError());
        //exit(GetLastError());
		return -1;
    }

    res = LookupPrivilegeValue(NULL, privilege, &tkp.Privileges[0].Luid);
    if (!res) {
        printf("LookupPrivilegeValue failed!\n");
        //PrintError(GetLastError());
        //exit(GetLastError());
		return -2;
    }
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

    error = GetLastError();
    if (error != ERROR_SUCCESS) {
        printf("AdjustTokenPrivileges failed\n");
        //PrintError(error);
        //exit(error);
		return -3;
    }
	return 0;
}

int MYLIBGetVariable(const wchar_t * tname ,const wchar_t * tguid,int * length,byte ** outvalue )
//int MYLIBGetVariable(TCHAR* tname ,TCHAR * tguid,int * length,byte ** outvalue )
{
#define BUF_SIZE 0x40000
	{
		static byte rdbuf[BUF_SIZE]={0};
		DWORD size=BUF_SIZE;
		DWORD retsize=0;
		int obret=ObtainPrivileges(SE_SYSTEM_ENVIRONMENT_NAME);
		if(obret)
			return obret;
		retsize=GetFirmwareEnvironmentVariable(tname,tguid,rdbuf,size);

		printf("retsize=%08x\n",retsize);
		if(retsize<=0)
		{
			retsize=GetLastError();
			return retsize;
		}
		*length=retsize;
		*outvalue=rdbuf;
		retsize=GetLastError();
		printf("lasterror=%08x,dec=%d\n",retsize,retsize);
	}
	return 0;
}

int MYLIBSetVariable(const wchar_t * tname ,const wchar_t * tguid,int  length,byte * invalue )
//int MYLIBGetVariable(TCHAR* tname ,TCHAR * tguid,int * length,byte ** outvalue )
{
		DWORD size=length;
		DWORD retsize=0;
		int obret=ObtainPrivileges(SE_SYSTEM_ENVIRONMENT_NAME);
		if(obret)
			return obret;
		retsize=SetFirmwareEnvironmentVariable(tname,tguid,invalue,size);

		printf("retsize=%08x\n",retsize);
		if(!retsize)
		{
			retsize=GetLastError();
			return retsize;
		}
		retsize=GetLastError();
		printf("lasterror=%08x,dec=%d\n",retsize,retsize);
	return 0;
}

int MYLIBDump_PhysMem(unsigned long address,unsigned char * data,unsigned long size)
{
	unsigned long remain_size;
	remain_size=size;
	BOOL retval=FALSE;
	int i=0;
#if defined(MIC_PERFORMANCE_PROFILE)&&MIC_PERFORMANCE_PROFILE
	//system("echo [mic]:start %time%");
	LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
	LARGE_INTEGER Frequency;

	QueryPerformanceFrequency(&Frequency); 
	QueryPerformanceCounter(&StartingTime);
#endif
	while(remain_size>0x1000){
		Dump_PhysMem(address+(i*0x1000),data+(i*0x1000),0x1000);
		remain_size-=0x1000;
		i++;
	}
	Dump_PhysMem(address+(i*0x1000),data+(i*0x1000),remain_size);

#if defined(MIC_PERFORMANCE_PROFILE)&&MIC_PERFORMANCE_PROFILE
	// Activity to be timed

	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;


	//
	// We now have the elapsed number of ticks, along with the
	// number of ticks-per-second. We use these values
	// to convert to the number of elapsed microseconds.
	// To guard against loss-of-precision, we convert
	// to microseconds *before* dividing by ticks-per-second.
	//

	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

	printf("[mic]: duration:%dms\n",ElapsedMicroseconds.QuadPart);
	//system("echo [mic]:end %time%");
#endif
//	retval=Dump_PhysMem(address,data,size);
	return retval;
}

int  (MYLIBRead_PCI_Dword_Sync)(unsigned long dPCIAddress,PDWORD pdValue)
{
	return Read_PCI_Dword_Sync(dPCIAddress,pdValue);
}
int  (MYLIBWrite_PCI_Dword_Sync)(unsigned long dPCIAddress,PDWORD pdValue)
{
	return Write_PCI_Dword_Sync(dPCIAddress,pdValue);
}

/*

Read_Mem_Byte
Read_Mem_Word
Read_Mem_Dword
Write_Mem_Byte
Write_Mem_Word
Write_Mem_Dword


MYLIBWrite_Io_Byte

MYLIBWrite_Io_Word
MYLIBWrite_Io_Dword

MYLIBRead_Mem_Byte
MYLIBRead_Mem_Word
MYLIBRead_Mem_Dword
MYLIBWrite_Mem_Byte
MYLIBWrite_Mem_Word
MYLIBWrite_Mem_Dword




*/