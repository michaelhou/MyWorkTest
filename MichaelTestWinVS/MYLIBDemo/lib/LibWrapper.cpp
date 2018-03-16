#include"LibWrapper.h"

pMYLIBinitialize MYLIBinitialize;
pMYLIBDeInitialize MYLIBDeInitialize;

pMYLIBRead_Io_Byte MYLIBRead_Io_Byte;
pMYLIBRead_Io_Word MYLIBRead_Io_Word;
pMYLIBRead_Io_Dword MYLIBRead_Io_Dword;
pMYLIBWrite_Io_Byte MYLIBWrite_Io_Byte;
pMYLIBWrite_Io_Word MYLIBWrite_Io_Word;
pMYLIBWrite_Io_Dword MYLIBWrite_Io_Dword;
pMYLIBRead_Mem_Byte MYLIBRead_Mem_Byte;
pMYLIBRead_Mem_Word MYLIBRead_Mem_Word;
pMYLIBRead_Mem_Dword MYLIBRead_Mem_Dword;
pMYLIBWrite_Mem_Byte MYLIBWrite_Mem_Byte;
pMYLIBWrite_Mem_Word MYLIBWrite_Mem_Word;
pMYLIBWrite_Mem_Dword MYLIBWrite_Mem_Dword;
pMYLIBGetVariable MYLIBGetVariable;
pMYLIBSetVariable MYLIBSetVariable;
pMYLIBDump_PhysMem MYLIBDump_PhysMem;
pMYLIBRead_PCI_Dword_Sync MYLIBRead_PCI_Dword_Sync;
pMYLIBWrite_PCI_Dword_Sync MYLIBWrite_PCI_Dword_Sync;

int debugInfoFlag;
/*
for x64 build
please put file 
R:\mylibiowrapper\extlib\MYLIBIOWrapper.dll

R:\mylibiowrapper\extlib\MYLIBIO64.sys

with your exe.

*/
static HMODULE dllhdl;
int MYLIBInitialize(void * parg)
{
	dllhdl=LoadLibrary("MYLIBWrapperDLL.dll");
	DWORD result=GetLastError();

	if(result){
		if(debugInfoFlag>0)printf("error occor, errcode=0x%08x\n",result);
		return -1;
	}
	else{
		if(debugInfoFlag>4)printf("load dll ok! dllhdl=%p\n",dllhdl);
	}
	MYLIBinitialize=(pMYLIBinitialize) GetProcAddress(dllhdl,"MYLIBInitialize");;
	MYLIBDeInitialize =(pMYLIBinitialize)GetProcAddress(dllhdl,"MYLIBDeInitialize");;
	MYLIBRead_Io_Byte= (pMYLIBRead_Io_Byte) GetProcAddress(dllhdl,"MYLIBRead_Io_Byte");
	MYLIBRead_Io_Word= (pMYLIBRead_Io_Word) GetProcAddress(dllhdl,"MYLIBRead_Io_Word");
	MYLIBRead_Io_Dword= (pMYLIBRead_Io_Dword) GetProcAddress(dllhdl,"MYLIBRead_Io_Dword");
	MYLIBWrite_Io_Byte= (pMYLIBWrite_Io_Byte) GetProcAddress(dllhdl,"MYLIBWrite_Io_Byte");
	MYLIBWrite_Io_Word= (pMYLIBWrite_Io_Word) GetProcAddress(dllhdl,"MYLIBWrite_Io_Word");
	MYLIBWrite_Io_Dword= (pMYLIBWrite_Io_Dword) GetProcAddress(dllhdl,"MYLIBWrite_Io_Dword");
	MYLIBRead_Mem_Byte= (pMYLIBRead_Mem_Byte) GetProcAddress(dllhdl,"MYLIBRead_Mem_Byte");
	MYLIBRead_Mem_Word= (pMYLIBRead_Mem_Word) GetProcAddress(dllhdl,"MYLIBRead_Mem_Word");
	MYLIBRead_Mem_Dword= (pMYLIBRead_Mem_Dword) GetProcAddress(dllhdl,"MYLIBRead_Mem_Dword");
	MYLIBWrite_Mem_Byte= (pMYLIBWrite_Mem_Byte) GetProcAddress(dllhdl,"MYLIBWrite_Mem_Byte");
	MYLIBWrite_Mem_Word= (pMYLIBWrite_Mem_Word) GetProcAddress(dllhdl,"MYLIBWrite_Mem_Word");
	MYLIBWrite_Mem_Dword= (pMYLIBWrite_Mem_Dword) GetProcAddress(dllhdl,"MYLIBWrite_Mem_Dword");
	MYLIBGetVariable= (pMYLIBGetVariable) GetProcAddress(dllhdl,"MYLIBGetVariable");
	MYLIBSetVariable= (pMYLIBSetVariable) GetProcAddress(dllhdl,"MYLIBSetVariable");
	MYLIBDump_PhysMem= (pMYLIBDump_PhysMem) GetProcAddress(dllhdl,"MYLIBDump_PhysMem");
	MYLIBDump_PhysMem= (pMYLIBDump_PhysMem) GetProcAddress(dllhdl,"MYLIBDump_PhysMem");
	MYLIBRead_PCI_Dword_Sync= (pMYLIBRead_PCI_Dword_Sync) GetProcAddress(dllhdl,"MYLIBRead_PCI_Dword_Sync");
	MYLIBWrite_PCI_Dword_Sync= (pMYLIBWrite_PCI_Dword_Sync) GetProcAddress(dllhdl,"MYLIBWrite_PCI_Dword_Sync");



	if(!MYLIBinitialize){
		if(debugInfoFlag>0)printf("getprocaddress error!\n");
		return -1;
	}
	if(MYLIBinitialize()){
		if(debugInfoFlag>0)printf("driver initialize error!\n");
		return -2;
	}


	return 0;

}

int MYLIBFinalize(void * parg)
{
	if(MYLIBDeInitialize)MYLIBDeInitialize();
	if(dllhdl)FreeLibrary(dllhdl);

	return 0;
}