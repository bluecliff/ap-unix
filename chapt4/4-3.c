//测试系统的文件的st_blksize字段，该字段反映系统推荐的IO一次的最佳字节数
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
	struct stat statbuf;
	if(argc!=2)
		printf("usage: a.out <pathname>\n");
	if(stat(argv[1], &statbuf)<0)
	{				
		printf("erro to get status\n");
	}
	else
	{
		printf("st_blksize=%d\n", statbuf.st_blksize);
		printf("st_blocks=%d\n", statbuf.st_blocks);
	}

	return 0;
}
