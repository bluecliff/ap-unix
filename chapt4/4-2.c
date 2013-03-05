//access函数测试
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	if(argc != 2)
	  printf("usage: a.out <pathname>");
	if(access(argv[1],R_OK)<0)
	  printf("access erro for %s",argv[1]);
	else
	  printf("read access ok\n");
	if(open(argv[1], O_RDONLY)<0)
	  printf("open erro for %s",argv[1]);
	else
	  printf("open for reading ok\n");
	return 0;
}
