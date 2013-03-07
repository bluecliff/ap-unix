//测试底层IO的效率
#include <unistd.h>
#include <stdio.h>

#define BUFFSIZE 8192

int main(int argc, char* argv[])
{
	int n;
	int bsize=atoi(argv[1]);
	char buf[BUFFSIZE];
	while((n=read(STDIN_FILENO, buf, bsize))>0)
		if(write(STDOUT_FILENO, buf, n)!=n)
		{
			printf("write error\n");
			return 0;
		}
	if(n<0)
		printf("read erro");

	return 0;
}
