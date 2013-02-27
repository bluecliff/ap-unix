#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#define FILE_MODE  ( S_IRUSER | S_IWUSER | S_IRGRP | S_IROTH )

char buf1[]="abcdefghij";
char buf2[]="ABCDEFGHIJ";

int main(  )
{
	int fd;
	if( ( fd=create("file.hole",FILE_MODE ) )<0 )
		printf( "create error" );
	if( write( fd,buf1,10 )!=10 )
		printf( "buf1 write error" );
	if( lseek( fd,16384,SEEK_SET )==-1 )
		printf( "lseek error" );
	if( write( fd,buf2,10 )!=10 )
		printf( "write erro" );
	exit( 0 );
	return 0;
}
