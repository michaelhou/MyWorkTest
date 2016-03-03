#include"header.h"
///reference COMMON\EM\CORESRC\CRISIS\InitLib\DXE_BS\CRISIS_Update.c(184) :EFI_STATUS ReloadWinflashSmmDriver
int main(int argc, char** argv)
{
	FILE *fp;
	int sz1[]={sizeof(UINT8),sizeof(UINT16),sizeof(UINT32),sizeof(UINT64)};
	int BIOS_size=0x800000,Real_size,CurPos;
	void * ROM_img;
	UINT8 * ROM_Byte0;
	UINT64 CurSign;
	EFI_FIRMWARE_VOLUME_HEADER* pCurFWHDR;
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

	for(CurPos=0;CurPos<Real_size;CurPos+=1)
	{
		if(!memcmp(&gEfiFirmwareFileSystemGuid,CurPos+ROM_Byte0,sizeof(gEfiFirmwareFileSystemGuid)))
		{
			pCurFWHDR=(EFI_FIRMWARE_VOLUME_HEADER*)(CR(CurPos+ROM_Byte0,EFI_FIRMWARE_VOLUME_HEADER,FileSystemGuid));
			printf("--0x%08X-------------\n",(UINT8*)pCurFWHDR-ROM_Byte0);//relative address
			CurSign=0;
			memcpy(&CurSign,&pCurFWHDR->Signature,sizeof(pCurFWHDR->Signature));
			printf("    sign:%s\n",&CurSign);
		}
	}
	free(ROM_img);
	fclose(fp);
	return 0;
}