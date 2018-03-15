// compile with:
// gcc -static filename -lpthread
/*
find:
1. cond_signal must after wait
2. seems pthread_mutex_init useless.
3. cond_wait & mutex usage is a must. 

result:
[    main]:before init. g_mutex1=0000000000000000,g_cond1=0000000000000000.
[    main]:mutex1 init rc=00
[    main]:cond1 init rc=00
[    main]:after init. g_mutex1=0000000000000000,g_cond1=0000000000000000.
[    main]:threadid=00007f11485b4700.
[back_pro]:before sleep.
[back_pro]:before cond_wait.
[    main]:before cond_singnal.
[    main]:after cond_signal.
[back_pro]:after cond_wait.
in back_proc.id=00007f11485b4700
[    main]: relock.
[back_pro]:now exit.
[    main]: after destroy. g_mutex1=0000000000000000,g_cond1=0000000200000001.


*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
pthread_mutex_t g_mutex1; //= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t g_cond1;
int g_count1;
void* back_proc(void * arg)
{
	pthread_t myid;
	printf("[%8.8s]:before sleep.\n",__func__);
	usleep(1000*200);
	pthread_mutex_lock(&g_mutex1);
	printf("[%8.8s]:before cond_wait.\n",__func__);
	pthread_cond_wait(&g_cond1,&g_mutex1);
	printf("[%8.8s]:after cond_wait.\n",__func__);
	myid=pthread_self();
	printf("in %s.id=%016llx\n",__func__,(unsigned long long)myid);
	usleep(1000);
	pthread_mutex_unlock(&g_mutex1);
	usleep(1);
	printf("[%8.8s]:now exit.\n",__func__);
	pthread_exit(NULL);
}


int main(int argc,char** argv)
{
	int rc=0;
	pthread_t  thread_id;
	printf("[%8.8s]:before init. g_mutex1=%016llx,g_cond1=%016llx.\n",__func__,
		(unsigned long long)g_mutex1.__align,(unsigned long long)g_cond1.__align);
	rc=pthread_mutex_init(&g_mutex1,NULL);
	printf("[%8.8s]:mutex1 init rc=%02x\n",__func__,rc);
	
	rc=pthread_cond_init(&g_cond1,NULL);
	printf("[%8.8s]:cond1 init rc=%02x\n",__func__,rc);
	
	printf("[%8.8s]:after init. g_mutex1=%016llx,g_cond1=%016llx.\n",__func__,
		(unsigned long long )g_mutex1.__align,(unsigned long long)g_cond1.__align);
	pthread_create(&thread_id,NULL,back_proc,NULL);

	printf("[%8.8s]:threadid=%016llx.\n",__func__,(unsigned long long)thread_id);


	usleep(1000*800);
	pthread_mutex_lock(&g_mutex1);

	g_count1++;
	printf("[%8.8s]:before cond_singnal.\n",__func__);
	pthread_cond_signal(&g_cond1);
	pthread_mutex_unlock(&g_mutex1);
	printf("[%8.8s]:after cond_signal.\n",__func__);
	usleep(1);

	pthread_mutex_lock(&g_mutex1);
	printf("[%8.8s]: relock.\n",__func__);
	pthread_mutex_unlock(&g_mutex1);


	pthread_join(thread_id,NULL);
	pthread_mutex_destroy(&g_mutex1);
	pthread_cond_destroy(&g_cond1);
	
	printf("[%8.8s]: after destroy. g_mutex1=%016llx,g_cond1=%016llx.\n",__func__,
			(unsigned long long )g_mutex1.__align,(unsigned long long)g_cond1.__align);

	return 0;
}
