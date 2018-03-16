#pragma once
#include<Windows.h>
#include<MYLIB.h>

#pragma comment(lib,"MYLIB64_release.lib")

#ifdef __cplusplus
extern "C" {
#endif

	__declspec (dllexport) int  MYLIBInitialize();
	__declspec (dllexport) int  MYLIBDeInitialize();
__declspec (dllexport) int  MYLIBRead_Io_Byte(unsigned short port,unsigned char * value);
__declspec (dllexport) int  MYLIBRead_Io_Word(unsigned short port,unsigned short * value);
__declspec (dllexport) int  MYLIBRead_Io_Dword(unsigned short port,unsigned int * value);


__declspec (dllexport) int __cdecl MYLIBWrite_Io_Byte(unsigned short port,unsigned char value);
__declspec (dllexport) int __cdecl MYLIBWrite_Io_Word(unsigned short port,unsigned short  value);
__declspec (dllexport) int __cdecl MYLIBWrite_Io_Dword(unsigned short port,unsigned int  value);



__declspec (dllexport) int __cdecl MYLIBRead_Mem_Byte(unsigned long long address,unsigned char * value);
__declspec (dllexport) int __cdecl MYLIBRead_Mem_Word(unsigned long long address,unsigned short * value);
__declspec (dllexport) int __cdecl MYLIBRead_Mem_Dword(unsigned long long address,unsigned int * value);
__declspec (dllexport) int __cdecl MYLIBWrite_Mem_Byte(unsigned long long address,unsigned char  value);
__declspec (dllexport) int __cdecl MYLIBWrite_Mem_Word(unsigned long long address,unsigned short  value);
__declspec (dllexport) int __cdecl MYLIBWrite_Mem_Dword(unsigned long long address,unsigned int  value);
__declspec (dllexport) int __cdecl MYLIBGetVariable(const wchar_t * tname ,const wchar_t * tguid,int * length,byte ** outvalue );
__declspec (dllexport) int __cdecl MYLIBSetVariable(const wchar_t * tname ,const wchar_t * tguid,int  length,byte * invalue );

__declspec (dllexport) int __cdecl MYLIBDump_PhysMem(unsigned long address,unsigned char * data,unsigned long size);
__declspec (dllexport) int  (MYLIBRead_PCI_Dword_Sync)(unsigned long dPCIAddress,PDWORD pdValue);
__declspec (dllexport) int  (MYLIBWrite_PCI_Dword_Sync)(unsigned long dPCIAddress,PDWORD pdValue);

#ifdef __cplusplus
}
#endif