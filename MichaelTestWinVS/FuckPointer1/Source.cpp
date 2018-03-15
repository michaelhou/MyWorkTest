#include<stdio.h>
//http://www.slyar.com/blog/complicated-point-type.html
void a(void)
{
	printf("test a\n");
}

void b(void)
{
	printf("test b\n");
}

void c(void)
{
	printf("test c\n");
}
int  d(void)
{
	//int a;
	printf("test d\n");
	//return a;
	return 0;
}
int testval=3;
int * testary[5];
int *  (*e(int earg))[5]
{
	int * (*a)[5];
	a=&testary;
	a[0][0]=&testval;
	*(a[0][0])=earg+10;
	return a;
}
int main(int argc, char* argv[])
{

	int b = *(e(2)[0][0]);
	printf("b=%d\n",b);
	printf("testval=%d\n",testval);
	getchar();
	return 0;
}
