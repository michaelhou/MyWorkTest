#include"header.h"
///reference COMMON\EM\CORESRC\CRISIS\InitLib\DXE_BS\CRISIS_Update.c(184) :EFI_STATUS reloadwinflashsmmdriver
EFI_GUID SMBIOS_GUID={0XEB9D2D31,0X2D88,0X11D3,0X9A16,0X0090273FC14D};
EFI_GUID SMBIOS_GUID2={0x51a1c105, 0x7c13, 0x456a, {0xa6, 0xd8, 0xca, 0x8c, 0x27, 0xb4, 0xc0, 0x59}};
FV_GUID_NAME FV_GUID_NAMEs[]={
	{{0xcef5b9a3,0x476d,0x497f,{0x9f,0xdc,0xe9,0x81,0x43,0xe0,0x42,0x2c}},"NVRAM"},
};
UINT16 mic_htons(UINT16 ii)
{
	return (ii<<8)|(ii>>8);
}
UINT32 mic_htonl(UINT32 ii)
{
	return (mic_htons(ii)<<16)|(mic_htons(ii>>16));
}
UINT64 mic_htonll(UINT64 ii)
{
	UINT32 tmp32_1,tmp32_2;
	tmp32_1=(UINT32)ii;
	tmp32_1=mic_htonl(tmp32_1);
	memcpy(&tmp32_2,(UINT8*)&ii+4,4);
	tmp32_2=mic_htonl(tmp32_2);
	ii=tmp32_2;
	memcpy((UINT8*)&ii+4,&tmp32_1,4);
	return ii;
}
void printguid(EFI_GUID* cguid)
{
	int a=sizeof(UINT64);
	//LLX will not work.%16llX
	printf("%08X-%04X-%04X-%llX",
		(UINTN)(cguid->Data1),(UINTN)(cguid->Data2),(UINTN)(cguid->Data3),(mic_htonll(*(UINT64*)cguid->Data4)));
}
int main(int argc, char** argv)
{
	FILE *fp;
	int sz1[]={sizeof(UINT8),sizeof(UINT16),sizeof(UINT32),sizeof(UINT64),sizeof(UINTN)};
	int BIOS_size=0x800000,Real_size,CurPos;
	void * ROM_img;
	char * File_Name_STR;
	UINT8 * ROM_Byte0;
	UINT64 CurSign;
	UINT32 CurFFSSize,FFSSizeLimit=0xffffff;
	UINT16 TestCKSum,*TempPosStart;
	UINTN TempCnt,TempEnd;
	EFI_FIRMWARE_VOLUME_HEADER* pCurFWHDR;
	UINT8 achar;
	EFI_FFS_FILE_HEADER* pCurFFSHDR;
	EFI_GUID      gEfiFirmwareFileSystemGuid = EFI_FIRMWARE_FILE_SYSTEM2_GUID;
	UINT16 testvar16_1=0x1234,testvar16_2;
	UINT32 testvar32_1=0x12345678,testvar32_2;
	UINT64 testvar64_1=0x1234567890654321,testvar64_2;
	testvar16_2=mic_htons(testvar16_1);
	testvar32_2=mic_htonl(testvar32_1);
	testvar64_2=mic_htonll(testvar64_1);

	if(argc<2)
	{
		return -1;
	}
	File_Name_STR=argv[1];
	if(!(ROM_img=malloc(BIOS_size)))
	{
		printf("not enough mem to allocate!\n");
		return -1;
	}
	//if((fp=fopen("D:\\Work\\myrelease\\SRC\\X756UQ\\1.5MSku\\X756UQ.T21","rb"))==NULL)
	if((fp=fopen(File_Name_STR,"rb"))==NULL)
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
			do{
				printf("    :%p guid=",(UINT8*)pCurFFSHDR-ROM_Byte0);
				printguid(&pCurFFSHDR->Name);
				CurFFSSize=0;
				memcpy(&CurFFSSize,pCurFFSHDR->Size,sizeof(pCurFFSHDR->Size));
				CurFFSSize=(CurFFSSize+aligment_FFS)&~aligment_FFS;
				CurFFSSize&=FFSSizeLimit;
				printf(" CurFFSSize=%x\n",CurFFSSize);
				pCurFFSHDR=(EFI_FFS_FILE_HEADER*)((UINT8*)pCurFFSHDR+CurFFSSize);
			}while(CurFFSSize&&(memcmp(pCurFFSHDR->Size,&FFSSizeLimit,3)));
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