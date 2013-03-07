#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

char *env_init[]={"USER=unknown","PATH=/tmp",NULL};

int main()
{
	pid_t pid;
	if((pid=fork())<0)
	{
		printf("fork erro\n");
		return -1;
	}
	else if(pid==0)
	{
		if((execle("/home/lijsf/ap_unix/chapt8/echoall","myarg1","MYARG2",(char*)0,env_init))<0)
		{
			printf("exec error\n");
			return -1;
		}
	}
	if(waitpid(pid,NULL,0)<0)
	{
		printf("wait error\n");
		return -1;
	}

	if((pid=fork())<0)
	{
		printf("fork error\n");
		return -1;
	}
	else if(pid==0)
	{
		if(execlp("echoall","echoall","only 1 arg",(char*)0)<0)
		{
			printf("exec error\n");
		}
	}
	return 0;
}
