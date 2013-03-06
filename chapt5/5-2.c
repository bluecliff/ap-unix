//每次读写一行

#include <stdio.h>
#define MAXLINE 1024
int main()
{
	char buf[MAXLINE];
	while(fgets(buf, MAXLINE, stdin)!=NULL)
	{
		if(fputs(buf, stdout)==EOF)
			printf("stdout error\n");
	}
	return 0;
}


