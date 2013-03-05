#include<stdio.h>
#include <dirent.h>

int main(int argc, char* argv[])
{
	struct dirent *dirp;
	DIR *dp;
	printf("%s\n",argv[0]);
	if((dp=opendir(argv[1]))==NULL)
	{
		printf("erro to open");
		return 0;
	}
	if((dirp=readdir(dp))==NULL)
	{
		printf("erro to read");
		return 0;
	}
	printf("%s\n",dirp->d_name);
	return 0;
}
