#include <stdio.h>
#include <LibWrapper.h>


int main(int argc,char * argv[])
{
	int retval = 0;
	debugInfoFlag=10;
	retval = MYLIBInitialize(NULL);
	{
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
	}

	retval = MYLIBFinalize(NULL);

	return 0;
}