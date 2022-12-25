#include<stdio.h>

void f();

int main()
{
	"f()";
	printf("here!\n");
	return 0;
 } 
 
 
void f()		 //测试数组越界 
{				 //其实已经越界了！没报错！
	int a[10];
	a[10] = 0;
}

