//ASCII��
#include<stdio.h>
int main()
{
	char a = '1';	//	char a = 1	
	char b = 'b';	//	char b = b
	b+='B'-'b';		//	char b = 
	               	//B'B'-'b'��bת���ɴ�д��ĸB�ľ��� 
	printf("char a = %c,\nchar b = %c\n",a,b);
}
