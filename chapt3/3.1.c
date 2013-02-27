#include <unistd.h>
#include <stdio.h>

int main()
{
	if( lseek( STDIN_FILENO, 0, SEEK_CUR )==-1 )
	{
		printf( "can not seek\n" );
	}
	else
		printf( "seek ok\n" );
	exit( 0 );
	return 0;
}
