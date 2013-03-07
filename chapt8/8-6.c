//测试linux进程之间的竞争

#include <stdio.h>
#include <unistd.h>

static void charatatime(char*);

int main()
{
	pid_t pid;
	if((pid=fork())<0)
	{
		printf("fork error\n");
		return -1;
	}
	if(pid==0)
	{
		charatatime("out from child\n");
	}
	else
		charatatime("out from parent\n");
	exit(0);
}

static void charatatime(char* str)
{
	char* ptr;
	int c;
	setbuf(stdout,NULL);	//set unbufferd
	for(ptr=str;(c=*ptr++)!=0;)
	{
		putc(c,stdout);
	}
}
