//longjmp和setjmp对给类变量的影响

#include <stdio.h>
#include <setjmp.h>
static void f1(int, int, int, int,int);
static void f2(void);

static jmp_buf jmpbuffer;
static int gloval;

int main()
{
	int autoval;
	register int regval;
	volatile int volval;
	static int statval;

	gloval=1;autoval=2;regval=3;volval=4;statval=5;

	if(setjmp(jmpbuffer)!=0)
	{
		printf("after longjmp:\n");
		printf("gloval:%d,autoval:%d,regval:%d,volval:%d,statval:%d\n",gloval,autoval,regval,
					volval,statval);
		return 0;
	}

	gloval=95;autoval=96;regval=97;volval=98;statval=99;
	f1(gloval,autoval,regval,volval,statval);
	return 0;
}

static void f1(int i,int j,int k,int l,int m)
{
	printf("in f1():\n");
	printf("gloval:%d,autoval:%d,regval:%d,volval:%d,statval:%d\n",i,j,k,l,m);
	f2();
}

static void f2()
{
	longjmp(jmpbuffer,1);
}
