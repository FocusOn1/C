//ASCII码
#include<stdio.h>
int main()
{
	char a = '1';	//	char a = 1	
	char b = 'b';	//	char b = b
	b+='B'-'b';		//	char b = 
	               	//B'B'-'b'是b转换成大写字母B的距离 
	printf("char a = %c,\nchar b = %c\n",a,b);
}
