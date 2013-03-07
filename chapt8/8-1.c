#include <stdio.h>
#include <unistd.h>

int glob=6;
char buf[]="a write to stdout\n";

int main()
{
	int var;
	pid_t pid;
	var = 88 ;
	if(write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
		printf("write error\n");
	printf("before fork\n");
	if((pid=fork())<0)
		printf("fork error\n");
	else if(pid==0)
	{
		printf("sun pid=%d\n",getpid());
		var++;
		glob++;
	}
	else
	{
	  sleep(2);
	  printf("parent pid=%d\n",getpid());
	}
	printf("pid=%d,glob=%d,var=%d\n", getpid(),glob,var);

	return 0;	
}
