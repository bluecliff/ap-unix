#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
/* funciton type that is called for each file name */

typedef int Myfunc (const char* , const struct stat* , int);

static Myfunc myfunc;
static int myftw(char*, Myfunc*);
static int dopath(Myfunc* );

static long nreg, ndir, nblk, nchar, nfifo, nslink, nsock, ntot;

int main(int argc, char* argv[])
{
	int ret;
	if(argc!=2)
	{
		printf("usage: ftw <starting-path>\n");
		return 0;
	}

	ret=myftw(argv[1],myfunc); //does all
	ntot=nreg+ndir+nblk+nchar+nfifo+nslink+nsock;
	if(ntot==0)
	  ntot=1;
	printf("regular files = %7ld, %5.2f %%\n",nreg,nreg*100.0/ntot);
	printf("directories files = %7ld, %5.2f %%\n",ndir,ndir*100.0/ntot);
	printf("block files = %7ld, %5.2f %%\n",nblk,nblk*100.0/ntot);
	printf("character files = %7ld, %5.2f %%\n",nchar,nchar*100.0/ntot);
	printf("fifo files = %7ld, %5.2f %%\n",nfifo,nfifo*100.0/ntot);
	printf("symbolic link files = %7ld, %5.2f %%\n",nslink,nslink*100.0/ntot);
	printf("socket files = %7ld, %5.2f %%\n",nsock,nsock*100.0/ntot);
	
	return 0;
}

/* Descend through the hierarchy, starting at "pathname", the caller's func() is called for every file */

#define FTW_F	1
#define FTW_D	2
#define FTW_DNR	3
#define FTW_NS	4

static char* fullpath;
static int myftw(char* pathname,Myfunc* func)
{
	int len;

	//fullpath=path_alloc(&len);
	
	//路径名的长度不超过256
	fullpath=(char*)malloc(1024);
	len=1024;

	strncpy(fullpath, pathname, len);
	fullpath[len-1]=0;
	return (dopath(func));
}

static int dopath(Myfunc* func)
{
	struct stat statbuf;
	struct dirent *dirp;
	DIR *dp;
	int ret;
	char *ptr;

	//不能获取stat的目录或者文件，直接鬼入这一类中
	if(lstat(fullpath, &statbuf)<0)
		return(func(fullpath, &statbuf, FTW_NS));
	//非目录文件直接处理
	if(S_ISDIR(statbuf.st_mode)==0)
		return(func(fullpath, &statbuf, FTW_F));
	
	//若是目录文件，先计数后继续递归处理目录下的文件
	if((ret = func(fullpath, &statbuf, FTW_D))!=0)
		return ret;
	
	ptr=fullpath+strlen(fullpath);
	*ptr++ = '/';
	*ptr=0;

	if((dp = opendir(fullpath))==NULL)
		return(func(fullpath,&statbuf,FTW_DNR));

	while((dirp=readdir(dp))!=NULL)
	{
		//忽略 .. 和.
		if(strcmp(dirp->d_name,".")==0 || strcmp(dirp->d_name, "..")==0 )
		{
			continue;
		}
		
		strcpy(ptr,dirp->d_name); //构造新得到文件路径
		if((ret=dopath(func))!=0)
			break;
	}
	ptr[-1]=0;
	if(closedir(dp)<0)
		printf("can't close directory %s\n",fullpath);
	return ret;
}

static int myfunc(const char* pathname, const struct stat* statptr, int type)
{
	switch(type)
	{
		case FTW_F:
			switch(statptr->st_mode & S_IFMT)
			{
				case S_IFREG:	nreg++;	break;
				case S_IFBLK:	nblk++; break;
				case S_IFCHR:	nchar++;break;
				case S_IFIFO:	nfifo++;break;
				case S_IFLNK:	nslink++;break;
				case S_IFSOCK:	nsock++;break;
				case S_IFDIR:	printf("erro,dir %s\n",pathname);
			}
			break;
		case FTW_D:
			ndir++;
			break;
		case FTW_DNR:
			printf("erro: can't read directory %s\n",pathname);
			break;
		case FTW_NS:
			printf("stat erro for %s\n",pathname);
			break;
		default:
			printf("unknown for path: %s\n",pathname);
	}
	return 0;
}
