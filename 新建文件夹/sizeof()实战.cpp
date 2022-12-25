#include<stdio.h>
int main()
{
	printf("sizeof(10)=%d\n",sizeof(10));
	printf("sizeof(010)=%d\n",sizeof(010));
	printf("sizeof(0x10)=%d\n",sizeof(0x10));
	printf("sizeof(10.0)=%d\n",sizeof(10.0));
	return 0;
	//sizeof(32768)=4
	//sizeof('3')=1
	//sizeof(32768.0)=8
	//sizeof(32768.0F)=4
 } 
