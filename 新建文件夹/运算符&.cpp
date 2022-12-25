#include<stdio.h>
int main()
{
	int i;
	printf("%x\n",&i);// 62fe14
	printf("%p\n",&i);//000000000062FE14
	printf("-------------------------\n");
	
	int *p = &i;
	printf("i = %d\n",i);//i = 0000000000000000
	printf("i = %p\n",i);//i = 0
	printf("*i = %d\n",i);//*i = 0
	printf("*p = %d\n",i);//*p = 0
	printf("*p = %d\n",&i);//*p = 6487572
	printf("-------------------------\n");
	printf("*p = %p\n",&i);//*p = 000000000062FE14
	printf("-------------------------\n");
	

	int a = *p;
	printf("%d\n",a);//0
	*p = a + 1;
	printf("p = %p",*p); //p = 0000000000000001
 } 
 
