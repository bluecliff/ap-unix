
//标准IO的效率,每次单字读写
#include <stdio.h>
int main()
{
	int  c;
	while((c=getc(stdin))!=EOF)
	{
		if(putc(c,stdout)==EOF)
		{
			printf("put erro\n");
		}
	}
	if(ferror(stdin))
	{
		printf("input error\n");
	}
	return 0;
}

