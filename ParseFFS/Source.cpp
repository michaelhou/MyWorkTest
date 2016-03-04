#include"header.h"
///reference COMMON\EM\CORESRC\CRISIS\InitLib\DXE_BS\CRISIS_Update.c(184) :EFI_STATUS ReloadWinflashSmmDriver
EFI_GUID SMBIOS_GUID={0XEB9D2D31,0X2D88,0X11D3,0X9A16,0X0090273FC14D};
EFI_GUID SMBIOS_GUID2={0x51a1c105, 0x7c13, 0x456a, {0xa6, 0xd8, 0xca, 0x8c, 0x27, 0xb4, 0xc0, 0x59}};
void printguid(EFI_GUID* cguid)
{
	int a=sizeof(UINT64);
	//LLX will not work.%16llX
	printf("%08X-%04X-%04X-%llX",
		(UINTN)cguid->Data1,(UINTN)cguid->Data2,(UINTN)cguid->Data3,*(UINT64*)(cguid->Data4));
}
int main(int argc, char** argv)
{
	FILE *fp;
	int sz1[]={sizeof(UINT8),sizeof(UINT16),sizeof(UINT32),sizeof(UINT64),sizeof(UINTN)};
	int BIOS_size=0x800000,Real_size,CurPos;
	void * ROM_img;
	UINT8 * ROM_Byte0;
	UINT64 CurSign;
	UINT32 CurFFSSize;
	UINT16 TestCKSum,*TempPosStart;
	UINTN TempCnt,TempEnd;
	EFI_FIRMWARE_VOLUME_HEADER* pCurFWHDR;
	UINT8 achar;
	EFI_FFS_FILE_HEADER* pCurFFSHDR;
	EFI_GUID      gEfiFirmwareFileSystemGuid = EFI_FIRMWARE_FILE_SYSTEM2_GUID;
	if(!(ROM_img=malloc(BIOS_size)))
	{
		printf("not enough mem to allocate!\n");
		return -1;
	}
	if((fp=fopen("D:\\Work\\myrelease\\SRC\\X756UQ\\1.5MSku\\X756UQ.T21","rb"))==NULL)
	{
		printf("file open error!\n");
		return -2;
	}
	else
	{
		printf("fp=%p\n",fp);
	}
	memset(ROM_img,0x00,BIOS_size);
	fseek(fp,0,0);
	Real_size = fread(ROM_img,1,BIOS_size,fp);
	ROM_Byte0=(UINT8*)ROM_img;

	for(CurPos=0;CurPos<Real_size;)
	{
		if(!memcmp(&gEfiFirmwareFileSystemGuid,CurPos+ROM_Byte0,sizeof(gEfiFirmwareFileSystemGuid)))
		{
			pCurFWHDR=(EFI_FIRMWARE_VOLUME_HEADER*)(CR(CurPos+ROM_Byte0,EFI_FIRMWARE_VOLUME_HEADER,FileSystemGuid));
			printf("--0x%08X-------------\n",(UINT8*)pCurFWHDR-ROM_Byte0);//relative address
			CurSign=0;
			memcpy(&CurSign,&pCurFWHDR->Signature,sizeof(pCurFWHDR->Signature));
			//below will have the wrong output under vs2012.must have cast.
			//printf("    sign:%s,fw_len=%x,hdrlen=%x,cksum=%x\n",
			//	&CurSign,pCurFWHDR->FvLength,pCurFWHDR->HeaderLength,pCurFWHDR->Checksum);
			printf("    sign:%s,fw_len=%x,hdrlen=%x,cksum=%x\n",
				&CurSign,(UINTN)pCurFWHDR->FvLength,(UINTN)pCurFWHDR->HeaderLength,(UINTN)pCurFWHDR->Checksum);
			TempEnd=pCurFWHDR->HeaderLength/2;
			TempPosStart=(UINT16*)pCurFWHDR;
			TestCKSum=0;
			for(TempCnt=0;TempCnt<TempEnd;TempCnt++)
			{
				TestCKSum+=*(TempPosStart+TempCnt);
			}
			if(TestCKSum)
			{
				printf("checksum error\n");
				continue;
			}
			pCurFFSHDR=(EFI_FFS_FILE_HEADER*)((UINT8*)pCurFWHDR+pCurFWHDR->HeaderLength);
			printf("    :%p guid=",pCurFFSHDR);
			printguid(&pCurFFSHDR->Name);
			CurFFSSize=0;
			memcpy(&CurFFSSize,pCurFFSHDR->Size,sizeof(pCurFFSHDR->Size));
			printf(" CurFFSSize=%x\n",CurFFSSize);
			//if(!memcmp(&pCurFFSHDR->Name,))
			//{}
			//do{
			//	
			//}while(1);
			CurPos+=16;
		}
		else
		{
			CurPos+=16;
		}
		
	}
	free(ROM_img);
	fclose(fp);
	achar=getchar();
	return 0;
}